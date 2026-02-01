#pragma once
#ifndef PLANT_H
#define PLANT_H
#include "raylib.h"
 typedef enum PlantType
{
    PLANT_SUNFLOWER,
    PLANT_PEASHOOTER,
    PLANT_CHOMPER,
    PLANT_ROSE
} PlantType;


typedef struct HealthMeter
{
    Rectangle frameHP;
    Vector2 posHP;
    Rectangle frameOverhealBar;
    Vector2 posOverhealBar;
    float HpPercentage;
} HealthMeter;

typedef struct PlantBase
{
    PlantType Type;
    float Health;
    int X_Cell;
    int Y_Cell;
    Rectangle Coordinates;
    HealthMeter HpDisplay;
    bool isAlive;
} PlantBase;


typedef struct ActiveTimeBar
{
    Rectangle frameBAR;
    Vector2 posBar;
    float LifetimePercentage;
} ActiveTimeBar;

struct Zombies;
void UpdatePlantsTimer(void);
void UpdatePlantsAnimation(void);
void CooldownUpdate(void);
void DrawPlantsObject(void);
void UpdatePlants(void);
void DrawPlantsUnderZombie(void);
void DrawPlantsOverZombie(void);
void DrawHpBar(HealthMeter *bar);
void UpdateLifetimeBar(ActiveTimeBar *bar, float life, float maxLife);
void UpdateHpBar(PlantBase *Plant, float BaseHp);
void GeneratePlantBase(PlantBase *obj, PlantType Type, float HP, int X_Cell, int Y_Cell);
#endif