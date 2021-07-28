//
// Created by emiel on 27/07/21.
//
#include "Hooks.h"
#include "../netvars.h"
#include "../Injector.h"
#include "../TF2/C_BaseEntity.h"
#include <basehandle.h>
#include <string>

hooks::ClientMode_CreateMove_fn hooks::original_ClientMode_CreateMove = nullptr;
bool hooks::ClientMode_CreateMove(void *thisptr, float flInputSampleTime, CUserCmd *cmd)
{
    bool originalRet = original_ClientMode_CreateMove(thisptr, flInputSampleTime, cmd);

    auto* local = (C_BaseEntity*) g_entityList->GetClientEntity(g_engineClient->GetLocalPlayer());
    auto myTeam = NET_INT(local, netvar.iTeamNum);

    auto* activeWeaponEnt = (C_BaseEntity*) g_entityList->GetClientEntityFromHandle(NET_VAR(local, netvar.hActiveWeapon, CBaseHandle));
    if (!activeWeaponEnt) return originalRet;

    auto* name = activeWeaponEnt->GetClientClass()->chName;
    if (!name) return originalRet;
//    printf("\033[0;32m[CreateMove] %s\n\033[0m", name); //CTFKnife

    std::string sname(name);
    if (sname.find("CTFKnife") != std::string::npos)
    {
        bool ready = NET_VAR(activeWeaponEnt, netvar.m_bReadyToBackstab, bool);
        if (ready)
        {
            cmd->buttons |= IN_ATTACK;
        }
    }

//    for (int i = 1; i < 24; i++)
//    {
//        auto* entity = (C_BaseEntity*) g_entityList->GetClientEntity(i);
//        if (!entity || entity->IsDormant()) continue;
//        if (NET_BYTE(entity, netvar.iLifeState) != LIFE_ALIVE) continue;
//        if (NET_INT(entity, netvar.iTeamNum) == myTeam) continue;
//
//        Vector enemyPosition = entity->GetAbsOrigin();
//
//    }

    return originalRet;
}
