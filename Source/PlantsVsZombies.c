#include "Debug.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "LevelBase.h"
#include "Shop.h"
#include "SoundandMusic.h"
#include "levelselect.h"
#include "menu.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define FPS 60
bool EXIT = false;
GameScreen Screen = MENU;

int main()
{
    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Plants vs Zombies");
    SetTargetFPS(FPS);
    ClearBackground(YELLOW);
    InitAudioDevice();
    InitSound();
    InitMusic();
    InitMenu();
    InitShop();
    Initlevelselect();
    InitGame();
    InitLevel1();
    InitLevel2();
    InitLevel3();
    InitLevel4();

    PlayRandomMenuMusic();
    while (!WindowShouldClose() && Screen != EXITING)
    {
        UpdateMusic();
        if (Screen == MENU)
        {
            UpdateMenu();
        }
        else if (Screen == LEVEL_SELECT)
        {
            Updatelevelselect();
        }
        else if (Screen == SHOP)
        {
            UpdateShop();
        }
        else if (Screen == LVL1)
        {
            UpdateLevel1();
        }
        else if (Screen == LVL2)
        {
            UpdateLevel2();
        }
        else if (Screen == LVL3)
        {
            UpdateLevel3();
        }
        else if (Screen == LVL4)
        {
            UpdateLevel4();
        }
        else if (Screen == MUSICPLAYER)
        {
            UpdateMusicPlayerLogic();
        }
        BeginDrawing();

        ClearBackground(WHITE);

        if (Screen == MENU)
        {
            DrawMenu();
        }
        else if (Screen == LEVEL_SELECT)
        {
            Drawlevelselect();
        }
        else if (Screen == SHOP)
        {
            DrawShop();
        }
        else if (Screen == LVL1)
        {
            DrawLevel1();
        }
        else if (Screen == LVL2)
        {
            DrawLevel2();
        }
        else if (Screen == LVL3)
        {
            DrawLevel3();
        }
        else if (Screen == LVL4)
        {
            DrawLevel4();
        }
        else if (Screen == MUSICPLAYER)
        {
            DrawMusicPlayer();
        }
        MouseSelection();
        EndDrawing();
    }

    UnloadMenu();
    Unloadlevelselect();
    UnloadLevel1();
    UnloadSoundAndMusic();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}