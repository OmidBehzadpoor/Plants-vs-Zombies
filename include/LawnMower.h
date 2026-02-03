#pragma once
#ifndef LAWNMOWER_H
#define LAWNMOWER_H
#include "raylib.h"
#include "Level1.h"
#include "gif.h"
typedef struct Zombies Zombies;
typedef struct LawnMowerElement
{
    AnimatedObject LawnMowerObj;
    int X_Cell;
    int Y_Cell;
    Vector2 Markaz;
    bool isActive;
    bool Available;
} LawnMowerElement;
extern LawnMowerElement LawnMower[ROWLAWNMOWER];

void UpdateLawnMowers(void);
void UpdateLawnMowers(void);
void CheckLawnMowerCollision(Zombies *zombie);
void DrawLawnMowers(void);
void ActivateLawnMower(int Row);

#endif