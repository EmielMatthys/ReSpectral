//
// Created by emiel on 3/05/21.
//

#ifndef RESPECTRAL_PANEL_H
#define RESPECTRAL_PANEL_H

#include "../TF2/IPanel.h"
#include <stdarg.h>
#include <stdio.h>

#define RED(COLORCODE)	((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)	((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)	((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)	((int) COLORCODE & 0xFF )
#define COLORCODE(r,g,b,a)((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))

static unsigned long m_Font = -2000;

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

namespace hooks
{
    #define PANEL_PAINT_TRAVERSE 42
    typedef void* (*Fn_PaintTraverse)(IPanel* thisptr, unsigned int panelIndex, bool forceRepaint, bool allowForce);
    Fn_PaintTraverse original_PaintTraverse;

    void Panel_PaintTraverse(IPanel* thisptr, unsigned int panelIndex, bool forceRepaint, bool allowForce)
    {
        original_PaintTraverse(thisptr, panelIndex, forceRepaint, allowForce);
        static unsigned int vguiMatSystemTopPanel;
//        drawString( 200, 200, 0xFFFFFFFF, "Welcome to RESPECTRAL"); //Remove this if you want.
        if (!vguiMatSystemTopPanel)
        {
            const char* szName = g_panels->GetName(panelIndex);
            if( szName[0] == 'M' && szName[3] == 'S' ) //Look for MatSystemTopPanel without using slow operations like strcmp or strstr.
            {
                spdlog::debug("inside MatSystemTopPanel!");
                vguiMatSystemTopPanel = panelIndex;
                m_Font = g_surface->CreateFont( );
                g_surface->SetFontGlyphSet( m_Font, "Verdana", 21, 500, 0, 0, 0x200 );
            }
        }

        if ( vguiMatSystemTopPanel == panelIndex ) //If we're on MatSystemTopPanel, call our drawing code.
        {
            drawString( 200, 200, 0xFFFFFFFF, "Welcome to RESPECTRAL"); //Remove this if you want.
            drawRect(0, 0, 35, 35,0xFFFFFFFF);
        }
    }
}


#endif //RESPECTRAL_PANEL_H
