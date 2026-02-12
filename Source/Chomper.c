#include "Chomper.h"
#include "Level1.h"
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
ChomperElement Chomper[MAXNUMITEMS];


void ChomperEffect(ChomperElement *chomper, Zombies *zombieArray, int count)
{
    for (int j = 0; j < count; j++)
    {
        // ! فقط به زامبی های درون شبکه سلولی بازی اثر دارد
        if (zombieArray[j].isAlive && zombieArray[j].Markaz.x < CurrentLevelInfo->END_X &&
            zombieArray[j].Y_Cell == chomper->Base.Y_Cell)
        {
            // ? slowFactor
            // ? در سرعت پایه ضرب میشود
            zombieArray[j].slowFactor *= 2.0f / 3.0f; // هر چامپر 1/3 سرعت را کم می‌کند
        }
    }
}
void UpdateChomper(ChomperElement *chomper)
{
    if (!chomper->Base.isAlive)
    {
        return;
    }

    ChomperEffect(chomper, ZombieNormal, CurrentLevelInfo->MaxZombieNormalAllowed);
    ChomperEffect(chomper, ThinkingZombie, CurrentLevelInfo->MaxThinkingZombieAllowed);

    chomper->Lifespan -= GetFrameTime();
    if (chomper->Lifespan <= 0)
    {
        chomper->Base.isAlive = false;
        CellContent[chomper->Base.Y_Cell][chomper->Base.X_Cell] = EMPTY;
        RowStatus[chomper->Base.Y_Cell].plantCount--;
        RowStatus[chomper->Base.Y_Cell].rowChanged = true;
        RowStatus[chomper->Base.Y_Cell].WeightChanged = true; // ? باعث تفکر مجدد زامبی متفکر میشود
    }
}

void GenerateChomper(ChomperElement *obj, int X_Cell, int Y_Cell)
{
    // * طول عمر هر چامپر
    obj->Lifespan = 20;

    // * مقداردهی مختصات برای رسم انیمیشن
    obj->ChomperObj.posX = obj->ChomperObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->ChomperObj.posY = obj->ChomperObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;

    // *   مقداردهی مختصات رسم نوار مربوط به طول عمر
    // !  با توجه به سلول های شبکه مپ
    obj->LifetimeDisplay.frameBAR = (Rectangle){65 * 99, 0, 65, 3};
    obj->LifetimeDisplay.posBar = (Vector2){322.5 / 305.0f * CurrentLevelInfo->START_X + X_Cell * RectangleWidth,
                                            238.0f / 230.f * CurrentLevelInfo->START_Y + 5 + Y_Cell * RectangleHeight};
    obj->LifetimeDisplay.TimePercentage = 100;

    // * فراخوانی تابع که ویژگی های پایه ای گیاه را میسازد
    GeneratePlantBase(&obj->Base, PLANT_CHOMPER, CurrentLevelInfo->ChompertInfoLevel.BaseHealth, X_Cell, Y_Cell);

    return;
}