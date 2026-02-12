#include "PotatoMine.h"
#include "Chomper.h"
#include "Diamond.h"
#include "Level1.h"
#include "Peashooter.h"
#include "Plant.h"
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
PotatoMineElement PotatoMine[MAXNUMITEMS];
void GeneratePotatoMine(PotatoMineElement *obj, int X_Cell, int Y_Cell)
{
    ResetAnimatedObject(&obj->PotatoMineObj);
    obj->PotatoMineObj = GenerateAnimatedObject(&PotatoMineNotReadyPic, 75, 55, 80, 0, 0, 0, 0, 0, 0);
    obj->PotatoMineObj.posX = obj->PotatoMineObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->PotatoMineObj.posY = obj->PotatoMineObj.finalY = MapCell[Y_Cell][X_Cell].y + 25;
    obj->ActivationDisplay.frameBAR = (Rectangle){65 * 99, 0, 65, 3};
    obj->ActivationDisplay.posBar =
        (Vector2){322.5 / 305.0f * CurrentLevelInfo->START_X + X_Cell * RectangleWidth,
                  238.0f / 230.f * CurrentLevelInfo->START_Y + 5 + Y_Cell * RectangleHeight};
    obj->ActivationDisplay.TimePercentage = 0;
    obj->Timer = 0;
    obj->Active = false;
    obj->TamirShowsExplosion = 0;
    obj->Explosion = false;
    GeneratePlantBase(&obj->Base, PLANT_POTATOMINE, CurrentLevelInfo->PotatoMineInfoLevel.BaseHealth, X_Cell, Y_Cell);

    return;
}
void UpdatePotatoMine(PotatoMineElement *PotatoMine)
{
    UpdatePotatoMineExplosionEffect(PotatoMine);

    if (!PotatoMine->Base.isAlive)
    {
        return;
    }
    if (!PotatoMine->Active)
    {
        PotatoMine->Timer += GetFrameTime();
        if (PotatoMine->Timer >= CurrentLevelInfo->PotatoMineInfoLevel.ActivationTime)
        {
            PotatoMine->Active = true;
            ResetAnimatedObject(&PotatoMine->PotatoMineObj);
            PotatoMine->PotatoMineObj = GenerateAnimatedObject(
                &PotatoMineSheet, 75, 55, 80, PotatoMine->PotatoMineObj.posX, PotatoMine->PotatoMineObj.posY,
                PotatoMine->PotatoMineObj.speedX, PotatoMine->PotatoMineObj.speedY, PotatoMine->PotatoMineObj.finalX,
                PotatoMine->PotatoMineObj.finalY);
        }
    }
    PotatoMineExplosion(PotatoMine);
}
void PotatoMineExplosion(PotatoMineElement *PotatoMine)
{
    if (!PotatoMine->Active || !PotatoMine->Base.isAlive)
    {
        return;
    }
    Zombies *finalTarget = NULL;
    float minX = 2000.0f;
    int Chancepercentage = 0;
    for (int j = 0; j < CurrentLevelInfo->MaxZombieNormalAllowed; j++)
    {
        if (!ZombieNormal[j].isAlive || ZombieNormal[j].Markaz.x > CurrentLevelInfo->END_X ||
            ZombieNormal[j].Y_Cell != PotatoMine->Base.Y_Cell)
            continue;

        bool Explosion = false;
        if (ZombieNormal[j].X_Cell == PotatoMine->Base.X_Cell)
        {
            Explosion = true;
        }
        if (Explosion && ZombieNormal[j].Markaz.x < minX)
        {
            minX = ZombieNormal[j].Markaz.x;
            finalTarget = &ZombieNormal[j];
            Chancepercentage = 10;
        }
    }

    for (int j = 0; j < CurrentLevelInfo->MaxThinkingZombieAllowed; j++)
    {
        if (!ThinkingZombie[j].isAlive || ThinkingZombie[j].Markaz.x >= CurrentLevelInfo->END_X ||
            ThinkingZombie[j].Y_Cell != PotatoMine->Base.Y_Cell)
            continue;

        bool Explosion = false;
        if (ThinkingZombie[j].X_Cell == PotatoMine->Base.X_Cell)
        {
            Explosion = true;
        }

        if (Explosion && ThinkingZombie[j].Markaz.x < minX)
        {
            minX = ThinkingZombie[j].Markaz.x;
            finalTarget = &ThinkingZombie[j]; // آدرس زامبی نوع ۲ را ذخیره کن
            Chancepercentage = 25;
        }
    }
    if (finalTarget != NULL)
    {
        finalTarget->isAlive = false;
        PotatoMine->Explosion = true;
        ZombiesKilled++;
        CreatingDiamondLuck(DiamondElementArray, finalTarget->Markaz.x, finalTarget->Markaz.y, Chancepercentage);
        CellContent[PotatoMine->Base.Y_Cell][PotatoMine->Base.X_Cell] = EXPLODEDPOTATOMINE;
        RowStatus[PotatoMine->Base.Y_Cell].plantCount--;
        RowStatus[PotatoMine->Base.Y_Cell].rowChanged = true;
        RowStatus[PotatoMine->Base.Y_Cell].WeightChanged = true;
        PotatoMine->Base.isAlive = false;
    }
}
void UpdatePotatoMineExplosionEffect(PotatoMineElement *PotatoMine)
{
    if (!PotatoMine->Explosion)
    {
        return;
    }
    PotatoMine->TamirShowsExplosion += GetFrameTime();
    if (PotatoMine->TamirShowsExplosion > 2)
    {
        PotatoMine->Explosion = false;
        CellContent[PotatoMine->Base.Y_Cell][PotatoMine->Base.X_Cell] = EMPTY;
    }
}
void DrawPotatoMineExplosionEffect(PotatoMineElement *PotatoMine)
{
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (PotatoMine[i].Explosion)
        {
            DrawTexture(PotatoMineMashedPic, PotatoMine[i].PotatoMineObj.posX - 10,
                        PotatoMine[i].PotatoMineObj.posY + 15, WHITE);

            DrawTexture(ExplosionSpudow, PotatoMine[i].PotatoMineObj.posX - 15, PotatoMine[i].PotatoMineObj.posY - 15,
                        WHITE);
        }
    }
}