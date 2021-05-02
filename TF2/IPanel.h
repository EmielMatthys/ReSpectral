//
// Created by emiel on 2/05/21.
//

#ifndef RESPECTRAL_IPANEL_H
#define RESPECTRAL_IPANEL_H

#include "../getvfunc.h"

class IPanel
{
public:
    const char *GetName(unsigned int vguiPanel)
    {
        typedef const char* ( * OriginalFn )( void*, unsigned int );
        return getvfunc<OriginalFn>( this, 36 )( this, vguiPanel );
    }
};

#endif //RESPECTRAL_IPANEL_H
