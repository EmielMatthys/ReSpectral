//
// Created by emiel on 9/03/21.
//

#include "Module.h"
#include "spdlog/spdlog.h"
#include <dlfcn.h>

Module::Module(const char *filename) : _filename(filename)
{
    _handle = dlopen(filename, RTLD_NOLOAD | RTLD_NOW);
    if (_handle == nullptr)
    {
        char message[128];
        snprintf(message, sizeof(message), "module '%s' could not be opened!", filename);
        spdlog::error(message);
    }
}

void *Module::getSymbol(const char *symbolName)
{
    auto result = dlsym(_handle, symbolName);
    if (result == nullptr)
    {
        char message[128];
        snprintf(message, sizeof(message), "symbol '%s' of module '%s' could not be opened!", symbolName, _filename);
        spdlog::warn(message);
    }
    return result;
}

void Module::close()
{
    dlclose(_handle);
}
