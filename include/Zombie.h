#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Level1.h"
#include "LevelBase.h"
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
    bool IsMovedVertically;
    float signSpeedY;
    Rectangle CollisionBox;
} Zombies;

extern Zombies ZombieNormal[MAXNUZOMBIES];
extern Zombies ThinkingZombie[MAXNUZOMBIES];

void DrawZombiesObject(Zombies *ZombiesType, int MaxCount);
bool IsZombieSpawnTime(float *timer, float *regenerateTime);
bool IsZombieInRow(int row, int plantXCell);
int GetFreeZombieIndex(Zombies *ZombiesType, int MaxCount);
bool SpawnZombie(Zombies *ZombiesType, Texture2D *ZombieSheet, ZombieInfo *Zombie,
                float MaxSpawnCount);
void UpdateZombieMovement(Zombies *zombie , ZombieInfo *zombieInfo);
void EnableZombieAttack(Zombies *zombie, Texture2D *ZombieRunSheet, int FrameWidth, int FrameHeight);
void DisableZombieAttack(Zombies *zombie, Texture2D *ZombieAttackSheet, int FrameWidth, int FrameHeight);
void ApplyZombieDamageToPlant(Zombies *zombie, PlantBase *Plant);
void CheckLawnMowerCollision(Zombies *zombie);
void GenerateZombies(Zombies *obj, Texture2D *ZombieSheet, ZombieInfo *Zombie);
void EnableZombieAttack(Zombies *zombie, Texture2D *ZombieAttackSheet, int FrameWidth, int FrameHeight);
void ZombiesAttackPlants(Zombies *zombie);
void UpdateZombies(void);
void DrawZombies(void);
void ResetSlowFactorZombies(void);
void KillAllZombiesInCell(int Row, int Col);
double UpdateThinkingZombiesDeterminant(int Row);
void UpdateRowWeights();
void UpdateThinkingZombieVerticalMovement(Zombies *zombie);
#endif