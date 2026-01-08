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
#define GENERATERANDOM -555
#define VALUESUN 25
typedef struct SunflowerElement
{
    AnimatedObject SunFlowerObj;
    Rectangle Coordinates;
    float Cooldown;
    int Health;
    bool isAlive;
} SunflowerElement;
extern SunflowerElement SunFlower[MAXNUMITEMS];
typedef struct PeashooterElement
{
    AnimatedObject PeashooterObj;

    Rectangle Coordinates;

    float Firingspeed;
    int Health;
    bool isAlive;
} PeashooterElement;
extern PeashooterElement Peashooter[MAXNUMITEMS];

typedef struct ChomperElement
{
    AnimatedObject ChomperObj;

    Rectangle Coordinates;
    float Lifespan;
    int Health;
    bool isAlive;
} ChomperElement;
extern ChomperElement Chomper[MAXNUMITEMS];

typedef struct RoseElement
{
    AnimatedObject RoseObj;

    Rectangle Coordinates;
    float Lifespan;
    int Health;
    bool isAlive;
} RoseElement;
extern RoseElement Rose[MAXNUMITEMS];

typedef enum
{
    EMPTY = 0,
    LAWNMOWER,
    SUNFLOWER,
    PEASHOOTER,
    CHOMPER,
    ROSE

} MapContent;

extern MapContent CellContent[ROWS][COLUMNS];

typedef struct SunElementInfo
{
    int Value;
    float DisplayTime;
    float Regenerate;
} SunElementInfo;
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

struct SunFlowertInfo
{
    int price;
    float Cooldown;
    float Timer;
        bool Lock;

};
struct PeashooterInfo
{
    int price;

    float Cooldown;
    float Timer;
    bool Lock;
};
struct ChompertInfo
{
    int price;

    float Cooldown;
    float Timer;
        bool Lock;

};
struct RosetInfo
{
    int price;

    float Cooldown;
    float Timer;
        bool Lock;

};
typedef struct LevelInfo
{

    struct SunFlowertInfo SunFlowertInfoLevel;
    struct PeashooterInfo PeashooterInfoLevel;
    struct ChompertInfo ChompertInfoLevel;
    struct RosetInfo RosetInfoLevel;
    struct SunElementInfo SunElementInfoLevel;

} LevelInfo;
extern LevelInfo Level1Info;
extern float RectangleWidth;
extern float RectangleHeight;
extern Texture2D Map;
extern Rectangle MapCell[ROWS][COLUMNS];

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
#endif