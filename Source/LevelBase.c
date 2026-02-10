#include "LevelBase.h"
#include "Chomper.h"
#include "Debug.h"
#include "Diamond.h"
#include "LawnMower.h"
#include "Level1.h"
#include "Level4.h"
#include "LevelUi.h"
#include "Peashooter.h"
#include "Plant.h"
#include "PotatoMine.h"
#include "Rose.h"
#include "Shop.h"
#include "SoundandMusic.h"
#include "Sun.h"
#include "Sunflower.h"
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
    ButtonLose, map_naght;
Texture2D SunFlowerSheet, LawnMowerSheet, SunElementSheet, ChomperSheet, RoseSheet, PeashooterSheet, ZombieNormal1,
    ZombieNormalAttack1, ZombieNormal2, pea, PeaBulletHit, OverhealBar, LifetimeBar, HpBar, LockPic, RingBar,
    ThinkingZombiePic, ThinkingZombieAttackPic, LoseNowpic, YesOrNopic, TimeFramePic, PotatoMineNotReadyPic,
    PotatoMineMashedPic, PotatoMineSheet, ExplosionSpudow;
AnimatedObject icon[5];
Rectangle LoseNowButton;
Rectangle YesButton = {900, 560, 305, 95};
Rectangle NoButton = {500, 560, 290, 95};
LevelInfo *CurrentLevelInfo = NULL;
Color GoldOrange = {255, 188, 0, 255};
Color SaffronYellow = {222, 200, 95, 255};
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
    InitSpecialItems();
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
    PotatoMineMashedPic = LoadTexture("../assets/Level2/PotatoMineMashed.png");
    PotatoMineNotReadyPic = LoadTexture("../assets/Level2/PotatoMineNotReady.png");
    PotatoMineSheet = LoadTexture("../assets/Level2/PotatoMineSheet.png");
    ExplosionSpudow = LoadTexture("../assets/Level2/ExplosionSpudow.png");
    map_naght = LoadTexture("../assets/map/level3_map.png");
    LoadBestTime();
    for (int i = 0; i < 5; i++)
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
void SaveGame(void)
{
    FILE *file = fopen("savegame.bin", "wb");
    if (file != NULL)
    {
        fwrite(&DiamondBank, sizeof(int), 1, file);
        fwrite(&FireStorm.PlayerInventory, sizeof(int), 1, file);
        fwrite(&FreezeBurst.PlayerInventory, sizeof(int), 1, file);
        fwrite(&PotatoMineItems.PlayerInventory, sizeof(int), 1, file);
        fwrite(&SunPack.PlayerInventory, sizeof(int), 1, file);
        fwrite(&FireStorm.StoreInventory, sizeof(int), 1, file);
        fwrite(&FreezeBurst.StoreInventory, sizeof(int), 1, file);
        fwrite(&PotatoMineItems.StoreInventory, sizeof(int), 1, file);
        fwrite(&SunPack.StoreInventory, sizeof(int), 1, file);

        fclose(file);
    }
}
void LoadGame(void)
{
    FILE *file = fopen("savegame.bin", "rb"); // باز کردن فایل برای خواندن
    if (file != NULL)
    {
        fread(&DiamondBank, sizeof(int), 1, file);
        fread(&FireStorm.PlayerInventory, sizeof(int), 1, file);
        fread(&FreezeBurst.PlayerInventory, sizeof(int), 1, file);
        fread(&PotatoMineItems.PlayerInventory, sizeof(int), 1, file);
        fread(&SunPack.PlayerInventory, sizeof(int), 1, file);
        fread(&FireStorm.StoreInventory, sizeof(int), 1, file);
        fread(&FreezeBurst.StoreInventory, sizeof(int), 1, file);
        fread(&PotatoMineItems.StoreInventory, sizeof(int), 1, file);
        fread(&SunPack.StoreInventory, sizeof(int), 1, file);
        fclose(file);
    }
    else
    {
        DiamondBank = 0;
    }
}

