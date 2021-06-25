//
// Created by emiel on 6/03/21.
//
//
#include "Injector.h"
#include "Module.h"
#include <iostream>
#include "spdlog/spdlog.h"
#include "vtablehook.h"
#include "hooks/Panel.h"
#include "hexdump.h"
#include "hooks/ClientMode.h"
#include "hooks/shared.h"

//std::shared_ptr<Injector> Injector::_instance = nullptr;

/**
 * Grabs interface pointer with given name from given module and exits the process if not found.
 * @param module
 * @param name
 * @return pointer to given interface of given module
 */

template <typename T>
T grabCriticalInterface(const std::shared_ptr<Module>& module, const char *name)
{
    auto interface = module->CreateInterface(name, nullptr);
    if (!interface)
    {
        spdlog::error("interface %s not found!");
        exit(1);
    }
    return static_cast<T>(interface);
}

void Injector::inject()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Loading injector!");

    auto client_module  = Module::grab("tf/bin/client.so");
    auto vstdlib_module = Module::grab("bin/libvstdlib.so");
    auto vgui2_module   = Module::grab("bin/vgui2.so");
    auto surface_module = Module::grab("bin/vguimatsurface.so");
    auto engine_module  = Module::grab("bin/engine.so");
    auto input_module   = Module::grab("bin/inputsystem.so");


    auto interfaceregs_symb =  client_module->getSymbol("s_pInterfaceRegs");

    if (interfaceregs_symb)
    {
        client_module->close();
        spdlog::debug("s_pInterfaceRegs found! Using this instead of CreateInterface.");
    }
    else
    {

        g_clientdll = grabCriticalInterface<void*>(client_module, "VClient017");
        g_panels    = grabCriticalInterface<IPanel*>(vgui2_module, "VGUI_Panel009");
        g_cvar      = grabCriticalInterface<void*>(vstdlib_module, "VEngineCvar004");
        g_surface   = grabCriticalInterface<ISurface*>(surface_module, "VGUI_Surface030");
        g_engineClient = grabCriticalInterface<EngineClient*>(engine_module, "VEngineClient014");
        g_entityList   = grabCriticalInterface<EntityList*>(client_module, "VClientEntityList003");
        g_inputSystem  = grabCriticalInterface<IInputSystem*>(input_module, "InputSystemVersion001");

        auto clientVMT  = *(void***)g_clientdll;
        auto clientMode = **(void***)((char*)clientVMT[10] + 1);

        // Hook panel
        INSTANTIATE_HOOK(g_panels, Panel_PaintTraverse);

        if (!clientMode)
        {
            spdlog::error("ClientMode pointer was null!");
        } else
        {
            // Hook createmove
            INSTANTIATE_HOOK(clientMode, ClientMode_CreateMove);
        }


    }

    spdlog::info("Loaded successfully");


}

//std::shared_ptr<Injector> Injector::instance()
//{
//    if (_instance == nullptr) _instance = std::make_shared<Injector>();
//    return _instance;
//}
