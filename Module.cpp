//
// Created by emiel on 9/03/21.
//

#include "Module.h"
//#include "spdlog/spdlog.h"
#include <dlfcn.h>
#include <functional>

std::map<unsigned int, std::shared_ptr<Module>> Module::_cache;

Module::Module(const char *filename) : _filename(filename)
{
    _handle = dlopen(filename, RTLD_NOLOAD | RTLD_NOW);
    if (_handle == nullptr)
    {
        char message[128];
        snprintf(message, sizeof(message), "module '%s' could not be opened!", filename);
//        spdlog::error(message);
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
//        spdlog::warn(message);
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
//        spdlog::debug("{} => {}", current->m_pName, current->m_CreateFn());
    }
}
