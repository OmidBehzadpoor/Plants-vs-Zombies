#include "Level1.h"
#include "LevelBase.h"
#include "Level2.h"
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
    Initlevelselect();
    InitGame();
    InitLevel1();
    InitLevel2();
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
        else if (Screen == LVL1)
        {
            UpdateLevel1();
        }
         else if (Screen == LVL2)
        {
            UpdateLevel2();
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
        else if (Screen == LVL1)
        {
            DrawLevel1();
        }
        else if (Screen == LVL2)
        {
            DrawLevel2();
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