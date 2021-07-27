//
// Created by emiel on 27/07/21.
//
#include "Hooks.h"

hooks::ClientMode_CreateMove_fn hooks::original_ClientMode_CreateMove = nullptr;
bool hooks::ClientMode_CreateMove(void *thisptr, float flInputSampleTime, CUserCmd *cmd)
{
    return original_ClientMode_CreateMove(thisptr, flInputSampleTime, cmd);
}
