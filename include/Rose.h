#pragma once
#ifndef ROSE_H
#define ROSE_H
#include "Plant.h"
#include"Level1.h"
typedef struct RoseElement
{
    AnimatedObject RoseObj;
    ActiveTimeBar LifetimeDisplay;
    PlantBase Base;
    float Lifespan;
    float Timer;
} RoseElement;
extern RoseElement Rose[MAXNUMITEMS];

void ApplyRoseHealEffect(RoseElement *rose, PlantBase *Plant, float BaseHp);
void RoseEffect(RoseElement *rose);
void ApplyRoseFireingEffect(RoseElement *rose);
void UpdateRose(RoseElement *rose);
void GenerateRose(RoseElement *obj, int X_Cell, int Y_Cell);
#endif