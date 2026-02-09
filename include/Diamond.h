#pragma once
#ifndef DIAMOND_H
#define DIAMOND_H
#include "Level1.h"
typedef struct DiamondElement
{
    AnimatedObject Diamond;
    float Time;
    bool Available;
    bool IsCollected;
    float DiamondBankDisplayTimer;
} DiamondElement;
extern DiamondElement DiamondElementArray[10];
void CreatingDiamondLuck(DiamondElement *obj, int x, int y, int Chancepercentage);
void GenerateDiamond(DiamondElement *obj, int x, int y);
void CollectDiamondElement(void);
void DrawDiamondElement(void);
void UpdateDiamondElement(void);
#endif