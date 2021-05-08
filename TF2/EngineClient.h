//
// Created by emiel on 8/05/21.
//

#ifndef RESPECTRAL_ENGINECLIENT_H
#define RESPECTRAL_ENGINECLIENT_H

class EngineClient
{
public:
    void GetScreenSize( int& width, int& height )
    {
        typedef void ( * OriginalFn )( void*, int& , int& );
        return getvfunc<OriginalFn>( this, 5 )( this, width, height );
    }
//    bool GetPlayerInfo( int ent_num, player_info_t *pinfo )
//    {
//        typedef bool ( * OriginalFn )( void*, int, player_info_t * );
//        return getvfunc<OriginalFn>(this, 8)(this, ent_num, pinfo );
//    }
    bool Con_IsVisible(  )
    {
        typedef bool ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( this, 11 )( this );
    }
    int GetLocalPlayer(  )
    {
        typedef int ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( this, 12 )( this );
    }
    float Time(  )
    {
        typedef float ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( this, 14 )( this );
    }
//    void GetViewAngles( Vector& va )
//    {
//        typedef void ( * OriginalFn )( void*, Vector& va );
//        return getvfunc<OriginalFn>( this, 19 )( this, va );
//    }
//    void SetViewAngles( Vector& va )
//    {
//        typedef void ( * OriginalFn )( void*, Vector& va );
//        return getvfunc<OriginalFn>( this, 20 )( this, va );
//    }
    int GetMaxClients(  )
    {
        typedef int ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( this, 21 )( this );
    }
    bool IsInGame(  )
    {
        typedef bool ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( this, 26 )( this );
    }
    bool IsConnected(  )
    {
        typedef bool ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( this, 27 )( this );
    }
    bool IsDrawingLoadingImage(  )
    {
        typedef bool ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( this, 28 )( this );
    }
//    const matrix3x4& WorldToScreenMatrix( void )
//    {
//        typedef const matrix3x4& ( * OriginalFn )( void* );
//        return getvfunc<OriginalFn>(this, 36)(this);
//    }
    bool IsTakingScreenshot(  )
    {
        typedef bool ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( this, 85 )( this );
    }
    unsigned int* GetNetChannelInfo(  )
    {
        typedef unsigned int* ( * OriginalFn )( void* );
        return getvfunc<OriginalFn>( this, 72 )( this );
    }
    void ClientCmd_Unrestricted( const char* chCommandString )
    {
        typedef void ( * OriginalFn )( void*, const char * );
        return getvfunc<OriginalFn>( this, 106 )( this, chCommandString );
    }

};

#endif //RESPECTRAL_ENGINECLIENT_H
