#include "Zombie.h"
#include "Chomper.h"
#include "Level1.h"
#include "LevelUi.h"
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
Zombies ThinkingZombie[MAXNUZOMBIES];
void DrawZombies(void)
{
    DrawZombiesObject(ZombieNormal, CurrentLevelInfo->MaxZombieNormalAllowed);
    DrawZombiesObject(ThinkingZombie, CurrentLevelInfo->MaxThinkingZombieAllowed);
}

void UpdateZombies(void)
{
    if (IsZombieSpawnTime(&ZombieTimer, CurrentLevelInfo->ZombieNormal.Regenerate)) // بعدا ریجنریت اصلاح شود
    {
        bool spawned = false;
        if (rand() % 2 == 0)
        {
            spawned = SpawnZombie(ZombieNormal, &ZombieNormal1, &CurrentLevelInfo->ZombieNormal,
                                  CurrentLevelInfo->MaxZombieNormalAllowed);
        }
        if (!spawned)
        {
           spawned = SpawnZombie(ThinkingZombie, &ThinkingZombiePic, &CurrentLevelInfo->ThinkingZombie,
                       CurrentLevelInfo->MaxThinkingZombieAllowed
                    );
        }
        if (!spawned)
        {
            spawned = SpawnZombie(ZombieNormal, &ZombieNormal1, &CurrentLevelInfo->ZombieNormal,
                                  CurrentLevelInfo->MaxZombieNormalAllowed);
        }
    }

    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++)
    {

        UpdateZombieMovement(&ZombieNormal[i], &CurrentLevelInfo->ZombieNormal);
        ZombiesAttackPlants(&ZombieNormal[i]);
        EnableZombieAttack(&ZombieNormal[i], &ZombieNormalAttack1, 107, 122);
        ZombiesAttackPlants(&ZombieNormal[i]);
        DisableZombieAttack(&ZombieNormal[i], &ZombieNormal1, 107, 122);
        CheckLawnMowerCollision(&ZombieNormal[i]);
    }
    for (int i = 0; i < CurrentLevelInfo->MaxThinkingZombieAllowed; i++)
    {

        UpdateZombieMovement(&ThinkingZombie[i], &CurrentLevelInfo->ThinkingZombie);
        ZombiesAttackPlants(&ThinkingZombie[i]);
        EnableZombieAttack(&ThinkingZombie[i], &ThinkingZombieAttackPic, 107, 122);
        ZombiesAttackPlants(&ThinkingZombie[i]);
        DisableZombieAttack(&ThinkingZombie[i], &ThinkingZombiePic, 107, 122);
        CheckLawnMowerCollision(&ThinkingZombie[i]);
        UpdateThinkingZombieVerticalMovement(&ThinkingZombie[i]);
    }
    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++)
    {
        if (ZombieNormal[i].isAlive && ZombieNormal[i].Attack && ZombieNormal[i].Markaz.x <= END_X)
        {
            PlayEatSound(&plantEatSoundPlayed);
            break;
        }
    }
    for (int i = 0; i < CurrentLevelInfo->MaxThinkingZombieAllowed; i++)
    {
        if (ThinkingZombie[i].isAlive && ThinkingZombie[i].Attack && ThinkingZombie[i].Markaz.x <= END_X)
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
bool SpawnZombie(Zombies *ZombiesType, Texture2D *ZombieSheet, struct ZombieInfo *Zombie, float MaxSpawnCount)
{

    int FreeIndex = GetFreeZombieIndex(ZombiesType, MaxSpawnCount);
    if (FreeIndex < 0)
    {
        return false;
    }
    if (Zombie->ZombieSpawned < MaxSpawnCount || MaxSpawnCount == INFINITE)
    {
        if (ZombiesSpawned == 0)
        {
            PlaySound(ZombieSound);

            PlaySound(StartLevelSound);
        }
        GenerateZombies(&ZombiesType[FreeIndex], ZombieSheet, Zombie);
        ZombiesSpawned++;
    Zombie->ZombieSpawned++;
        return true;
    }
}
void UpdateZombieMovement(Zombies *zombie, ZombieInfo *zombieInfo)
{
    if (!zombie->isAlive)
    {
        return;
    }
    UpdateAnimatedObject(&zombie->ZombieObj);
    if (!zombie->Attack)
    {
        zombie->ZombieObj.speedX = zombieInfo->BassSpeedX * zombie->slowFactor;
        if (zombie->IsMovedVertically)
        {
            zombie->ZombieObj.speedY = zombieInfo->BassRunSpeedY * zombie->slowFactor * zombie->signSpeedY;
        }
        else
        {
            zombie->ZombieObj.speedY = zombieInfo->BassSpeedY * zombie->slowFactor * zombie->signSpeedY;
        }
    }
    zombie->ZombieObj.frameDelay = zombieInfo->BassFrameDelay / zombie->slowFactor;
    //   if(i==0) printf("zombie[%d] speedX = %f \n ", i, zombie->ZombieObj.speedX);  //debug
    zombie->Markaz.x = (zombie->ZombieObj.posX + zombie->ZombieObj.frames[0].width / 2);
    zombie->Markaz.y = (zombie->ZombieObj.posY + zombie->ZombieObj.frames[0].height / 2);
    zombie->CollisionBox.x = zombie->ZombieObj.posX + 40;
    zombie->CollisionBox.y = zombie->ZombieObj.posY + 20;
    if (zombie->Markaz.x < END_X)
    {
        zombie->X_Cell = (zombie->Markaz.x - START_X) / (RectangleWidth);
        // printf("%d\n" , zombie[0].Y_Cell );
        zombie->Y_Cell = (zombie->Markaz.y - START_Y) / (RectangleHeight);
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
        RowStatus[Plant->Y_Cell].plantCount--;
        RowStatus[Plant->Y_Cell].rowChanged = true;
        Plant->isAlive = false;
    }
}

void GenerateZombies(Zombies *obj, Texture2D *ZombieSheet, ZombieInfo *Zombie)
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

    obj->ZombieObj = GenerateAnimatedObject(ZombieSheet, 107, 122, Zombie->BassFrameDelay, xstart, Ystart,
                                            Zombie->BassSpeedX, Zombie->BassSpeedY, Xfinal, Yfinal);
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
    for (int j = 0; j < CurrentLevelInfo->MaxThinkingZombieAllowed; j++)
    {
        ThinkingZombie[j].slowFactor = 1.0f;
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
    for (int j = 0; j < CurrentLevelInfo->MaxThinkingZombieAllowed; j++)
    {
        if (ThinkingZombie[j].isAlive && ThinkingZombie[j].Markaz.x <= END_X && ThinkingZombie[j].Y_Cell == row &&
            ThinkingZombie[j].X_Cell >= plantXCell)
        {
            return true;
        }
    }

    return false;
}
void KillAllZombiesInCell(int Row, int Col)
{
    for (int j = 0; j < CurrentLevelInfo->MaxZombieNormalAllowed; j++)
    {
        if (ZombieNormal[j].isAlive && ZombieNormal[j].Markaz.x <= END_X && ZombieNormal[j].Y_Cell == Row &&
            ZombieNormal[j].X_Cell == Col)
        {
            ZombieNormal[j].isAlive = false;
            ZombiesKilled++;
        }
    }
    for (int j = 0; j < CurrentLevelInfo->MaxThinkingZombieAllowed; j++)
    {
        if (ThinkingZombie[j].isAlive && ThinkingZombie[j].Markaz.x <= END_X && ThinkingZombie[j].Y_Cell == Row &&
            ThinkingZombie[j].X_Cell == Col)
        {
            ThinkingZombie[j].isAlive = false;
            ZombiesKilled++;
        }
    }
}
void UpdateRowWeights()
{
    for (int i = 0; i < ROWS; i++)
    {

        float mowerFactor = (CellContent[i][0] == LAWNMOWER) ? 1.0f : 0.0f;
        if (RowStatus[i].rowChanged)
        {
            RowStatus[i].ThinkingZombiesDeterminant = UpdateThinkingZombiesDeterminant(i);
            RowStatus[i].rowChanged = false;
        }
        RowStatus[i].RowWeights = (mowerFactor * 100) - (RowStatus[i].ThinkingZombiesDeterminant);
    }
}
double UpdateThinkingZombiesDeterminant(int Row)
{
    int n = RowStatus[Row].plantCount;
    double S = 0;
    double Q = 0;
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (SunFlower[i].Base.isAlive && SunFlower[i].Base.Y_Cell == Row)
        {
            double RelativeHP = SunFlower[i].Base.Health / CurrentLevelInfo->SunFlowertInfoLevel.BaseHealth;
            S += RelativeHP;
            Q += (RelativeHP * RelativeHP);
        }
        if (Peashooter[i].Base.isAlive && Peashooter[i].Base.Y_Cell == Row)
        {
            double RelativeHP = Peashooter[i].Base.Health / CurrentLevelInfo->PeashooterInfoLevel.BaseHealth;
            S += RelativeHP;
            Q += (RelativeHP * RelativeHP);
        }
        if (Chomper[i].Base.isAlive && Chomper[i].Base.Y_Cell == Row)
        {
            double RelativeHP = Chomper[i].Base.Health / CurrentLevelInfo->ChompertInfoLevel.BaseHealth;
            S += RelativeHP;
            Q += (RelativeHP * RelativeHP);
        }
        if (Rose[i].Base.isAlive && Rose[i].Base.Y_Cell == Row)
        {
            double RelativeHP = Rose[i].Base.Health / CurrentLevelInfo->RosetInfoLevel.BaseHealth;
            S += RelativeHP;
            Q += (RelativeHP * RelativeHP);
        }
    }
    return 1 - (n * n) - (Q * Q) - (S * S) + (2 * S * Q * n); // Det
}
void UpdateThinkingZombieVerticalMovement(Zombies *zombie)
{
    if (!zombie->isAlive)
    {
        return;
    }
    if (zombie->Markaz.x >= END_X)
    {
        return;
    }
    UpdateRowWeights(); // اول وزن‌ها را آپدیت کن
// for (int i = 0; i < 5; i++)
// {
//    printf("W RoW %d = %f\n" ,i+1, RowStatus[i].RowWeights);
// }
 
    int currentRow = zombie->Y_Cell;
    int bestRow = currentRow;
    double minWeight = RowStatus[currentRow].RowWeights;

    // چک کردن ردیف بالا (اگر وجود دارد)
    if (currentRow > 0)
    {
        if (RowStatus[currentRow - 1].RowWeights < minWeight)
        {
            minWeight = RowStatus[currentRow - 1].RowWeights;
            bestRow = currentRow - 1;
        }
    }
    // چک کردن ردیف پایین (اگر وجود دارد)
    if (currentRow < ROWS - 1)
    {
        if (RowStatus[currentRow + 1].RowWeights < minWeight)
        {
            minWeight = RowStatus[currentRow + 1].RowWeights;
            bestRow = currentRow + 1;
        }
    }

    if (!zombie->IsMovedVertically)
    {
        float signSpeedY = 0;
        if (bestRow > currentRow)
        {
            signSpeedY = 1.0;
        }
        else if (bestRow < currentRow)
        {
            signSpeedY = -1.0;
        }
        else
        {
            signSpeedY = 0;
        }
        zombie->signSpeedY = signSpeedY;
        zombie->ZombieObj.speedY = CurrentLevelInfo->ThinkingZombie.BassRunSpeedY * signSpeedY;
        zombie->ZombieObj.finalY += RectangleHeight * signSpeedY;
        zombie->IsMovedVertically = true;
        // printf("%f\n", CurrentLevelInfo->ThinkingZombie.BassRunSpeedY);
    }
    if (zombie->ZombieObj.posY == zombie->ZombieObj.finalY)
    {
        zombie->IsMovedVertically = false;

        zombie->signSpeedY = 0;
    }
  
    // printf("Sp Y = %f\n"  , zombie->ZombieObj.speedY);
}