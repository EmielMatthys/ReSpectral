//
// Created by emiel on 2/05/21.
//

#ifndef RESPECTRAL_ISURFACE_H
#define RESPECTRAL_ISURFACE_H

#include "../getvfunc.h"

class ISurface
{
public:
    void DrawSetColor(int r, int g, int b, int a)
    {
        typedef void(* OriginalFn)(void*, int, int, int, int);
        getvfunc<OriginalFn>(this, 11)(this, r, g, b, a);
    }
    void DrawFilledRect(int x0, int y0, int x1, int y1)
    {
        typedef void(* OriginalFn)(void*, int, int, int, int);
        getvfunc<OriginalFn>(this, 12)(this, x0, y0, x1, y1);
    }
    void DrawOutlinedRect(int x0, int y0, int x1, int y1)
    {
        typedef void(* OriginalFn)(void*, int, int, int, int);
        getvfunc<OriginalFn>(this, 14)(this, x0, y0, x1, y1);
    }
    void DrawSetTextFont(unsigned long font)
    {
        typedef void(* OriginalFn)(void*, unsigned long);
        getvfunc<OriginalFn>(this, 17)(this, font);
    }
    void DrawSetTextColor(int r, int g, int b, int a)
    {
        typedef void(* OriginalFn)(void*, int, int, int, int);
        getvfunc<OriginalFn>(this, 18)(this, r, g, b, a);
    }
    void DrawSetTextPos(int x, int y)
    {
        typedef void(* OriginalFn)(void*, int, int);
        getvfunc<OriginalFn>(this, 20)(this, x, y);
    }
    void DrawPrintText(const wchar_t *text, int textLen)
    {
        typedef void(* OriginalFn)(void*, const wchar_t *, int, int);
        return getvfunc<OriginalFn>(this, 22)(this, text, textLen, 0);
    }
    unsigned long CreateFont()
    {
        typedef unsigned int(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 66)(this);
    }
    void SetFontGlyphSet(unsigned long font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
    {
        typedef void(* OriginalFn)(void*, unsigned long, const char*, int, int, int, int, int, int, int);
        getvfunc<OriginalFn>(this, 67)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
    }
    void GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall)
    {
        typedef void(* OriginalFn)(void*, unsigned long, const wchar_t *, int&, int&);
        getvfunc<OriginalFn>(this, 75)(this, font, text, wide, tall);
    }
};

#endif //RESPECTRAL_ISURFACE_H
