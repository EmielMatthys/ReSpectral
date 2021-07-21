//
// Created by emiel on 6/03/21.
//

#ifndef RESPECTRAL_INJECTOR_H
#define RESPECTRAL_INJECTOR_H

#include <memory>
//#include "TF2/IPanel.h"
//#include "TF2/ISurface.h"
//#include "TF2/EngineClient.h"
//#include "TF2/EntityList.h"
//#include "TF2/IInputSystem.h"
#include "vgui/IPanel.h"
#include "vgui/ISurface.h"
#include "cdll_int.h"
#include "icliententitylist.h"
#include "inputsystem/iinputsystem.h"

static void *g_clientdll   = nullptr;
static void *g_cvar        = nullptr;
static vgui::IPanel *g_panels    = nullptr;
static vgui::ISurface *g_surface = nullptr;
static IVEngineClient *g_engineClient = nullptr;
static IClientEntityList *g_entityList     = nullptr;
static IInputSystem *g_inputSystem  = nullptr;

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
