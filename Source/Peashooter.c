#include "Peashooter.h"
#include "Chomper.h"
#include "Level1.h"
#include "Plant.h"
#include "Rose.h"
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
PeashooterElement Peashooter[MAXNUMITEMS];

void ResetEffectiveFireRate(void)
{
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (Peashooter[i].Base.isAlive)
        {
            Peashooter[i].EffectiveFireRate = 1.0f;
        }
    }
}

void DrawPeashooterBullets(void)
{
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            if (Peashooter[i].Pea[k].isActive)
            {
                DrawAnimatedObject(&Peashooter[i].Pea[k].Pea, WHITE);
            }
            if (Peashooter[i].Pea[k].PeaBulletHit.isActive)
            {
                DrawAnimatedObject(&Peashooter[i].Pea[k].PeaBulletHit.BulletHitObj, WHITE);
            }
        }
    }
}

void GeneratePeashooter(PeashooterElement *obj, int X_Cell, int Y_Cell)
{
    for (int i = 0; i < 10; i++)
    {
        ResetAnimatedObject(&obj->Pea[i].Pea);
        ResetAnimatedObject(&obj->Pea[i].PeaBulletHit.BulletHitObj);
    }

    obj->Firingspeed = 2;
    obj->PeashooterObj.posX = obj->PeashooterObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->PeashooterObj.posY = obj->PeashooterObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;

    obj->FireTimer = 1;
    obj->EffectiveFireRate = 1.0f;
    obj->peaDamege = 10;

    obj->Firing = false;
    for (int i = 0; i < 10; i++)
    {
        obj->Pea[i].isActive = false;
    }

    GeneratePlantBase(&obj->Base, PLANT_PEASHOOTER, CurrentLevelInfo->PeashooterInfoLevel.BaseHealth, X_Cell, Y_Cell);

    return;
}

