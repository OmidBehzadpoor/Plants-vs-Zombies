#include "Level1.h"
#include "Chomper.h"
#include "LawnMower.h"
#include "LevelBase.h"
#include "LevelUi.h"
#include "Peashooter.h"
#include "Plant.h"
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
LevelInfo Level1Info;
double lvl1Runtime = 0;

void InitLevel1(void)
{

    InitLevel1Animation();
    InitLevel1MapCell();
    InitLevel1Info();
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
        DrawBottom();
    }
    if (CurrentGameState == WIN)
    {
        DrawVictory();
        DrawBottom();
    }
}
void UpdateLevel1(void)
{
    if (restart)
    {
        resartLevel();
        InitLevel1Animation();
        ResetUi();
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
    for (int i = 0; i < 4; i++)
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

void CellularNetworkMap(void)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            char Coordinates[16];
            sprintf(Coordinates, "(%d , %d)", i + 1, j + 1);
            DrawRectangleLinesEx(MapCell[i][j], 1, WHITE);
            DrawText(Coordinates, MapCell[i][j].x + 5, MapCell[i][j].y + 5, 20, RED);
        }
    }
}

//--------------------------------------------------------------------------------//

// ---------------------- Init Functions-----------------------------------------  //

void InitLevel1Info(void)
{
    Level1Info.SunFlowertInfoLevel.price = 50;
    Level1Info.PeashooterInfoLevel.price = 100;
    Level1Info.ChompertInfoLevel.price = 125;
    Level1Info.RosetInfoLevel.price = 150;
    Level1Info.SunFlowertInfoLevel.Cooldown = 2; // 45;
    Level1Info.PeashooterInfoLevel.Cooldown = 2; // 45;
    Level1Info.ChompertInfoLevel.Cooldown = 2;   // 60;
    Level1Info.RosetInfoLevel.Cooldown = 0.5;    // 70;
    Level1Info.SunFlowertInfoLevel.Timer = 0;
    Level1Info.PeashooterInfoLevel.Timer = 0;
    Level1Info.ChompertInfoLevel.Timer = 0;
    Level1Info.RosetInfoLevel.Timer = 0;
    Level1Info.SunFlowertInfoLevel.BaseHealth = 100;
    Level1Info.PeashooterInfoLevel.BaseHealth = 100;
    Level1Info.ChompertInfoLevel.BaseHealth = 100;
    Level1Info.RosetInfoLevel.BaseHealth = 100;
    Level1Info.SunFlowertInfoLevel.Lock = false;
    Level1Info.PeashooterInfoLevel.Lock = false;
    Level1Info.ChompertInfoLevel.Lock = false;
    Level1Info.RosetInfoLevel.Lock = false;
    Level1Info.SunElementInfoLevel.Value = VALUESUN;
    Level1Info.SunElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level1Info.SunElementInfoLevel.Regenerate = GENERATESUN;
    Level1Info.ZombieNormal.Regenerate = 5;
    Level1Info.ZombieNormal.Timer = 0;
    Level1Info.ZombieNormal.BassSpeedX = -20;
    Level1Info.ZombieNormal.BassSpeedY = 0;
    Level1Info.ZombieNormal.BassRunSpeedY = 0;

    Level1Info.ZombieNormal.BassFrameDelay = 40.0f;
    Level1Info.ThinkingZombie.Timer = 0;
    Level1Info.ThinkingZombie.BassSpeedX = -20;
    Level1Info.ThinkingZombie.BassSpeedY = 0;
    Level1Info.ThinkingZombie.BassRunSpeedY = 20;

    Level1Info.ThinkingZombie.BassFrameDelay = 40.0f;
    Level1Info.MaxThinkingZombieAllowed = 0;
    Level1Info.MaxZombieNormalAllowed = 30;

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
    for (int i = 0; i < 4; i++)
    {
        int pixel = (i == 2) ? 100 : 71;
        int pixelY = (i == 2) ? 0 : 25;
        int k = (i == 2) ? 12 : 0;

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
}
void InitLevel1MapCell(void)
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

void CheckWin(void)
{
    if (CurrentLevelInfo->ZombieNormal.ZombieSpawned < CurrentLevelInfo->MaxZombieNormalAllowed)
        return;
    if (CurrentLevelInfo->ThinkingZombie.ZombieSpawned < CurrentLevelInfo->MaxThinkingZombieAllowed)
        return;
    if (ZombiesSpawned == CurrentLevelInfo->MaxZombieNormalAllowed + CurrentLevelInfo->MaxThinkingZombieAllowed &&
        ZombiesKilled == CurrentLevelInfo->MaxZombieNormalAllowed + CurrentLevelInfo->MaxThinkingZombieAllowed)
    {
        CurrentGameState = WIN;
        PlaySound(VictorySound);
    }
}
void CheckLose(void)
{
    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++)
    {
        if (ZombieNormal[i].isAlive && ZombieNormal[i].Markaz.x < START_X)
        {
            CurrentGameState = LOSE;
            PlaySound(EndGameSound);
            return;
        }
    }
    for (int i = 0; i < CurrentLevelInfo->MaxThinkingZombieAllowed; i++)
    {
        if (ThinkingZombie[i].isAlive && ThinkingZombie[i].Markaz.x < START_X)
        {
            CurrentGameState = LOSE;
            PlaySound(EndGameSound);
            return;
        }
    }
}

