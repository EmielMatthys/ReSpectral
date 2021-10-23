//
// Created by emiel on 25/07/21.
//

#include <string>
#include <icliententity.h>
#include "../netvars.h"
#include <KeyValues.h>
#include "../getvfunc.h"
#include "../DrawTools.h"
#include "Hooks.h"

IMaterial* flattened = nullptr;
IMaterial* createMaterial(const char *, bool, bool, bool);

hooks::DrawModelExecute_fn hooks::original_DrawModelExecute = nullptr;

void hooks::DrawModelExecute(IVModelRender *thisptr, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
    original_DrawModelExecute(thisptr, state, pInfo, pCustomBoneToWorld);
    std::string modelName = g_modelInfo->GetModelName(pInfo.pModel);

    if (draw::enabled && modelName.find("models/player") != std::string::npos)
    {
        auto *entity = g_entityList->GetClientEntity(pInfo.entity_index);
        auto *local = g_entityList->GetClientEntity(g_engineClient->GetLocalPlayer());
        if (!entity || entity->IsDormant() || NET_BYTE(entity, netvar.iLifeState) != LIFE_ALIVE) return;
        int teamnum = NET_INT(entity, netvar.iTeamNum);
        if (NET_INT(local, netvar.iTeamNum) == teamnum || teamnum > 3 || teamnum < 2) return;

        auto colorInvisible = Color(255, 255, 0);
        auto colorVisible = teamnum == 3 ?  Color(0, 0, 255) : Color(255, 0, 0);

        if(!flattened)
        {
            typedef IMaterial* (* OriginalFindMaterial) (void*, const char *pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix);
            flattened = getvfunc<OriginalFindMaterial>(g_materialSystem, 73)(g_materialSystem, "dev/glow_color", TEXTURE_GROUP_MODEL, false, nullptr);

//            flattened = createMaterial("respectral", false, true, false);
        }

        flattened->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
        float blendd[3] = {(float)colorInvisible[0] / 255.f,
                           (float)colorInvisible[1] / 255.f,
                           (float)colorInvisible[2] / 255.f };

        g_renderView->SetColorModulation(blendd);
        g_modelRender->ForcedMaterialOverride(flattened);
        original_DrawModelExecute(thisptr, state, pInfo, pCustomBoneToWorld);

        flattened->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
        float blend[3] = {(float)colorVisible[0] / 255.f,
                          (float)colorVisible[1] / 255.f,
                          (float)colorVisible[2] / 255.f };

        g_renderView->SetColorModulation(blend);
        g_modelRender->ForcedMaterialOverride(flattened);
        original_DrawModelExecute(thisptr, state, pInfo, pCustomBoneToWorld);

        g_modelRender->ForcedMaterialOverride(nullptr);
    }
}

class key_value
{
public:
    int m_iKeyName;
    char *m_sValue;
    wchar_t *m_wsValue;

    union
    {
        int m_iValue;
        float m_flValue;
        void *m_pValue;
        unsigned char m_Color[4];
    };

    char	m_iDataType;
    char	m_bHasEscapeSequences;
    char	m_bEvaluateConditionals;
    char	unused[1];

    key_value *m_pPeer;
    key_value *m_pSub;
    key_value *m_pChain;
};

//key_value* KVInitialize(key_value* key_valuez, char* name) {
//    using originalfn = key_value *(__thiscall*)(key_value*, char*);
//
//    uint64_t signature = utilities::find_signature("engine.dll", "FF 15 ? ? ? ? 83 C4 08 89 06 8B C6");
//    signature -= 0x42; static auto initialize = (originalfn)signature;
//
//    return initialize(key_valuez, name);
//}
//
//bool KVLoadFromBuffer(key_value* key_valuez, char const* resource_name, const char* buffer) {
//    using originalfn = int(__thiscall*)(key_value*, char const*, const char*, void*, const char*);
//    uint64_t signature = utilities::find_signature("engine.dll", "55 8B EC 83 EC 38 53 8B 5D 0C");
//
//    static originalfn load_from_the_buffer = (originalfn)signature;
//    return load_from_the_buffer(key_valuez, resource_name, buffer, null, null);
//}

IMaterial* createMaterial(const char *materialName, bool flat, bool ignorez, bool wireframe)
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
			\n\t\"$wireframe\" \"%i\"\
			\n}\n"
    };

    const char* baseType = (flat ? "UnlitGeneric" : "VertexLitGeneric");
    char material[512];
    snprintf(material, sizeof(material), tmp, baseType, (ignorez) ? 1 : 0, wireframe ? 1 : 0);

    char name[512];
    snprintf(name, sizeof(name), "#textured_cham_material%i.vmt", created);
    created++;

//    auto *keyValues = (key_value*) malloc(sizeof(key_value));
//    keyValues->LoadFromBuffer(materialName, material);
//
//    typedef IMaterial *(__thiscall * OriginalCreateMaterial) (void* , const char *, KeyValues *);
//    auto *newMaterial = getvfunc<OriginalCreateMaterial> (g_materialSystem, 72) (g_materialSystem, materialName, keyValues);
//    newMaterial->IncrementReferenceCount();
//
//    return newMaterial;
}