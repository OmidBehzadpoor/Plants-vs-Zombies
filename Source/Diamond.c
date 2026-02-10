#include "Diamond.h"
#include "Shop.h"
#include "SoundandMusic.h"
#include "raylib.h"
DiamondElement DiamondElementArray[10];
void CreatingDiamondLuck(DiamondElement *obj, int x, int y, int Chancepercentage)
{
    int Num = rand();
    if (Num % 100 < Chancepercentage)
    {
        GenerateDiamond(obj, x, y);
    }
}
void GenerateDiamond(DiamondElement *obj, int x, int y)
{
    DiamondElement *target = NULL;
    for (int i = 0; i < 10; i++)
    {
        if (!obj[i].Available)
        {
            target = &obj[i];
            break;
        }
    }
    if (target == NULL)
        return;
    if (x == GENERATERANDOM && y == GENERATERANDOM)
    {
        x = CurrentLevelInfo->START_X + rand() % (CurrentLevelInfo->END_X - CurrentLevelInfo->START_X);
        y = CurrentLevelInfo->START_Y + rand() % (CurrentLevelInfo->END_Y - CurrentLevelInfo->START_Y);
    }

    int rand1 = rand() % 2;
    target->Diamond.posY = y - 40;
    if (rand1)
    {
        target->Diamond.posX = x;
    }
    else
    {
        target->Diamond.posX = x - 10;
    }
    target->Diamond.speedY = 30;

    target->Diamond.finalX = x;
    target->Diamond.finalY = y + 35;
    target->Available = true;
    target->IsCollected = false;
    target->DiamondBankDisplayTimer = 0;
    target->Time = 0;
    return;
}

void CollectDiamondElement(void)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 MousePos = GetMousePosition();

        for (int i = 0; i < 10; i++)
        {

            if (DiamondElementArray[i].Available && !DiamondElementArray[i].IsCollected)
            {
                if (MousePos.x >= DiamondElementArray[i].Diamond.posX &&
                    MousePos.x <=
                        DiamondElementArray[i].Diamond.posX + DiamondElementArray[i].Diamond.frames[0].width &&
                    MousePos.y >= DiamondElementArray[i].Diamond.posY &&
                    MousePos.y <= DiamondElementArray[i].Diamond.posY + DiamondElementArray[i].Diamond.frames[0].height)
                {
                    PlaySound(CollectSound);
                    DiamondElementArray[i].IsCollected = true;
                    //   DrawTexture(MapDiamond, 31, 105, WHITE);
                    DiamondElementArray[i].Diamond.finalX = 31;
                    DiamondElementArray[i].Diamond.finalY = 105;

                    DiamondElementArray[i].Diamond.speedX = (31 - DiamondElementArray[i].Diamond.posX) / 1.5;
                    DiamondElementArray[i].Diamond.speedY = (105 - DiamondElementArray[i].Diamond.posY) / 1.5;
                }
            }
        }
    }
}
void DrawDiamondElement(void)
{
    for (int i = 0; i < 10; i++)
    {
        if (DiamondElementArray[i].Available)
        {
            DrawAnimatedObject(&DiamondElementArray[i].Diamond, WHITE);
        }
    }
}

void UpdateDiamondElement(void)
{
    CollectDiamondElement();

    for (int i = 0; i < 10; i++)
    {
        if (DiamondElementArray[i].Available)
        {
            UpdateAnimatedObject(&DiamondElementArray[i].Diamond);
            DiamondElementArray[i].Time += GetFrameTime();
            if (DiamondElementArray[i].Time >= CurrentLevelInfo->DiamondElementInfoLevel.DisplayTime &&
                !DiamondElementArray[i].IsCollected)
            {
                DiamondElementArray[i].Available = false;
            }
            if (DiamondElementArray[i].IsCollected)
            {
                if (DiamondElementArray[i].Diamond.posX == DiamondElementArray[i].Diamond.finalX &&
                    DiamondElementArray[i].Diamond.posY == DiamondElementArray[i].Diamond.finalY)
                {
                    DiamondBank += CurrentLevelInfo->DiamondElementInfoLevel.Value;
                    SaveGame();
                    DiamondElementArray[i].Available = false;
                }
            }
        }
        else
        {
            if (DiamondElementArray[i].IsCollected)
            {
                DiamondElementArray[i].DiamondBankDisplayTimer += GetFrameTime();
                if (DiamondElementArray[i].DiamondBankDisplayTimer >= 1)
                {
                    DiamondElementArray[i].DiamondBankDisplayTimer = 0;
                    DiamondElementArray[i].IsCollected = false;
                }
            }
        }
    }
}