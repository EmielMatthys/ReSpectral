//
// Created by emiel on 22/07/21.
//

/*
a * entity.cpp
 *
 *  Created on: Oct 6, 2016
 *      Author: nullifiedcat
 */

#include "NetVar.h"
#include "netvars.h"

NetVars netvar;

void NetVars::Init()
{
    this->iFlags               = gNetvars.get_offset("DT_BasePlayer", "m_fFlags");
    this->iHealth              = gNetvars.get_offset("DT_BasePlayer", "m_iHealth");
    this->iLifeState           = gNetvars.get_offset("DT_BasePlayer", "m_lifeState");
    this->iTeamNum             = gNetvars.get_offset("DT_BaseEntity", "m_iTeamNum");
    this->vViewOffset          = gNetvars.get_offset("DT_BasePlayer", "localdata", "m_vecViewOffset[0]");
    this->hActiveWeapon        = gNetvars.get_offset("DT_BaseCombatCharacter", "m_hActiveWeapon");
    this->hMyWeapons           = gNetvars.get_offset("DT_BaseCombatCharacter", "m_hMyWeapons");
    this->iHitboxSet           = gNetvars.get_offset("DT_BaseAnimating", "m_nHitboxSet");
    this->vVelocity            = gNetvars.get_offset("DT_BasePlayer", "localdata", "m_vecVelocity[0]");
    this->m_iAmmo              = gNetvars.get_offset("DT_BasePlayer", "localdata", "m_iAmmo");
    this->m_iPrimaryAmmoType   = gNetvars.get_offset("DT_BaseCombatWeapon", "LocalWeaponData", "m_iPrimaryAmmoType");
    this->m_iSecondaryAmmoType = gNetvars.get_offset("DT_BaseCombatWeapon", "LocalWeaponData", "m_iSecondaryAmmoType");
    this->m_iClip1             = gNetvars.get_offset("DT_BaseCombatWeapon", "LocalWeaponData", "m_iClip1");
    this->m_iClip2             = gNetvars.get_offset("DT_BaseCombatWeapon", "LocalWeaponData", "m_iClip2");
    this->m_Collision          = gNetvars.get_offset("DT_BaseEntity", "m_Collision");
    this->m_flSimulationTime   = gNetvars.get_offset("DT_BaseEntity", "m_flSimulationTime");
    this->m_flAnimTime         = gNetvars.get_offset("DT_BaseEntity", "AnimTimeMustBeFirst", "m_flAnimTime");
    this->m_flCycle            = gNetvars.get_offset("DT_BaseAnimating", "serveranimdata", "m_flCycle");
    this->m_angRotation        = gNetvars.get_offset("DT_BaseEntity", "m_angRotation");
    this->m_vecOrigin          = gNetvars.get_offset("DT_BaseEntity", "m_vecOrigin");


    this->m_flMaxspeed         = gNetvars.get_offset("DT_BasePlayer", "m_flMaxspeed");
    res_iTeam                  = gNetvars.get_offset("DT_TFPlayerResource", "baseclass", "m_iTeam");
    res_bAlive                 = gNetvars.get_offset("DT_TFPlayerResource", "baseclass", "m_bAlive");
    this->res_iMaxBuffedHealth = gNetvars.get_offset("DT_TFPlayerResource", "m_iMaxBuffedHealth");
    m_angEyeAngles             = gNetvars.get_offset("DT_TFPlayer", "tfnonlocaldata", "m_angEyeAngles[0]");
    m_angEyeAnglesLocal        = gNetvars.get_offset("DT_TFPlayer", "tflocaldata", "m_angEyeAngles[0]");
    this->bGlowEnabled         = gNetvars.get_offset("DT_TFPlayer", "m_bGlowEnabled");
    // this->iDecapitations = gNetvars.get_offset("DT_TFPlayer", "m_Shared",
    // "m_iDecapitations");  this->flReloadPriorNextFire =
    // gNetvars.get_offset("DT_TFWeaponBase", "LocalActiveTFWeaponData",
    // "m_flReloadPriorNextFire");  this->flObservedCritChance =
    // gNetvars.get_offset("DT_TFWeaponBase", "LocalActiveTFWeaponData",
    // "m_flObservedCritChance");
    this->iItemDefinitionIndex      = gNetvars.get_offset("DT_EconEntity", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex");
    this->AttributeList             = gNetvars.get_offset("DT_EconEntity", "m_AttributeManager", "m_Item",
                                                          "m_AttributeList"); // hmmm
    this->flChargeBeginTime         = gNetvars.get_offset("DT_WeaponPipebombLauncher", "PipebombLauncherLocalData", "m_flChargeBeginTime");
    this->flDetonateTime            = gNetvars.get_offset("DT_WeaponGrenadeLauncher", "m_flDetonateTime");
    this->flLastFireTime            = gNetvars.get_offset("DT_TFWeaponBase", "LocalActiveTFWeaponData", "m_flLastFireTime");
    this->flObservedCritChance      = gNetvars.get_offset("DT_TFWeaponBase", "LocalActiveTFWeaponData", "m_flObservedCritChance");
    this->bDistributed              = gNetvars.get_offset("DT_CurrencyPack", "m_bDistributed");
    this->_condition_bits           = gNetvars.get_offset("DT_TFPlayer", "m_Shared", "m_ConditionList", "_condition_bits");
    this->m_flStealthNoAttackExpire = gNetvars.get_offset("DT_TFPlayer", "m_Shared", "tfsharedlocaldata", "m_flStealthNoAttackExpire");
    this->m_iCrits                  = gNetvars.get_offset("DT_TFPlayer", "m_Shared", "tfsharedlocaldata", "m_RoundScoreData", "m_iCrits");
    this->m_nChargeResistType       = gNetvars.get_offset("DT_WeaponMedigun", "m_nChargeResistType");
    this->m_hHealingTarget          = gNetvars.get_offset("DT_WeaponMedigun", "m_hHealingTarget");
    this->m_flChargeLevel           = gNetvars.get_offset("DT_WeaponMedigun", "NonLocalTFWeaponMedigunData", "m_flChargeLevel");
    this->m_flChargeMeter           = gNetvars.get_offset("DT_TFPlayer", "m_Shared", "m_flChargeMeter");
    this->m_bFeignDeathReady        = gNetvars.get_offset("DT_TFPlayer", "m_Shared", "m_bFeignDeathReady");
    this->m_bCarryingObject         = gNetvars.get_offset("DT_TFPlayer", "m_Shared", "m_bCarryingObject");
    this->m_hCarriedObject          = gNetvars.get_offset("DT_TFPlayer", "m_Shared", "m_hCarriedObject");
    this->m_nSequence               = gNetvars.get_offset("DT_BaseAnimating", "m_nSequence");
    this->m_iTauntIndex             = gNetvars.get_offset("DT_TFPlayer", "m_Shared", "m_iTauntIndex");
    this->m_iTauntConcept           = gNetvars.get_offset("DT_TFPlayer", "m_Shared", "m_iTauntConcept");
    this->m_bViewingCYOAPDA         = gNetvars.get_offset("DT_TFPlayer", "m_bViewingCYOAPDA");

    this->res_iScore = gNetvars.get_offset("DT_TFPlayerResource", "baseclass", "m_iScore");

    this->flNextAttack          = gNetvars.get_offset("DT_BaseCombatCharacter", "bcc_localdata", "m_flNextAttack");
    this->flNextPrimaryAttack   = gNetvars.get_offset("DT_BaseCombatWeapon", "LocalActiveWeaponData", "m_flNextPrimaryAttack");
    this->flNextSecondaryAttack = gNetvars.get_offset("DT_BaseCombatWeapon", "LocalActiveWeaponData", "m_flNextSecondaryAttack");
    this->iNextThinkTick        = gNetvars.get_offset("DT_BaseCombatWeapon", "LocalActiveWeaponData", "m_nNextThinkTick");
    this->nTickBase             = gNetvars.get_offset("DT_BasePlayer", "localdata", "m_nTickBase");
    this->vecPunchAngle         = gNetvars.get_offset("DT_BasePlayer", "localdata", "m_Local", "m_vecPunchAngle");
    this->vecPunchAngleVel      = gNetvars.get_offset("DT_BasePlayer", "localdata", "m_Local", "m_vecPunchAngleVel");
    this->hThrower              = gNetvars.get_offset("DT_BaseGrenade", "m_hThrower");
    this->iObserverMode         = gNetvars.get_offset("DT_BasePlayer", "m_iObserverMode");
    this->hObserverTarget       = gNetvars.get_offset("DT_BasePlayer", "m_hObserverTarget");
    this->deadflag              = gNetvars.get_offset("DT_BasePlayer", "pl", "deadflag");
    this->iFOV                  = gNetvars.get_offset("DT_BasePlayer", "m_iFOV");
    this->iDefaultFOV           = gNetvars.get_offset("DT_BasePlayer", "m_iDefaultFOV");
    this->hOwner                = gNetvars.get_offset("DT_BaseCombatWeapon", "m_hOwner");
    this->m_rgflCoordinateFrame = 0x324;
}

void InitNetVars()
{
    netvar.Init();
}
