//
// Created by emiel on 6/03/21.
//

#include "Injector.h"
#include "Logger/ILogger.h"
#include <iostream>
#include <dlfcn.h>

void Injector::Initialize()
{
    if (_initialized) return;
    _initialized = true;

    printf("[RESPECTRAL] is being loaded\n");

    auto logger = ILogger::consoleLogger(ILogger::Level::INFO);

    void* library_handle = dlopen("tf/bin/client.so", RTLD_NOLOAD | RTLD_NOW);
//    nullcheck(library_handle, "client.so");

    void* interfaceregs_symb = dlsym(library_handle, "s_pInterfaceRegs");

//    nullcheck(interfaceregs_symb, "s_pInterfaceRegs");

    if (interfaceregs_symb)
    {
        dlclose(library_handle);
        printf("[RESPECTRAL]: s_pInterfaceRegs found!\n");
    }
    else
    {
        void* createinterface_symb = dlsym(library_handle, "CreateInterface");
        dlclose(library_handle);

        if (createinterface_symb)
        {
            printf("[RESPECTRAL]: CreateInterface symbol not found!");
        }

        auto client_factory = reinterpret_cast<CreateInterfaceFn>(createinterface_symb);
        g_clientdll = client_factory("VClient017", nullptr);
    }
}