void ResetCellContent(void)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            CellContent[i][j] = EMPTY;
        }
    }
}
void ResetAllAnimation(void)
{
    // ! نشتی مموری در سان و دایموند
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        ResetAnimatedObject(&LawnMower[i].LawnMowerObj);
    }
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        ResetAnimatedObject(&SunFlower[i].SunFlowerObj);
        ResetAnimatedObject(&Peashooter[i].PeashooterObj);
        ResetAnimatedObject(&Chomper[i].ChomperObj);
        ResetAnimatedObject(&Rose[i].RoseObj);
        ResetAnimatedObject(&PotatoMine[i].PotatoMineObj);
        PotatoMine[i].Explosion = false;
        for (int j = 0; j < 10; j++)
        {
            ResetAnimatedObject(&Peashooter[i].Pea[j].PeaBulletHit.BulletHitObj);
            ResetAnimatedObject(&Peashooter[i].Pea[j].Pea);
        }
    }
    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++)
    {
        ZombieNormal[i].isAlive = false;
        ZombieNormal[i].Attack = false;
        ResetAnimatedObject(&ZombieNormal[i].ZombieObj);
    }
    for (int i = 0; i < CurrentLevelInfo->MaxThinkingZombieAllowed; i++)
    {
        ThinkingZombie[i].isAlive = false;
        ThinkingZombie[i].Attack = false;
        ResetAnimatedObject(&ThinkingZombie[i].ZombieObj);
    }
    for (int i = 0; i < 5; i++)
    {
        ResetAnimatedObject(&icon[i]);
    }
}

