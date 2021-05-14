//
// Created by emiel on 8/05/21.
//

#ifndef RESPECTRAL_DRAWTOOLS_H
#define RESPECTRAL_DRAWTOOLS_H

#include "Injector.h"
#include <stdarg.h>
#include <stdio.h>

#define RED(COLORCODE)	((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)	((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)	((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)	((int) COLORCODE & 0xFF )
#define COLORCODE(r,g,b,a)((unsigned int)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))

namespace draw
{
    static unsigned long m_Font = -2000;
    static bool enabled = false;

    int screenWidth;
    int screenHeight;

    void init()
    {
        m_Font = g_surface->CreateFont( );
        g_engineClient->GetScreenSize(screenWidth, screenHeight);
        g_surface->SetFontGlyphSet( m_Font, "Verdana", 16, 500, 0, 0, 0x200 );
    }

    void drawString( int x, int y, unsigned int dwColor, const wchar_t *pszText)
    {
        if( !pszText )
            return;

        g_surface->DrawSetTextPos( x, y );
        g_surface->DrawSetTextFont( m_Font );
        g_surface->DrawSetTextColor( RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor) );
        g_surface->DrawPrintText( pszText, wcslen( pszText ) );
    }

    void drawString( int x, int y, unsigned int dwColor, const char *pszText, ... )
    {
        if( pszText == NULL )
            return;

        va_list va_alist;
        char szBuffer[1024] = { '\0' };
        wchar_t szString[1024] = { '\0' };

        va_start( va_alist, pszText );
        vsprintf( szBuffer, pszText, va_alist );
        va_end( va_alist );

        swprintf( szString, 1024, L"%s", szBuffer );

        g_surface->DrawSetTextPos( x, y );
        g_surface->DrawSetTextFont( m_Font );
        g_surface->DrawSetTextColor( RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor) );
        g_surface->DrawPrintText( szString, wcslen( szString ) );
    }

    void OutlineRect( int x, int y, int w, int h, unsigned int dwColor )
    {
        g_surface->DrawSetColor( RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor) );
        g_surface->DrawOutlinedRect( x, y, x + w, y + h );
    }

    void DrawRect( int x, int y, int w, int h, unsigned int dwColor )
    {
        g_surface->DrawSetColor( RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor) );
        g_surface->DrawFilledRect( x, y, x + w, y + h );
    }

    bool WorldToScreen( Vector &vOrigin, Vector &vScreen )
    {
        const matrix3x4& worldToScreen = g_engineClient->WorldToScreenMatrix(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix

        float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.
        vScreen.z = 0; //Screen doesn't have a 3rd dimension.

        if( w > 0.001 ) //If the object is within view.
        {
            float fl1DBw = 1 / w; //Divide 1 by the angle.
            vScreen.x = (screenWidth / 2) + ( 0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * fl1DBw) * screenWidth + 0.5); //Get the X dimension and push it in to the Vector.
            vScreen.y = (screenHeight / 2) - ( 0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * fl1DBw) * screenHeight + 0.5); //Get the Y dimension and push it in to the Vector.
            return true;
        }

        return false;
    }

    void GetTextSize(int &wide, int &tall, const char *pszText, ...)
    {
        if( pszText == NULL )
            return;

        va_list va_alist;
        char szBuffer[1024] = { '\0' };
        wchar_t szString[1024] = { '\0' };

        va_start( va_alist, pszText );
        vsprintf( szBuffer, pszText, va_alist );
        va_end( va_alist );

        swprintf( szString, 1024, L"%s", szBuffer );
        g_surface->GetTextSize(m_Font, szString, wide, tall);
    }

    void DrawBox( Vector vOrigin, int r, int g, int b, int alpha, int box_width, int radius )
    {
        Vector vScreen;

        if( !WorldToScreen( vOrigin, vScreen ) )
            return;

        int radius2 = radius<<1;

        OutlineRect( vScreen.x - radius + box_width, vScreen.y - radius + box_width, radius2 - box_width, radius2 - box_width, 0x000000FF );
        OutlineRect( vScreen.x - radius - 1, vScreen.y - radius - 1, radius2 + ( box_width + 2 ), radius2 + ( box_width + 2 ), 0x000000FF );
        DrawRect( vScreen.x - radius + box_width, vScreen.y - radius, radius2 - box_width, box_width,COLORCODE( r, g, b, alpha ));
        DrawRect( vScreen.x - radius, vScreen.y + radius, radius2, box_width,COLORCODE( r, g, b, alpha ));
        DrawRect( vScreen.x - radius, vScreen.y - radius, box_width, radius2,COLORCODE( r, g, b, alpha ));
        DrawRect( vScreen.x + radius, vScreen.y - radius, box_width, radius2 + box_width, COLORCODE( r, g, b, alpha ) );
    }
}

#endif //RESPECTRAL_DRAWTOOLS_H
