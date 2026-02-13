#include "Sun.h"
#include "Chomper.h"
#include "Level1.h"
#include "Peashooter.h"
#include "Plant.h"
#include "Rose.h"
#include "SoundandMusic.h"
#include "Sunflower.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
SunElement SunElementArray[MAXSUNELEMENT];
int CurrentSunIndex = 0;

void GenerateSun(SunElement *obj, int x, int y)
{
    if (x == GENERATERANDOM && y == GENERATERANDOM)
    {
        int xstart = rand() % (SCREEN_WIDTH - 80);  //  کمتر از  طول صفحه باشد تا از کادر خارج نشود
        int yfinal = rand() % (SCREEN_HEIGHT - 80); //  کمتر از  عرض صفحه باشد تا از کادر خارج نشود
        obj->sun.posY = 0;
        obj->sun.speedY = 45;
        obj->sun.posX = obj->sun.finalX = xstart;
        obj->sun.finalY = yfinal;
        obj->Available = true;
        obj->time = 0;
        return;
    }
    else
    {
        int rand1 = rand() % 2;
        obj->sun.posY = y - 40;
        if (rand1)
        {
            obj->sun.posX = x + 30;
        }
        else
        {
            obj->sun.posX = x - 30;
        }
        obj->sun.speedY = 5;

        obj->sun.finalX = x;
        obj->sun.finalY = y + 35;
        obj->Available = true;
        obj->time = 0;
        return;
    }
}

void CollectSunElement(void)
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }
    Vector2 MousePos = GetMousePosition();

    for (int i = 0; i < MAXSUNELEMENT; i++)
    {

        if (SunElementArray[i].Available)
        {
            if (MousePos.x >= SunElementArray[i].sun.posX &&
                MousePos.x <= SunElementArray[i].sun.posX + SunElementArray[i].sun.frames[0].width &&
                MousePos.y >= SunElementArray[i].sun.posY &&
                MousePos.y <= SunElementArray[i].sun.posY + SunElementArray[i].sun.frames[0].height)
            {
                SunElementArray[i].Available = false;
                SunBank += CurrentLevelInfo->SunElementInfoLevel.Value;
                PlaySound(CollectSound);
            }
        }
    }
}
void DrawSunElement(void)
{
    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        if (SunElementArray[i].Available == true)
        {
            DrawAnimatedObject(&SunElementArray[i].sun, WHITE);
        }
    }
}

void UpdateSUNELEMENT(void)
{
    CollectSunElement();
    SunTimer += GetFrameTime();
    if (SunTimer >= CurrentLevelInfo->SunElementInfoLevel.Regenerate)
    {
        SunTimer = 0 + ((float)rand() / (float)RAND_MAX) * (2.5/12 * CurrentLevelInfo->SunElementInfoLevel.Regenerate);

        GenerateSun(&SunElementArray[CurrentSunIndex], GENERATERANDOM, GENERATERANDOM);
        CurrentSunIndex = (CurrentSunIndex + 1) % MAXSUNELEMENT;
    }
    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        if (SunElementArray[i].Available == true)
        {
            UpdateAnimatedObject(&SunElementArray[i].sun);
            SunElementArray[i].time += GetFrameTime();
            if (SunElementArray[i].time >= CurrentLevelInfo->SunElementInfoLevel.DisplayTime)
            {
                SunElementArray[i].Available = false;
            }
        }
    }
}