//
// Created by emiel on 25/07/21.
//

#include <mathlib/vector.h>
#include <mathlib/mathlib.h>
#include "../getvfunc.h"
#include "../ClientClass.h"

#ifndef RESPECTRAL_C_BASEENTITY_H
#define RESPECTRAL_C_BASEENTITY_H

class C_BaseEntity
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
    bool IsPlayer()
    {
        typedef bool ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>(this, 198)(this);
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
    bool SetupBones( matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime )
    {
        void* pRenderable = (void*)(this + 0x4);
        typedef bool ( * OriginalFn )( void*, matrix3x4_t*, int, int, float );
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


#endif //RESPECTRAL_C_BASEENTITY_H
