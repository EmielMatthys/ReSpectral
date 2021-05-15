//
// Created by emiel on 3/05/21.
//

#ifndef RESPECTRAL_PANEL_H
#define RESPECTRAL_PANEL_H

#include "../TF2/IPanel.h"
#include "../DrawTools.h"

enum keystate_t
{
    DOWN,
    UP
};

static keystate_t keystate = UP;

namespace hooks
{
    #define PANEL_PAINT_TRAVERSE 42
    typedef void* (*Fn_PaintTraverse)(IPanel* thisptr, unsigned int panelIndex, bool forceRepaint, bool allowForce);
    Fn_PaintTraverse original_PaintTraverse;

    void drawPlayerPos(int i);
    static int maxwidth = 0;

    void Panel_PaintTraverse(IPanel* thisptr, unsigned int panelIndex, bool forceRepaint, bool allowForce)
    {
        original_PaintTraverse(thisptr, panelIndex, forceRepaint, allowForce);
        static unsigned int vguiMatSystemTopPanel;

        if (!vguiMatSystemTopPanel)
        {
            const char* szName = g_panels->GetName(panelIndex);
            if( szName[0] == 'M' && szName[3] == 'S' ) //Look for MatSystemTopPanel without using slow operations like strcmp or strstr.
            {
                vguiMatSystemTopPanel = panelIndex;
                draw::init();
            }
        }

        if ( vguiMatSystemTopPanel == panelIndex ) //If we're on MatSystemTopPanel, call our drawing code.
        {

            if (g_inputSystem->IsButtonDown(KEY_HOME))
            {
                if (keystate == UP)
                {
                    draw::enabled = !draw::enabled;
                }
                keystate = DOWN;
            } else
            {
                keystate = UP;
            }

            if (draw::enabled)
            {
                char debugValue[32];
                snprintf(debugValue,32,"debugValue: %i",draw::debugValue);
                draw::drawString(500, 500,0xFFFFFFFF,debugValue);
                for (int i = 1; i < 24; i++)
                {
                    maxwidth = 0;
                    drawPlayerPos(i);

                }

                CBaseEntity* pBaseLocalEnt = g_entityList->GetClientEntity(g_engineClient->GetLocalPlayer());  //Grab the local player's entity.

                if (!pBaseLocalEnt ) //Always check for null pointers.
                    return;

                Vector vecWorld, vecScreen; //Setup the Vectors.

                pBaseLocalEnt->GetWorldSpaceCenter(vecWorld); //Get the center of the player.

                if ( draw::WorldToScreen(vecWorld, vecScreen) ) //If the player is visible.
                {
                    draw::drawString( vecScreen.x, vecScreen.y, 0xFFFFFFFF, "You" ); //Draw on the player.
                }
            }

        }
    }

    void drawPlayerPos(int i)
    {
        auto entity = g_entityList->GetClientEntity(i);
        if (!entity || entity->IsDormant()) return;
        Vector screenPos, worldPos;
        entity->GetWorldSpaceCenter(worldPos);

        player_info_t *playerInfo;
        g_engineClient->GetPlayerInfo(i, playerInfo);

        if (!playerInfo)
        {
            spdlog::error("PLayerInfo was NULL");
            return;
        }

        const char *name = playerInfo->name;

        char posStr[256];
        snprintf(posStr, 256, "Pos: %f : %f", worldPos.x, worldPos.y);

        int textWidth, textHeight;
        draw::GetTextSize(textWidth, textHeight, name);
        if (textWidth > maxwidth) maxwidth = textWidth;

        draw::drawString(200 , 200 + i*12, 0xFFFFFFFF, name);
        draw::drawString(200 + maxwidth + 10, 200 + i*12, 0xFFFFFFFF, posStr);

//        if (draw::WorldToScreen(worldPos, screenPos))
//        {
//            draw::drawString(static_cast<int>(screenPos.x - textWidth/2) , static_cast<int>(screenPos.y), 0xFFFFFFFF, name);
//        }

    }
}


#endif //RESPECTRAL_PANEL_H
