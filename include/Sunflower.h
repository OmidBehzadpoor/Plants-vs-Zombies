#pragma once
#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include "Plant.h"
#include"Level1.h"
typedef struct SunflowerElement
{
    AnimatedObject SunFlowerObj;
    PlantBase Base;
    float Cooldown;
} SunflowerElement;
extern SunflowerElement SunFlower[MAXNUMITEMS];

void GenerateSunFlower(SunflowerElement *obj, int X_Cell, int Y_Cell);


#endif