#include "Level3.h"
#include "Chomper.h"
#include "LawnMower.h"
#include "Level1.h"
#include "LevelBase.h"
#include "LevelUi.h"
#include "Peashooter.h"
#include "Plant.h"
#include "PotatoMine.h"
#include "Rose.h"
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

    InitLevel3Animation();
    InitLevel3MapCell();
    InitLevel3Info();
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
        InitLevel3Animation();
        ResetUi();
        SunBank = 3000;
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
// ---------------------- Generate Functions-----------------------  //

//--------------------------------------------------------------------------------//

// ---------------------- Init Functions-----------------------------------------  //

void InitLevel3Info(void)
{
    Level3Info.SunFlowertInfoLevel.price = 50;
    Level3Info.PeashooterInfoLevel.price = 100;
    Level3Info.ChompertInfoLevel.price = 125;
    Level3Info.RosetInfoLevel.price = 150;
    Level3Info.PotatoMineInfoLevel.price = 25;

    Level3Info.SunFlowertInfoLevel.Cooldown = 2; // 45;
    Level3Info.PeashooterInfoLevel.Cooldown = 2; // 45;
    Level3Info.ChompertInfoLevel.Cooldown = 2;   // 60;
    Level3Info.RosetInfoLevel.Cooldown = 0.5;    // 70;
    Level3Info.SunFlowertInfoLevel.Timer = 0;
    Level3Info.PeashooterInfoLevel.Timer = 0;
    Level3Info.ChompertInfoLevel.Timer = 0;
    Level3Info.RosetInfoLevel.Timer = 0;
    Level3Info.PotatoMineInfoLevel.Timer = 0;
    Level3Info.PotatoMineInfoLevel.ActivationTime = 5;

    Level3Info.SunFlowertInfoLevel.BaseHealth = 100;
    Level3Info.PeashooterInfoLevel.BaseHealth = 100;
    Level3Info.ChompertInfoLevel.BaseHealth = 100;
    Level3Info.RosetInfoLevel.BaseHealth = 100;
    Level3Info.PotatoMineInfoLevel.BaseHealth = 100;

    Level3Info.SunFlowertInfoLevel.Lock = false;
    Level3Info.PeashooterInfoLevel.Lock = false;
    Level3Info.ChompertInfoLevel.Lock = false;
    Level3Info.RosetInfoLevel.Lock = false;
    Level3Info.PotatoMineInfoLevel.Lock = false;

    Level3Info.SunFlowertInfoLevel.IsAvailable = false;
    Level3Info.PeashooterInfoLevel.IsAvailable = true;
    Level3Info.ChompertInfoLevel.IsAvailable = true;
    Level3Info.RosetInfoLevel.IsAvailable = true;
    Level3Info.PotatoMineInfoLevel.IsAvailable = true;

    Level3Info.SunElementInfoLevel.Value = VALUESUN;
    Level3Info.SunElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level3Info.SunElementInfoLevel.Regenerate = GENERATESUN;
    Level3Info.ZombieNormal.Regenerate = 5;
    Level3Info.ZombieNormal.Timer = 0;
    Level3Info.ZombieNormal.BassSpeedX = -20;
    Level3Info.ZombieNormal.BassSpeedY = 0;
    Level3Info.ZombieNormal.BassRunSpeedY = 0;
    Level3Info.ZombieNormal.ZombieSpawned = 0;
    Level3Info.ZombieNormal.BassFrameDelay = 40.0f;
    Level3Info.ThinkingZombie.Timer = 0;
    Level3Info.ThinkingZombie.BassSpeedX = -20;
    Level3Info.ThinkingZombie.BassSpeedY = 0;
    Level3Info.ThinkingZombie.BassRunSpeedY = 20;
    Level3Info.ThinkingZombie.ZombieSpawned = 0;
    Level3Info.ZombieNormal.InfiniteSpan = false;
    Level3Info.ThinkingZombie.InfiniteSpan = false;
    Level3Info.ThinkingZombie.BassFrameDelay = 40.0f;
    Level3Info.MaxThinkingZombieAllowed = 15;
    Level3Info.MaxZombieNormalAllowed = 15;
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
    for (int i = 0; i < 5; i++)
    {
        int pixel = (i == 2) ? 80 : 71;
        int pixelY = (i == 2) ? 14 : 25;
        int k = (i == 2 || i == 4) ? 12 : 0;

        icon[i] = GenerateAnimatedObject(&iconPic[i], pixel, pixel, 80, 370 - k + Frame.width * i, pixelY, 0, 0,
                                         370 - k + Frame.width * i, 25);
    }
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        LawnMower[i].LawnMowerObj = GenerateAnimatedObject(&LawnMowerSheet, 70, 57, 80, 210, 270 + RectangleHeight * i,
                                                           50, 0, 320, 270 + RectangleHeight * i);
        LawnMower[i].Y_Cell = i;
        LawnMower[i].X_Cell = 0;
        LawnMower[i].Available = true;
        LawnMower[i].isActive = true;
        CellContent[i][0] = LAWNMOWER;
        LawnMower[i].Markaz.x = LawnMower[i].LawnMowerObj.posX + LawnMower[i].LawnMowerObj.frames[0].width / 2;
        LawnMower[i].Markaz.y = LawnMower[i].LawnMowerObj.posY + LawnMower[i].LawnMowerObj.frames[0].height / 2;
    }
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        SunFlower[i].SunFlowerObj = GenerateAnimatedObject(&SunFlowerSheet, 80, 80, 60, 0, 0, 0, 0, 0, 0);
        SunFlower[i].Base.isAlive = false;
        SunFlower[i].Base.Health = 100;
        Rose[i].RoseObj = GenerateAnimatedObject(&RoseSheet, 80, 80, 80, 0, 0, 0, 0, 0, 0);
        Rose[i].Base.Health = 100;
        Rose[i].Base.isAlive = false;
        Chomper[i].ChomperObj = GenerateAnimatedObject(&ChomperSheet, 80, 80, 80, 0, 0, 0, 0, 0, 0);
        Chomper[i].Base.isAlive = false;
        Peashooter[i].PeashooterObj = GenerateAnimatedObject(&PeashooterSheet, 80, 80, 16.75, 0, 0, 0, 0, 0, 0);
        Peashooter[i].Base.isAlive = false;
        Peashooter[i].FireTimer = 0;
        Peashooter[i].Firing = false;
        PotatoMine[i].PotatoMineObj = GenerateAnimatedObject(&PotatoMineNotReadyPic, 75, 55, 80, 0, 0, 0, 0, 0, 0);
        PotatoMine[i].Base.isAlive = false;
        for (int j = 0; j < 10; j++)
        {
            Peashooter[i].Pea[j].isActive = false;
            Peashooter[i].Pea[j].Pea = GenerateAnimatedObject(&pea, 29, 32, 80, 0, 0, 0, 0, 0, 0);
            Peashooter[i].Pea[j].isActive = false;
            Peashooter[i].Pea[j].PeaBulletHit.DisplayTime = 0.1f;
            Peashooter[i].Pea[j].PeaBulletHit.DisplayTimer = 0.0;
        }
    }

    SunTimer = 0;
    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        SunElementArray[i].sun = GenerateAnimatedObject(&SunElementSheet, 79, 79, 60, 0, 0, 0, 45, 0, 0);
        SunElementArray[i].Available = false;
        SunElementArray[i].time = 0.0f;
    }
    ZombieTimer = 0;
    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++)
    {
        ZombieNormal[i].isAlive = false;
        ZombieNormal[i].Attack = false;
        ZombieNormal[i].ZombieObj = GenerateAnimatedObject(&ZombieNormal1, 12, 12, 0, 0, 0, 0, 0, 0, 0);
    }
    for (int i = 0; i < CurrentLevelInfo->MaxThinkingZombieAllowed; i++)
    {
        ThinkingZombie[i].isAlive = false;
        ThinkingZombie[i].Attack = false;
        ThinkingZombie[i].ZombieObj = GenerateAnimatedObject(&ThinkingZombiePic, 12, 12, 0, 0, 0, 0, 0, 0, 0);
    }
}
void InitLevel3MapCell(void)
{
    for (int Y = START_Y, i = 0, j = 0; Y <= END_Y - RectangleHeight; Y = Y + RectangleHeight)
    {
        j = 0;
        for (int X = START_X; X <= END_X - RectangleWidth; X = X + RectangleWidth)
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

void resartLevel3(void)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            CellContent[i][j] = EMPTY;
        }
    }

    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        ResetAnimatedObject(&LawnMower[i].LawnMowerObj);
        LawnMower[i].isActive = false;
        LawnMower[i].Available = false;
    }
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        ResetAnimatedObject(&SunFlower[i].SunFlowerObj);
        ResetAnimatedObject(&Peashooter[i].PeashooterObj);
        ResetAnimatedObject(&Chomper[i].ChomperObj);
        ResetAnimatedObject(&Rose[i].RoseObj);
        ResetAnimatedObject(&PotatoMine[i].PotatoMineObj);
        PotatoMine[i].Explosion = false;

        for (int j = 0; j < 10; j++)
        {
            ResetAnimatedObject(&Peashooter[i].Pea[j].PeaBulletHit.BulletHitObj);
            ResetAnimatedObject(&Peashooter[i].Pea[j].Pea);
        }
    }
    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++)
    {
        ZombieNormal[i].isAlive = false;
        ZombieNormal[i].Attack = false;
        ResetAnimatedObject(&ZombieNormal[i].ZombieObj);
    }
    for (int i = 0; i < CurrentLevelInfo->MaxThinkingZombieAllowed; i++)
    {
        ThinkingZombie[i].isAlive = false;
        ThinkingZombie[i].Attack = false;
        ResetAnimatedObject(&ThinkingZombie[i].ZombieObj);
    }
    FirstRun = true;
    for (int i = 0; i < 5; i++)
    {
        ResetAnimatedObject(&icon[i]);
    }
    CurrentLevelInfo = &Level3Info;
    restart = false;
}
