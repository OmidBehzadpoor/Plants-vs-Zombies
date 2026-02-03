
#include "LawnMower.h"
#include "Level1.h"
#include "Plant.h"
#include "SoundandMusic.h"
#include "Sun.h"
#include "Zombie.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
LawnMowerElement LawnMower[ROWLAWNMOWER];

void DrawLawnMowers(void)
{
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        if (LawnMower[i].LawnMowerObj.posX == LawnMower[i].LawnMowerObj.finalX && CellContent[i][0] == LAWNMOWER)
        {

            DrawTexture(OFFlawnMowerRow, LawnMower[i].LawnMowerObj.finalX, LawnMower[i].LawnMowerObj.finalY, WHITE);
        }
        else if (LawnMower[i].isActive)
        {
            DrawAnimatedObject(&LawnMower[i].LawnMowerObj, WHITE);
        }
    }
}
void UpdateLawnMowers(void)
{
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        if (LawnMower[i].isActive)
        {
            if (LawnMower[i].Markaz.x >= END_X || LawnMower[i].LawnMowerObj.posX == LawnMower[i].LawnMowerObj.finalX)
            {
                LawnMower[i].isActive = false;
            }
            KillAllZombiesInCell(LawnMower[i].Y_Cell, LawnMower[i].X_Cell);
            LawnMower[i].Markaz.x = LawnMower[i].LawnMowerObj.posX + LawnMower[i].LawnMowerObj.frames[0].width / 2;
            LawnMower[i].Markaz.y = LawnMower[i].LawnMowerObj.posY + LawnMower[i].LawnMowerObj.frames[0].height / 2;
            UpdateAnimatedObject(&LawnMower[i].LawnMowerObj);
            LawnMower[i].X_Cell = (LawnMower[i].Markaz.x - START_X) / (RectangleWidth);
        }
    }
}

void ActivateLawnMower(int Row)
{
    CellContent[Row][0] = EMPTY;
    RowStatus[Row].WeightChanged = true;

    ResetAnimatedObject(&LawnMower[Row].LawnMowerObj);

    LawnMower[Row].LawnMowerObj = GenerateAnimatedObject(&LawnMowerSheet, 70, 57, 80, 320, 270 + RectangleHeight * Row,
                                                         500, 0, END_X, 270 + RectangleHeight * Row);
    LawnMower[Row].isActive = true;
    PlaySound(LawnmowerSound);
}
void CheckLawnMowerCollision(Zombies *zombie)
{
    if (zombie->Markaz.x >= END_X || !zombie->isAlive)
    {
        return;
    }
    if (CellContent[zombie->Y_Cell][zombie->X_Cell] == LAWNMOWER)
    {
        ActivateLawnMower(zombie->Y_Cell);
    }
}