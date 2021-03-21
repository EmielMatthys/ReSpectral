//
// Created by emiel on 6/03/21.
//

#include "Injector.h"
#include "Module.h"
#include <iostream>
#include "spdlog/spdlog.h"

Injector    *Injector::_instance = nullptr;


Injector::Injector()
{
    spdlog::info("Loading injector!");
    spdlog::set_level(spdlog::level::debug);

    auto client_module = Module("tf/bin/client.so");
    auto interfaceregs_symb =  client_module.getSymbol("s_pInterfaceRegs");

    if (interfaceregs_symb)
    {
        client_module.close();
        spdlog::debug("s_pInterfaceRegs found! Using this instead of CreateInterface.");
    }
    else
    {
        auto createinterface_symb =  client_module.getSymbol("CreateInterface");
        client_module.close();

        if (!createinterface_symb)
        {
            spdlog::error("CreateInterface symbol not found!");
        }

        auto client_factory = reinterpret_cast<CreateInterfaceFn>(createinterface_symb);
        g_clientdll = client_factory("VClient017", nullptr);
    }

    spdlog::info("Loaded successfully");

}

Injector *Injector::instance()
{
    if (_instance == nullptr) _instance = new Injector();
    return static_cast<Injector *>(_instance);
}
