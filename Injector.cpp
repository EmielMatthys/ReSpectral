//
// Created by emiel on 6/03/21.
//
//
#include "Injector.h"
#include "Module.h"
#include <iostream>
#include "vtablehook.h"
#include "hooks/Panel.h"
#include "hexdump.h"
#include "hooks/ClientMode.h"
#include "hooks/shared.h"

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
        printf("interface %s not found!\n", name);
        exit(1);
    }
    return static_cast<T>(interface);
}

void Injector::inject()
{
    printf("Loading injector!\n");

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
        printf("s_pInterfaceRegs found! Using this instead of CreateInterface.\n");
    }
    else
    {

        g_clientdll = grabCriticalInterface<IBaseClientDLL*>(client_module, "VClient017");
        g_panels    = grabCriticalInterface<vgui::IPanel*>(vgui2_module, "VGUI_Panel009");
        g_cvar      = grabCriticalInterface<void*>(vstdlib_module, "VEngineCvar004");
        g_surface   = grabCriticalInterface<vgui::ISurface*>(surface_module, "VGUI_Surface030");
        g_engineClient = grabCriticalInterface<IVEngineClient*>(engine_module, "VEngineClient014");
        g_entityList   = grabCriticalInterface<IClientEntityList*>(client_module, "VClientEntityList003");
        g_inputSystem  = grabCriticalInterface<IInputSystem*>(input_module, "InputSystemVersion001");

        auto clientVMT  = *(void***)g_clientdll;
        auto clientMode = **(void***)((char*)clientVMT[10] + 1);

        // Hook panel
        INSTANTIATE_HOOK(g_panels, Panel_PaintTraverse);

        if (!clientMode)
        {
            printf("ClientMode pointer was struct_null!\n");
        } else
        {
            // Hook createmove
            INSTANTIATE_HOOK(clientMode, ClientMode_CreateMove);
        }


    }

    printf("Loaded successfully\n");


}
