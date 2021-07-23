//
// Created by emiel on 23/07/21.
//

#ifndef RESPECTRAL_IVMODELRENDER_H
#define RESPECTRAL_IVMODELRENDER_H

#include "shared.h"
#include "../Injector.h"

namespace hooks
{
    DECLARE_HOOK(19, void, DrawModelExecute, (IVModelRender* thisptr,  const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld))
    {
        original_DrawModelExecute(thisptr, state, pInfo, pCustomBoneToWorld);
    }
}

#endif //RESPECTRAL_IVMODELRENDER_H
