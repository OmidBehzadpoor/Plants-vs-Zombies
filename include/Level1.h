#pragma once
#ifndef LEVEL1_H
#define LEVEL1_H

#include "gif.h"
#include "raylib.h"
#include "LevelBase.h"
#include "LevelUi.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define ROWLAWNMOWER 5
#define GENERATESUN 17
#define DISPLAYSUN 30
#define MAXSUNELEMENT 55
#define MAXNUMITEMS 50
#define MAXNUZOMBIES 30
#define GENERATERANDOM -555
#define VALUESUN 25
#define INFINITE -1


void InitLevel1(void);
void DrawLevel1(void);
void UpdateLevel1(void);


void InitLevel1Animation(void);
void InitLevel1MapCell(void);
void InitLevel1Info(void);


void DrawGameOver(void);
void DrawVictory(void);
void DrawBottom(void);
void UpdateBottom(void);
void resartLevel1(void);

#endif
