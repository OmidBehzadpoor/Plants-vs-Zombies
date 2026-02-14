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
    //  float Regenerate; // ! در حال حاضر از استفاده نمیشود
    // float Timer;  // ! فعلا در پروژه کاربرد ندارد
    float BassSpeedX;
    float BassSpeedY;
    float BassRunSpeedY;
    float FreezingSpeedX;
    float FreezingSpeedY;
    float FreezingRunSpeedY;

    float FreezingFrameDelay;
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
typedef struct Circle
{
    Vector2 center; // مختصات x و y مرکز
    float radius;   // شعاع دایره
} Circle;
typedef struct LevelInfo
{
    struct PlantsInfo SunFlowertInfoLevel;
    struct PlantsInfo PeashooterInfoLevel;
    struct PlantsInfo IcePeashooterInfoLevel;
    struct PlantsInfo ChompertInfoLevel;
    struct PlantsInfo RosetInfoLevel;
    struct PlantsInfo PotatoMineInfoLevel;
    struct ElementInfo SunElementInfoLevel;
    struct ElementInfo DiamondElementInfoLevel;

    struct ZombieInfo ZombieNormal;
    struct ZombieInfo ThinkingZombie;

    int MaxZombieNormalAllowed;
    int MaxThinkingZombieAllowed;
    float ZombieRegenerateTimer;
    int START_X;
    int END_X;
    int START_Y;
    int END_Y;
} LevelInfo;
extern LevelInfo *CurrentLevelInfo;
extern Font HorrorFont;
extern Texture2D Map, OFFlawnMowerRow, SunBankPic, Frame, selectpic, Price[5], iconPic[6], GameOver, Victory, ButtonWin,
    ButtonLose, map_naght;
extern Texture2D SunFlowerSheet, LawnMowerSheet, SunElementSheet, ChomperSheet, RoseSheet, PeashooterSheet,IcePeashooterSheet,
    ZombieNormal1, ZombieNormalAttack1, ZombieNormal2, pea , IcePea , IcePeaBulletHit, PeaBulletHit, OverhealBar, LifetimeBar, HpBar, LockPic,
    RingBar, ThinkingZombiePic, ThinkingZombieAttackPic, LoseNowpic, YesOrNopic, TimeFramePic, PotatoMineNotReadyPic,
    PotatoMineMashedPic, PotatoMineSheet, ExplosionSpudow;
extern Color GoldOrange, SaffronYellow;
extern AnimatedObject icon[6];
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
void UnloadLevelFont(void);
void SaveBestTime(void);
void LoadBestTime(void);
void CalculateBestTimeHMS(void);
void CalculateSurvivalTimeHMS(void);
void LoadGame(void);
void SaveGame(void);
void ResetCellContent(void);
void ResetAllAnimation(void);
void CheckWin(void);
void CheckLose(void);
void InitAllAnimation(void);
void SetupLawnMowerAnimation(void);
void DrawTextCentered(Font font, const char *text, Vector2 center, float fontSize, float spacing, Color color);
void UnloadLevelTexture(void);

#endif