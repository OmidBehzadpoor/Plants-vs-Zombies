#pragma once
#ifndef LEVEL1_H
#define LEVEL1_H

#include "raylib.h"
#include <stdbool.h>
#define ROWS 5
#define COLUMNS 10
#define START_X 305
#define END_X 1380
#define START_Y 230
#define END_Y 840
void InitLevel1(void);
void DrawLevel1(void);
void UpdateLevel1(void);
void UnloadLevel1(void);
void CellularNetworkMap(void);
extern float RectangleWidth;
extern float RectangleHeight;
extern Texture2D Map;
extern Rectangle MapCell[ROWS][COLUMNS];
typedef struct Sunflower
{

    Rectangle Coordinates;
    float Cooldown;
    int Health;
    bool isAlive;
} Sunflower;
typedef struct Peashooter
{

    Rectangle Coordinates;
    float Firingspeed;
    int Health;
    bool isAlive;
} Peashooter;
typedef struct Chomper
{

    Rectangle Coordinates;
    float Lifespan;
    int Health;
    bool isAlive;
} Chomper;

typedef struct Rose
{

    Rectangle Coordinates;
    float Lifespan;
    int Health;
    bool isAlive;
} Rose;
typedef enum {
    EMPTY = 0,             
    LAWNMOWER,             
    SUNFLOWER,             
    PEASHOOTER,            
    CHOMPER,               
    ROSE                 
   
} MapContent;
extern  MapContent CellContent[ROWS][COLUMNS];
#endif