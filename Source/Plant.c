
#include "Level1.h"
#include "Plant.h"
#include "Sun.h"
#include "SoundandMusic.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Zombie.h"
#include <string.h>
#include "Chomper.h"
#include "Peashooter.h"
#include "Rose.h"
#include "Sunflower.h"
#include "Sun.h"
void UpdatePlants(void)
{
    UpdatePlantsTimer();
    UpdatePlantsAnimation();
    CooldownUpdate();
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        UpdatePeashooterFiring(&Peashooter[i]);
        UpdatePeashooterPeas(&Peashooter[i]);
    }
}
void DrawPlantsUnderZombie(void)
{
    DrawPlantsObject();
}
void DrawPlantsOverZombie(void)
{
    DrawPeashooterBullets();
}
void CooldownUpdate(void)
{
    if (CurrentLevelInfo->SunFlowertInfoLevel.Lock)
    {
        CurrentLevelInfo->SunFlowertInfoLevel.Timer += GetFrameTime();
        if (CurrentLevelInfo->SunFlowertInfoLevel.Timer >= CurrentLevelInfo->SunFlowertInfoLevel.Cooldown)
        {
            CurrentLevelInfo->SunFlowertInfoLevel.Lock = false;
            CurrentLevelInfo->SunFlowertInfoLevel.Timer = 0;
        }
    }
    if (CurrentLevelInfo->PeashooterInfoLevel.Lock)
    {
        CurrentLevelInfo->PeashooterInfoLevel.Timer += GetFrameTime();
        if (CurrentLevelInfo->PeashooterInfoLevel.Timer >= CurrentLevelInfo->PeashooterInfoLevel.Cooldown)
        {
            CurrentLevelInfo->PeashooterInfoLevel.Lock = false;
            CurrentLevelInfo->PeashooterInfoLevel.Timer = 0;
        }
    }
    if (CurrentLevelInfo->ChompertInfoLevel.Lock)
    {
        CurrentLevelInfo->ChompertInfoLevel.Timer += GetFrameTime();
        if (CurrentLevelInfo->ChompertInfoLevel.Timer >= CurrentLevelInfo->ChompertInfoLevel.Cooldown)
        {
            CurrentLevelInfo->ChompertInfoLevel.Lock = false;
            CurrentLevelInfo->ChompertInfoLevel.Timer = 0;
        }
    }
    if (CurrentLevelInfo->RosetInfoLevel.Lock)
    {
        CurrentLevelInfo->RosetInfoLevel.Timer += GetFrameTime();
        if (CurrentLevelInfo->RosetInfoLevel.Timer >= CurrentLevelInfo->RosetInfoLevel.Cooldown)
        {
            CurrentLevelInfo->RosetInfoLevel.Lock = false;
            CurrentLevelInfo->RosetInfoLevel.Timer = 0;
        }
    }
}
void UpdatePlantsTimer(void)
{
    ResetSlowFactorZombies();
    ResetEffectiveFireRate();
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (SunFlower[i].Base.isAlive)
        {
            SunFlower[i].Cooldown -= GetFrameTime();
            if (SunFlower[i].Cooldown <= 0)
            {
                SunFlower[i].Cooldown = GENERATESUN; //?اصلاح
                GenerateSun(&SunElementArray[CurrentSunIndex], SunFlower[i].SunFlowerObj.posX,
                            SunFlower[i].SunFlowerObj.posY);
                CurrentSunIndex = (CurrentSunIndex + 1) % MAXSUNELEMENT;
            }
        }
        UpdateRose(&Rose[i]);
        UpdateChomper(&Chomper[i]);
    }
}

