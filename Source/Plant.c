
#include "Plant.h"
#include "Chomper.h"
#include "Level1.h"
#include "Peashooter.h"
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
void UpdatePlants(void)
{
    UpdatePlantsTimer();
    UpdatePlantsAnimation();
    CooldownUpdate();
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        UpdatePeashooterFiring(&Peashooter[i]);
        UpdatePeashooterPeas(&Peashooter[i]);
        UpdatePeashooterFiring(&ICEPeashooter[i]);
        UpdatePeashooterPeas(&ICEPeashooter[i]);
    }
}
void DrawPlantsUnderZombie(void)
{
    DrawPlantsObject();
}
void DrawPlantsOverZombie(void)
{
    DrawPeashooterBullets();
    DrawPotatoMineExplosionEffect(PotatoMine);
}
void CooldownUpdate(void)
{
    if (CurrentLevelInfo->SunFlowertInfoLevel.IsAvailable && CurrentLevelInfo->SunFlowertInfoLevel.Lock)
    {
        CurrentLevelInfo->SunFlowertInfoLevel.Timer += GetFrameTime();
        if (CurrentLevelInfo->SunFlowertInfoLevel.Timer >= CurrentLevelInfo->SunFlowertInfoLevel.Cooldown)
        {
            CurrentLevelInfo->SunFlowertInfoLevel.Lock = false;
            CurrentLevelInfo->SunFlowertInfoLevel.Timer = 0;
        }
    }
    if (CurrentLevelInfo->PeashooterInfoLevel.IsAvailable && CurrentLevelInfo->PeashooterInfoLevel.Lock)
    {
        CurrentLevelInfo->PeashooterInfoLevel.Timer += GetFrameTime();
        if (CurrentLevelInfo->PeashooterInfoLevel.Timer >= CurrentLevelInfo->PeashooterInfoLevel.Cooldown)
        {
            CurrentLevelInfo->PeashooterInfoLevel.Lock = false;
            CurrentLevelInfo->PeashooterInfoLevel.Timer = 0;
        }
    }
    if (CurrentLevelInfo->IcePeashooterInfoLevel.IsAvailable && CurrentLevelInfo->IcePeashooterInfoLevel.Lock)
    {
        CurrentLevelInfo->IcePeashooterInfoLevel.Timer += GetFrameTime();
        if (CurrentLevelInfo->IcePeashooterInfoLevel.Timer >= CurrentLevelInfo->IcePeashooterInfoLevel.Cooldown)
        {
            CurrentLevelInfo->IcePeashooterInfoLevel.Lock = false;
            CurrentLevelInfo->IcePeashooterInfoLevel.Timer = 0;
        }
    }
    if (CurrentLevelInfo->ChompertInfoLevel.IsAvailable && CurrentLevelInfo->ChompertInfoLevel.Lock)
    {
        CurrentLevelInfo->ChompertInfoLevel.Timer += GetFrameTime();
        if (CurrentLevelInfo->ChompertInfoLevel.Timer >= CurrentLevelInfo->ChompertInfoLevel.Cooldown)
        {
            CurrentLevelInfo->ChompertInfoLevel.Lock = false;
            CurrentLevelInfo->ChompertInfoLevel.Timer = 0;
        }
    }
    if (CurrentLevelInfo->RosetInfoLevel.IsAvailable && CurrentLevelInfo->RosetInfoLevel.Lock)
    {
        CurrentLevelInfo->RosetInfoLevel.Timer += GetFrameTime();
        if (CurrentLevelInfo->RosetInfoLevel.Timer >= CurrentLevelInfo->RosetInfoLevel.Cooldown)
        {
            CurrentLevelInfo->RosetInfoLevel.Lock = false;
            CurrentLevelInfo->RosetInfoLevel.Timer = 0;
        }
    }
    if (CurrentLevelInfo->PotatoMineInfoLevel.IsAvailable && CurrentLevelInfo->PotatoMineInfoLevel.Lock)
    {
        CurrentLevelInfo->PotatoMineInfoLevel.Timer += GetFrameTime();
        if (CurrentLevelInfo->PotatoMineInfoLevel.Timer >= CurrentLevelInfo->PotatoMineInfoLevel.Cooldown)
        {
            CurrentLevelInfo->PotatoMineInfoLevel.Lock = false;
            CurrentLevelInfo->PotatoMineInfoLevel.Timer = 0;
        }
    }
}
void UpdatePlantsTimer(void)
{
    ResetSlowFactorZombies();
    ResetEffectiveFireRate();
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        UpdateSunFlower(&SunFlower[i]);
        UpdateRose(&Rose[i]);
        UpdateChomper(&Chomper[i]);
        UpdatePotatoMine(&PotatoMine[i]);
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
        if (ICEPeashooter[i].Base.isAlive)
        {
            DrawAnimatedObject(&ICEPeashooter[i].PeashooterObj, WHITE);
            DrawHpBar(&ICEPeashooter[i].Base.HpDisplay);
        }
        if (Rose[i].Base.isAlive)
        {
            DrawAnimatedObject(&Rose[i].RoseObj, WHITE);
            DrawTextureRec(LifetimeBar, Rose[i].LifetimeDisplay.frameBAR, Rose[i].LifetimeDisplay.posBar, WHITE);
            DrawHpBar(&Rose[i].Base.HpDisplay);
        }
        if (PotatoMine[i].Base.isAlive)
        {
            DrawAnimatedObject(&PotatoMine[i].PotatoMineObj, WHITE);
            if (!PotatoMine[i].Active)
                DrawTextureRec(LifetimeBar, PotatoMine[i].ActivationDisplay.frameBAR,
                               PotatoMine[i].ActivationDisplay.posBar, WHITE);
            DrawHpBar(&PotatoMine[i].Base.HpDisplay);
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
        if (ICEPeashooter[i].Base.isAlive)
        {
            UpdateAnimatedObject(&ICEPeashooter[i].PeashooterObj);
            UpdateHpBar(&ICEPeashooter[i].Base, CurrentLevelInfo->IcePeashooterInfoLevel.BaseHealth);
        }
        if (Chomper[i].Base.isAlive)
        {
            UpdateAnimatedObject(&Chomper[i].ChomperObj);
            UpdateHpBar(&Chomper[i].Base, CurrentLevelInfo->ChompertInfoLevel.BaseHealth);

            Chomper[i].LifetimeDisplay.TimePercentage = (Chomper[i].Lifespan / 20.0f) * 100.0f;
            UpdateLifetimeBar(&Chomper[i].LifetimeDisplay, Chomper[i].Lifespan, 20);
        }
        if (Rose[i].Base.isAlive)
        {
            UpdateAnimatedObject(&Rose[i].RoseObj);
            UpdateHpBar(&Rose[i].Base, CurrentLevelInfo->RosetInfoLevel.BaseHealth);
            UpdateLifetimeBar(&Rose[i].LifetimeDisplay, Rose[i].Lifespan, 10);
        }
        if (PotatoMine[i].Base.isAlive)
        {
            UpdateAnimatedObject(&PotatoMine[i].PotatoMineObj);
            UpdateHpBar(&PotatoMine[i].Base, CurrentLevelInfo->PotatoMineInfoLevel.BaseHealth);
            if (!PotatoMine[i].Active)
                UpdateLifetimeBar(&PotatoMine[i].ActivationDisplay, PotatoMine[i].Timer,
                                  CurrentLevelInfo->PotatoMineInfoLevel.ActivationTime);
        }
    }
}
void GeneratePlantBase(PlantBase *obj, PlantType Type, float HP, int X_Cell, int Y_Cell)
{
    obj->Health = HP;
    obj->X_Cell = X_Cell;
    obj->Y_Cell = Y_Cell;
    obj->HpDisplay.frameHP = (Rectangle){65 * 99, 0, 65, 5};
    obj->HpDisplay.posHP = (Vector2){322.5f / 305.0f * CurrentLevelInfo->START_X + X_Cell * RectangleWidth,
                                     238.0f / 230.f * CurrentLevelInfo->START_Y + Y_Cell * RectangleHeight};
    obj->HpDisplay.frameOverhealBar = (Rectangle){65 * 0, 0, 65, 3};
    obj->HpDisplay.posOverhealBar =
        (Vector2){322.5f / 305.0f * CurrentLevelInfo->START_X + X_Cell * RectangleWidth,
                  238.0f / 230.f * CurrentLevelInfo->START_Y - 3 + Y_Cell * RectangleHeight};
    obj->HpDisplay.HpPercentage = 100;
    obj->Type = Type;
    obj->isAlive = true;

    return;
}
void UpdateLifetimeBar(ActiveTimeBar *bar, float life, float maxLife)
{
    bar->TimePercentage = (life / maxLife) * 100.0f;

    int frame = (int)bar->TimePercentage - 1;
    if (frame < 0)
        frame = 0;
    if (frame > 99)
        frame = 99;

    bar->frameBAR = (Rectangle){65 * frame, 0, 65, 3};
}
