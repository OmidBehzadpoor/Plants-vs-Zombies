#include "Level1.h"
#include "Chomper.h"
#include "Diamond.h"
#include "LawnMower.h"
#include "LevelBase.h"
#include "LevelUi.h"
#include "Peashooter.h"
#include "Plant.h"
#include "PotatoMine.h"
#include "Rose.h"
#include "Shop.h"
#include "SoundandMusic.h"
#include "Sun.h"
#include "Sunflower.h"
#include "Zombie.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void CellularNetworkMap(void)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            char Coordinates[16];
            sprintf(Coordinates, "(%d , %d)", i + 1, j + 1);
            DrawRectangleLinesEx(MapCell[i][j], 1, WHITE);
            DrawText(Coordinates, MapCell[i][j].x + 5, MapCell[i][j].y + 5, 20, RED);
        }
    }
}
void DrawDebug(void)
{

    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++) // for debug
    {
        if (ZombieNormal[i].isAlive)
        {
            DrawText("O", ZombieNormal[i].ZombieObj.posX + ZombieNormal[i].ZombieObj.frames[0].width / 2,
                     ZombieNormal[i].ZombieObj.posY + ZombieNormal[i].ZombieObj.frames[0].height / 2, 20, RED);
            DrawRectangleLines((int)ZombieNormal[i].CollisionBox.x, (int)ZombieNormal[i].CollisionBox.y,
                               (int)ZombieNormal[i].CollisionBox.width, (int)ZombieNormal[i].CollisionBox.height, RED);
        }
    }
    for (int i = 0; i < CurrentLevelInfo->MaxThinkingZombieAllowed; i++) // for debug
    {
        if (ThinkingZombie[i].isAlive)
        {
            DrawText("O", ThinkingZombie[i].ZombieObj.posX + ThinkingZombie[i].ZombieObj.frames[0].width / 2,
                     ThinkingZombie[i].ZombieObj.posY + ThinkingZombie[i].ZombieObj.frames[0].height / 2, 20, RED);
            DrawRectangleLines((int)ThinkingZombie[i].CollisionBox.x, (int)ThinkingZombie[i].CollisionBox.y,
                               (int)ThinkingZombie[i].CollisionBox.width, (int)ThinkingZombie[i].CollisionBox.height,
                               RED);
        }
    }
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            if (Peashooter[i].Pea[k].isActive)
            {
                DrawCircleLines((int)Peashooter[i].Pea[k].Markaz.x, (int)Peashooter[i].Pea[k].Markaz.y,
                                Peashooter[i].Pea[k].Radius, BLUE);
            }
        }
    }

    CellularNetworkMap(); // for debug.

    /*
    Rectangle frame = {65 * 99, 0, 65, 5};
    Rectangle frame1 = {65 * 25, 0, 65, 3};
    Rectangle frame2 = {65 * 50, 0, 65, 5};
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < 10; j++)
        {

            Vector2 pos = {322.5 + j * 107.5, 238 + i * 122};
            Vector2 pos1 = {322.5 + j * 107.5, 235 + i * 122};
            Vector2 pos2 = {322.5 + j * 107.5, 243 + i * 122};
            DrawTextureRec(HpBar, frame, pos, WHITE);
            DrawTextureRec(OverhealBar, frame1, pos1, WHITE);
            DrawTextureRec(LifetimeBar, frame2, pos2, WHITE);

        }

    }
    */
}
void MouseSelection(void)
{
    Vector2 mousePos = GetMousePosition();
    char coordText[50];
    sprintf(coordText, "X: %.0f, Y: %.0f", mousePos.x, mousePos.y);

    DrawText(coordText, 10, 850, 40, RED);
}