#include "Level1.h"
#include "Chomper.h"
#include "Debug.h"
#include "Diamond.h"
#include "LawnMower.h"
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

LevelInfo Level1Info;
double lvl1Runtime = 0;

void InitLevel1(void)
{
    InitLevel1Info();
    InitLevel1Animation();
    InitLevel1MapCell();
}

void DrawLevel1(void)
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
    }
    if (CurrentGameState == WIN)
    {

        DrawVictory();
    }
    if (CurrentGameState == YesNo)
    {
        DrawYesOrNop("       There's still a chance...\n\n\nAre you sure you want to give up? ");
    }
    DrawBottom();
}
void UpdateLevel1(void)
{
    if (restart)
    {
        resartLevel1();
        ResetUi();
        InitLevel1Animation();
        InitLevel1MapCell();
    }

    UpdateUI();
    if (CurrentGameState == PLAYING)
    {

        UpdateSUNELEMENT();
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
void UnloadLevel1(void)
{
    UnloadTexture(Map);
    UnloadTexture(SunBankPic);
    UnloadTexture(selectpic);
    UnloadTexture(SunFlowerSheet);
    UnloadTexture(LawnMowerSheet);
    UnloadTexture(SunElementSheet);
    UnloadTexture(Frame);

    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        UnloadAnimatedObject(&LawnMower[i].LawnMowerObj);
    }
    UnloadTexture(OFFlawnMowerRow);

    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        UnloadAnimatedObject(&SunElementArray[i].sun);
    }
    for (int i = 0; i < 5; i++)
    {
        UnloadAnimatedObject(&icon[i]);
        UnloadTexture(Price[i]);
    }

    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        UnloadAnimatedObject(&SunFlower[i].SunFlowerObj);
        UnloadAnimatedObject(&Chomper[i].ChomperObj);
        UnloadAnimatedObject(&Peashooter[i].PeashooterObj);
        UnloadAnimatedObject(&Rose[i].RoseObj);
    }
    UnloadFont(HorrorFont);
}
// ---------------------- Generate Functions-----------------------  //

//--------------------------------------------------------------------------------//

// ---------------------- Init Functions-----------------------------------------  //

void InitLevel1Info(void)
{
    Level1Info.SunFlowertInfoLevel.price = 50;
    Level1Info.PeashooterInfoLevel.price = 100;
    Level1Info.ChompertInfoLevel.price = 125;
    Level1Info.RosetInfoLevel.price = 150;
    Level1Info.PotatoMineInfoLevel.price = 25;

    Level1Info.SunFlowertInfoLevel.Cooldown = 2; // 45;
    Level1Info.PeashooterInfoLevel.Cooldown = 2; // 45;
    Level1Info.ChompertInfoLevel.Cooldown = 2;   // 60;
    Level1Info.RosetInfoLevel.Cooldown = 0.5;    // 70;
    Level1Info.PotatoMineInfoLevel.Cooldown = 0.5;
    Level1Info.SunFlowertInfoLevel.Timer = 0;
    Level1Info.PeashooterInfoLevel.Timer = 0;
    Level1Info.ChompertInfoLevel.Timer = 0;
    Level1Info.RosetInfoLevel.Timer = 0;
    Level1Info.PotatoMineInfoLevel.Timer = 0;
    Level1Info.PotatoMineInfoLevel.ActivationTime = 5;
    Level1Info.SunFlowertInfoLevel.BaseHealth = 100;
    Level1Info.PeashooterInfoLevel.BaseHealth = 100;
    Level1Info.ChompertInfoLevel.BaseHealth = 100;
    Level1Info.RosetInfoLevel.BaseHealth = 100;
    Level1Info.PotatoMineInfoLevel.BaseHealth = 100;
    Level1Info.SunFlowertInfoLevel.Lock = true;
    Level1Info.PeashooterInfoLevel.Lock = false;
    Level1Info.ChompertInfoLevel.Lock = false;

    Level1Info.RosetInfoLevel.Lock = false;
    Level1Info.PotatoMineInfoLevel.Lock = false;

    Level1Info.SunFlowertInfoLevel.IsAvailable = true;
    Level1Info.PeashooterInfoLevel.IsAvailable = true;
    Level1Info.ChompertInfoLevel.IsAvailable = true;
    Level1Info.RosetInfoLevel.IsAvailable = true;
    Level1Info.PotatoMineInfoLevel.IsAvailable = true;

    Level1Info.SunElementInfoLevel.Value = VALUESUN;
    Level1Info.SunElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level1Info.SunElementInfoLevel.Regenerate = GENERATESUN;
    Level1Info.DiamondElementInfoLevel.Value = VALUESUN;
    Level1Info.DiamondElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level1Info.DiamondElementInfoLevel.Regenerate = GENERATESUN;
    Level1Info.ZombieRegenerateTimer = 5 ;
    //   //    Level1Info.ZombieNormal.Regenerate = 5;
    //   // Level1Info.ZombieNormal.Timer = 0;
    Level1Info.ZombieNormal.BassSpeedX = -20;
    Level1Info.ZombieNormal.BassSpeedY = 0;
    Level1Info.ZombieNormal.BassRunSpeedY = 0;
    Level1Info.ZombieNormal.InfiniteSpan = false;
    Level1Info.ZombieNormal.ZombieSpawned = 0;
    Level1Info.ThinkingZombie.InfiniteSpan = false;
    Level1Info.ThinkingZombie.ZombieSpawned = 0;
    Level1Info.ZombieNormal.BassFrameDelay = 40.0f;
    //   //   Level1Info.ThinkingZombie.Timer = 0;
    Level1Info.ThinkingZombie.BassSpeedX = -20;
    Level1Info.ThinkingZombie.BassSpeedY = 0;
    Level1Info.ThinkingZombie.BassRunSpeedY = 20;

    Level1Info.ThinkingZombie.BassFrameDelay = 40.0f;
    Level1Info.MaxThinkingZombieAllowed = 0;
    Level1Info.MaxZombieNormalAllowed = 30;
    Level1Info.START_X = 305;
    Level1Info.START_Y = 230;
    Level1Info.END_X = 1380;
    Level1Info.END_Y = 840;

    LackSunWarning.isActive = false;
    LackSunWarning.duration = 2.0f;
    LackSunWarning.baseSize = 30.0f;
    LackSunWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 150};
    LockWarning.isActive = false;
    LockWarning.duration = 2.0f;
    LockWarning.baseSize = 30.0f;
    LockWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 130};
}

void InitLevel1Animation(void)
{
    CurrentLevelInfo = &Level1Info;
    SetupLawnMowerAnimation();
    InitAllAnimation();
}
void InitLevel1MapCell(void)
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

void resartLevel1(void)
{
    ResetCellContent();
    ResetAllAnimation();
    FirstRun = true;
    CurrentLevelInfo = &Level1Info;
    restart = false;
}