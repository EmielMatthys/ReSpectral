//
// Created by emiel on 27/07/21.
//

#ifndef RESPECTRAL_HOOKS_H
#define RESPECTRAL_HOOKS_H

#include "../TF2/CUserCmd.h"
#include <mathlib/vector.h>
#include <iclientrenderable.h>
#include <vgui/IPanel.h>

#define DECLARE_HOOK(index,ret,name,header) static const int name ## _index = index;\
                                            typedef ret (* name ## _fn) header ; \
                                            extern name ## _fn original_ ## name ;\
                                            ret name header

#define INSTANTIATE_HOOK(instance, funcname) \
hooks::original_ ## funcname = \
        (hooks::funcname ## _fn) vtablehook_hook(instance, (void*) hooks::funcname, hooks::funcname ## _index)

namespace hooks
{
    DECLARE_HOOK(21, bool, ClientMode_CreateMove,(void* thisptr,float flInputSampleTime, CUserCmd* cmd));
    DECLARE_HOOK(5, int, ListLeavesInBox, (void* thisptr, const Vector& mins, const Vector& maxs, unsigned short *pList, int listMax));
    DECLARE_HOOK(42, void, Panel_PaintTraverse, (vgui::IPanel* thisptr, unsigned int panelIndex, bool forceRepaint, bool allowForce));
    DECLARE_HOOK(19, void, DrawModelExecute, (IVModelRender* thisptr,  const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld));
}

#endif //RESPECTRAL_HOOKS_H
