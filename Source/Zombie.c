#include "Zombie.h"
#include "Chomper.h"
#include "Level1.h"
#include "Peashooter.h"
#include "Plant.h"
#include "Rose.h"
#include "SoundandMusic.h"
#include "Sun.h"
#include "Sunflower.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Zombies ZombieNormal[MAXNUZOMBIES];

void DrawZombies(void)
{
    DrawZombiesObject(ZombieNormal, CurrentLevelInfo->MaxZombieNormalAllowed);
}

void UpdateZombies(void)
{

    SpawnZombie(ZombieNormal, CurrentLevelInfo->MaxZombieNormalAllowed, &ZombieTimer,
                CurrentLevelInfo->ZombieNormal.Regenerate, CurrentLevelInfo->MaxZombieNormalAllowed);
    // printf("%d\n", ZombiesSpawned);
    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++)
    {

        UpdateZombieMovement(&ZombieNormal[i]);
        ZombiesAttackPlants(&ZombieNormal[i]);
        EnableZombieAttack(&ZombieNormal[i], &ZombieNormalAttack1, 107, 122);
        ZombiesAttackPlants(&ZombieNormal[i]);
        DisableZombieAttack(&ZombieNormal[i], &ZombieNormal1, 107, 122);
        CheckLawnMowerCollision(&ZombieNormal[i]);
    }

    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++)
    {
        if (ZombieNormal[i].isAlive && ZombieNormal[i].Attack && ZombieNormal[i].Markaz.x <= END_X)
        {
            PlayEatSound(&plantEatSoundPlayed);
            break;
        }
    }
    UpdateEatSound(&plantEatSoundPlayed);
}
void DrawZombiesObject(Zombies *ZombiesType, int MaxCount)
{
    for (int i = 0; i < MaxCount; i++)
    {
        if (ZombiesType[i].isAlive)
        {
            DrawAnimatedObject(&ZombiesType[i].ZombieObj, WHITE);
        }
    }
}

bool IsZombieSpawnTime(float *timer, float regenerateTime)
{
    *timer += GetFrameTime();
    if (*timer >= regenerateTime)
    {
        *timer = 0;
        return true;
    }
    return false;
}
int GetFreeZombieIndex(Zombies *ZombiesType, int MaxCount)
{
    {
        for (int i = 0; i < MaxCount; i++)
        {
            if (!ZombiesType[i].isAlive)
                return i;
        }
        return -1;
    }
}
void SpawnZombie(Zombies *ZombiesType, int MaxCount, float *zombieTimer, float regenerateTime, float MaxSpawnCount)
{
    if (!IsZombieSpawnTime(zombieTimer, regenerateTime))
    {
        return;
    }
    int FreeIndex = GetFreeZombieIndex(ZombiesType, MaxCount);
    if (FreeIndex < 0)
    {
        return;
    }
    if (ZombiesSpawned < MaxSpawnCount || MaxSpawnCount == INFINITE)
    {
        if (ZombiesSpawned == 0)
        {
            PlaySound(ZombieSound);

            PlaySound(StartLevelSound);
        }
        GenerateZombies(&ZombiesType[FreeIndex]);
        ZombiesSpawned++;
    }
}
void UpdateZombieMovement(Zombies *zombie)
{
    if (!zombie->isAlive)
    {
        return;
    }
    UpdateAnimatedObject(&zombie->ZombieObj);
    if (!zombie->Attack)
    {
        zombie->ZombieObj.speedX = CurrentLevelInfo->ZombieNormal.BassSpeedX * zombie->slowFactor;
        zombie->ZombieObj.speedY = CurrentLevelInfo->ZombieNormal.BassSpeedY * zombie->slowFactor;
    }
    zombie->ZombieObj.frameDelay = CurrentLevelInfo->ZombieNormal.BassFrameDelay / zombie->slowFactor;
    //   if(i==0) printf("zombie[%d] speedX = %f \n ", i, zombie->ZombieObj.speedX);  //debug
    zombie->Markaz.x = (zombie->ZombieObj.posX + zombie->ZombieObj.frames[0].width / 2);
    zombie->Markaz.y = (zombie->ZombieObj.posY + zombie->ZombieObj.frames[0].height / 2);
    zombie->CollisionBox.x = zombie->ZombieObj.posX + 40;
    zombie->CollisionBox.y = zombie->ZombieObj.posY + 20;
    if (zombie->Markaz.x < END_X)
    {
        zombie->X_Cell = (zombie->Markaz.x - START_X) / (RectangleWidth);
        // printf("%d\n" , zombie[0].Y_Cell );
    }
}
void EnableZombieAttack(Zombies *zombie, Texture2D *ZombieAttackSheet, int FrameWidth, int FrameHeight)
{
    if (zombie->Attack)
    {
        return;
    }
    if (zombie->Markaz.x >= END_X || !zombie->isAlive)
    {
        return;
    }
    if (CellContent[zombie->Y_Cell][zombie->X_Cell] == EMPTY)
    {
        return;
    }
    ResetAnimatedObject(&zombie->ZombieObj);

    zombie->ZombieObj =
        GenerateAnimatedObject(ZombieAttackSheet, FrameWidth, FrameHeight, 40, zombie->ZombieObj.posX,
                               zombie->ZombieObj.posY, 0, 0, zombie->ZombieObj.finalX, zombie->ZombieObj.finalY);
    zombie->ZombieObj.speedX = 0;
    zombie->Attack = true;
}
void DisableZombieAttack(Zombies *zombie, Texture2D *ZombieRunSheet, int FrameWidth, int FrameHeight)
{

    if (!zombie->Attack)
    {
        return;
    }
    if (zombie->Markaz.x >= END_X || !zombie->isAlive)
    {
        return;
    }
    if (CellContent[zombie->Y_Cell][zombie->X_Cell] == EMPTY ||
        CellContent[zombie->Y_Cell][zombie->X_Cell] == LAWNMOWER)
    {
        ResetAnimatedObject(&zombie->ZombieObj);

        zombie->ZombieObj =
            GenerateAnimatedObject(ZombieRunSheet, FrameWidth, FrameHeight, 40, zombie->ZombieObj.posX,
                                   zombie->ZombieObj.posY, -20, 0, zombie->ZombieObj.finalX, zombie->ZombieObj.finalY);

        zombie->Attack = false;
    }
}
void ZombiesAttackPlants(Zombies *zombie)
{
    if (zombie->Markaz.x >= END_X || !zombie->isAlive)
    {
        return;
    }
    if (CellContent[zombie->Y_Cell][zombie->X_Cell] == EMPTY)
    {
        return;
    }
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        ApplyZombieDamageToPlant(zombie, &SunFlower[i].Base);
        ApplyZombieDamageToPlant(zombie, &Peashooter[i].Base);
        ApplyZombieDamageToPlant(zombie, &Chomper[i].Base);
        ApplyZombieDamageToPlant(zombie, &Rose[i].Base);
    }
}
void ApplyZombieDamageToPlant(Zombies *zombie, PlantBase *Plant)
{
    if (!zombie->isAlive)
    {
        return;
    }
    if (!Plant->isAlive)
    {
        return;
    }
    if (zombie->X_Cell != Plant->X_Cell || zombie->Y_Cell != Plant->Y_Cell)
    {
        return;
    }
    Plant->Health -= zombie->Damege;
    if (Plant->Health <= 0)
    {
        CellContent[Plant->Y_Cell][Plant->X_Cell] = EMPTY;
        Plant->isAlive = false;
    }
}

