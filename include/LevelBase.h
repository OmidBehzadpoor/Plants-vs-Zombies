#pragma once
#ifndef LEVELBASE_H
#define LEVELBASE_H
#include "gif.h"
#include "raylib.h"

typedef struct ElementInfo
{
    int Value;
    float DisplayTime;
    float Regenerate;
} ElementInfo;

typedef struct ZombieInfo
{
    float Regenerate;
    float Timer;
    float BassSpeedX;
    float BassSpeedY;
    float BassRunSpeedY;
    float BassFrameDelay;
    int ZombieSpawned;
    bool InfiniteSpan;
} ZombieInfo;

struct PlantsInfo
{
    int price;
    float Cooldown;
    float BaseHealth;
    float ActivationTime;
    float Timer;
    bool Lock;
    bool IsAvailable;
};

typedef struct LevelInfo
{
    struct PlantsInfo SunFlowertInfoLevel;
    struct PlantsInfo PeashooterInfoLevel;
    struct PlantsInfo ChompertInfoLevel;
    struct PlantsInfo RosetInfoLevel;
    struct PlantsInfo PotatoMineInfoLevel;
    struct ElementInfo SunElementInfoLevel;
    struct ElementInfo DiamondElementInfoLevel;

    struct ZombieInfo ZombieNormal;
    struct ZombieInfo ThinkingZombie;

    int MaxZombieNormalAllowed;
    int MaxThinkingZombieAllowed;
} LevelInfo;
extern LevelInfo *CurrentLevelInfo;
extern Font HorrorFont;
extern Texture2D Map, OFFlawnMowerRow, SunBankPic, Frame, selectpic, Price[5], iconPic[5], GameOver, Victory, ButtonWin,
    ButtonLose;
extern Texture2D SunFlowerSheet, LawnMowerSheet, SunElementSheet, ChomperSheet, RoseSheet, PeashooterSheet,
    ZombieNormal1, ZombieNormalAttack1, ZombieNormal2, pea, PeaBulletHit, OverhealBar, LifetimeBar, HpBar, LockPic,
    RingBar, ThinkingZombiePic, ThinkingZombieAttackPic, LoseNowpic, YesOrNopic, TimeFramePic, PotatoMineNotReadyPic,
    PotatoMineMashedPic, PotatoMineSheet, ExplosionSpudow;
extern Color GoldOrange, SaffronYellow;
extern AnimatedObject icon[5];
extern Rectangle LoseNowButton;
extern Rectangle YesButton;
extern Rectangle NoButton;
extern int bestHours;
extern int bestMinutes;
extern int bestSeconds;
extern int SurvivalHours;
extern int SurvivalMinutes;
extern int SurvivalSeconds;
extern float SunTimer, ZombieTimer;
extern int ZombiesKilled, ZombiesSpawned;
extern float SurvivalTimer;    // زمان سپری شده به ثانیه
extern float BestSurvivalTime; // رکورد بالاترین زمان
extern bool restart;
extern bool FirstRun;
void InitLevelTexture(void);
void InitLevelFont(void);
void InitGame(void);
void SaveBestTime(void);
void LoadBestTime(void);
void CalculateBestTimeHMS(void);
void CalculateSurvivalTimeHMS(void);
#endif