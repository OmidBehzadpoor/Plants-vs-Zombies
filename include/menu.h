#pragma once
#ifndef MENU_H
#define MENU_H

#include "levelselect.h"
#include "raylib.h"
typedef enum GameScreen
{
    MENU = 0,
    LEVEL_SELECT,
    SHOP,
    LVL1,
    LVL2,
    LVL3,
    LVL4,
    MUSICPLAYER,
    EXITING
} GameScreen;
extern GameScreen Screen;
extern bool EXIT;
extern bool shopHoverPlayed;
extern bool exitHoverPlayed;
extern bool playHoverPlayed;
extern bool exitHoverPlayed;
extern Rectangle PlayButton;
extern Rectangle ShopButton;
extern Rectangle ExitButton;
extern Texture2D Menu3Button, Menu4Button;

void InitMenu(void);
void DrawMenu(void);
void UpdateMenu(void);
void UnloadMenu(void);

#endif