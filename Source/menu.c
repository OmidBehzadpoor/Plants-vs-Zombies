#include "menu.h"
#include "LevelBase.h"
#include "SoundandMusic.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

Texture2D Menu3Button, Menu4Button;
Rectangle PlayButton =(Rectangle) { 660 , 260 ,920 - 660 ,  320 - 260 };
Rectangle ShopButton=(Rectangle) { 660 , 350 ,920 - 660 ,  415 - 350 };
Rectangle ExitButton=(Rectangle) { 660 , 535 ,920 - 660 ,  600 - 535 };
bool shopHoverPlayed = false;
bool exitHoverPlayed = false;
bool playHoverPlayed = false;
void InitMenu(void)
{

    Menu3Button = LoadTexture("../assets/menu/3-button_menu.png");
    Menu4Button = LoadTexture("../assets/menu/4-button_menu.png");
    // // PlayButton
    // PlayButton.x = 660;
    // PlayButton.y = 260;
    // PlayButton.width = 920 - PlayButton.x;
    // PlayButton.height = 320 - PlayButton.y;

    // // ShopButton
    // ShopButton.x = 660;
    // ShopButton.y = 350;
    // ShopButton.width = 920 - ShopButton.x;
    // ShopButton.height = 415 - ShopButton.y;

    // // ExitButton
    // ExitButton.x = 600;
    // ExitButton.y = 535;
    // ExitButton.width = 920 - ExitButton.x;
    // ExitButton.height = 600 - ExitButton.y;
    // //  menuOpen = LoadSound("../assets/Sounds/menu_open.wav");
}

void DrawMenu(void)
{
    //  // DrawTexture(Menu3Button, 0, 0, WHITE);
    DrawTexture(Menu4Button, 0, 0, WHITE);

    DrawText("Play", 733, 265, 50, playHoverPlayed ? GREEN : SaffronYellow);

    DrawText("Shop", 733, 365, 45, shopHoverPlayed ? BLUE : SaffronYellow);

    DrawText("Exit", 733, 545, 50, exitHoverPlayed ? RED : SaffronYellow);
}

void UpdateMenu(void)
{

    Vector2 mousePos = GetMousePosition();

    // هاور PlayButton
    if (CheckCollisionPointRec(mousePos, PlayButton))
    {
        if (!playHoverPlayed)
        {
            PlaySound(menuHover);
            playHoverPlayed = true;
        }
    }
    else
    {
        playHoverPlayed = false;
    }

    // هاور ShopButton

    ;
    if (CheckCollisionPointRec(mousePos, ShopButton))
    {
        if (!shopHoverPlayed)
        {
            PlaySound(menuHover);
            shopHoverPlayed = true;
        }
    }
    else
    {
        shopHoverPlayed = false;
    }

    // هاور ExitButton
    if (CheckCollisionPointRec(mousePos, ExitButton))
    {
        if (!exitHoverPlayed)
        {
            PlaySound(menuHover);
            exitHoverPlayed = true;
        }
    }
    else
    {
        exitHoverPlayed = false;
    }
    // کلیک دکمه‌ها
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (playHoverPlayed)
        {
            PlaySound(menuSelect);
            Screen = LEVEL_SELECT;
        }
        else if (shopHoverPlayed)
        {
            PlaySound(menuSelect);
            Screen = SHOP;
        }
        else if (exitHoverPlayed)
        {
            PlaySound(menuSelect);
            Screen = EXITING;
        }
    }
}
void UnloadMenu(void)
{
    UnloadTexture(Menu3Button);
    UnloadTexture(Menu4Button);
}
void MouseSelection(void)
{
    Vector2 mousePos = GetMousePosition();
    char coordText[50];
    sprintf(coordText, "X: %.0f, Y: %.0f", mousePos.x, mousePos.y);

    DrawText(coordText, 10, 850, 40, RED);
}