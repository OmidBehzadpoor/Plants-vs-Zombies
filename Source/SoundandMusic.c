#include "SoundandMusic.h"
#include "LevelBase.h"
#include "levelselect.h"
#include "menu.h"
#include "raylib.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int CurrentBackgroundMusic = -1;
Sound menuOpen, menuSelect, menuHover, BackButtonSoundClick, Clocks, SetupLawnMowerSound, LawnmowerSound,
    EatPlantsSound[2], StartLevelSound, CollectSound, CollectSoundDiamond, PlantingSound[3], ZombieSound, EndGameSound,
    BulletHitSound[4], PeaShootSfx, VictorySound, MineFX[2], bleep, pause, pop1, pop2, FireFX, FreezeFX, CoinFX,
    ErrorShopFX, SunPackCollectFX, ErrorItemFX, UiErrorFX, LockErrorFX, UiClickFX;
Texture2D MusicPlayerPlay, MusicPlayerPause, spritesheetgreen, MusicPonter, MusicBGpic[4];
Music MusicBackgrand[4];
EatSound plantEatSoundPlayed;
Circle PlayMusicButton1 = {{811, 704}, 50};
Circle PlayMusicButton2 = {{1032, 422}, 32};
Circle MoveForward_5 = {{1154, 420}, 32};
Circle MoveBack_5 = {{912, 420}, 32};
Circle NextMusic = {{971, 706}, 50};
Circle PreviousMusic = {{652, 702}, 50};
const char *MusicNames[4] = {"Cerebrawl", "Garden", "Graze The Roof", "Grasswalk"};

