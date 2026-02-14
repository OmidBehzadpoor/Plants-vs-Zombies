#include "Level3.h"
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

LevelInfo Level3Info;
double lvl3Runtime = 0;

void InitLevel3(void)
{
    InitLevel3Info();
    InitLevel3Animation();
    InitLevel3MapCell();
}

void DrawLevel3(void)
{
    DrawUI();
    DrawLawnMowers();
    DrawPlantsUnderZombie();

    DrawZombies();
    DrawPlantsOverZombie();
    //   DrawSunElement();

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
void UpdateLevel3(void)
{
    if (restart)
    {
        resartLevel3();
        ResetUi();
        InitLevel3Animation();
        InitLevel3MapCell();

        SunBank = 1500;
    }

    UpdateUI();
    if (CurrentGameState == PLAYING)
    {

        // UpdateSUNELEMENT();
        UpdatePlants();
        UpdateLawnMowers();

        UpdateZombies();
        CheckWin();
        CheckLose();
    }
    if (CurrentGameState == YesNo)
    {
        UpdateYesOrNop();
    }
}

void InitLevel3Info(void)
{
    Level3Info.SunFlowertInfoLevel.price = 50;
    Level3Info.PeashooterInfoLevel.price = 100;
    Level3Info.ChompertInfoLevel.price = 125;
    Level3Info.RosetInfoLevel.price = 150;
    Level3Info.PotatoMineInfoLevel.price = 25;
    Level3Info.IcePeashooterInfoLevel.price = 125;

    Level3Info.SunFlowertInfoLevel.Cooldown = 11;   // 45;
    Level3Info.PeashooterInfoLevel.Cooldown = 15;   // 45;
    Level3Info.IcePeashooterInfoLevel.Cooldown = 9; // 45;
    Level3Info.ChompertInfoLevel.Cooldown = 7;    // 60;
    Level3Info.RosetInfoLevel.Cooldown = 8;       // 70;
    Level3Info.PotatoMineInfoLevel.Cooldown = 14; // 70;

    Level3Info.SunFlowertInfoLevel.Timer = 0;
    Level3Info.PeashooterInfoLevel.Timer = 0;
    Level3Info.IcePeashooterInfoLevel.Timer = 0;

    Level3Info.ChompertInfoLevel.Timer = 0;
    Level3Info.RosetInfoLevel.Timer = 0;
    Level3Info.PotatoMineInfoLevel.Timer = 0;
    Level3Info.PotatoMineInfoLevel.ActivationTime = 10;

    Level3Info.SunFlowertInfoLevel.BaseHealth = 100;
    Level3Info.PeashooterInfoLevel.BaseHealth = 100;
    Level3Info.IcePeashooterInfoLevel.BaseHealth = 100;

    Level3Info.ChompertInfoLevel.BaseHealth = 100;
    Level3Info.RosetInfoLevel.BaseHealth = 100;
    Level3Info.PotatoMineInfoLevel.BaseHealth = 100;

    Level3Info.SunFlowertInfoLevel.Lock = false;
    Level3Info.PeashooterInfoLevel.Lock = false;
    Level3Info.IcePeashooterInfoLevel.Lock = false;

    Level3Info.ChompertInfoLevel.Lock = false;
    Level3Info.RosetInfoLevel.Lock = false;
    Level3Info.PotatoMineInfoLevel.Lock = false;

    Level3Info.SunFlowertInfoLevel.IsAvailable = false;
    Level3Info.PeashooterInfoLevel.IsAvailable = true;
    Level3Info.ChompertInfoLevel.IsAvailable = true;
    Level3Info.RosetInfoLevel.IsAvailable = true;
    Level3Info.PotatoMineInfoLevel.IsAvailable = true;
    Level3Info.IcePeashooterInfoLevel.IsAvailable = true;

    Level3Info.SunElementInfoLevel.Value = VALUESUN;
    Level3Info.SunElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level3Info.SunElementInfoLevel.Regenerate = GENERATESUN;
    Level3Info.DiamondElementInfoLevel.Value = VALUESUN;
    Level3Info.DiamondElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level3Info.DiamondElementInfoLevel.Regenerate = GENERATESUN;
    Level3Info.ZombieRegenerateTimer = 25;

    //  Level3Info.ZombieNormal.Regenerate = 5;
    //  Level3Info.ZombieNormal.Timer = 0;
    Level3Info.ZombieNormal.BassSpeedX = -17.5;
    Level3Info.ZombieNormal.BassSpeedY = 0;
    Level3Info.ZombieNormal.BassRunSpeedY = 0;
        Level3Info.ZombieNormal.FreezingSpeedX = Level3Info.ZombieNormal.BassSpeedX / 2;
    Level3Info.ZombieNormal.FreezingSpeedY = Level3Info.ZombieNormal.BassSpeedY / 2;
    Level3Info.ZombieNormal.FreezingRunSpeedY = Level3Info.ZombieNormal.BassRunSpeedY / 2;
    Level3Info.ZombieNormal.ZombieSpawned = 0;
    Level3Info.ZombieNormal.BassFrameDelay = 50.0f;
        Level3Info.ZombieNormal.FreezingFrameDelay = Level3Info.ZombieNormal.BassFrameDelay * 2;

    //   Level3Info.ThinkingZombie.Timer = 0;
    Level3Info.ThinkingZombie.BassSpeedX = -17.5;
    Level3Info.ThinkingZombie.BassSpeedY = 0;
    Level3Info.ThinkingZombie.BassRunSpeedY = 20;
    Level3Info.ThinkingZombie.ZombieSpawned = 0;
    Level3Info.ZombieNormal.InfiniteSpan = false;
    Level3Info.ThinkingZombie.InfiniteSpan = false;
    Level3Info.ThinkingZombie.FreezingSpeedX = Level3Info.ThinkingZombie.BassSpeedX / 2;
    Level3Info.ThinkingZombie.FreezingSpeedY = Level3Info.ThinkingZombie.BassSpeedY / 2;
    Level3Info.ThinkingZombie.FreezingRunSpeedY = Level3Info.ThinkingZombie.BassRunSpeedY / 2;

    Level3Info.ThinkingZombie.BassFrameDelay = 50.0f;
    Level3Info.ThinkingZombie.FreezingFrameDelay = Level3Info.ThinkingZombie.BassFrameDelay * 2;    Level3Info.MaxThinkingZombieAllowed = 15;
    Level3Info.MaxZombieNormalAllowed = 15;
    Level3Info.START_X = 305;
    Level3Info.START_Y = 230;
    Level3Info.END_X = 1418;
    Level3Info.END_Y = 840;
    LackSunWarning.isActive = false;
    LackSunWarning.duration = 2.0f;
    LackSunWarning.baseSize = 30.0f;
    LackSunWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 150};
    LockWarning.isActive = false;
    LockWarning.duration = 2.0f;
    LockWarning.baseSize = 30.0f;
    LockWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 130};
}

void InitLevel3Animation(void)
{
    CurrentLevelInfo = &Level3Info;
    SetupLawnMowerAnimation();
    InitAllAnimation();
}
void InitLevel3MapCell(void)
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

void resartLevel3(void)
{
    ResetCellContent();
    ResetAllAnimation();
    FirstRun = true;

    CurrentLevelInfo = &Level3Info;
    restart = false;
}
