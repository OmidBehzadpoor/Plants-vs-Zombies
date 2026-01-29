#pragma once
#ifndef CHOMPER_H
#define CHOMPER_H
#include "Plant.h"
#include"Level1.h"
typedef struct Zombies Zombies ;
typedef struct ChomperElement
{
    AnimatedObject ChomperObj;
    ActiveTimeBar LifetimeDisplay;
    PlantBase Base;
    float Lifespan;
} ChomperElement;
extern ChomperElement Chomper[MAXNUMITEMS];
void ChomperEffect(ChomperElement *chomper , Zombies *zombieArray, int count);
void UpdateChomper(ChomperElement *chomper);
void GenerateChomper(ChomperElement *obj, int X_Cell, int Y_Cell);
#endif