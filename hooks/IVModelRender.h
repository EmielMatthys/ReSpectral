//
// Created by emiel on 23/07/21.
//

#ifndef RESPECTRAL_IVMODELRENDER_H
#define RESPECTRAL_IVMODELRENDER_H

#include <Color.h>
#include "shared.h"
#include "../Injector.h"
#include "KeyValues.h"
#include "../getvfunc.h"

namespace hooks
{
    IMaterial* chamsMaterialOutline = nullptr;
    IMaterial* visibleFlattened = nullptr;

    DECLARE_HOOK(19, void, DrawModelExecute, (IVModelRender* thisptr,  const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld))
    {
        original_DrawModelExecute(thisptr, state, pInfo, pCustomBoneToWorld);
        std::string modelName = g_modelInfo->GetModelName(pInfo.pModel);

        if (modelName.find("models/player") != std::string::npos)
        {
            auto *entity = g_entityList->GetClientEntity(pInfo.entity_index);
            if (!entity || entity->IsDormant() || NET_BYTE(entity, netvar.iLifeState) != LIFE_ALIVE) return;
            auto color = Color(255,255,0);

            if(!visibleFlattened)
            {
                typedef IMaterial* (* OriginalFindMaterial) (void*, const char *pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix);
                visibleFlattened = getvfunc<OriginalFindMaterial>(g_materialSystem, 73)(g_materialSystem, "dev/glow_color", TEXTURE_GROUP_MODEL, false, nullptr);
//                visibleFlattened = g_materialSystem->FindMaterial("dev/glow_color", TEXTURE_GROUP_OTHER, false, nullptr);
            }
            if(!visibleFlattened)
            {
                return;
            }

            visibleFlattened->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
            float blend[3] = {  (float)color[0] / 255.f,
                                (float)color[1] / 255.f,
                                (float)color[2] / 255.f };
            g_renderView->SetColorModulation(blend);
            g_modelRender->ForcedMaterialOverride(visibleFlattened);
            original_DrawModelExecute(thisptr, state, pInfo, pCustomBoneToWorld);
            g_modelRender->ForcedMaterialOverride(nullptr);
        }
    }

    IMaterial* createMaterial(bool flat, bool ignorez)
    {
        static int created = 0;
        static const char tmp[] = {
            "\"%s\"\
            \n{\
			\n\t\"$basetexture\" \"vgui/white_additive\"\
			\n\t\"$envmap\" \"\"\
			\n\t\"$normalmapalphaenvmapmask\" \"\"\
			\n\t\"$envmapcontrast\" \"\"\
			\n\t\"$model\" \"1\"\
			\n\t\"$flat\" \"1\"\
			\n\t\"$nocull\" \"0\"\
			\n\t\"$selfillum\" \"1\"\
			\n\t\"$halflambert\" \"1\"\
			\n\t\"$nofog\" \"0\"\
			\n\t\"$ignorez\" \"%i\"\
			\n\t\"$znearer\" \"0\"\
			\n\t\"$wireframe\" \"\"\
			\n}\n"
        };

        const char* baseType = (flat ? "UnlitGeneric" : "VertexLitGeneric");
        char material[512];
        snprintf(material, sizeof(material), tmp, baseType, (ignorez) ? 1 : 0);

        char name[512];
        snprintf(name, sizeof(name), "#textured_cham_material%i.vmt", created);
        created++;

        auto* keyValues = (KeyValues *) malloc(sizeof(KeyValues));
    }

}

#endif //RESPECTRAL_IVMODELRENDER_H
