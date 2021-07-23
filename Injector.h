//
// Created by emiel on 6/03/21.
//

#ifndef RESPECTRAL_INJECTOR_H
#define RESPECTRAL_INJECTOR_H

#include <memory>
#include "vgui/IPanel.h"
#include "vgui/ISurface.h"
#include "cdll_int.h"
#include "icliententitylist.h"
#include "inputsystem/iinputsystem.h"
#include "ivrenderview.h"
#include "engine/ivmodelrender.h"
#include "engine/ivmodelinfo.h"

extern IBaseClientDLL *g_clientdll;
extern void *g_cvar;
extern vgui::IPanel *g_panels;
extern vgui::ISurface *g_surface;
extern IVEngineClient *g_engineClient;
extern IClientEntityList *g_entityList;
extern IInputSystem *g_inputSystem;
extern IVRenderView *g_renderView;
extern IVModelRender *g_modelRender;
extern IVModelInfo *g_modelInfo;
extern IMaterialSystem *g_materialSystem;

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
