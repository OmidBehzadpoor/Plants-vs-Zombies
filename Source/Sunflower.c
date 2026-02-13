#include "Sunflower.h"
#include "Chomper.h"
#include "Level1.h"
#include "Peashooter.h"
#include "Plant.h"
#include "Rose.h"
#include "SoundandMusic.h"
#include "Sun.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
SunflowerElement SunFlower[MAXNUMITEMS];
void GenerateSunFlower(SunflowerElement *obj, int X_Cell, int Y_Cell)
{
    // * فاصله زمانی بین ساختن نور خورشید
    obj->Cooldown = GENERATESUN -5;

    // * مقداردهی مختصات برای رسم انیمیشن
    obj->SunFlowerObj.posX = obj->SunFlowerObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->SunFlowerObj.posY = obj->SunFlowerObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;

    // * فراخوانی تابع که ویژگی های پایه ای گیاه را میسازد
    GeneratePlantBase(&obj->Base, PLANT_SUNFLOWER, CurrentLevelInfo->SunFlowertInfoLevel.BaseHealth, X_Cell, Y_Cell);

    return;
}
void UpdateSunFlower(SunflowerElement *SunFlower)
{
    if (!SunFlower->Base.isAlive)
    {
        return;
    }
    SunFlower->Cooldown -= GetFrameTime();
    if (SunFlower->Cooldown <= 0)
    {
        if (!CurrentLevelInfo->ZombieNormal.InfiniteSpan && !CurrentLevelInfo->ThinkingZombie.InfiniteSpan)
        {
            SunFlower->Cooldown = GENERATESUN - (((float)rand() / (float)RAND_MAX) * 2.0f) +
                                 ( 11.0f * (ZombiesSpawned / (CurrentLevelInfo->MaxThinkingZombieAllowed +
                                                            CurrentLevelInfo->MaxZombieNormalAllowed)));
        }
        else
        {
            SunFlower->Cooldown = GENERATESUN - ((float)rand() / (float)RAND_MAX) * 2.0f  ;
        }
        GenerateSun(&SunElementArray[CurrentSunIndex], SunFlower->SunFlowerObj.posX, SunFlower->SunFlowerObj.posY);
        CurrentSunIndex = (CurrentSunIndex + 1) % MAXSUNELEMENT;
    }
}