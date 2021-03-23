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
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Loading injector!");

    auto client_module  = Module::grab("tf/bin/client.so");
    auto vstdlib_module = Module::grab("bin/libvstdlib.so");

    auto interfaceregs_symb =  client_module->getSymbol("s_pInterfaceRegs");

    if (interfaceregs_symb)
    {
        client_module->close();
        spdlog::debug("s_pInterfaceRegs found! Using this instead of CreateInterface.");
    }
    else
    {


        g_clientdll = client_module->CreateInterface("VClient017", nullptr);
        if (!g_clientdll)
        {
            spdlog::error("g_clientdll not found!");
            exit(1);
        }

//        auto engine = Module("bin/engine.so");
//        InterfaceReg* interface_list = *reinterpret_cast<InterfaceReg**>(reinterpret_cast<uintptr_t*>(engine.getHandle()) + 0xD0BE50);
//
//        for (InterfaceReg* current = engine.getInterfaces(); current; current = current->_next) {
//            spdlog::debug("%s => 0x%X\n", current->_name, current->_createFn());
//        }

        g_cvar = vstdlib_module->CreateInterface("VEnvineCvar004", nullptr);

        if (!g_cvar)
        {
            spdlog::error("g_pCvar not found!");
            exit(1);
        }
    }

    spdlog::info("Loaded successfully");


}

Injector *Injector::instance()
{
    if (_instance == nullptr) _instance = new Injector();
    return static_cast<Injector *>(_instance);
}