bool isMusicPaused = false;
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
    CollectSoundDiamond = LoadSound("../assets/Sounds/chime.mp3");
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
    VictorySound = LoadSound("../assets/Sounds/Victory.ogg");
    MineFX[0] = LoadSound("../assets/Sounds/mine1.wav");
    MineFX[1] = LoadSound("../assets/Sounds/mine2.wav");
    bleep = LoadSound("../assets/Sounds/bleep.mp3");
    pause = LoadSound("../assets/Sounds/pause.mp3");
    pop1 = LoadSound("../assets/Sounds/limbspop.ogg");
    pop2 = LoadSound("../assets/Sounds/loadingbarflower.mp3");
    FireFX = LoadSound("../assets/Sounds/Fire.mp3");
    FreezeFX = LoadSound("../assets/Sounds/Freeze.mp3");
    CoinFX = LoadSound("../assets/Sounds/coin.mp3");
    ErrorShopFX = LoadSound("../assets/Sounds/Error.mp3");
    SunPackCollectFX = LoadSound("../assets/Sounds/SunPackCollect.mp3");
    ErrorItemFX = LoadSound("../assets/Sounds/ErrorItem.mp3");
    UiClickFX = LoadSound("../assets/Sounds/uiClick.mp3");
    UiErrorFX = LoadSound("../assets/Sounds/uierror.mp3");
    LockErrorFX = LoadSound("../assets/Sounds/lockerror.mp3");

    SetSoundVolume(menuHover, 0.25f);
    SetSoundVolume(menuSelect, 0.5f);
}
void UnloadMusicPlayer(void)
{
    for (int i = 0; i < 4; i++)
    {
        UnloadTexture(MusicBGpic[i]);
    }
    UnloadTexture(MusicPlayerPause);
    UnloadTexture(MusicPlayerPlay);
    UnloadTexture(spritesheetgreen);
    UnloadTexture(MusicPonter);
}
void InitMusicPlayer(void)
{
    MusicPlayerPause = LoadTexture("../assets/MusicPlayer/Pause.png");
    MusicPlayerPlay = LoadTexture("../assets/MusicPlayer/Play.png");
    spritesheetgreen = LoadTexture("../assets/MusicPlayer/spritesheetgreen.png");
    MusicPonter = LoadTexture("../assets/MusicPlayer/MusicPonter.png");
    MusicBGpic[0] = LoadTexture("../assets/MusicPlayer/MusicBG.png");
    MusicBGpic[1] = LoadTexture("../assets/MusicPlayer/MusicBG.png");
    MusicBGpic[2] = LoadTexture("../assets/MusicPlayer/MusicBG.png");
    MusicBGpic[3] = LoadTexture("../assets/MusicPlayer/MusicBG.png");
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
    if (CurrentBackgroundMusic != -1 &&
        (Screen == MENU || Screen == LEVEL_SELECT || Screen == SHOP || Screen == MUSICPLAYER))
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
void DrawMusicPlayer(void)
{
    if (!isMusicPaused)
    {
        DrawTexture(MusicPlayerPause, 0, 0, WHITE);
    }
    else
    {
        DrawTexture(MusicPlayerPlay, 0, 0, WHITE);
    }
    // DrawCircleLinesV(PlayMusicButton1.center, PlayMusicButton1.radius, RED);
    // DrawCircleLinesV(PlayMusicButton2.center, PlayMusicButton2.radius, RED);
    // DrawCircleLinesV(MoveBack_5.center, MoveBack_5.radius, RED);
    // DrawCircleLinesV(MoveForward_5.center, MoveForward_5.radius, RED);
    // DrawCircleLinesV(NextMusic.center, NextMusic.radius, RED);
    // DrawCircleLinesV(PreviousMusic.center, PreviousMusic.radius, RED);
    DrawMusicAnimationGrid(spritesheetgreen, 10, 10, (Vector2){432, 550}, 1.0f);
    if (CurrentBackgroundMusic != -1)
    {
        DrawTexture(MusicBGpic[CurrentBackgroundMusic], 442, 202, WHITE);
        DrawTextCentered(HorrorFont, MusicNames[CurrentBackgroundMusic], (Vector2){1035, 235}, 55, 2,
                         (Color){188, 253, 189, 255});
        char text[18];
        sprintf(text, "Song %d of 4", CurrentBackgroundMusic + 1);
        DrawTextCentered(HorrorFont, text, (Vector2){1035, 330}, 25, 2, (Color){222, 163, 105, 255});
    }
    DrawButton(&BackButton);
}
// تابع برای تغییر آهنگ (بعدی یا قبلی)
void ChangeMusicTrack(int direction)
{
    if (CurrentBackgroundMusic != -1)
    {
        StopMusicStream(MusicBackgrand[CurrentBackgroundMusic]);
        CurrentBackgroundMusic = (CurrentBackgroundMusic + direction + 4) % 4;
        PlayMusicStream(MusicBackgrand[CurrentBackgroundMusic]);
        isMusicPaused = false;
    }
}

// تابع برای پرش زمانی (جلو یا عقب)
void SeekMusic(float seconds)
{
    if (CurrentBackgroundMusic != -1)
    {
        float currentTime = GetMusicTimePlayed(MusicBackgrand[CurrentBackgroundMusic]);
        float totalTime = GetMusicTimeLength(MusicBackgrand[CurrentBackgroundMusic]);
        float newTime = currentTime + seconds;

        // محدود کردن زمان بین و انتهای آهنگ
        if (newTime < 0)
            newTime = 0;
        if (newTime > totalTime)
            newTime = totalTime - 0.1f;

        SeekMusicStream(MusicBackgrand[CurrentBackgroundMusic], newTime);
    }
}

void UpdateMusicPlayerLogic(void)
{
    if (CurrentBackgroundMusic == -1)
        return;

    Vector2 mousePos = GetMousePosition();
    ButtonAnimation(&BackButton);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {

        // --- دکمه توقف و پخش (Play/Pause) ---
        if (CheckCollisionPointCircle(mousePos, PlayMusicButton1.center, PlayMusicButton1.radius) ||
            CheckCollisionPointCircle(mousePos, PlayMusicButton2.center, PlayMusicButton2.radius))
        {

            isMusicPaused = !isMusicPaused;
            if (isMusicPaused)
                PauseMusicStream(MusicBackgrand[CurrentBackgroundMusic]);
            else
                ResumeMusicStream(MusicBackgrand[CurrentBackgroundMusic]);

            PlaySound(bleep);
        }

        // --- آهنگ بعدی (Next) ---
        if (CheckCollisionPointCircle(mousePos, NextMusic.center, NextMusic.radius))
        {
            ChangeMusicTrack(1);
            PlaySound(bleep);
        }

        // --- آهنگ قبلی (Previous) ---
        if (CheckCollisionPointCircle(mousePos, PreviousMusic.center, PreviousMusic.radius))
        {
            ChangeMusicTrack(-1);
            PlaySound(bleep);
        }

        // --- ۵ ثانیه جلو رفتن ---
        if (CheckCollisionPointCircle(mousePos, MoveForward_5.center, MoveForward_5.radius))
        {
            SeekMusic(5.0f);
        }

        // --- ۵ ثانیه عقب رفتن ---
        if (CheckCollisionPointCircle(mousePos, MoveBack_5.center, MoveBack_5.radius))
        {
            SeekMusic(-5.0f);
        }

        if (CheckCollisionPointRec(mousePos, BackButton.ClickArea))
        {
            PlaySound(bleep);

            Screen = MENU;
        }
    }
}
void DrawMusicAnimationGrid(Texture2D spriteSheet, int rows, int cols, Vector2 position, float scale)
{
    if (CurrentBackgroundMusic == -1)
        return;

    // ۱. محاسبه درصد پخش آهنگ
    float timePlayed = GetMusicTimePlayed(MusicBackgrand[CurrentBackgroundMusic]);
    float timeLength = GetMusicTimeLength(MusicBackgrand[CurrentBackgroundMusic]);
    float progress = timePlayed / timeLength;

    // ۲. محاسبه کل فریم‌ها و فریم فعلی
    int totalFrames = rows * cols;
    int currentFrame = (int)(progress * totalFrames);

    if (currentFrame >= totalFrames)
        currentFrame = totalFrames - 1;

    // ۳. پیدا کردن ردیف و ستون فریم فعلی
    // فریم اول در ردیف ۰ و ستون ۰ است
    int currentRow = currentFrame / cols;
    int currentCol = currentFrame % cols;

    // ۴. تعیین ابعاد هر فریم در شیت
    float frameWidth = (float)spriteSheet.width / cols;
    float frameHeight = (float)spriteSheet.height / rows;

    // ۵. ناحیه منبع (Source Rectangle) در عکس اصلی
    Rectangle sourceRec = {currentCol * frameWidth, currentRow * frameHeight, frameWidth, frameHeight};

    // ۶. ناحیه مقصد (Destination Rectangle) در صفحه نمایش
    Rectangle destRec = {position.x, position.y, frameWidth * scale, frameHeight * scale};

    Vector2 origin = {0, 0};

    DrawTexturePro(spriteSheet, sourceRec, destRec, origin, 0.0f, WHITE);
    DrawTexture(MusicPonter, position.x + (frameWidth / 100) * currentFrame - 8, position.y - 1, WHITE);
    const char *currentTimeText = TextFormat("%d:%02d", (int)timePlayed / 60, (int)timePlayed % 60);
    const char *totalTimeText = TextFormat("%d:%02d", (int)timeLength / 60, (int)timeLength % 60);
    int currentTextWidth = MeasureText(currentTimeText, 20);
    DrawText(currentTimeText, position.x - currentTextWidth - 10, position.y, 20, WHITE);

    DrawText(totalTimeText, position.x + frameWidth + 10, position.y, 20, WHITE);
}