void GenerateZombies(Zombies *obj)
{
    obj->Damege = 0.1;
    obj->Health = 100;
    int Row = rand() % 5;
    int xstart = SCREEN_WIDTH;
    int Xfinal = 0;
    int Ystart = START_Y + Row * RectangleHeight - 10;
    int Yfinal = Ystart;
    obj->Markaz.x = 1600;
    obj->Y_Cell = Row;
    obj->slowFactor = 1.0f;
    ResetAnimatedObject(&obj->ZombieObj);

    obj->ZombieObj = GenerateAnimatedObject(&ZombieNormal1, 107, 122, CurrentLevelInfo->ZombieNormal.BassFrameDelay,
                                            xstart, Ystart, CurrentLevelInfo->ZombieNormal.BassSpeedX,
                                            CurrentLevelInfo->ZombieNormal.BassSpeedY, Xfinal, Yfinal);
    obj->isAlive = true;
    obj->CollisionBox = (Rectangle){obj->ZombieObj.posX + 15, obj->ZombieObj.posY + 20,
                                    obj->ZombieObj.frames[0].width - 65, obj->ZombieObj.frames[0].height - 20};
}
void ResetSlowFactorZombies(void)
{
    for (int j = 0; j < CurrentLevelInfo->MaxZombieNormalAllowed; j++)
    {
        ZombieNormal[j].slowFactor = 1.0f;
    }
}
bool IsZombieInRow(int row, int plantXCell)
{
    for (int j = 0; j < CurrentLevelInfo->MaxZombieNormalAllowed; j++)
    {
        if (ZombieNormal[j].isAlive && ZombieNormal[j].Markaz.x <= END_X && ZombieNormal[j].Y_Cell == row &&
            ZombieNormal[j].X_Cell >= plantXCell)
        {
            return true;
        }
    }

    // ۲. چک کردن زامبی‌های جدید (مثلاً کلاه کپسولی) در آینده فقط یک حلقه
    // اینجا اضافه می‌کنی
    /*
    for (int j = 0; j < CurrentLevelInfo->MaxZombieBucketAllowed; j++) {
        if (ZombieBucket[j].isAlive && ... ) return true;
    }
    */

    return false;
}
void KillAllZombiesInCell(int Row, int Col)
{
    for (int j = 0; j < CurrentLevelInfo->MaxZombieNormalAllowed; j++)
    {
        if (ZombieNormal[j].isAlive && ZombieNormal[j].Markaz.x <= END_X &&
            ZombieNormal[j].Y_Cell == Row && ZombieNormal[j].X_Cell == Col)
        {
            ZombieNormal[j].isAlive = false;
            ZombiesKilled++;
        }
    }

    // ۲. در آینده زامبی‌های جدید را اینجا اضافه کن
    /*
    for (int j = 0; j < CurrentLevelInfo->MaxZombieBucketAllowed; j++) {
        if (ZombieBucket[j].isAlive && ZombieBucket[j].Y_Cell == row && ZombieBucket[j].X_Cell == col) {
            ZombieBucket[j].isAlive = false;
            ZombiesKilled++;
        }
    }
    */
}