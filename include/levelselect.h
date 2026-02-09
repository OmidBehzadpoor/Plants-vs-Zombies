#pragma once
#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include "raylib.h"
#include "stdlib.h"
extern bool EXIT;
extern Texture2D BackgroundLevelselect;
extern Texture2D LVL1Picture;
extern Texture2D LVL2Picture;
extern Texture2D LVL3Picture;
extern Texture2D LVL4Picture;
extern Vector2 CenterCircle;
extern float Radius1;
extern float Radius2;
extern float Radius3;
extern float Radius4;
extern float RadiusBackButton;
typedef struct Button
{

    Texture2D Picture;
    Rectangle ClickArea;
    float targetScale;
    float DefaultScale;
    float ScaleNow;
    float scaleSpeed;
    Vector2 CenterPosition;
} Button;
typedef struct CircleButtonAnim
{

    Texture2D Picture;
    float Radius;
    float targetScale;
    float DefaultScale;
    float ScaleNow;
    float scaleSpeed;
    float rotationSpeed;
    float rotation;
    Vector2 CenterPosition;
    bool IsHover;
    bool rotational;
} CircleButtonAnim;
extern Button BackButton;

void ButtonAnimation(Button *Button);
void Initlevelselect(void);
void Drawlevelselect(void);
void Updatelevelselect(void);
void Unloadlevelselect(void);
void MouseSelection(void);
void DrawButton(Button *Button);
void DrawCircleButton(CircleButtonAnim *btn);
void CircleButtonAnimation(CircleButtonAnim *btn);
#endif