void GeneratePea(PeashooterElement *obj)
{
    for (int i = 0; i < 10; i++)
    {
        if (!(obj->Pea[i].isActive))
        {
            ResetAnimatedObject(&obj->Pea[i].Pea);
            obj->Pea[i].Pea = GenerateAnimatedObject(&pea, 29, 32, 1000, 385 + obj->Base.X_Cell * RectangleWidth,
                                                     247 + obj->Base.Y_Cell * RectangleHeight, 300, 0, END_X, 385);
            obj->Pea[i].Radius = (obj->Pea[i].Pea.frames[0].width / 2.0f) * 0.80f;
            obj->Pea[i].Markaz.x = obj->Pea[i].Pea.posX + obj->Pea[i].Radius;
            obj->Pea[i].Markaz.y = obj->Pea[i].Pea.posY + obj->Pea[i].Radius;
            obj->Pea[i].isActive = true;
            return;
        }
    }
}
void UpdatePeashooterFiring(PeashooterElement *Peashooter)
{
    if (!Peashooter->Base.isAlive)
        return;
    if (IsZombieInRow(Peashooter->Base.Y_Cell, Peashooter->Base.X_Cell))
    {
        Peashooter->Firing = true;
    }
    else
    {
        Peashooter->Firing = false;
    }
    if (Peashooter->Firing)
    {
        Peashooter->FireTimer += GetFrameTime();
        if (Peashooter->FireTimer >= Peashooter->Firingspeed / Peashooter->EffectiveFireRate)
        {
            Peashooter->FireTimer = 0;
            GeneratePea(Peashooter);
            PlaySound(PeaShootSfx);
        }
    }
}
void UpdatePeashooterPeas(PeashooterElement *Peashooter)
{
    for (int PeaNumber = 0; PeaNumber < 10; PeaNumber++)
    {
        if (Peashooter->Pea[PeaNumber].isActive)
        {
            UpdatePeashooterSinglePea(Peashooter, PeaNumber);
        }
        if (Peashooter->Pea[PeaNumber].PeaBulletHit.isActive)
        {
            UpdatePeaHitEffect(&Peashooter->Pea[PeaNumber].PeaBulletHit);
        }
    }
}
void UpdatePeashooterSinglePea(PeashooterElement *Peashooter, int PeaNumber)
{
    UpdateAnimatedObject(&Peashooter->Pea[PeaNumber].Pea);
    Peashooter->Pea[PeaNumber].Markaz.x =
        (Peashooter->Pea[PeaNumber].Pea.posX + Peashooter->Pea[PeaNumber].Pea.frames[0].width / 2);
    Peashooter->Pea[PeaNumber].Markaz.y =
        (Peashooter->Pea[PeaNumber].Pea.posY + Peashooter->Pea[PeaNumber].Pea.frames[0].height / 2);
    if (Peashooter->Pea[PeaNumber].Markaz.x >= END_X)
    {
        Peashooter->Pea[PeaNumber].isActive = false;
        return;
    }

    Peashooter->Pea[PeaNumber].Y_Cell = Peashooter->Base.Y_Cell;
    Peashooter->Pea[PeaNumber].X_Cell = (Peashooter->Pea[PeaNumber].Markaz.x - START_X) / (RectangleWidth);
    // printf("%d\n", Peashooter->Pea[PeaNumber].X_Cell);
    HandlePeaZombieCollision(Peashooter, PeaNumber);
}
void HandlePeaZombieCollision(PeashooterElement *Peashooter, int PeaNumber)
{
if (!Peashooter->Pea[PeaNumber].isActive) return;

    Zombies *finalTarget = NULL; 
    float minX = 2000.0f; 

    for (int j = 0; j < CurrentLevelInfo->MaxZombieNormalAllowed; j++)
    {
        if (!ZombieNormal[j].isAlive || ZombieNormal[j].Y_Cell != Peashooter->Pea[PeaNumber].Y_Cell)
            continue;

        bool hasHit = false;
        if (ZombieNormal[j].X_Cell == Peashooter->Base.X_Cell &&
            ZombieNormal[j].X_Cell == Peashooter->Pea[PeaNumber].X_Cell)
            Peashooter->Pea[PeaNumber].Pea.finalX = ZombieNormal[j].Markaz.x;

        if (Peashooter->Pea[PeaNumber].Pea.finalX <= Peashooter->Pea[PeaNumber].Pea.posX) hasHit = true;
        else if (CheckCollisionCircleRec(Peashooter->Pea[PeaNumber].Markaz, Peashooter->Pea[PeaNumber].Radius, ZombieNormal[j].CollisionBox)) hasHit = true;

        if (hasHit && ZombieNormal[j].Markaz.x < minX) {
            minX = ZombieNormal[j].Markaz.x;
            finalTarget = &ZombieNormal[j]; }
    }

    for (int j = 0; j < CurrentLevelInfo->MaxThinkingZombieAllowed; j++)
    {
        if (!ThinkingZombie[j].isAlive || ThinkingZombie[j].Y_Cell != Peashooter->Pea[PeaNumber].Y_Cell)
            continue;

        bool hasHit = false;
        if (ThinkingZombie[j].X_Cell == Peashooter->Base.X_Cell && ThinkingZombie[j].X_Cell == Peashooter->Pea[PeaNumber].X_Cell)
            Peashooter->Pea[PeaNumber].Pea.finalX = ThinkingZombie[j].Markaz.x;

        if (Peashooter->Pea[PeaNumber].Pea.finalX <= Peashooter->Pea[PeaNumber].Pea.posX) hasHit = true;
        else if (CheckCollisionCircleRec(Peashooter->Pea[PeaNumber].Markaz, Peashooter->Pea[PeaNumber].Radius, ThinkingZombie[j].CollisionBox)) hasHit = true;

        if (hasHit && ThinkingZombie[j].Markaz.x < minX) {
            minX = ThinkingZombie[j].Markaz.x;
            finalTarget = &ThinkingZombie[j]; // آدرس زامبی نوع ۲ را ذخیره کن
        }
    }

    if (finalTarget != NULL)
    {
        finalTarget->Health -= Peashooter->peaDamege;
        PlaySound(BulletHitSound[rand() % 4]);
        
        Peashooter->Pea[PeaNumber].isActive = false;
        Peashooter->Pea[PeaNumber].PeaBulletHit.isActive = true;
        Peashooter->Pea[PeaNumber].PeaBulletHit.DisplayTimer = 0;
        ResetAnimatedObject(&Peashooter->Pea[PeaNumber].PeaBulletHit.BulletHitObj);

        Peashooter->Pea[PeaNumber].PeaBulletHit.BulletHitObj = GenerateAnimatedObject(
            &PeaBulletHit, 49, 43, 100000, finalTarget->Markaz.x - 20, Peashooter->Pea[PeaNumber].Markaz.y,
            finalTarget->ZombieObj.speedX, finalTarget->ZombieObj.speedY, finalTarget->ZombieObj.finalX,
            Peashooter->Pea[PeaNumber].Markaz.y);

        if (finalTarget->Health <= 0) {
            finalTarget->isAlive = false;
            ZombiesKilled++;
        }
    }

}
void UpdatePeaHitEffect(struct BulletHit *PeaBulletHit)
{
    UpdateAnimatedObject(&PeaBulletHit->BulletHitObj);
    PeaBulletHit->DisplayTimer += GetFrameTime();
    if (PeaBulletHit->DisplayTimer >= PeaBulletHit->DisplayTime)
    {
        PeaBulletHit->DisplayTimer = 0;
        PeaBulletHit->isActive = false;
    }
}