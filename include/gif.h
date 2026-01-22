#pragma once
#ifndef GIF_H
#define GIF_H

#include "raylib.h"
#include "stdlib.h"
typedef struct AnimatedObject
{
    Texture2D texture;
    Rectangle *frames;

    int frameCount;
    int currentFrame;
    float frameTimer;
    float frameDelay;

    float posX, posY;
    float speedX, speedY;
    float finalX, finalY;
} AnimatedObject;
AnimatedObject GenerateAnimatedObject(const Texture2D *Sheet, int frameWidth, int frameHeight, float frameDelay,
                                      float startX, float startY, float speedX, float speedY, float finalX,
                                      float finalY);
AnimatedObject LoadAnimatedObject(const char *fileName, int frameWidth, int frameHeight, float frameDelay, float startX,
                                  float startY, float speedX, float speedY, float finalX, float finalY);
void UpdateAnimatedObject(AnimatedObject *obj);
void DrawAnimatedObject(const AnimatedObject *obj, Color tint);
void UnloadAnimatedObject(AnimatedObject *obj);
void ResetAnimatedObject(AnimatedObject *obj);
#endif