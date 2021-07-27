//
// Created by emiel on 27/07/21.
//
#include "Hooks.h"
#include <bsptreedata.h>
#include <coordsize.h>
#include "../TF2/C_BaseEntity.h"

struct RenderableInfo_t {
    IClientRenderable* m_pRenderable;
    void* m_pAlphaProperty;
    int m_EnumCount;
    int m_nRenderFrame;
    unsigned short m_FirstShadow;
    unsigned short m_LeafList;
    short m_Area;
    uint16_t m_Flags;   // 0x0016
    uint16_t m_Flags2; // 0x0018
    Vector m_vecBloatedAbsMins;
    Vector m_vecBloatedAbsMaxs;
    Vector m_vecAbsMins;
    Vector m_vecAbsMaxs;
    int pad;
};

hooks::ListLeavesInBox_fn hooks::original_ListLeavesInBox = nullptr;
int hooks::ListLeavesInBox(void *thisptr, const Vector &mins, const Vector &maxs, unsigned short *pList, int listMax)
{
    printf("HIER");
    // get current renderable info from stack ( https://github.com/pmrowla/hl2sdk-csgo/blob/master/game/client/clientleafsystem.cpp#L1470 )
    auto info = *(RenderableInfo_t**)( (uintptr_t) __builtin_frame_address(0) + 0x14 );
    if ( !info || !info->m_pRenderable )
        return original_ListLeavesInBox( thisptr, mins, maxs, pList, listMax );

    // check if disabling occulusion for players ( https://github.com/pmrowla/hl2sdk-csgo/blob/master/game/client/clientleafsystem.cpp#L1491 )
    auto base_entity = info->m_pRenderable->GetIClientUnknown()->GetBaseEntity();
    if ( !base_entity || !base_entity->IsPlayer() )
        return original_ListLeavesInBox( thisptr, mins, maxs, pList, listMax );

    // fix render order, force translucent group ( https://www.unknowncheats.me/forum/2429206-post15.html )
    // AddRenderablesToRenderLists: https://i.imgur.com/hcg0NB5.png ( https://github.com/pmrowla/hl2sdk-csgo/blob/master/game/client/clientleafsystem.cpp#L2473 )
    info->m_Flags &= ~0x100;
    info->m_Flags2 |= 0xC0;

    // extend world space bounds to maximum ( https://github.com/pmrowla/hl2sdk-csgo/blob/master/game/client/clientleafsystem.cpp#L707 )
    static const Vector map_min = Vector( MIN_COORD_FLOAT, MIN_COORD_FLOAT, MIN_COORD_FLOAT );
    static const Vector map_max = Vector( MAX_COORD_FLOAT, MAX_COORD_FLOAT, MAX_COORD_FLOAT );
    auto count = original_ListLeavesInBox( thisptr, map_min, map_max, pList, listMax );
    return count;
}