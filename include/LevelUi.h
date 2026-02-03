#pragma once
#ifndef LEVELUI_H
#define LEVELUI_H
#include <stdbool.h>
#include "raylib.h"
#define ROWS 5
#define COLUMNS 10
extern bool IsDrawVictory ;
extern bool IsDrawGameOver ;

typedef struct
{
    Vector2 center;
    float radius;
    bool hovered;
} CircleButton;
typedef enum GameState
{
    PLAYING,
    WIN,
    LOSE,
    PAUSED ,
    YesNo
} GameState;
extern GameState CurrentGameState;
typedef enum MapContent
{
    EMPTY = 0,
    LAWNMOWER,
    SUNFLOWER,
    PEASHOOTER,
    CHOMPER,
    ROSE
} MapContent;
typedef struct WarningMessage
{
    char text[32];
    float duration;
    float timer;
    bool isActive;
    Vector2 startPos;
    float baseSize;
} WarningMessage;
typedef struct RowManager
{
    int plantCount;   
    bool rowChanged; //  هر گونه تغییر در کاشت  یا تغییر خون که نیاز به محاسبه دترمینان باشد 
    bool WeightChanged; // تغییر ردیف یا چمن زن
    double ThinkingZombiesDeterminant;
    double RowWeights ;
} RowManager;

extern RowManager RowStatus[ROWS];
extern WarningMessage LackSunWarning, LockWarning;
extern MapContent Selection;
extern MapContent CellContent[ROWS][COLUMNS];
extern Rectangle MapCell[ROWS][COLUMNS];
extern float RectangleWidth;
extern float RectangleHeight;
 extern   float scaleVictoryPic ;
 extern float scaleGameOverPic;
extern int  SunBank;
void UpdateBottom(void);
void DrawBottom(void);
void DrawVictory(void);
void DrawGameOver(void);
void DrawLockWarning(void);
void DrawLackSunWarning(void);
void DrawLevelItems(void);
void DrawSelectionTick(void);
void UpdateSelectionItems(void);
void UpdateLackSunWarning(void);
void UpdateLockWarning(void);
void UpdateLevelItems(void);
void CheckSelect(void);
void ShowLackSunWarning(void);
void ShowLockWarning(void);
void DrawUI(void);
void UpdateUI(void);
void DrawLockPicture(void);
void ResetUi(void);
void UpdateLoseNowButton(void);
void ResetRowManager(void);
void DrawYesOrNop(char *Question);
void UpdateYesOrNop(void);
#endif