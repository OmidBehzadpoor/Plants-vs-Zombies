#pragma once
#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "Level1.h"
#include "Plant.h"

struct BulletHit
{
    AnimatedObject BulletHitObj;
    bool isActive;
    float DisplayTime;
    float DisplayTimer;
};

struct PeaFire
{
    AnimatedObject Pea;
    struct BulletHit PeaBulletHit;
    int X_Cell;
    Vector2 Markaz;
    float Radius;
    int Y_Cell;
    Rectangle CollisionBox;
    bool isActive;
};



typedef struct PeashooterElement
{
    AnimatedObject PeashooterObj;
    struct PeaFire Pea[10];
    PlantBase Base;
    float Firingspeed;
    float FireTimer;
    float EffectiveFireRate;
    float peaDamege;
    bool Firing;
} PeashooterElement;
extern PeashooterElement Peashooter[MAXNUMITEMS];

void ResetEffectiveFireRate(void);
void DrawPeashooterBullets(void);
void GeneratePeashooter(PeashooterElement *obj, int X_Cell, int Y_Cell);
void GeneratePea(PeashooterElement *obj);
void UpdatePeashooterFiring(PeashooterElement *Peashooter);
void UpdatePeashooterPeas(PeashooterElement *Peashooter);
void UpdatePeashooterSinglePea(PeashooterElement *Peashooter, int PeaNumber);
void HandlePeaZombieCollision(PeashooterElement *Peashooter, int PeaNumber);
void UpdatePeaHitEffect(struct BulletHit *PeaBulletHit);
#endif