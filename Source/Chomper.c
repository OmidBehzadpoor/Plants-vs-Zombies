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

        if (zombieArray[j].isAlive && zombieArray[j].Markaz.x < END_X && zombieArray[j].Y_Cell == chomper->Base.Y_Cell)
        {
            zombieArray[j].slowFactor *= 2.0f / 3.0f; // هر چامپر 1/3 سرعت کم می‌کند
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
    }
}

void GenerateChomper(ChomperElement *obj, int X_Cell, int Y_Cell)
{
    obj->Lifespan = 20;
    obj->ChomperObj.posX = obj->ChomperObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->ChomperObj.posY = obj->ChomperObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;

    obj->LifetimeDisplay.frameBAR = (Rectangle){65 * 99, 0, 65, 3};
    obj->LifetimeDisplay.posBar = (Vector2){322.5 + X_Cell * 107.5, 243 + Y_Cell * 122};
    obj->LifetimeDisplay.LifetimePercentage = 100;
    GeneratePlantBase(&obj->Base, PLANT_CHOMPER, CurrentLevelInfo->ChompertInfoLevel.BaseHealth, X_Cell, Y_Cell);

    return;
}