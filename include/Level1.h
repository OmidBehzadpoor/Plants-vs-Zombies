#pragma once
#ifndef LEVEL1_H
#define LEVEL1_H

#include "gif.h"
#include "raylib.h"
#include "LevelBase.h"
#include "LevelUi.h"

// ------------------- Constants -------------------

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
#define INFINITE -1

// ------------------- Enumerations -------------------



// ------------------- Structures -------------------







// ------------------- Extern Variables -------------------







// ------------------- Function Prototypes -------------------
void InitLevel1(void);
void DrawLevel1(void);
void UpdateLevel1(void);
void UnloadLevel1(void);
void CellularNetworkMap(void);
void CheckSelect(void);
void ShowLackSunWarning(void);

void CooldownUpdate(void);
void DrawPlantsObject(void);
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

void InitLevel1Animation(void);
void InitLevel1MapCell(void);
void InitLevel1Info(void);
void DrawLockWarning(void);
void ShowLockWarning(void);
void UpdateLockWarning(void);
void ResetSlowFactorZombies(void);
void ResetEffectiveFireRate(void);
void CheckWin(void);
void CheckLose(void);

void DrawGameOver(void);
void DrawVictory(void);
void DrawBottom(void);
void UpdateBottom(void);
void resartLevel(void);

void DrawDebug(void);
void DrawPeashooterBullets(void);
#endif
