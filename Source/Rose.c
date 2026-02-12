#include "Rose.h"
#include "Chomper.h"
#include "Level1.h"
#include "Peashooter.h"
#include "Plant.h"
#include "PotatoMine.h"
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
RoseElement Rose[MAXNUMITEMS];

void ApplyRoseHealEffect(RoseElement *rose, PlantBase *Plant, float BaseHp)
{
    if (Plant->isAlive && Plant->Y_Cell == rose->Base.Y_Cell)
    {
        // ! اعمال درمان فقط در صورتی که سلامت کمتر از 150% حد پایه باشد
        if (Plant->Health < 1.5 * BaseHp)
        {
            // * افزایش 10 درصدی سلامت نسبت به مقدار فعلی
            Plant->Health = Plant->Health + 0.1f * Plant->Health;
            RowStatus[Plant->Y_Cell].rowChanged = true;
            RowStatus[Plant->Y_Cell].WeightChanged = true; // ? باعث تفکر مجدد زامبی متفکر میشود
        }
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
            // ! تقویت سرعت شلیک 20 درصد
            Peashooter[k].EffectiveFireRate *= 1.2f;
        }
    }
}
void RoseEffect(RoseElement *rose)
{

    rose->Timer += GetFrameTime();
    // ! رز در هر ثانیه فقط یک بار سلامتی را افزایش میدهد
    if (rose->Timer >= 1)
    {
        rose->Timer = 0;
        for (int i = 0; i < MAXNUMITEMS; i++)
        {
            ApplyRoseHealEffect(rose, &SunFlower[i].Base, CurrentLevelInfo->SunFlowertInfoLevel.BaseHealth);
            ApplyRoseHealEffect(rose, &Peashooter[i].Base, CurrentLevelInfo->PeashooterInfoLevel.BaseHealth);
            ApplyRoseHealEffect(rose, &Chomper[i].Base, CurrentLevelInfo->ChompertInfoLevel.BaseHealth);
            ApplyRoseHealEffect(rose, &PotatoMine[i].Base, CurrentLevelInfo->PotatoMineInfoLevel.BaseHealth);

            //  TODO: ???  ApplyRoseHealEffect(rose, &Rose[i].Base, CurrentLevelInfo->RosetInfoLevel.BaseHealth);
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
        RowStatus[rose->Base.Y_Cell].plantCount--;
        RowStatus[rose->Base.Y_Cell].rowChanged = true;
        RowStatus[rose->Base.Y_Cell].WeightChanged = true; // ? باعث تفکر مجدد زامبی متفکر میشود
    }
}

void GenerateRose(RoseElement *obj, int X_Cell, int Y_Cell)
{
    // * طول عمر هر رز
    obj->Lifespan = 10;
    obj->Timer = 0;

    // * مقداردهی مختصات برای رسم انیمیشن
    obj->RoseObj.posX = obj->RoseObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->RoseObj.posY = obj->RoseObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;

    // *   مقداردهی مختصات رسم نوار مربوط به طول عمر
    // !  با توجه به سلول های شبکه مپ
    obj->LifetimeDisplay.frameBAR = (Rectangle){65 * 99, 0, 65, 3};
    obj->LifetimeDisplay.posBar = (Vector2){322.5 / 305.0f * CurrentLevelInfo->START_X + X_Cell * RectangleWidth,
                                            238.0f / 230.f * CurrentLevelInfo->START_Y + 5 + Y_Cell * RectangleHeight};
    obj->LifetimeDisplay.TimePercentage = 100;

    // * فراخوانی تابع که ویژگی های پایه ای گیاه را میسازد
    GeneratePlantBase(&obj->Base, PLANT_ROSE, CurrentLevelInfo->RosetInfoLevel.BaseHealth, X_Cell, Y_Cell);

    return;
}