void DrawHpBar(HealthMeter *bar)
{
    DrawTextureRec(HpBar, bar->frameHP, bar->posHP, WHITE);

    if (bar->HpPercentage > 100)
        DrawTextureRec(OverhealBar, bar->frameOverhealBar, bar->posOverhealBar, WHITE);
}
void DrawPlantsObject(void)
{
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (SunFlower[i].Base.isAlive)
        {
            DrawAnimatedObject(&SunFlower[i].SunFlowerObj, WHITE);
            DrawHpBar(&SunFlower[i].Base.HpDisplay);
        }
        if (Chomper[i].Base.isAlive)
        {
            DrawAnimatedObject(&Chomper[i].ChomperObj, WHITE);
            DrawTextureRec(LifetimeBar, Chomper[i].LifetimeDisplay.frameBAR, Chomper[i].LifetimeDisplay.posBar, WHITE);

            DrawHpBar(&Chomper[i].Base.HpDisplay);
        }
        if (Peashooter[i].Base.isAlive)
        {
            DrawAnimatedObject(&Peashooter[i].PeashooterObj, WHITE);
            DrawHpBar(&Peashooter[i].Base.HpDisplay);
        }
        if (Rose[i].Base.isAlive)
        {
            DrawAnimatedObject(&Rose[i].RoseObj, WHITE);
            DrawTextureRec(LifetimeBar, Rose[i].LifetimeDisplay.frameBAR, Rose[i].LifetimeDisplay.posBar, WHITE);
            DrawHpBar(&Rose[i].Base.HpDisplay);
        }
    }
}

void UpdateHpBar(PlantBase *Plant, float BaseHp)
{
    Plant->HpDisplay.HpPercentage = (Plant->Health / BaseHp) * 100.0f;

    int frame = (int)Plant->HpDisplay.HpPercentage - 1;
    if (frame < 0)
        frame = 0;
    if (frame > 99)
        frame = 99;

    Plant->HpDisplay.frameHP = (Rectangle){65 * frame, 0, 65, 5};

    if (Plant->HpDisplay.HpPercentage > 100)
    {
        int over = Plant->HpDisplay.HpPercentage - 100 - 1;
        if (over < 0)
        {
            over = 0;
        }
        Plant->HpDisplay.frameOverhealBar = (Rectangle){65 * over, 0, 65, 3};
    }
}

void UpdatePlantsAnimation(void)
{
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (SunFlower[i].Base.isAlive)
        {
            UpdateAnimatedObject(&SunFlower[i].SunFlowerObj);
            UpdateHpBar(&SunFlower[i].Base, CurrentLevelInfo->SunFlowertInfoLevel.BaseHealth);
        }
        if (Peashooter[i].Base.isAlive)
        {
            UpdateAnimatedObject(&Peashooter[i].PeashooterObj);
            UpdateHpBar(&Peashooter[i].Base, CurrentLevelInfo->PeashooterInfoLevel.BaseHealth);
        }
        if (Chomper[i].Base.isAlive)
        {
            UpdateAnimatedObject(&Chomper[i].ChomperObj);
            UpdateHpBar(&Chomper[i].Base, CurrentLevelInfo->ChompertInfoLevel.BaseHealth);

            Chomper[i].LifetimeDisplay.LifetimePercentage = (Chomper[i].Lifespan / 20.0f) * 100.0f;
            UpdateLifetimeBar(&Chomper[i].LifetimeDisplay, Chomper[i].Lifespan, 20);
        }
        if (Rose[i].Base.isAlive)
        {
            UpdateAnimatedObject(&Rose[i].RoseObj);
            UpdateHpBar(&Rose[i].Base, CurrentLevelInfo->RosetInfoLevel.BaseHealth);
            UpdateLifetimeBar(&Rose[i].LifetimeDisplay, Rose[i].Lifespan, 10);
        }
    }
}
void GeneratePlantBase(PlantBase *obj, PlantType Type, float HP, int X_Cell, int Y_Cell)
{
    obj->Health = HP;
    obj->X_Cell = X_Cell;
    obj->Y_Cell = Y_Cell;
    obj->HpDisplay.frameHP = (Rectangle){65 * 99, 0, 65, 5};
    obj->HpDisplay.posHP = (Vector2){322.5 + X_Cell * 107.5, 238 + Y_Cell * 122};
    obj->HpDisplay.frameOverhealBar = (Rectangle){65 * 0, 0, 65, 3};
    obj->HpDisplay.posOverhealBar = (Vector2){322.5 + X_Cell * 107.5, 235 + Y_Cell * 122};
    obj->HpDisplay.HpPercentage = 100;
    obj->Type = Type;
    obj->isAlive = true;

    return;
}
void UpdateLifetimeBar(ActiveTimeBar *bar, float life, float maxLife)
{
    bar->LifetimePercentage = (life / maxLife) * 100.0f;

    int frame = (int)bar->LifetimePercentage - 1;
    if (frame < 0)
        frame = 0;
    if (frame > 99)
        frame = 99;

    bar->frameBAR = (Rectangle){65 * frame, 0, 65, 3};
}
