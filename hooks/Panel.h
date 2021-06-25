//
// Created by emiel on 3/05/21.
//

#ifndef RESPECTRAL_PANEL_H
#define RESPECTRAL_PANEL_H

#include "shared.h"
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
    void drawPlayerPos(int i);
    static int maxwidth = 0;

    DECLARE_HOOK(42, void, Panel_PaintTraverse, (IPanel* thisptr, unsigned int panelIndex, bool forceRepaint, bool allowForce))
    {
        original_Panel_PaintTraverse(thisptr, panelIndex, forceRepaint, allowForce);
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
//                draw::OutlineRect(200-50, 200-50, 200, 600, 0xFFFFFFFF);

                draw::TitleFont();
                draw::drawString(200 , 200, 0xFFFFFFFF, "Player");
                draw::drawString(200 + 100, 200 , 0xFFFFFFFF, "Cheat score");
                draw::DefaultFont();

                maxwidth = 0;
                for (int i = 1; i < 24; i++)
                {
                    drawPlayerPos(i);
                }

                CBaseEntity* pBaseLocalEnt = g_entityList->GetClientEntity(g_engineClient->GetLocalPlayer());  //Grab the local player's entity.

                if (!pBaseLocalEnt ) //Always check for null pointers.
                    return;

                Vector vecWorld, vecScreen; //Setup the Vectors.

                pBaseLocalEnt->GetWorldSpaceCenter(vecWorld); //Get the center of the player.

                if ( draw::WorldToScreen(vecWorld, vecScreen) ) //If the player is visible.
                {
                    draw::drawString( vecScreen.x, vecScreen.y, COLORCODE(0,0xFF,0,0xFF), "You" ); //Draw on the player.
                }
            }

        }
    }

    void drawPlayerPos(int i)
    {
//        char debugValue[256];
//        snprintf(debugValue,256,"debugValue: %i",draw::debugValue);

        auto entity = g_entityList->GetClientEntity(i);
        if (!entity || entity->IsDormant()) return;
        Vector screenPos, worldPos;
        entity->GetWorldSpaceCenter(worldPos);

//        player_info_t *playerInfo;
//        g_engineClient->GetPlayerInfo(i, playerInfo);
//
//        if (!playerInfo)
//        {
//            spdlog::error("PlayerInfo was NULL");
//            return;
//        }
//
//        const char *name = playerInfo->name;

//        char posStr[256];
//        snprintf(posStr, 256, "Pos: %f : %f", worldPos.x, worldPos.y);

//        int textWidth, textHeight;
//        draw::GetTextSize(textWidth, textHeight, name);
//        if (textWidth > maxwidth) maxwidth = textWidth;

//        draw::drawString(200 , 200 + 10 + i*12, 0xFFFFFFFF, name);
//        draw::drawString(200 + maxwidth + 10, 200 + i*12, COLORCODE(0,0xFF,0,0xFF), "0");

//        if (draw::WorldToScreen(worldPos, screenPos))
//        {
//            draw::drawString(static_cast<int>(screenPos.x - textWidth/2) , static_cast<int>(screenPos.y), 0xFFFFFFFF, name);
//        }

    }
}


#endif //RESPECTRAL_PANEL_H
