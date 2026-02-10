#include "Level2.h"
#include "Chomper.h"
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
#include "Debug.h"
LevelInfo Level2Info;
double lvl2Runtime = 0;

void InitLevel2(void)
{
    InitLevel2Info();
    InitLevel2Animation();
    InitLevel2MapCell();
}

void DrawLevel2(void)
{
    DrawUI();
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
void UpdateLevel2(void)
{
    if (restart)
    {
        resartLevel2();
        ResetUi();
        InitLevel2Animation();
        InitLevel2MapCell();
    }

    UpdateUI();
    if (CurrentGameState == PLAYING)
    {

        UpdateSUNELEMENT();
        UpdatePlants();

        UpdateZombies();
        CheckWin();
        CheckLose();
    }
    if (CurrentGameState == YesNo)
    {
        UpdateYesOrNop();
    }
}
// ---------------------- Generate Functions-----------------------  //

//--------------------------------------------------------------------------------//

// ---------------------- Init Functions-----------------------------------------  //

void InitLevel2Info(void)
{
    Level2Info.SunFlowertInfoLevel.price = 50;
    Level2Info.PeashooterInfoLevel.price = 100;
    Level2Info.ChompertInfoLevel.price = 125;
    Level2Info.RosetInfoLevel.price = 150;
    Level2Info.PotatoMineInfoLevel.price = 25;

    Level2Info.SunFlowertInfoLevel.Cooldown = 2; // 45;
    Level2Info.PeashooterInfoLevel.Cooldown = 2; // 45;
    Level2Info.ChompertInfoLevel.Cooldown = 2;   // 60;
    Level2Info.RosetInfoLevel.Cooldown = 0.5;    // 70;
    Level2Info.SunFlowertInfoLevel.Timer = 0;
    Level2Info.PeashooterInfoLevel.Timer = 0;
    Level2Info.ChompertInfoLevel.Timer = 0;
    Level2Info.RosetInfoLevel.Timer = 0;
    Level2Info.PotatoMineInfoLevel.Timer = 0;
    Level2Info.PotatoMineInfoLevel.ActivationTime = 5;

    Level2Info.SunFlowertInfoLevel.BaseHealth = 100;
    Level2Info.PeashooterInfoLevel.BaseHealth = 100;
    Level2Info.ChompertInfoLevel.BaseHealth = 100;
    Level2Info.RosetInfoLevel.BaseHealth = 100;
    Level2Info.PotatoMineInfoLevel.BaseHealth = 100;

    Level2Info.SunFlowertInfoLevel.Lock = false;
    Level2Info.PeashooterInfoLevel.Lock = false;
    Level2Info.ChompertInfoLevel.Lock = false;
    Level2Info.RosetInfoLevel.Lock = false;
    Level2Info.PotatoMineInfoLevel.Lock = false;

    Level2Info.SunFlowertInfoLevel.IsAvailable = true;
    Level2Info.PeashooterInfoLevel.IsAvailable = true;
    Level2Info.ChompertInfoLevel.IsAvailable = true;
    Level2Info.RosetInfoLevel.IsAvailable = true;
    Level2Info.PotatoMineInfoLevel.IsAvailable = true;

    Level2Info.SunElementInfoLevel.Value = VALUESUN;
    Level2Info.SunElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level2Info.SunElementInfoLevel.Regenerate = GENERATESUN;
    Level2Info.DiamondElementInfoLevel.Value = VALUESUN;
    Level2Info.DiamondElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level2Info.DiamondElementInfoLevel.Regenerate = GENERATESUN;
    Level2Info.ZombieNormal.Regenerate = 5;
    Level2Info.ZombieNormal.Timer = 0;
    Level2Info.ZombieNormal.BassSpeedX = -20;
    Level2Info.ZombieNormal.BassSpeedY = 0;
    Level2Info.ZombieNormal.BassRunSpeedY = 0;
    Level2Info.ZombieNormal.ZombieSpawned = 0;
    Level2Info.ZombieNormal.BassFrameDelay = 40.0f;
    Level2Info.ThinkingZombie.Timer = 0;
    Level2Info.ThinkingZombie.BassSpeedX = -20;
    Level2Info.ThinkingZombie.BassSpeedY = 0;
    Level2Info.ThinkingZombie.BassRunSpeedY = 20;
    Level2Info.ThinkingZombie.ZombieSpawned = 0;
    Level2Info.ThinkingZombie.BassFrameDelay = 40.0f;
    Level2Info.MaxThinkingZombieAllowed = 30;
    Level2Info.MaxZombieNormalAllowed = 0;
    Level2Info.ZombieNormal.InfiniteSpan = false;
    Level2Info.ThinkingZombie.InfiniteSpan = false;
    Level2Info.START_X = 305;
    Level2Info.START_Y = 230;
    Level2Info.END_X = 1380;
    Level2Info.END_Y = 840;
    LackSunWarning.isActive = false;
    LackSunWarning.duration = 2.0f;
    LackSunWarning.baseSize = 30.0f;
    LackSunWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 150};
    LockWarning.isActive = false;
    LockWarning.duration = 2.0f;
    LockWarning.baseSize = 30.0f;
    LockWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 130};
}

void InitLevel2Animation(void)
{
    CurrentLevelInfo = &Level2Info;
    InitAllAnimation();
}
void InitLevel2MapCell(void)
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
//------------------------------------------------------------------------------------------------//

void resartLevel2(void)
{
   ResetCellContent();
    ResetAllAnimation();
    FirstRun = true;
 
    CurrentLevelInfo = &Level2Info;
    restart = false;
}
