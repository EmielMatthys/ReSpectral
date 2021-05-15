//
// Created by emiel on 15/05/21.
//

#ifndef RESPECTRAL_CLIENTMODE_H
#define RESPECTRAL_CLIENTMODE_H

#include "../TF2/CUserCmd.h"

namespace hooks
{
    #define CLIENTMODE_CREATEMOVE 21
    typedef bool (*Fn_CreateMove)(void* thisptr, float flInputSampleTime, CUserCmd* cmd);
    Fn_CreateMove original_ClientModeCreateMove;

    bool ClientMode_CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd)
    {
        return original_ClientModeCreateMove(thisptr, flInputSampleTime, cmd);
    }
}


#endif //RESPECTRAL_CLIENTMODE_H
