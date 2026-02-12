#include "Gameloop.h"
#include "Chomper.h"
#include "Debug.h"
#include "Diamond.h"
#include "LawnMower.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "LevelBase.h"
#include "LevelUi.h"
#include "Peashooter.h"
#include "Plant.h"
#include "PotatoMine.h"
#include "Rose.h"
#include "Shop.h"
#include "SoundandMusic.h"
#include "Sun.h"
#include "Sunflower.h"
#include "Zombie.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Gameloop(void)
{

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
}
void InitGame(void)
{
    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Plants vs Zombies");
    SetTargetFPS(FPS);
    InitAudioDevice();

    InitLevelTexture();
    InitLevelFont();
    InitSound();
    InitMusic();
    InitMusicPlayer();
    InitMenu();
    InitShop();
    Initlevelselect();
    InitLevel1();
    InitLevel2();
    InitLevel3();
    InitLevel4();
    InitSpecialItems();
    PlayRandomMenuMusic();
}
void UnloadGame(void)
{
    ResetAllAnimation();
    UnloadMenu();
    Unloadlevelselect();
    UnloadShop();
    UnloadMusicPlayer();
    UnloadLevelFont();
    UnloadLevelTexture();
    UnloadSoundAndMusic();
    CloseAudioDevice();
    CloseWindow();
}