#pragma once
#ifndef SOUNDANDMUSIC_H
#define SOUNDANDMUSIC_H
#include "raylib.h"
typedef struct EatSound
{
    bool Active;
    float Timer;
    int CurrentSound;
} EatSound;
extern EatSound plantEatSoundPlayed;
extern bool isMusicPaused ;

extern Sound menuOpen, menuSelect, menuHover, BackButtonSoundClick, Clocks, SetupLawnMowerSound, LawnmowerSound,
    EatPlantsSound[2], StartLevelSound, CollectSound, PlantingSound[3], ZombieSound, EndGameSound, BulletHitSound[4],
    PeaShootSfx , VictorySound;
extern Music MusicBackgrand[4];
void InitSound(void);
void InitMusic(void);
void UpdateMusic(void);
void PlayRandomMenuMusic(void);
void UnloadSoundAndMusic(void);
void UpdateEatSound(EatSound *eat);
void PlayEatSound(EatSound *eat);
#endif