//
// Created by emiel on 15/05/21.
//

#ifndef RESPECTRAL_CLIENTMODE_H
#define RESPECTRAL_CLIENTMODE_H

#include "shared.h"
#include "../TF2/CUserCmd.h"
#include "../NetVar.h"


namespace hooks
{

    DECLARE_HOOK(21, bool, ClientMode_CreateMove,(void* thisptr,float flInputSampleTime, CUserCmd* cmd))
    {
        return original_ClientMode_CreateMove(thisptr, flInputSampleTime, cmd);
    }
}


#endif //RESPECTRAL_CLIENTMODE_H
