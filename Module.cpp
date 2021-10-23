//
// Created by emiel on 9/03/21.
//

#include "Module.h"
#include <dlfcn.h>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

std::map<unsigned int, std::shared_ptr<Module>> Module::_cache;

Module::Module(const char *filename) : _filename(filename)
{
    _handle = dlopen(filename, RTLD_NOLOAD | RTLD_NOW);
    if (_handle == nullptr)
    {
        char message[128];
        snprintf(message, sizeof(message), "module '%s' could not be opened!", filename);
        printf("%s\n", message);
    }
    CreateInterface = reinterpret_cast<CreateInterfaceFn>(getSymbol("CreateInterface"));
}

void *Module::getSymbol(const char *symbolName) const
{
    auto result = dlsym(_handle, symbolName);
    if (result == nullptr)
    {
        char message[128];
        snprintf(message, sizeof(message), "symbol '%s' of module '%s' could not be found!", symbolName, _filename);
        printf("%s\n", message);
    }
    return result;
}

void Module::close()
{
    dlclose(_handle);
}

InterfaceReg *Module::getInterfaces() const
{
    auto interface_symb = getSymbol("s_pInterfaceRegs");
    if (interface_symb)
    {
        return *reinterpret_cast<InterfaceReg**>(interface_symb);
    } else
    {
        auto createInterface = getSymbol("CreateInterface");
        auto jmp_adr = uintptr_t(createInterface) + 4;
        auto offset = *reinterpret_cast<int32_t *>(jmp_adr + 1);

        auto createInterfaceInternal = (jmp_adr + 5) + offset;

        return **reinterpret_cast<InterfaceReg***>(createInterfaceInternal + 11);
    }
}

std::shared_ptr<Module> Module::grab(const char* filename)
{
    auto hash = std::hash<const char*>{}(filename);

    if (_cache.count(hash))
    {
        return _cache[hash];
    }

    std::shared_ptr<Module> ret(new Module(filename));
    _cache[hash] = ret;

    return ret;
}

void Module::walkInterfaces() const
{
    for (InterfaceReg* current = getInterfaces(); current; current = current->m_pNext) {
        printf("\033[0;36m%s => 0x%p\n\033[0m", current->m_pName, (void *) current->m_CreateFn());
    }
}

uint64_t Module::findSignature(const char *sig)
{
    auto fp = fopen("/proc/self/maps", "r");
    if (!fp) return -1;

    unsigned int base = 0, end = 0;
    char *line;
    size_t line_size = 0;
    while (getline(&line, &line_size, fp) > 0)
    {
        std::string sline(line);
        if (sline.find(this->_filename) != std::string::npos && sline.find("r-xp") != std::string::npos)
        {
            printf("%s", line);
            // use find for '-' and space
            std::string base_addr(sline.substr(0,sline.find('-')));
            std::string end_addr(sline.substr(0, sline.find(' ')));
            printf("base: %s, end: %s", base_addr.c_str(), end_addr.c_str());

            sscanf(base_addr.c_str(), "%x", &base);
            sscanf(end_addr.c_str(), "%x", &end);

            break;
        }
    }

    free(line);
    if (base == 0) return -1;
//                                            |firstMatch
//                                            |current
//Memory:    +----------------------------------------------------------------------------+
//pat:                                        +----------+
//                                            012

    const char* pat = sig;
    unsigned int firstMatch = 0;
    for (unsigned int current = base; current < end; current++)
    {
        if (!*pat) return firstMatch; // We matched the whole pattern
        if (pat[0] == '\?' || *(byte*) current == (byte) pat[0]) // Wildcard or match?
        {
            if (firstMatch == 0) firstMatch = current; // We just started matching
            if (!pat[2]) return firstMatch;
            if (*(uint16_t*) pat == '\?\?' || *(byte*) pat != '\?') pat += 3;
            else pat += 2;
        } else
        {
            pat = sig;
            firstMatch = 0;
        }
    }

    return -1;
}
