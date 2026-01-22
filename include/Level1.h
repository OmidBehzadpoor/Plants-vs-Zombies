#pragma once
#ifndef LEVEL1_H
#define LEVEL1_H

#include "gif.h"
#include "raylib.h"
#include <stdbool.h>
#define ROWS 5
#define COLUMNS 10
#define START_X 305
#define END_X 1380
#define START_Y 230
#define END_Y 840
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define ROWLAWNMOWER 5
#define GENERATESUN 20
#define DISPLAYSUN 30
#define MAXSUNELEMENT 55
#define MAXNUMITEMS 50
#define MAXNUZOMBIES 30
#define GENERATERANDOM -555
#define VALUESUN 25

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

typedef struct SunflowerElement
{
    AnimatedObject SunFlowerObj;
    Rectangle Coordinates;
    float Cooldown;
    float Health;
    int X_Cell;
    int Y_Cell;
    bool isAlive;
} SunflowerElement;

typedef struct PeashooterElement
{
    AnimatedObject PeashooterObj;
    struct PeaFire Pea[10];

    Rectangle Coordinates;

    float Firingspeed;
    float FireTimer;
    float EffectiveFireRate ;
    float peaDamege;
    float Health;
    int X_Cell;
    int Y_Cell;
    bool isAlive;
    bool Firing;

} PeashooterElement;

typedef struct ChomperElement
{
    AnimatedObject ChomperObj;

    Rectangle Coordinates;
    float Lifespan;
    float Health;
    int X_Cell;
    int Y_Cell;
    bool isAlive;
} ChomperElement;

typedef struct RoseElement
{
    AnimatedObject RoseObj;

    Rectangle Coordinates;
    float Lifespan;
    float Health;
    float Timer ;
    int X_Cell;
    int Y_Cell;
    bool isAlive;
} RoseElement;
typedef struct LawnMowerElement
{
    AnimatedObject LawnMowerObj;

    int X_Cell;
    int Y_Cell;
    Vector2 Markaz;
    bool isActive;
    bool Available;
} LawnMowerElement;
typedef enum
{
    EMPTY = 0,
    LAWNMOWER,
    SUNFLOWER,
    PEASHOOTER,
    CHOMPER,
    ROSE

} MapContent;

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
typedef struct SunElement
{
    AnimatedObject sun;
    float time;
    bool Available;
} SunElement;

typedef struct
{
    char text[32];    // متن پیام (مثلاً "SUN NOT ENOUGH")
    float duration;   // مدت زمان نمایش پیام (مثلاً 2.0 ثانیه)
    float timer;      // تایمر شمارش معکوس
    bool isActive;    // آیا پیام فعال است؟
    Vector2 startPos; // موقعیت شروع (مرکز صفحه)
    float baseSize;   // اندازه فونت پایه
} WarningMessage;
struct PlantsInfo
{
    int price;
    float Cooldown;
    float BaseHealth;
    float Timer;
    bool Lock;
};

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
typedef struct LevelInfo
{

    struct PlantsInfo SunFlowertInfoLevel;
    struct PlantsInfo PeashooterInfoLevel;
    struct PlantsInfo ChompertInfoLevel;
    struct PlantsInfo RosetInfoLevel;
    struct SunElementInfo SunElementInfoLevel;
    struct ZombieInfo ZombieNormal;

} LevelInfo;

extern float RectangleWidth;
extern float RectangleHeight;
extern LevelInfo Level1Info;
extern Texture2D Map, OFFlawnMowerRow, SunBankPic, Frame, selectpic, Price[4];
extern Texture2D SunFlowerSheet, LawnMowerSheet, SunElementSheet;
extern AnimatedObject icon[4];
extern Color GoldOrange;
extern WarningMessage LackSunWarning;
extern Rectangle MapCell[ROWS][COLUMNS];
extern MapContent CellContent[ROWS][COLUMNS];
extern SunflowerElement SunFlower[MAXNUMITEMS];
extern PeashooterElement Peashooter[MAXNUMITEMS];
extern ChomperElement Chomper[MAXNUMITEMS];
extern RoseElement Rose[MAXNUMITEMS];
extern LawnMowerElement LawnMower[ROWLAWNMOWER];
void InitLevel1(void);
void DrawLevel1(void);
void UpdateLevel1(void);
void UnloadLevel1(void);
void CellularNetworkMap(void);
void CheckSelect(void);
void GenerateSun(SunElement *obj, int x, int y);
void GenerateSunFlower(SunflowerElement *obj, int X_Cell, int Y_Cell);
void ShowLackSunWarning(void);
void GeneratePeashooter(PeashooterElement *obj, int X_Cell, int Y_Cell);
void GenerateChomper(ChomperElement *obj, int X_Cell, int Y_Cell);
void GenerateRose(RoseElement *obj, int X_Cell, int Y_Cell);
void CooldownUpdate(void);
void DrawPlants(void);
void DrawSunElement(void);
void DrawSelectionTick(void);
void DrawLevelItems(void);
void DrawLackSunWarning(void);
void UpdatePlantsTimer(void);
void UpdateSUNELEMENT(void);
void UpdateLevelItems(void);
void UpdateLackSunWarning(void);
void UpdateSelectionItems(void);
void UpdatePlantsAnimation(void);
void CollectSunElement(void);
void InitLevel1Texture(void);
void InitLevel1Font(void);
void InitLevel1Animation(void);
void InitLevel1MapCell(void);
void InitLevel1Info(void);
void DrawLockWarning(void);
void ShowLockWarning(void);
void UpdateLockWarning(void);
void GenerateZombies(Zombies *obj);
void GeneratePea(PeashooterElement *obj);
void ResetSlowFactorZombies(void);
void ResetEffectiveFireRate(void);

#endif