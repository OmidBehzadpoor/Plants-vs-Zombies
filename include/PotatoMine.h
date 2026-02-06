#pragma once
#ifndef POTATOMINE_H
#define POTATOMINE_H
#include "Level1.h"
#include "Plant.h"
typedef struct Zombies Zombies;
typedef struct PotatoMineElement
{
    AnimatedObject PotatoMineObj;
    PlantBase Base;
    ActiveTimeBar ActivationDisplay;
    float Timer;
    bool Active;
    bool Explosion;
    float TamirShowsExplosion;
} PotatoMineElement;
extern PotatoMineElement PotatoMine[MAXNUMITEMS];
void GeneratePotatoMine(PotatoMineElement *obj, int X_Cell, int Y_Cell);
void UpdatePotatoMine(PotatoMineElement *PotatoMine);
void PotatoMineExplosion(PotatoMineElement *PotatoMine);
void UpdatePotatoMineExplosionEffect(PotatoMineElement *PotatoMine);
void DrawPotatoMineExplosionEffect(PotatoMineElement *PotatoMine);
#endif