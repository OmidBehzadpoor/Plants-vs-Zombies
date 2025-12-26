#pragma once
#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "levelselect.h"
typedef enum GameScreen
{
    MENU = 0,
    LEVEL_SELECT,
    SHOP,
    LVL1,
    LVL2,
    LVL3,
    LVL4,
    EXITING
} GameScreen;
extern GameScreen Screen ;
extern bool EXIT;
extern Rectangle PlayButton ;
extern Rectangle ShopButton ;
extern Rectangle ExitButton ;
extern Texture2D background;


void InitMenu(void);
void DrawMenu(void);
void UpdateMenu(void);
void UnloadMenu(void);
void MouseSelection(void);

#endif