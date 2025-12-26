#include "menu.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
Texture2D background;
Rectangle PlayButton;
Rectangle ShopButton;
Rectangle ExitButton;

void InitMenu(void)
{

    background = LoadTexture("../assets/menu/3-button_menu.png");
    // // PlayButton
    PlayButton.x = 594;
    PlayButton.y = 261;
    PlayButton.width = 291;
    PlayButton.height = 90;

    // // ShopButton
    ShopButton.x = 604;
    ShopButton.y = 411;
    ShopButton.width = 257;
    ShopButton.height = 76;

    // // ExitButton
    ExitButton.x = 616;
    ExitButton.y = 550;
    ExitButton.width = 250;
    ExitButton.height = 73;
}


void DrawMenu(void)
{
    DrawTexture(background, 0, 0, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), PlayButton))
    {
        DrawText("Play", 687, 285, 50, BLUE);
    }
    else
    {
        DrawText("Play", 687, 285, 50, YELLOW);
    }
    if (CheckCollisionPointRec(GetMousePosition(), ShopButton))
    {
        DrawText("Shop", 687, 430, 40, BLUE);
    }
    else
    {
        DrawText("Shop", 687, 430, 40, YELLOW);
    }
    if (CheckCollisionPointRec(GetMousePosition(), ExitButton))
    {
        DrawText("Exit", 687, 570, 40, RED);
    }
    else
    {
        DrawText("Exit", 687, 570, 40, YELLOW);
    }
}

void UpdateMenu(void)
{

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(GetMousePosition(), PlayButton))
        {
            Screen = LEVEL_SELECT;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), ShopButton))
        {
            Screen = SHOP;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), ExitButton))
        {
            Screen = EXITING;
        }
    }
}
void UnloadMenu(void)
{
    UnloadTexture(background);
}
void MouseSelection(void)
{
    Vector2 mousePos = GetMousePosition();
    char coordText[50];
    sprintf(coordText, "X: %.0f, Y: %.0f", mousePos.x, mousePos.y);

    DrawText(coordText, 10, 10, 40, RED);
}