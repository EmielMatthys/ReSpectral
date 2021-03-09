//
// Created by emiel on 6/03/21.
//

#include "Injector.h"
#include "Logger/ILogger.h"
#include "Module.h"
#include <iostream>
#include <dlfcn.h>

Injector    *Injector::_instance = nullptr;
ILogger     *ILogger::logger     = nullptr;

Injector::Injector()
{
    ILogger::logger = ILogger::consoleLogger({ILogger::INFO,
            ILogger::DEBUG,
            ILogger::WARN,
            ILogger::ERROR});

    ILogger::logger->logMessage("Is being loaded", ILogger::INFO);

    auto client_module = Module("tf/bin/client.so");
    auto interfaceregs_symb =  client_module.getSymbol("s_pInterfaceRegs");

    if (interfaceregs_symb)
    {
        client_module.close();
        ILogger::logger->logMessage("s_pInterfaceRegs found!", ILogger::DEBUG);
    }
    else
    {
        auto createinterface_symb =  client_module.getSymbol("CreateInterface");
        client_module.close();

        if (!createinterface_symb)
        {
            ILogger::logger->logMessage("CreateInterface symbol not found!", ILogger::DEBUG);
        }

        auto client_factory = reinterpret_cast<CreateInterfaceFn>(createinterface_symb);
        g_clientdll = client_factory("VClient017", nullptr);
    }

    ILogger::logger->logMessage("Loaded successfully", ILogger::INFO);
}


Injector *Injector::instance()
{
    if (_instance == nullptr) _instance = new Injector();
    return static_cast<Injector *>(_instance);
}
