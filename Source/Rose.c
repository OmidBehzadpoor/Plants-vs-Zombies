#include "Level1.h"
#include "SoundandMusic.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Zombie.h"
#include "Chomper.h"
#include "Peashooter.h"
#include "Rose.h"
#include "Sunflower.h"
#include "Sun.h"
#include "Plant.h"
RoseElement Rose[MAXNUMITEMS];

void ApplyRoseHealEffect(RoseElement *rose, PlantBase *Plant, float BaseHp)
{
    if (Plant->isAlive && Plant->Y_Cell == rose->Base.Y_Cell)
    {
        Plant->Health = Plant->Health + 0.1f * Plant->Health;
        if (Plant->Health >= 1.5 * BaseHp)
        {
            Plant->Health = 1.5 * BaseHp;
        }
    }
}
void ApplyRoseFireingEffect(RoseElement *rose)
{
    for (int k = 0; k < MAXNUMITEMS; k++)
    {
        if (Peashooter[k].Base.isAlive && Peashooter[k].Base.Y_Cell == rose->Base.Y_Cell)
        {
            Peashooter[k].EffectiveFireRate *= 1.2f;
        }
    }
}
void RoseEffect(RoseElement *rose)
{

    rose->Timer += GetFrameTime();
    if (rose->Timer >= 1)
    {
        rose->Timer = 0;
        for (int i = 0; i < MAXNUMITEMS; i++)
        {
            ApplyRoseHealEffect(rose, &SunFlower[i].Base, CurrentLevelInfo->SunFlowertInfoLevel.BaseHealth);
            ApplyRoseHealEffect(rose, &Peashooter[i].Base, CurrentLevelInfo->PeashooterInfoLevel.BaseHealth);
            ApplyRoseHealEffect(rose, &Chomper[i].Base, CurrentLevelInfo->ChompertInfoLevel.BaseHealth);
            ApplyRoseHealEffect(rose, &Rose[i].Base, CurrentLevelInfo->RosetInfoLevel.BaseHealth);
        }
    }

    ApplyRoseFireingEffect(rose);
}
void UpdateRose(RoseElement *rose)
{
    if (!rose->Base.isAlive)
    {
        return;
    }
    RoseEffect(rose);
    rose->Lifespan -= GetFrameTime();
    if (rose->Lifespan <= 0)
    {
        rose->Base.isAlive = false;
        CellContent[rose->Base.Y_Cell][rose->Base.X_Cell] = EMPTY;
    }
}

void GenerateRose(RoseElement *obj, int X_Cell, int Y_Cell)
{

    obj->Lifespan = 10;
    obj->RoseObj.posX = obj->RoseObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->RoseObj.posY = obj->RoseObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;

    obj->Timer = 0;

    obj->LifetimeDisplay.frameBAR = (Rectangle){65 * 99, 0, 65, 3};
    obj->LifetimeDisplay.posBar = (Vector2){322.5 + X_Cell * 107.5, 243 + Y_Cell * 122};
    obj->LifetimeDisplay.LifetimePercentage = 100;
    GeneratePlantBase(&obj->Base, PLANT_ROSE, CurrentLevelInfo->RosetInfoLevel.BaseHealth, X_Cell, Y_Cell);

    return;
}