//
// Created by emiel on 3/05/21.
//

#ifndef RESPECTRAL_PANEL_H
#define RESPECTRAL_PANEL_H

#include "../TF2/IPanel.h"
#include "../DrawManager.h"

namespace hooks
{
    #define PANEL_PAINT_TRAVERSE 42
    typedef void* (*Fn_PaintTraverse)(IPanel* thisptr, unsigned int panelIndex, bool forceRepaint, bool allowForce);
    Fn_PaintTraverse original_PaintTraverse;

    void Panel_PaintTraverse(IPanel* thisptr, unsigned int panelIndex, bool forceRepaint, bool allowForce)
    {
        original_PaintTraverse(thisptr, panelIndex, forceRepaint, allowForce);
        static unsigned int vguiMatSystemTopPanel;

        if (!vguiMatSystemTopPanel)
        {
            const char* szName = g_panels->GetName(panelIndex);
            if( szName[0] == 'M' && szName[3] == 'S' ) //Look for MatSystemTopPanel without using slow operations like strcmp or strstr.
            {
                spdlog::debug("inside MatSystemTopPanel!");
                vguiMatSystemTopPanel = panelIndex;
                draw::init();
            }
        }

        if ( vguiMatSystemTopPanel == panelIndex ) //If we're on MatSystemTopPanel, call our drawing code.
        {
            if (g_inputSystem->IsButtonDown(KEY_INSERT))
                draw::drawString( 200, 200, 0xFFFFFFFF, "Welcome to RESPECTRAL");
//            draw::drawRect(0, 0, 35, 35,0xFFFFFFFF);

        }
    }
}


#endif //RESPECTRAL_PANEL_H
