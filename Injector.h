//
// Created by emiel on 6/03/21.
//

#ifndef RESPECTRAL_INJECTOR_H
#define RESPECTRAL_INJECTOR_H

#include <memory>

static void *g_clientdll = nullptr;
static void *g_cvar      = nullptr;
static void *g_panels    = nullptr;

class Injector {
public:
//    static std::shared_ptr<Injector> instance();
    static void inject();
//protected:
//    Injector();

private:
//    static std::shared_ptr<Injector> _instance;
};


#endif //RESPECTRAL_INJECTOR_H
