#include "LevelBase.h"
#include "Level1.h"
#include "Plant.h"
#include "SoundandMusic.h"
#include "Zombie.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Font HorrorFont;
Texture2D Map, OFFlawnMowerRow, SunBankPic, Frame, selectpic, Price[5], iconPic[5], GameOver, Victory, ButtonWin,
    ButtonLose;
Texture2D SunFlowerSheet, LawnMowerSheet, SunElementSheet, ChomperSheet, RoseSheet, PeashooterSheet, ZombieNormal1,
    ZombieNormalAttack1, ZombieNormal2, pea, PeaBulletHit, OverhealBar, LifetimeBar, HpBar, LockPic, RingBar,
    ThinkingZombiePic, ThinkingZombieAttackPic, LoseNowpic, YesOrNopic, TimeFramePic ,PotatoMineNotReadyPic ,PotatoMineMashedPic , PotatoMineSheet , ExplosionSpudow;
AnimatedObject icon[5];
Rectangle LoseNowButton;
Rectangle YesButton = {900, 560, 305, 95};
Rectangle NoButton = {500, 560, 290, 95};
LevelInfo *CurrentLevelInfo = NULL;
Color GoldOrange = {255, 188, 0, 255};
Color SaffronYellow = { 222,200 ,95 ,255 };
bool restart = true;
int ZombiesSpawned = 0;
int ZombiesKilled = 0;
float SurvivalTimer = 0.0f;
float BestSurvivalTime = 0.0f;
int bestHours;
int bestMinutes;
int bestSeconds;
int SurvivalHours;
int SurvivalMinutes;
int SurvivalSeconds;

float SunTimer, ZombieTimer;
bool FirstRun = true;

void InitGame(void)
{
    InitLevelTexture();
    InitLevelFont();
}
void InitLevelTexture(void)
{
    Map = LoadTexture("../assets/map/level1_map.png");
    SunBankPic = LoadTexture("../assets/Level1/SunBack.png");
    selectpic = LoadTexture("../assets/Level1/Select.png");
    OFFlawnMowerRow = LoadTexture("../assets/Level1/lawnMower_Idle.png");
    SunFlowerSheet = LoadTexture("../assets/Level1/SunFlower.png");
    PeashooterSheet = LoadTexture("../assets/Level1/PeashooterSheet.png");
    ZombieNormal2 = LoadTexture("../assets/Level1/NormalZombieRunSheet.png");
    ZombieNormal1 = LoadTexture("../assets/Level1/ZombieSheet.png");
    ZombieNormalAttack1 = LoadTexture("../assets/Level1/ZombieAttackSheet.png");
    ChomperSheet = LoadTexture("../assets/Level1/ChomperSheet.png");
    RoseSheet = LoadTexture("../assets/Level1/roseSheet.png");
    LawnMowerSheet = LoadTexture("../assets/Level1/lawnMower_Active-Sheet.png");
    SunElementSheet = LoadTexture("../assets/Level1/Sun_Sheet.png");
    Frame = LoadTexture("../assets/Level1/Frame.png");
    pea = LoadTexture("../assets/Level1/PB.png");
    PeaBulletHit = LoadTexture("../assets/Level1/PeaBulletHit.png");
    HpBar = LoadTexture("../assets/Level1/HpBar.png");
    LifetimeBar = LoadTexture("../assets/Level1/LifetimeBar.png");
    OverhealBar = LoadTexture("../assets/Level1/OverhealBar.png");
    GameOver = LoadTexture("../assets/Level1/GameOver.png");
    Victory = LoadTexture("../assets/Level1/Victory.png");
    ButtonWin = LoadTexture("../assets/Level1/Button.png");
    ButtonLose = LoadTexture("../assets/Level1/Button1.png");
    LockPic = LoadTexture("../assets/Level1/lock.png");
    RingBar = LoadTexture("../assets/Level1/RingBar.png");
    ThinkingZombieAttackPic = LoadTexture("../assets/Level2/FlagZombieAttackSheet.png");
    ThinkingZombiePic = LoadTexture("../assets/Level2/FlagZombieSheet.png");
    LoseNowpic = LoadTexture("../assets/Level1/LoseNow.png");
    LoseNowButton = (Rectangle){1495, 785, LoseNowpic.width, LoseNowpic.height};
    YesOrNopic = LoadTexture("../assets/Level1/YorN.png");
    TimeFramePic = LoadTexture("../assets/Level1/TimeFrame.png");
    PotatoMineMashedPic = LoadTexture("../assets/Level2/PotatoMineMashed.png") ;
    PotatoMineNotReadyPic = LoadTexture("../assets/Level2/PotatoMineNotReady.png") ; 
    PotatoMineSheet = LoadTexture("../assets/Level2/PotatoMineSheet.png") ;
    ExplosionSpudow = LoadTexture("../assets/Level2/ExplosionSpudow.png") ;
    LoadBestTime();
    for (int i = 0; i <5; i++)
    {
        char temp[100];

        sprintf(temp, "../assets/Level1/icon%d.png", i);
        iconPic[i] = LoadTexture(temp);
        sprintf(temp, "../assets/Level1/price%d.png", i);
        Price[i] = LoadTexture(temp);
    }
}
void InitLevelFont(void)
{
    HorrorFont = LoadFont("../assets/Level1/houseofterrormedium.ttf");
}
void SaveBestTime(void)
{
    SaveFileData("../assets/Level1/BestTime.dat", &BestSurvivalTime, sizeof(float));
}

void LoadBestTime(void)
{
    if (FileExists("../assets/Level1/BestTime.dat"))
    {
        unsigned int bytesRead = 0;
        unsigned char *data = LoadFileData("../assets/Level1/BestTime.dat", &bytesRead);
        if (data != NULL && bytesRead == sizeof(float))
        {
            BestSurvivalTime = *(float *)data;
            CalculateBestTimeHMS();
            UnloadFileData(data);
        }
    }
}
void CalculateBestTimeHMS(void)
{
    bestHours = BestSurvivalTime / 3600;
    bestMinutes = ((int)BestSurvivalTime % 3600) / 60;
    bestSeconds = (int)BestSurvivalTime % 60;
}
void CalculateSurvivalTimeHMS(void)
{
    SurvivalHours = SurvivalTimer / 3600;
    SurvivalMinutes = ((int)SurvivalTimer % 3600) / 60;
    SurvivalSeconds = (int)SurvivalTimer % 60;
}