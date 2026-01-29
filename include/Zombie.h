#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Level1.h"
#include "Plant.h"
typedef struct Zombies
{
    AnimatedObject ZombieObj;
    float Health;
    float Damege;
    int X_Cell;
    int Y_Cell;
    Vector2 Markaz;
    float slowFactor;
    bool isAlive;
    bool Attack;
    Rectangle CollisionBox;
} Zombies;

extern Zombies ZombieNormal[MAXNUZOMBIES];
void DrawZombiesObject(Zombies *ZombiesType, int MaxCount);
bool IsZombieSpawnTime(float *timer, float regenerateTime);
bool IsZombieInRow(int row, int plantXCell);
int GetFreeZombieIndex(Zombies *ZombiesType, int MaxCount);
void SpawnZombie(Zombies *ZombiesType, int MaxCount, float *zombieTimer, float regenerateTime, float MaxSpawnCount);
void UpdateZombieMovement(Zombies *zombie);
void EnableZombieAttack(Zombies *zombie, Texture2D *ZombieRunSheet, int FrameWidth, int FrameHeight);
void DisableZombieAttack(Zombies *zombie, Texture2D *ZombieAttackSheet, int FrameWidth, int FrameHeight);
void ApplyZombieDamageToPlant(Zombies *zombie, PlantBase *Plant);
void CheckLawnMowerCollision(Zombies *zombie);
void GenerateZombies(Zombies *obj);
void EnableZombieAttack(Zombies *zombie, Texture2D *ZombieAttackSheet, int FrameWidth, int FrameHeight);
void ZombiesAttackPlants(Zombies *zombie);
void UpdateZombies(void);
void DrawZombies(void);
void ResetSlowFactorZombies(void);
void KillAllZombiesInCell(int Row, int Col);





#endif