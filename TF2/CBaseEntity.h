//
// Created by emiel on 8/05/21.
//

#ifndef RESPECTRAL_CBASEENTITY_H
#define RESPECTRAL_CBASEENTITY_H

#include "Vector.h"

class ClientClass;

class CBaseEntity
{
public:
    Vector& GetAbsOrigin( )
    {
        typedef Vector& ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>(this, 11)(this);
    }
    Vector& GetAbsAngles( )
    {
        typedef Vector& ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>(this, 12)(this);
    }
    void GetWorldSpaceCenter( Vector& vWorldSpaceCenter)
    {
        Vector vMin, vMax;
        this->GetRenderBounds( vMin, vMax );
        vWorldSpaceCenter = this->GetAbsOrigin();
        vWorldSpaceCenter.z += (vMin.z + vMax.z) / 2;
    }
    unsigned int* GetModel( )
    {
        void* pRenderable = (void*)(this + 0x4);
        typedef unsigned int* ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( pRenderable, 9 )( pRenderable );
    }
    bool SetupBones( matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime )
    {
        void* pRenderable = (void*)(this + 0x4);
        typedef bool ( * OriginalFn )( void*, matrix3x4*, int, int, float );
        return getvfunc<OriginalFn>( pRenderable, 16 )( pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime );
    }
    ClientClass* GetClientClass( )
    {
        void* pNetworkable = (void*)(this + 0x8);
        typedef ClientClass* ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( pNetworkable, 2 )( pNetworkable );
    }
    bool IsDormant( )
    {
        void* pNetworkable = (void*)(this + 0x8);
        typedef bool ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( pNetworkable, 8 )( pNetworkable );
    }
    int GetIndex( )
    {
        void* pNetworkable = (void*)(this + 0x8);
        typedef int ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( pNetworkable, 9 )( pNetworkable );
    }
    void GetRenderBounds( Vector& mins, Vector& maxs )
    {
        void* pRenderable = (void*)(this + 0x4);
        typedef void ( * OriginalFn )( void*, Vector& , Vector& );
        getvfunc<OriginalFn>( pRenderable, 20 )( pRenderable, mins, maxs );
    }
};

#endif //RESPECTRAL_CBASEENTITY_H