void CheckWin(void)
{
    if (CurrentLevelInfo->ZombieNormal.ZombieSpawned < CurrentLevelInfo->MaxZombieNormalAllowed)
        return;
    if (CurrentLevelInfo->ThinkingZombie.ZombieSpawned < CurrentLevelInfo->MaxThinkingZombieAllowed)
        return;
    if (ZombiesSpawned == CurrentLevelInfo->MaxZombieNormalAllowed + CurrentLevelInfo->MaxThinkingZombieAllowed &&
        ZombiesKilled == CurrentLevelInfo->MaxZombieNormalAllowed + CurrentLevelInfo->MaxThinkingZombieAllowed)
    {
        CurrentGameState = WIN;
        PotatoMineItems.StoreInventory += 5;
        FireStorm.StoreInventory += 5;
        FreezeBurst.StoreInventory += 5;
        SunPack.StoreInventory += 5;

        GenerateDiamond(DiamondElementArray, GENERATERANDOM, GENERATERANDOM);
        GenerateDiamond(DiamondElementArray, GENERATERANDOM, GENERATERANDOM);
        GenerateDiamond(DiamondElementArray, GENERATERANDOM, GENERATERANDOM);
        GenerateDiamond(DiamondElementArray, GENERATERANDOM, GENERATERANDOM);
        for (int i = 0; i < 10; i++)
        {
            if (DiamondElementArray[i].Available)
            {
                PlaySound(CollectSound);
                DiamondElementArray[i].IsCollected = true;
                //   DrawTexture(MapDiamond, 31, 105, WHITE);
                DiamondElementArray[i].Diamond.finalX = 31;
                DiamondElementArray[i].Diamond.finalY = 105;

                DiamondElementArray[i].Diamond.speedX = (31 - DiamondElementArray[i].Diamond.posX) / 1.5;
                DiamondElementArray[i].Diamond.speedY = (105 - DiamondElementArray[i].Diamond.posY) / 1.5;
            }
        }
        SaveGame();
        PlaySound(VictorySound);
    }
}
void CheckLose(void)
{
    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++)
    {
        if (ZombieNormal[i].isAlive && ZombieNormal[i].Markaz.x < CurrentLevelInfo->START_X)
        {

            int Chance = ZombiesKilled /
                         (CurrentLevelInfo->MaxThinkingZombieAllowed + CurrentLevelInfo->MaxZombieNormalAllowed) * 100;
            if (CurrentLevelInfo->ThinkingZombie.InfiniteSpan || CurrentLevelInfo->ZombieNormal.InfiniteSpan)
            {
                Chance = ZombiesKilled;
                if (Chance > 100)
                {
                    Chance = 100;
                }
            }
            CurrentGameState = LOSE;
            PlaySound(EndGameSound);
            CreatingDiamondLuck(DiamondElementArray, GENERATERANDOM, GENERATERANDOM, Chance);
            CreatingDiamondLuck(DiamondElementArray, GENERATERANDOM, GENERATERANDOM, Chance);
            for (int i = 0; i < 10; i++)
            {
                if (DiamondElementArray[i].Available)
                {
                    PlaySound(CollectSound);
                    DiamondElementArray[i].IsCollected = true;
                    //   DrawTexture(MapDiamond, 31, 105, WHITE);
                    DiamondElementArray[i].Diamond.finalX = 31;
                    DiamondElementArray[i].Diamond.finalY = 105;

                    DiamondElementArray[i].Diamond.speedX = (31 - DiamondElementArray[i].Diamond.posX) / 1.5;
                    DiamondElementArray[i].Diamond.speedY = (105 - DiamondElementArray[i].Diamond.posY) / 1.5;
                }

                SaveGame();
                return;
            }
        }
    }
    for (int i = 0; i < CurrentLevelInfo->MaxThinkingZombieAllowed; i++)
    {
        if (ThinkingZombie[i].isAlive && ThinkingZombie[i].Markaz.x < CurrentLevelInfo->START_X)
        {
            int Chance = ZombiesKilled /
                         (CurrentLevelInfo->MaxThinkingZombieAllowed + CurrentLevelInfo->MaxZombieNormalAllowed) * 100;
            if (CurrentLevelInfo->ThinkingZombie.InfiniteSpan || CurrentLevelInfo->ZombieNormal.InfiniteSpan)
            {
                Chance = ZombiesKilled;
                if (Chance > 100)
                {
                    Chance = 100;
                }
            }
            CurrentGameState = LOSE;
            PlaySound(EndGameSound);
            CreatingDiamondLuck(DiamondElementArray, GENERATERANDOM, GENERATERANDOM, Chance);
            CreatingDiamondLuck(DiamondElementArray, GENERATERANDOM, GENERATERANDOM, Chance);

            for (int i = 0; i < 10; i++)
            {
                if (DiamondElementArray[i].Available)
                {
                    PlaySound(CollectSound);
                    DiamondElementArray[i].IsCollected = true;
                    //   DrawTexture(MapDiamond, 31, 105, WHITE);
                    DiamondElementArray[i].Diamond.finalX = 31;
                    DiamondElementArray[i].Diamond.finalY = 105;

                    DiamondElementArray[i].Diamond.speedX = (31 - DiamondElementArray[i].Diamond.posX) / 1.5;
                    DiamondElementArray[i].Diamond.speedY = (105 - DiamondElementArray[i].Diamond.posY) / 1.5;
                }
            }
            SaveGame();
            return;
        }
    }
}
void InitAllAnimation(void)
{
    for (int i = 0; i < 5; i++)
    {
        int pixel = (i == 2) ? 80 : 71;
        int pixelY = (i == 2) ? 14 : 25;
        int k = (i == 2 || i == 4) ? 12 : 0;

        icon[i] = GenerateAnimatedObject(&iconPic[i], pixel, pixel, 80, 370 - k + Frame.width * i, pixelY, 0, 0,
                                         370 - k + Frame.width * i, 25);
    }
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        LawnMower[i].LawnMowerObj = GenerateAnimatedObject(
            &LawnMowerSheet, 70, 57, 80, CurrentLevelInfo->START_X - 95.0f / 305.0f * CurrentLevelInfo->START_X,
            CurrentLevelInfo->START_Y + (40.0f / 61.0f * RectangleHeight / 2) + RectangleHeight * i, 50, 0,
            15.0f / 305.0f * CurrentLevelInfo->START_X + CurrentLevelInfo->START_X,
            CurrentLevelInfo->START_Y + (40.0f / 61.0f * RectangleHeight / 2) + RectangleHeight * i);
    }
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        SunFlower[i].SunFlowerObj = GenerateAnimatedObject(&SunFlowerSheet, 80, 80, 60, 0, 0, 0, 0, 0, 0);
        SunFlower[i].Base.isAlive = false;
        SunFlower[i].Base.Health = 100;
        Rose[i].RoseObj = GenerateAnimatedObject(&RoseSheet, 80, 80, 80, 0, 0, 0, 0, 0, 0);
        Rose[i].Base.Health = 100;
        Rose[i].Base.isAlive = false;
        Chomper[i].ChomperObj = GenerateAnimatedObject(&ChomperSheet, 80, 80, 80, 0, 0, 0, 0, 0, 0);
        Chomper[i].Base.isAlive = false;
        Peashooter[i].PeashooterObj = GenerateAnimatedObject(&PeashooterSheet, 80, 80, 16.75, 0, 0, 0, 0, 0, 0);
        Peashooter[i].Base.isAlive = false;
        Peashooter[i].FireTimer = 0;
        Peashooter[i].Firing = false;
        PotatoMine[i].PotatoMineObj = GenerateAnimatedObject(&PotatoMineNotReadyPic, 75, 55, 80, 0, 0, 0, 0, 0, 0);
        PotatoMine[i].Base.isAlive = false;

        for (int j = 0; j < 10; j++)
        {
            Peashooter[i].Pea[j].isActive = false;
            Peashooter[i].Pea[j].Pea = GenerateAnimatedObject(&pea, 29, 32, 80, 0, 0, 0, 0, 0, 0);
            Peashooter[i].Pea[j].isActive = false;
            Peashooter[i].Pea[j].PeaBulletHit.DisplayTime = 0.1f;
            Peashooter[i].Pea[j].PeaBulletHit.DisplayTimer = 0.0;
            Peashooter[i].Pea[j].PeaBulletHit.isActive = false;
            Peashooter[i].Pea[j].PeaBulletHit.BulletHitObj =
                GenerateAnimatedObject(&PeaBulletHit, 49, 43, 100000, 0, 0, 0, 0, 0, 0);
        }
    }

    SunTimer = 0;
    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        SunElementArray[i].sun = GenerateAnimatedObject(&SunElementSheet, 79, 79, 60, 0, 0, 0, 45, 0, 0);
        SunElementArray[i].Available = false;
        SunElementArray[i].time = 0.0f;
    }
    for (int i = 0; i < 10; i++)
    {
        DiamondElementArray[i].Diamond = GenerateAnimatedObject(&MapDiamond, 58, 47, 10000, 0, 0, 0, 45, 0, 0);
        DiamondElementArray[i].Available = false;
        DiamondElementArray[i].Time = 0.0f;
    }
    ZombieTimer = 0;
    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++)
    {
        ZombieNormal[i].isAlive = false;
        ZombieNormal[i].Attack = false;
        ZombieNormal[i].ZombieObj = GenerateAnimatedObject(&ZombieNormal1, 12, 12, 0, 0, 0, 0, 0, 0, 0);
    }
    for (int i = 0; i < CurrentLevelInfo->MaxThinkingZombieAllowed; i++)
    {
        ThinkingZombie[i].isAlive = false;
        ThinkingZombie[i].Attack = false;
        ThinkingZombie[i].ZombieObj = GenerateAnimatedObject(&ThinkingZombiePic, 12, 12, 0, 0, 0, 0, 0, 0, 0);
    }
}
void SetupLawnMowerAnimation(void)
{
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        LawnMower[i].LawnMowerObj = GenerateAnimatedObject(
            &LawnMowerSheet, 70, 57, 80, CurrentLevelInfo->START_X - 95.0f / 305.0f * CurrentLevelInfo->START_X,
            CurrentLevelInfo->START_Y + (40.0f / 61.0f * RectangleHeight / 2) + RectangleHeight * i, 50, 0,
            15.0f / 305.0f * CurrentLevelInfo->START_X + CurrentLevelInfo->START_X, 270 + RectangleHeight * i);
        LawnMower[i].Y_Cell = i;
        LawnMower[i].X_Cell = 0;
        LawnMower[i].Available = true;
        LawnMower[i].isActive = true;
        CellContent[i][0] = LAWNMOWER;
        LawnMower[i].Markaz.x = LawnMower[i].LawnMowerObj.posX + LawnMower[i].LawnMowerObj.frames[0].width / 2;
        LawnMower[i].Markaz.y = LawnMower[i].LawnMowerObj.posY + LawnMower[i].LawnMowerObj.frames[0].height / 2;
    }
}
