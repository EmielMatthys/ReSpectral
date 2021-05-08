//
// Created by emiel on 8/05/21.
//

#ifndef RESPECTRAL_ENTITYLIST_H
#define RESPECTRAL_ENTITYLIST_H

#include "CBaseEntity.h"
#include "../getvfunc.h"

class EntityList
{
public:
    CBaseEntity* GetClientEntity( int entnum )
    {
        typedef CBaseEntity* ( * OriginalFn )( void*, int );
        return getvfunc<OriginalFn>( this, 3 )( this, entnum );
    }
    CBaseEntity* GetClientEntityFromHandle( int hEnt )
    {
        typedef CBaseEntity* ( * OriginalFn )( void*, int );
        return getvfunc<OriginalFn>( this, 4 )( this, hEnt );
    }
};

#endif //RESPECTRAL_ENTITYLIST_H
