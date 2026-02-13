#include "Level4.h"
#include "Chomper.h"
#include "Debug.h"
#include "Diamond.h"
#include "LawnMower.h"
#include "Level1.h"
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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LevelInfo Level4Info;

void InitLevel4(void)
{
    InitLevel4Info();
    InitLevel4Animation();
    InitLevel4MapCell();
}

void DrawLevel4(void)
{
    DrawUI();
    DrawLawnMowers();
    DrawPlantsUnderZombie();

    DrawZombies();
    DrawPlantsOverZombie();
    DrawSunElement();

    DrawDebug();
    if (CurrentGameState == LOSE)
    {
        DrawGameOver();
        DrawBottom();
    }
    if (CurrentGameState == WIN)
    {
        DrawVictory();
        DrawBottom();
    }
    if (CurrentGameState == YesNo)
    {
        DrawYesOrNop("       There's still a chance...\n\n\nAre you sure you want to give up? ");
    }
}
void UpdateLevel4(void)
{
    if (restart)
    {
        resartLevel4();
        ResetUi();

        InitLevel4Animation();
        InitLevel4MapCell();
    }

    UpdateUI();
    if (CurrentGameState == PLAYING)
    {
        SurvivalTimer += GetFrameTime();
        UpdateSUNELEMENT();
        UpdatePlants();
        UpdateLawnMowers();

        UpdateZombies();
        CheckLose();
    }
    if (CurrentGameState == LOSE)
    {
        if (SurvivalTimer > BestSurvivalTime)
        {
            GenerateDiamond(DiamondElementArray, 1410, 30);
            GenerateDiamond(DiamondElementArray, 1410, 30);

            for (int i = 0; i < 10; i++)
            {
                if (DiamondElementArray[i].Available)
                {
                    PlaySound(CollectSoundDiamond);
                    DiamondElementArray[i].IsCollected = true;
                    //   DrawTexture(MapDiamond, 31, 105, WHITE);
                    DiamondElementArray[i].Diamond.finalX = 31;
                    DiamondElementArray[i].Diamond.finalY = 105;

                    DiamondElementArray[i].Diamond.speedX = (31 - DiamondElementArray[i].Diamond.posX) / 1.5;
                    DiamondElementArray[i].Diamond.speedY = (105 - DiamondElementArray[i].Diamond.posY) / 1.5;
                }
            }
            SaveGame();
            BestSurvivalTime = SurvivalTimer;
            CalculateBestTimeHMS();
            SaveBestTime();
        }
    }
    if (CurrentGameState == YesNo)
    {
        UpdateYesOrNop();
    }
}


