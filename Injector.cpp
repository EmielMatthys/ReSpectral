//
// Created by emiel on 6/03/21.
//

#include "Injector.h"
#include "Module.h"
#include <iostream>
#include "spdlog/spdlog.h"

//std::shared_ptr<Injector> Injector::_instance = nullptr;

/**
 * Grabs interface pointer with given name from given module and exits the process if not found.
 * @param module
 * @param name
 * @return pointer to given interface of given module
 */
void* grabCriticalInterface(const std::shared_ptr<Module>& module, const char *name)
{
    auto interface = module->CreateInterface(name, nullptr);
    if (!interface)
    {
        spdlog::error("interface %s not found!");
        exit(1);
    }
    return interface;
}

void Injector::inject()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Loading injector!");

    auto client_module  = Module::grab("tf/bin/client.so");
    auto vstdlib_module = Module::grab("bin/libvstdlib.so");
    auto vgui2_module   = Module::grab("bin/vgui2.so");
    auto surface_module = Module::grab("bin/vguimatsurface.so");

    auto interfaceregs_symb =  client_module->getSymbol("s_pInterfaceRegs");

    if (interfaceregs_symb)
    {
        client_module->close();
        spdlog::debug("s_pInterfaceRegs found! Using this instead of CreateInterface.");
    }
    else
    {

        g_clientdll = grabCriticalInterface(client_module, "VClient017");
        g_panels    = static_cast<IPanel *>(grabCriticalInterface(vgui2_module, "VGUI_Panel009"));
        g_cvar      = grabCriticalInterface(vstdlib_module, "VEngineCvar004");
        g_surface   = static_cast<ISurface *>(grabCriticalInterface(surface_module, "VGUI_Surface030"));


//        auto engine = Module("bin/engine.so");
//        InterfaceReg* interface_list = *reinterpret_cast<InterfaceReg**>(reinterpret_cast<uintptr_t*>(engine.getHandle()) + 0xD0BE50);
//
//        for (InterfaceReg* current = engine.getInterfaces(); current; current = current->_next) {
//            spdlog::debug("%s => 0x%X\n", current->_name, current->_createFn());
//        }

    }

    spdlog::info("Loaded successfully");


}

//std::shared_ptr<Injector> Injector::instance()
//{
//    if (_instance == nullptr) _instance = std::make_shared<Injector>();
//    return _instance;
//}
