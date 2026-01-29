#include "Level1.h"
#include "SoundandMusic.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chomper.h"
#include "Peashooter.h"
#include "Rose.h"
#include "Sunflower.h"
#include "Sun.h"
#include "Plant.h"
SunflowerElement SunFlower[MAXNUMITEMS];
void GenerateSunFlower(SunflowerElement *obj, int X_Cell, int Y_Cell)
{
    obj->Cooldown = 30;
    obj->SunFlowerObj.posX = obj->SunFlowerObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->SunFlowerObj.posY = obj->SunFlowerObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;

    GeneratePlantBase(&obj->Base, PLANT_SUNFLOWER, CurrentLevelInfo->SunFlowertInfoLevel.BaseHealth, X_Cell, Y_Cell);

    return;
}