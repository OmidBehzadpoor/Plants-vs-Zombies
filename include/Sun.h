#pragma once
#ifndef SUN_H
#define SUN_H
#include "Level1.h"
#include "gif.h"
typedef struct SunElement
{
    AnimatedObject sun;
    float time;
    bool Available;
} SunElement;
extern int CurrentSunIndex;
extern SunElement SunElementArray[MAXSUNELEMENT];
void CollectSunElement(void);
void GenerateSun(SunElement *obj, int x, int y);
void UpdateSUNELEMENT(void);
void DrawSunElement(void);
#endif