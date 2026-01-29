#include "menu.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "SoundandMusic.h"
int CurrentBackgroundMusic = -1;
Sound menuOpen, menuSelect, menuHover, BackButtonSoundClick, Clocks, SetupLawnMowerSound, LawnmowerSound,
    EatPlantsSound[2], StartLevelSound, CollectSound, PlantingSound[3], ZombieSound, EndGameSound, BulletHitSound[4] , PeaShootSfx , VictorySound;
Music MusicBackgrand[4];
EatSound plantEatSoundPlayed;

void InitSound(void)
{
    BackButtonSoundClick = LoadSound("../assets/Sounds/buttonclick.mp3");
    SetSoundVolume(BackButtonSoundClick, 0.5f);
    menuSelect = LoadSound("../assets/Sounds/kernelpult.ogg");
    menuHover = LoadSound("../assets/Sounds/puff.mp3");
    Clocks = LoadSound("../assets/Sounds/Clocks.ogg");
    SetupLawnMowerSound = LoadSound("../assets/Sounds/hydraulic.wav");
    LawnmowerSound = LoadSound("../assets/Sounds/lawnmower.mp3");
    EatPlantsSound[0] = LoadSound("../assets/Sounds/chomp.ogg");
    EatPlantsSound[1] = LoadSound("../assets/Sounds/chomp2.mp3");
    StartLevelSound = LoadSound("../assets/Sounds/awooga.mp3");
    CollectSound = LoadSound("../assets/Sounds/sparkles.mp3");
    PlantingSound[0] = LoadSound("../assets/Sounds/plant1.mp3");
    PlantingSound[1] = LoadSound("../assets/Sounds/plant2.mp3");
    PlantingSound[2] = LoadSound("../assets/Sounds/seedlift.mp3");
    ZombieSound = LoadSound("../assets/Sounds/zombie.mp3");
    EndGameSound = LoadSound("../assets/Sounds/GameOver.mp3");
    BulletHitSound[0] = LoadSound("../assets/Sounds/splat.mp3");
    BulletHitSound[1] = LoadSound("../assets/Sounds/splat1.mp3");
    BulletHitSound[2] = LoadSound("../assets/Sounds/splat2.mp3");
    BulletHitSound[3] = LoadSound("../assets/Sounds/splat3.mp3");
   PeaShootSfx = LoadSound("../assets/Sounds/shoop.ogg");
   VictorySound =LoadSound("../assets/Sounds/Victory.ogg");
    SetSoundVolume(menuHover, 0.25f);
    SetSoundVolume(menuSelect, 0.5f);
}
void InitMusic(void)
{
    MusicBackgrand[0] = LoadMusicStream("../assets/Sounds/Cerebrawl.mp3");
    MusicBackgrand[1] = LoadMusicStream("../assets/Sounds/Garden.ogg");
    MusicBackgrand[2] = LoadMusicStream("../assets/Sounds/GrazeTheRoof2.mp3");
    MusicBackgrand[3] = LoadMusicStream("../assets/Sounds/IZ.mp3");
    for (int i = 0; i < 4; i++)
    {
        SetMusicVolume(MusicBackgrand[i], 0.5f);
    }
}
void UpdateMusic(void)
{
    if (CurrentBackgroundMusic != -1 && (Screen == MENU || Screen == LEVEL_SELECT))
    {
        UpdateMusicStream(MusicBackgrand[CurrentBackgroundMusic]);
    }
}

void UnloadSoundAndMusic(void)
{
    UnloadSound(menuOpen);
    UnloadSound(menuSelect);
    UnloadSound(menuHover);
    UnloadSound(BackButtonSoundClick);
    for (int i = 0; i < 4; i++)
    {
        UnloadMusicStream(MusicBackgrand[i]);
    }
}

void PlayRandomMenuMusic(void)
{
    if (CurrentBackgroundMusic != -1)
    {
        StopMusicStream(MusicBackgrand[CurrentBackgroundMusic]);
    }

    CurrentBackgroundMusic = rand() % 4;

    MusicBackgrand[CurrentBackgroundMusic].looping = true;
    PlayMusicStream(MusicBackgrand[CurrentBackgroundMusic]);
}

void UpdateEatSound(EatSound *eat)
{
    if (eat->Active)
    {
        eat->Timer -= GetFrameTime();
        if (eat->Timer <= 0.0f)
        {
            eat->Active = false;
        }
    }
    return;
}
void PlayEatSound(EatSound *eat)
{
    if (!eat->Active)
    {
        eat->CurrentSound = rand() % 2;

        PlaySound(EatPlantsSound[eat->CurrentSound]);

        eat->Timer = (float)EatPlantsSound[eat->CurrentSound].frameCount /
                     (float)EatPlantsSound[eat->CurrentSound].stream.sampleRate;

        eat->Active = true;
    }
}