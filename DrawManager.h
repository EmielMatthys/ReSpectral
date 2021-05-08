//
// Created by emiel on 8/05/21.
//

#ifndef RESPECTRAL_DRAWMANAGER_H
#define RESPECTRAL_DRAWMANAGER_H

#include "Injector.h"
#include <stdarg.h>
#include <stdio.h>

#define RED(COLORCODE)	((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)	((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)	((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)	((int) COLORCODE & 0xFF )
#define COLORCODE(r,g,b,a)((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))

namespace draw
{
    static unsigned long m_Font = -2000;

    void init()
    {
        m_Font = g_surface->CreateFont( );
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

    void drawRect( int x, int y, int w, int h, unsigned int dwColor )
    {
        g_surface->DrawSetColor( RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor) );
        g_surface->DrawFilledRect( x, y, x + w, y + h );
    }
}

#endif //RESPECTRAL_DRAWMANAGER_H
