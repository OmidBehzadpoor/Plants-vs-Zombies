#pragma once
#ifndef LEVELBASE_H
#define LEVELBASE_H
#include "raylib.h"
#include "gif.h"

typedef struct SunElementInfo
{
    int Value;
    float DisplayTime;
    float Regenerate;
} SunElementInfo;


typedef struct ZombieInfo
{
    float Regenerate;
    float Timer;
    float BassSpeedX;
    float BassSpeedY;
    float BassFrameDelay;
} ZombieInfo;



struct PlantsInfo
{
    int price;
    float Cooldown;
    float BaseHealth;
    float Timer;
    bool Lock;
};

typedef struct LevelInfo
{
    struct PlantsInfo SunFlowertInfoLevel;
    struct PlantsInfo PeashooterInfoLevel;
    struct PlantsInfo ChompertInfoLevel;
    struct PlantsInfo RosetInfoLevel;
    struct SunElementInfo SunElementInfoLevel;
    struct ZombieInfo ZombieNormal;
    int MaxZombieNormalAllowed;
} LevelInfo;
extern LevelInfo *CurrentLevelInfo;
extern Font HorrorFont;
extern Texture2D Map, OFFlawnMowerRow, SunBankPic, Frame, selectpic, Price[4],iconPic[4], GameOver, Victory, ButtonWin, ButtonLose;
extern Texture2D SunFlowerSheet, LawnMowerSheet, SunElementSheet, ChomperSheet, RoseSheet, PeashooterSheet,
    ZombieNormal1, ZombieNormalAttack1, ZombieNormal2, pea, PeaBulletHit, OverhealBar, LifetimeBar, HpBar ,LockPic , RingBar;
extern Color GoldOrange;
extern AnimatedObject icon[4];
extern float SunTimer, ZombieTimer;
extern int ZombiesKilled , ZombiesSpawned;

 extern bool restart;
 extern bool FirstRun;
void InitLevelTexture(void);
void InitLevelFont(void);
void InitGame(void);
#endif