void resartLevel(void)
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
    }
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        ResetAnimatedObject(&SunFlower[i].SunFlowerObj);
        ResetAnimatedObject(&Peashooter[i].PeashooterObj);
        ResetAnimatedObject(&Chomper[i].ChomperObj);
        ResetAnimatedObject(&Rose[i].RoseObj);
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
    for (int i = 0; i < 4; i++)
    {
        ResetAnimatedObject(&icon[i]);
    }
    CurrentLevelInfo = &Level1Info;
    restart = false;
}

void DrawDebug(void)
{

    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++) // for debug
    {
        if (ZombieNormal[i].isAlive)
        {
            DrawText("O", ZombieNormal[i].ZombieObj.posX + ZombieNormal[i].ZombieObj.frames[0].width / 2,
                     ZombieNormal[i].ZombieObj.posY + ZombieNormal[i].ZombieObj.frames[0].height / 2, 20, RED);
            DrawRectangleLines((int)ZombieNormal[i].CollisionBox.x, (int)ZombieNormal[i].CollisionBox.y,
                               (int)ZombieNormal[i].CollisionBox.width, (int)ZombieNormal[i].CollisionBox.height, RED);
        }
    }
    for (int i = 0; i < CurrentLevelInfo->MaxThinkingZombieAllowed; i++) // for debug
    {
        if (ThinkingZombie[i].isAlive)
        {
            DrawText("O", ThinkingZombie[i].ZombieObj.posX + ThinkingZombie[i].ZombieObj.frames[0].width / 2,
                     ThinkingZombie[i].ZombieObj.posY + ThinkingZombie[i].ZombieObj.frames[0].height / 2, 20, RED);
            DrawRectangleLines((int)ThinkingZombie[i].CollisionBox.x, (int)ThinkingZombie[i].CollisionBox.y,
                               (int)ThinkingZombie[i].CollisionBox.width, (int)ThinkingZombie[i].CollisionBox.height,
                               RED);
        }
    }
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            if (Peashooter[i].Pea[k].isActive)
            {
                DrawCircleLines((int)Peashooter[i].Pea[k].Markaz.x, (int)Peashooter[i].Pea[k].Markaz.y,
                                Peashooter[i].Pea[k].Radius, BLUE);
            }
        }
    }

    CellularNetworkMap(); // for debug.

    /*
    Rectangle frame = {65 * 99, 0, 65, 5};
    Rectangle frame1 = {65 * 25, 0, 65, 3};
    Rectangle frame2 = {65 * 50, 0, 65, 5};
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < 10; j++)
        {

            Vector2 pos = {322.5 + j * 107.5, 238 + i * 122};
            Vector2 pos1 = {322.5 + j * 107.5, 235 + i * 122};
            Vector2 pos2 = {322.5 + j * 107.5, 243 + i * 122};
            DrawTextureRec(HpBar, frame, pos, WHITE);
            DrawTextureRec(OverhealBar, frame1, pos1, WHITE);
            DrawTextureRec(LifetimeBar, frame2, pos2, WHITE);

        }

    }
    */
}
