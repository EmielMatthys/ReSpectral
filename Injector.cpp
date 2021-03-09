//
// Created by emiel on 6/03/21.
//

#include "Injector.h"
#include "Logger/ILogger.h"
#include <iostream>
#include <dlfcn.h>

Injector *Injector::_instance = nullptr;

Injector::Injector()
{
    auto logger = ILogger::consoleLogger({ILogger::INFO,
            ILogger::DEBUG,
            ILogger::WARN,
            ILogger::ERROR});

    logger->logMessage("is being loaded", ILogger::INFO);

    void* library_handle = dlopen("tf/bin/client.so", RTLD_NOLOAD | RTLD_NOW);

    void* interfaceregs_symb = dlsym(library_handle, "s_pInterfaceRegs");

    if (interfaceregs_symb)
    {
        dlclose(library_handle);
        logger->logMessage("s_pInterfaceRegs found!", ILogger::DEBUG);
    }
    else
    {
        void* createinterface_symb = dlsym(library_handle, "CreateInterface");
        dlclose(library_handle);

        if (!createinterface_symb)
        {
            logger->logMessage("CreateInterface symbol not found!", ILogger::DEBUG);
        }

        auto client_factory = reinterpret_cast<CreateInterfaceFn>(createinterface_symb);
        g_clientdll = client_factory("VClient017", nullptr);
    }

    logger->logMessage("Loaded successfully", ILogger::INFO);
}


Injector *Injector::instance()
{
    if (_instance == nullptr) _instance = new Injector();
    return static_cast<Injector *>(_instance);
}
