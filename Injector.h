//
// Created by emiel on 6/03/21.
//

#ifndef RESPECTRAL_INJECTOR_H
#define RESPECTRAL_INJECTOR_H

#include <memory>
#include "TF2/IPanel.h"
#include "TF2/ISurface.h"
#include "TF2/EngineClient.h"
#include "TF2/EntityList.h"

static void *g_clientdll   = nullptr;
static void *g_cvar        = nullptr;
static IPanel *g_panels    = nullptr;
static ISurface *g_surface = nullptr;
static EngineClient *g_engineClient = nullptr;
static EntityList *g_entityList     = nullptr;

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