void InitLevel4Info(void)
{
    Level4Info.SunFlowertInfoLevel.price = 50;
    Level4Info.PeashooterInfoLevel.price = 100;
    Level4Info.ChompertInfoLevel.price = 125;
    Level4Info.RosetInfoLevel.price = 150;
    Level4Info.PotatoMineInfoLevel.price = 25;

    Level4Info.SunFlowertInfoLevel.Cooldown = 2; // 45;
    Level4Info.PeashooterInfoLevel.Cooldown = 2; // 45;
    Level4Info.ChompertInfoLevel.Cooldown = 2;   // 60;
    Level4Info.RosetInfoLevel.Cooldown = 0.5;    // 70;
    Level4Info.SunFlowertInfoLevel.Timer = 0;
    Level4Info.PeashooterInfoLevel.Timer = 0;
    Level4Info.ChompertInfoLevel.Timer = 0;
    Level4Info.RosetInfoLevel.Timer = 0;
    Level4Info.PotatoMineInfoLevel.Timer = 0;
    Level4Info.PotatoMineInfoLevel.ActivationTime = 5;

    Level4Info.SunFlowertInfoLevel.BaseHealth = 100;
    Level4Info.PeashooterInfoLevel.BaseHealth = 100;
    Level4Info.ChompertInfoLevel.BaseHealth = 100;
    Level4Info.RosetInfoLevel.BaseHealth = 100;
    Level4Info.PotatoMineInfoLevel.BaseHealth = 100;

    Level4Info.SunFlowertInfoLevel.Lock = false;
    Level4Info.PeashooterInfoLevel.Lock = false;
    Level4Info.ChompertInfoLevel.Lock = false;
    Level4Info.RosetInfoLevel.Lock = false;
    Level4Info.PotatoMineInfoLevel.Lock = false;

    Level4Info.SunFlowertInfoLevel.IsAvailable = true;
    Level4Info.PeashooterInfoLevel.IsAvailable = true;
    Level4Info.ChompertInfoLevel.IsAvailable = true;
    Level4Info.RosetInfoLevel.IsAvailable = true;
    Level4Info.PotatoMineInfoLevel.IsAvailable = true;

    Level4Info.SunElementInfoLevel.Value = VALUESUN;
    Level4Info.SunElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level4Info.SunElementInfoLevel.Regenerate = GENERATESUN;
    Level4Info.DiamondElementInfoLevel.Value = VALUESUN;
    Level4Info.DiamondElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level4Info.DiamondElementInfoLevel.Regenerate = GENERATESUN;
    Level4Info.ZombieRegenerateTimer = 5;

    //   Level4Info.ZombieNormal.Regenerate = 5;
    //   Level4Info.ZombieNormal.Timer = 0;
    Level4Info.ZombieNormal.BassSpeedX = -20;
    Level4Info.ZombieNormal.BassSpeedY = 0;
    Level4Info.ZombieNormal.BassRunSpeedY = 0;
    Level4Info.ZombieNormal.ZombieSpawned = 0;
    Level4Info.ZombieNormal.BassFrameDelay = 40.0f;
    //  Level4Info.ThinkingZombie.Timer = 0;
    Level4Info.ThinkingZombie.BassSpeedX = -20;
    Level4Info.ThinkingZombie.BassSpeedY = 0;
    Level4Info.ThinkingZombie.BassRunSpeedY = 20;
    Level4Info.ThinkingZombie.ZombieSpawned = 0;
    Level4Info.ZombieNormal.InfiniteSpan = true;
    Level4Info.ThinkingZombie.InfiniteSpan = true;
    Level4Info.ThinkingZombie.BassFrameDelay = 40.0f;
    Level4Info.MaxThinkingZombieAllowed = MAXNUZOMBIES;
    Level4Info.MaxZombieNormalAllowed = MAXNUZOMBIES;
    Level4Info.START_X = 305;
    Level4Info.START_Y = 230;
    Level4Info.END_X = 1380;
    Level4Info.END_Y = 840;
    LackSunWarning.isActive = false;
    LackSunWarning.duration = 2.0f;
    LackSunWarning.baseSize = 30.0f;
    LackSunWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 150};
    LockWarning.isActive = false;
    LockWarning.duration = 2.0f;
    LockWarning.baseSize = 30.0f;
    LockWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 130};
}

void InitLevel4Animation(void)
{
    CurrentLevelInfo = &Level4Info;
    SetupLawnMowerAnimation();
    InitAllAnimation();
}
void InitLevel4MapCell(void)
{
    for (int Y = CurrentLevelInfo->START_Y, i = 0, j = 0; Y <= CurrentLevelInfo->END_Y - RectangleHeight;
         Y = Y + RectangleHeight)
    {
        j = 0;
        for (int X = CurrentLevelInfo->START_X; X <= CurrentLevelInfo->END_X - RectangleWidth; X = X + RectangleWidth)
        {
            MapCell[i][j].x = X;
            MapCell[i][j].y = Y;
            MapCell[i][j].width = RectangleWidth;
            MapCell[i][j].height = RectangleHeight;
            j++;
        }
        i++;
    }
}

void resartLevel4(void)
{
    ResetCellContent();
    ResetAllAnimation();
    FirstRun = true;

    CurrentLevelInfo = &Level4Info;
    restart = false;
}
