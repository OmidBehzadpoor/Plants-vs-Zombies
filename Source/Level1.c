#include "Level1.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Texture2D Map, OFFlawnMowerRow, SunBankPic, Frame, selectpic, Price[4];
Texture2D SunFlowerSheet, LawnMowerSheet, SunElementSheet, ChomperSheet, RoseSheet, PeashooterSheet, ZombieNormal1,
    ZombieNormalAttack1, ZombieNormal2, pea, PeaBulletHit;
AnimatedObject icon[4];
LawnMowerElement LawnMower[ROWLAWNMOWER];
LevelInfo Level1Info;
Color GoldOrange = {255, 188, 0, 255};
WarningMessage LackSunWarning, LockWarning;
Rectangle MapCell[ROWS][COLUMNS];
MapContent CellContent[ROWS][COLUMNS] = {EMPTY};
MapContent Selection = EMPTY;
SunElement SunElementArray[MAXSUNELEMENT];
SunflowerElement SunFlower[MAXNUMITEMS];
PeashooterElement Peashooter[MAXNUMITEMS];
ChomperElement Chomper[MAXNUMITEMS];
RoseElement Rose[MAXNUMITEMS];
Zombies ZombieNormal[MAXNUZOMBIES];
Font HorrorFont;
int SunBank = 9999;
int CurrentSunIndex = 0;
double lvl1Runtime = 0;
float RectangleWidth = (float)(END_X - START_X) / COLUMNS; // 107.5
float RectangleHeight = (float)(END_Y - START_Y) / ROWS;   // 122
float SunTimer, ZombieTimer;
bool FirstRun = true;

void InitLevel1(void)
{
    InitLevel1Texture();
    InitLevel1Font();
    InitLevel1Animation();
    InitLevel1MapCell();
    InitLevel1Info();
}

void DrawLevel1(void)
{

    DrawLevelItems();
    if (Selection != EMPTY)
    {
        DrawSelectionTick();
    }
    DrawPlants();
    DrawSunElement();
    if (LackSunWarning.isActive)
    {
        DrawLackSunWarning();
    }
    if (LockWarning.isActive)
    {
        DrawLockWarning();
    }
    for (int i = 0; i < MAXNUZOMBIES; i++)
    {
        if (ZombieNormal[i].isAlive)
        {
            DrawAnimatedObject(&ZombieNormal[i].ZombieObj, WHITE);
        }
    }

    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            if (Peashooter[i].Pea[k].isActive)
            {
                DrawAnimatedObject(&Peashooter[i].Pea[k].Pea, WHITE);
            }
            if (Peashooter[i].Pea[k].PeaBulletHit.isActive)
            {
                DrawAnimatedObject(&Peashooter[i].Pea[k].PeaBulletHit.BulletHitObj, WHITE);
            }
        }
    }

    for (int i = 0; i < MAXNUZOMBIES; i++) // for debug
    {
        if (ZombieNormal[i].isAlive)
        {
            DrawText("O", ZombieNormal[i].ZombieObj.posX + ZombieNormal[i].ZombieObj.frames[0].width / 2,
                     ZombieNormal[i].ZombieObj.posY + ZombieNormal[i].ZombieObj.frames[0].height / 2, 20, RED);
            DrawRectangleLines((int)ZombieNormal[i].CollisionBox.x, (int)ZombieNormal[i].CollisionBox.y,
                               (int)ZombieNormal[i].CollisionBox.width, (int)ZombieNormal[i].CollisionBox.height,
                               RED // رنگ مستطیل
            );
        }
    }
    // رسم HitBox دایره‌ای تیرها برای دیباگ
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            if (Peashooter[i].Pea[k].isActive)
            {
                DrawCircleLines((int)Peashooter[i].Pea[k].Markaz.x, // مرکز X
                                (int)Peashooter[i].Pea[k].Markaz.y, // مرکز Y
                                Peashooter[i].Pea[k].Radius,        // شعاع
                                BLUE                                // رنگ دایره (قرمز برای دیباگ)
                );
            }
        }
    }

    CellularNetworkMap(); // for debug
}
void UpdateLevel1(void)
{

    UpdateLevelItems();
    UpdateSUNELEMENT();
    UpdatePlantsTimer();
    UpdatePlantsAnimation();
    CooldownUpdate();
    if (LackSunWarning.isActive)
    {
        UpdateLackSunWarning();
    }
    if (LockWarning.isActive)
    {
        UpdateLockWarning();
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        CheckSelect();
        UpdateSelectionItems();
        CollectSunElement();
    }
    ZombieTimer += GetFrameTime();
    if (ZombieTimer >= Level1Info.ZombieNormal.Regenerate)
    {
        ZombieTimer = 0;
        for (int i = 0; i < MAXNUZOMBIES; i++)
        {
            if (!ZombieNormal[i].isAlive)
            {
                GenerateZombies(&ZombieNormal[i]);
                break;
            }
        }
    }
    for (int i = 0; i < MAXNUZOMBIES; i++)
    {
        if (ZombieNormal[i].isAlive)
        {
            UpdateAnimatedObject(&ZombieNormal[i].ZombieObj);
            if (!ZombieNormal[i].Attack)
            {
                ZombieNormal[i].ZombieObj.speedX = Level1Info.ZombieNormal.BassSpeedX * ZombieNormal[i].slowFactor;
                ZombieNormal[i].ZombieObj.speedY = Level1Info.ZombieNormal.BassSpeedY * ZombieNormal[i].slowFactor;
            }
            ZombieNormal[i].ZombieObj.frameDelay = Level1Info.ZombieNormal.BassFrameDelay / ZombieNormal[i].slowFactor;
            //   if(i==0) printf("ZombieNormal[%d] speedX = %f \n ", i, ZombieNormal[i].ZombieObj.speedX);  //debug
            ZombieNormal[i].Markaz.x = (ZombieNormal[i].ZombieObj.posX + ZombieNormal[i].ZombieObj.frames[0].width / 2);
            ZombieNormal[i].Markaz.y =
                (ZombieNormal[i].ZombieObj.posY + ZombieNormal[i].ZombieObj.frames[0].height / 2);
            ZombieNormal[i].CollisionBox.x = ZombieNormal[i].ZombieObj.posX + 40;
            ZombieNormal[i].CollisionBox.y = ZombieNormal[i].ZombieObj.posY + 20;
            if (ZombieNormal[i].Markaz.x < END_X)
            {
                ZombieNormal[i].X_Cell = (ZombieNormal[i].Markaz.x - START_X) / (RectangleWidth);
                // printf("%d\n" , ZombieNormal[0].Y_Cell );
            }
            if (ZombieNormal[i].Markaz.x < END_X &&
                CellContent[ZombieNormal[i].Y_Cell][ZombieNormal[i].X_Cell] != EMPTY)
            {
                if (!ZombieNormal[i].Attack)
                {
                    ZombieNormal[i].ZombieObj =
                        GenerateAnimatedObject(&ZombieNormalAttack1, 107, 122, 40, ZombieNormal[i].ZombieObj.posX,
                                               ZombieNormal[i].ZombieObj.posY, 0, 0, ZombieNormal[i].ZombieObj.finalX,
                                               ZombieNormal[i].ZombieObj.finalY);
                    ZombieNormal[i].ZombieObj.speedX = 0;
                    ZombieNormal[i].Attack = true;
                }
                if (CellContent[ZombieNormal[i].Y_Cell][ZombieNormal[i].X_Cell] == SUNFLOWER)
                {

                    for (int j = 0; j < MAXNUMITEMS; j++)
                    {
                        if (SunFlower[j].isAlive && SunFlower[j].X_Cell == ZombieNormal[i].X_Cell &&
                            SunFlower[j].Y_Cell == ZombieNormal[i].Y_Cell)
                        {
                            SunFlower[j].Health -= ZombieNormal[i].Damege;
                            // printf("%f\n",SunFlower[j].Health);
                            if (SunFlower[j].Health <= 0)
                            {
                                CellContent[SunFlower[j].Y_Cell][SunFlower[j].X_Cell] = EMPTY;
                                SunFlower[j].isAlive = false;
                            }
                        }
                    }
                }
                else if (CellContent[ZombieNormal[i].Y_Cell][ZombieNormal[i].X_Cell] == PEASHOOTER)
                {

                    for (int j = 0; j < MAXNUMITEMS; j++)
                    {
                        if (Peashooter[j].isAlive && Peashooter[j].X_Cell == ZombieNormal[i].X_Cell &&
                            Peashooter[j].Y_Cell == ZombieNormal[i].Y_Cell)
                        {
                            Peashooter[j].Health -= ZombieNormal[i].Damege;
                            // printf("%f\n",Peashooter[j].Health);
                            if (Peashooter[j].Health <= 0)
                            {
                                CellContent[Peashooter[j].Y_Cell][Peashooter[j].X_Cell] = EMPTY;
                                Peashooter[j].Firing = false;
                                Peashooter[j].isAlive = false;
                            }
                        }
                    }
                }
                else if (CellContent[ZombieNormal[i].Y_Cell][ZombieNormal[i].X_Cell] == CHOMPER)
                {

                    for (int j = 0; j < MAXNUMITEMS; j++)
                    {
                        if (Chomper[j].isAlive && Chomper[j].X_Cell == ZombieNormal[i].X_Cell &&
                            Chomper[j].Y_Cell == ZombieNormal[i].Y_Cell)
                        {
                            Chomper[j].Health -= ZombieNormal[i].Damege;
                            // printf("%f\n",Chomper[j].Health);
                            if (Chomper[j].Health <= 0)
                            {
                                CellContent[Chomper[j].Y_Cell][Chomper[j].X_Cell] = EMPTY;
                                Chomper[j].isAlive = false;
                            }
                        }
                    }
                }
                else if (CellContent[ZombieNormal[i].Y_Cell][ZombieNormal[i].X_Cell] == ROSE)
                {

                    for (int j = 0; j < MAXNUMITEMS; j++)
                    {
                        if (Rose[j].isAlive && Rose[j].X_Cell == ZombieNormal[i].X_Cell &&
                            Rose[j].Y_Cell == ZombieNormal[i].Y_Cell)
                        {
                            Rose[j].Health -= ZombieNormal[i].Damege;
                            // printf("%f\n",Rose[j].Health);
                            if (Rose[j].Health <= 0)
                            {
                                CellContent[Rose[j].Y_Cell][Rose[j].X_Cell] = EMPTY;
                                Rose[j].isAlive = false;
                            }
                        }
                    }
                }
                else if (CellContent[ZombieNormal[i].Y_Cell][ZombieNormal[i].X_Cell] == LAWNMOWER)
                {
                    CellContent[ZombieNormal[i].Y_Cell][ZombieNormal[i].X_Cell] = EMPTY;
                    LawnMower[ZombieNormal[i].Y_Cell].LawnMowerObj = GenerateAnimatedObject(
                        &LawnMowerSheet, 70, 57, 80, 320, 270 + RectangleHeight * ZombieNormal[i].Y_Cell, 500, 0, END_X,
                        270 + RectangleHeight * ZombieNormal[i].Y_Cell);
                    LawnMower[ZombieNormal[i].Y_Cell].isActive = true;
                }
            }
            else
            {
                if (ZombieNormal[i].Attack)
                {
                    ZombieNormal[i].ZombieObj = GenerateAnimatedObject(
                        &ZombieNormal1, 107, 122, 40, ZombieNormal[i].ZombieObj.posX, ZombieNormal[i].ZombieObj.posY,
                        -20, 0, ZombieNormal[i].ZombieObj.finalX, ZombieNormal[i].ZombieObj.finalY);

                    ZombieNormal[i].Attack = false;
                }
            }
        }
    }

    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (Peashooter[i].isAlive)
        {
            
            if (Peashooter[i].Firing == false)
            {
                for (int j = 0; j < MAXNUZOMBIES; j++)
                {

                    if (ZombieNormal[j].isAlive && ZombieNormal[j].Markaz.x <= END_X &&
                        ZombieNormal[j].Y_Cell == Peashooter[i].Y_Cell)
                    {
                        if (Peashooter[i].X_Cell <= ZombieNormal[j].X_Cell)
                        {
                            Peashooter[i].Firing = true;
                            // printf("Peashooter %d : on by ZombieNormal %d x=%f \n ", i, j, ZombieNormal[j].Markaz.x);

                            break;
                        }
                    }
                }
            }
            else
            {
                bool OFFfire = true;
                for (int j = 0; j < MAXNUZOMBIES; j++)
                {

                    if (ZombieNormal[j].isAlive && ZombieNormal[j].Markaz.x <= END_X &&
                        ZombieNormal[j].Y_Cell == Peashooter[i].Y_Cell)
                    {
                        if (Peashooter[i].X_Cell <= ZombieNormal[j].X_Cell)
                        {
                            OFFfire = false;
                            j = MAXNUZOMBIES;
                            break;
                        }
                    }
                }
                if (OFFfire)
                {
                    Peashooter[i].Firing = false;
                }
            }
        }
        if (Peashooter[i].Firing)
        {
            Peashooter[i].FireTimer += GetFrameTime();
            if (Peashooter[i].FireTimer >= Peashooter[i].Firingspeed / Peashooter[i].EffectiveFireRate)
            {
                Peashooter[i].FireTimer = 0;
                GeneratePea(&Peashooter[i]);
            }
        }
        for (int k = 0; k < 10; k++)
        {
            if (Peashooter[i].Pea[k].isActive)
            {
                UpdateAnimatedObject(&Peashooter[i].Pea[k].Pea);
                Peashooter[i].Pea[k].Markaz.x =
                    (Peashooter[i].Pea[k].Pea.posX + Peashooter[i].Pea[k].Pea.frames[0].width / 2);
                Peashooter[i].Pea[k].Markaz.y =
                    (Peashooter[i].Pea[k].Pea.posY + Peashooter[i].Pea[k].Pea.frames[0].height / 2);
                if (Peashooter[i].Pea[k].Markaz.x < END_X)
                {
                    Peashooter[i].Pea[k].Y_Cell = Peashooter[i].Y_Cell;
                    Peashooter[i].Pea[k].X_Cell = (Peashooter[i].Pea[k].Markaz.x - START_X) / (RectangleWidth);
                    // printf("%d\n", Peashooter[i].Pea[k].X_Cell);
                }
                else
                {
                    Peashooter[i].Pea[k].isActive = false;
                    continue;
                }
                int j = 0;

                for (int j = 0; j < MAXNUZOMBIES; j++)
                {
                    if (!ZombieNormal[j].isAlive)
                        continue;
                    if (ZombieNormal[j].Y_Cell != Peashooter[i].Pea[k].Y_Cell)
                        continue;
                    if (ZombieNormal[j].X_Cell == Peashooter[i].Pea[k].X_Cell)
                    {
                        Peashooter[i].Pea[k].Pea.finalX = ZombieNormal[j].Markaz.x;
                    }
                    if (Peashooter[i].Pea[k].Pea.finalX <= Peashooter[i].Pea[k].Pea.posX)
                    { // دمیج
                        ZombieNormal[j].Health -= Peashooter[i].peaDamege;

                        // تیر حذف
                        Peashooter[i].Pea[k].isActive = false;

                        // افکت برخورد (حتی اگر زامبی بمیرد)
                        Peashooter[i].Pea[k].PeaBulletHit.isActive = true;
                        Peashooter[i].Pea[k].PeaBulletHit.DisplayTimer = 0;

                        Peashooter[i].Pea[k].PeaBulletHit.BulletHitObj = GenerateAnimatedObject(
                            &PeaBulletHit, 49, 43, 100000, ZombieNormal[j].Markaz.x - 20, Peashooter[i].Pea[k].Markaz.y,
                            ZombieNormal[j].ZombieObj.speedX, ZombieNormal[j].ZombieObj.speedY,
                            ZombieNormal[j].ZombieObj.finalX, Peashooter[i].Pea[k].Markaz.y);

                        // مرگ زامبی
                        if (ZombieNormal[j].Health <= 0)
                            ZombieNormal[j].isAlive = false;
                        // printf("0\n");
                        break; // یک تیر فقط به یک زامبی
                    }
                    if (CheckCollisionCircleRec(Peashooter[i].Pea[k].Markaz, Peashooter[i].Pea[k].Radius,
                                                ZombieNormal[j].CollisionBox))
                    {
                        // دمیج
                        ZombieNormal[j].Health -= Peashooter[i].peaDamege;

                        // تیر حذف
                        Peashooter[i].Pea[k].isActive = false;

                        // افکت برخورد (حتی اگر زامبی بمیرد)
                        Peashooter[i].Pea[k].PeaBulletHit.isActive = true;
                        Peashooter[i].Pea[k].PeaBulletHit.DisplayTimer = 0;

                        Peashooter[i].Pea[k].PeaBulletHit.BulletHitObj = GenerateAnimatedObject(
                            &PeaBulletHit, 49, 43, 100000, ZombieNormal[j].Markaz.x - 20, Peashooter[i].Pea[k].Markaz.y,
                            ZombieNormal[j].ZombieObj.speedX, ZombieNormal[j].ZombieObj.speedY,
                            ZombieNormal[j].ZombieObj.finalX, Peashooter[i].Pea[k].Markaz.y);

                        // مرگ زامبی
                        if (ZombieNormal[j].Health <= 0)
                            ZombieNormal[j].isAlive = false;

                        break; // یک تیر فقط به یک زامبی
                    }
                }
            }
            if (Peashooter[i].Pea[k].PeaBulletHit.isActive)
            {
                UpdateAnimatedObject(&Peashooter[i].Pea[k].PeaBulletHit.BulletHitObj);
                Peashooter[i].Pea[k].PeaBulletHit.DisplayTimer += GetFrameTime();
                if (Peashooter[i].Pea[k].PeaBulletHit.DisplayTimer >= Peashooter[i].Pea[k].PeaBulletHit.DisplayTime)
                {
                    Peashooter[i].Pea[k].PeaBulletHit.DisplayTimer = 0;
                    Peashooter[i].Pea[k].PeaBulletHit.isActive = false;
                }
            }
        }
    }
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        if (LawnMower[i].isActive)
        {
            if (LawnMower[i].Markaz.x >= END_X || LawnMower[i].LawnMowerObj.posX == LawnMower[i].LawnMowerObj.finalX)
            {
                LawnMower[i].isActive = false;
            }
            for (int j = 0; j < MAXNUZOMBIES; j++)
            {
                if (ZombieNormal[j].isAlive && ZombieNormal[j].Markaz.x <= END_X &&
                    ZombieNormal[j].Y_Cell == LawnMower[i].Y_Cell && ZombieNormal[j].X_Cell == LawnMower[i].X_Cell)
                {
                    ZombieNormal[j].isAlive = false;
                }
            }
        }
    }
}
void UnloadLevel1(void)
{
    UnloadTexture(Map);
    UnloadTexture(SunBankPic);
    UnloadTexture(selectpic);
    UnloadTexture(SunFlowerSheet);
    UnloadTexture(LawnMowerSheet);
    UnloadTexture(SunElementSheet);
    UnloadTexture(Frame);

    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        UnloadAnimatedObject(&LawnMower[i].LawnMowerObj);
    }
    UnloadTexture(OFFlawnMowerRow);

    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        UnloadAnimatedObject(&SunElementArray[i].sun);
    }
    for (int i = 0; i < 4; i++)
    {
        UnloadAnimatedObject(&icon[i]);
        UnloadTexture(Price[i]);
    }

    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        UnloadAnimatedObject(&SunFlower[i].SunFlowerObj);
        UnloadAnimatedObject(&Chomper[i].ChomperObj);
        UnloadAnimatedObject(&Peashooter[i].PeashooterObj);
        UnloadAnimatedObject(&Rose[i].RoseObj);
    }
    UnloadFont(HorrorFont);
}
// ---------------------- Generate Functions-----------------------  //

void GenerateSun(SunElement *obj, int x, int y)
{
    if (x == GENERATERANDOM && y == GENERATERANDOM)
    {
        int xstart = rand() % (SCREEN_WIDTH - 80);  //  کمتر از  طول صفحه باشد تا از کادر خارج نشود
        int yfinal = rand() % (SCREEN_HEIGHT - 80); //  کمتر از  عرض صفحه باشد تا از کادر خارج نشود
        obj->sun.posY = 0;
        obj->sun.speedY = 45;
        obj->sun.posX = obj->sun.finalX = xstart;
        obj->sun.finalY = yfinal;
        obj->Available = true;
        obj->time = 0;
        return;
    }
    else
    {
        int rand1 = rand() % 2;
        int rand2 = rand() % 2;
        obj->sun.posY = y - 40;
        if (rand1)
        {
            obj->sun.posX = x + 30;
        }
        else
        {
            obj->sun.posX = x - 30;
        }
        obj->sun.speedY = 5;

        obj->sun.finalX = x;
        obj->sun.finalY = y + 35;
        obj->Available = true;
        obj->time = 0;
        return;
    }
}

void GenerateSunFlower(SunflowerElement *obj, int X_Cell, int Y_Cell)
{
    obj->Cooldown = 30;
    obj->Health = Level1Info.SunFlowertInfoLevel.BaseHealth;
    obj->SunFlowerObj.posX = obj->SunFlowerObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->SunFlowerObj.posY = obj->SunFlowerObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;
    obj->X_Cell = X_Cell;
    obj->Y_Cell = Y_Cell;
    obj->isAlive = true;

    return;
}
void GenerateRose(RoseElement *obj, int X_Cell, int Y_Cell)
{
    obj->Lifespan = 10;
    obj->Health = Level1Info.RosetInfoLevel.BaseHealth;
    obj->RoseObj.posX = obj->RoseObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->RoseObj.posY = obj->RoseObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;
    obj->X_Cell = X_Cell;
    obj->Y_Cell = Y_Cell;
    obj->Timer = 0;
    obj->isAlive = true;

    return;
}
void GenerateChomper(ChomperElement *obj, int X_Cell, int Y_Cell)
{
    obj->Lifespan = 20;
    obj->Health = Level1Info.ChompertInfoLevel.BaseHealth;
    obj->ChomperObj.posX = obj->ChomperObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->ChomperObj.posY = obj->ChomperObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;
    obj->X_Cell = X_Cell;
    obj->Y_Cell = Y_Cell;
    obj->isAlive = true;

    return;
}
void GeneratePeashooter(PeashooterElement *obj, int X_Cell, int Y_Cell)
{
    obj->Health = Level1Info.PeashooterInfoLevel.BaseHealth;
    obj->Firingspeed = 2 ;
    obj->PeashooterObj.posX = obj->PeashooterObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->PeashooterObj.posY = obj->PeashooterObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;
    obj->X_Cell = X_Cell;
    obj->Y_Cell = Y_Cell;
    obj->FireTimer = 1;
    obj->EffectiveFireRate = 1.0f;
    obj->peaDamege = 10;
    obj->Firing = false;
    for (int i = 0; i < 10; i++)
    {
        obj->Pea[i].isActive = false;
    }
    obj->isAlive = true;

    return;
}
void ShowLackSunWarning(void)
{

    strcpy(LackSunWarning.text, "SUN NOT ENOUGH!");
    LackSunWarning.isActive = true;
    LackSunWarning.timer = LackSunWarning.duration; // ریست تایمر
}
void ShowLockWarning(void)
{

    strcpy(LockWarning.text, "Lock!");
    LockWarning.isActive = true;
    LockWarning.timer = LockWarning.duration; // ریست تایمر
}
void GenerateZombies(Zombies *obj)
{
    obj->Damege = 0.1;
    obj->Health = 100;
    int Row = rand() % 5;
    int xstart = SCREEN_WIDTH;
    int Xfinal = 0;
    int Ystart = START_Y + Row * RectangleHeight - 10;
    int Yfinal = Ystart;
    obj->Markaz.x = 1600;
    obj->Y_Cell = Row;
    obj->slowFactor = 1.0f;
    obj->ZombieObj =
        GenerateAnimatedObject(&ZombieNormal1, 107, 122, Level1Info.ZombieNormal.BassFrameDelay, xstart, Ystart,
                               Level1Info.ZombieNormal.BassSpeedX, Level1Info.ZombieNormal.BassSpeedY, Xfinal, Yfinal);
    obj->isAlive = true;
    obj->CollisionBox = (Rectangle){obj->ZombieObj.posX + 15, obj->ZombieObj.posY + 20,
                                    obj->ZombieObj.frames[0].width - 65, obj->ZombieObj.frames[0].height - 20};
}
void GeneratePea(PeashooterElement *obj)
{
    for (int i = 0; i < 10; i++)
    {
        if (!(obj->Pea[i].isActive))
        {
            obj->Pea[i].Pea = GenerateAnimatedObject(&pea, 29, 32, 1000, 385 + obj->X_Cell * RectangleWidth,
                                                     247 + obj->Y_Cell * RectangleHeight, 300, 0, END_X, 385);
            obj->Pea[i].Radius = (obj->Pea[i].Pea.frames[0].width / 2.0f) * 0.80f;
            obj->Pea[i].Markaz.x = obj->Pea[i].Pea.posX + obj->Pea[i].Radius;
            obj->Pea[i].Markaz.y = obj->Pea[i].Pea.posY + obj->Pea[i].Radius;
            obj->Pea[i].isActive = true;
            return;
        }
    }
}
//----------------------------------------------------------------------------//
// ---------------------- Update Functions-----------------------  //

void CheckSelect()
{
    Vector2 MousePos = GetMousePosition();

    for (int i = 0; i < 4; i++)
    {
        if (MousePos.y >= 0 && MousePos.y <= Frame.height && MousePos.x >= 300 + i * Frame.width &&
            MousePos.x <= 300 + i * Frame.width + Frame.width)
        {
            switch (i)
            {
            case 0:
                if (!Level1Info.SunFlowertInfoLevel.Lock)
                {
                    if (SunBank >= Level1Info.SunFlowertInfoLevel.price)
                    {

                        Selection = SUNFLOWER;
                    }
                    else
                    {
                        ShowLackSunWarning();
                    }
                }
                else
                {
                    ShowLockWarning();
                }
                break;
            case 1:
                if (!Level1Info.PeashooterInfoLevel.Lock)
                {
                    if (SunBank >= Level1Info.PeashooterInfoLevel.price)
                    {
                        Selection = PEASHOOTER;
                    }
                    else
                    {
                        ShowLackSunWarning();
                    }
                }
                else
                {
                    ShowLockWarning();
                }
                break;
            case 2:
                if (!Level1Info.ChompertInfoLevel.Lock)
                {
                    if (SunBank >= Level1Info.ChompertInfoLevel.price)
                    {
                        Selection = CHOMPER;
                    }
                    else
                    {
                        ShowLackSunWarning();
                    }
                }
                else
                {
                    ShowLockWarning();
                }
                break;
            case 3:
                if (!Level1Info.RosetInfoLevel.Lock)
                {
                    if (SunBank >= Level1Info.RosetInfoLevel.price)
                    {
                        Selection = ROSE;
                    }
                    else
                    {
                        ShowLackSunWarning();
                    }
                }
                else
                {
                    ShowLockWarning();
                }
                break;
            default:
                Selection = EMPTY;
            }
            return;
        }
        else
        {
            if (!(MousePos.x >= START_X && MousePos.x <= END_X && MousePos.y >= START_Y && MousePos.y <= END_Y))
            {
                Selection = EMPTY;
            }
        }
    }
}
void CooldownUpdate(void)
{
    if (Level1Info.SunFlowertInfoLevel.Lock)
    {
        Level1Info.SunFlowertInfoLevel.Timer += GetFrameTime();
        if (Level1Info.SunFlowertInfoLevel.Timer >= Level1Info.SunFlowertInfoLevel.Cooldown)
        {
            Level1Info.SunFlowertInfoLevel.Lock = false;
            Level1Info.SunFlowertInfoLevel.Timer = 0;
        }
    }
    if (Level1Info.PeashooterInfoLevel.Lock)
    {
        Level1Info.PeashooterInfoLevel.Timer += GetFrameTime();
        if (Level1Info.PeashooterInfoLevel.Timer >= Level1Info.PeashooterInfoLevel.Cooldown)
        {
            Level1Info.PeashooterInfoLevel.Lock = false;
            Level1Info.PeashooterInfoLevel.Timer = 0;
        }
    }
    if (Level1Info.ChompertInfoLevel.Lock)
    {
        Level1Info.ChompertInfoLevel.Timer += GetFrameTime();
        if (Level1Info.ChompertInfoLevel.Timer >= Level1Info.ChompertInfoLevel.Cooldown)
        {
            Level1Info.ChompertInfoLevel.Lock = false;
            Level1Info.ChompertInfoLevel.Timer = 0;
        }
    }
    if (Level1Info.RosetInfoLevel.Lock)
    {
        Level1Info.RosetInfoLevel.Timer += GetFrameTime();
        if (Level1Info.RosetInfoLevel.Timer >= Level1Info.RosetInfoLevel.Cooldown)
        {
            Level1Info.RosetInfoLevel.Lock = false;
            Level1Info.RosetInfoLevel.Timer = 0;
        }
    }
}
void UpdatePlantsTimer(void)
{
    ResetSlowFactorZombies();
    ResetEffectiveFireRate();
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (SunFlower[i].isAlive)
        {
            SunFlower[i].Cooldown -= GetFrameTime();
            if (SunFlower[i].Cooldown <= 0)
            {
                SunFlower[i].Cooldown = 30;
                GenerateSun(&SunElementArray[CurrentSunIndex], SunFlower[i].SunFlowerObj.posX,
                            SunFlower[i].SunFlowerObj.posY);
                CurrentSunIndex = (CurrentSunIndex + 1) % MAXSUNELEMENT;
            }
        }
        if (Rose[i].isAlive)
        {
            Rose[i].Timer += GetFrameTime();
            if (Rose[i].Timer >= 1)
            {
                Rose[i].Timer = 0;
                for (int k = 0; k < MAXNUMITEMS; k++)
                {
                    if (SunFlower[k].isAlive && SunFlower[k].Y_Cell == Rose[i].Y_Cell)
                    {
                        SunFlower[k].Health = SunFlower[k].Health + 0.1f * SunFlower[k].Health;
                        if (SunFlower[k].Health >= 1.5 * Level1Info.SunFlowertInfoLevel.BaseHealth)
                        {
                            SunFlower[k].Health = 1.5 * Level1Info.SunFlowertInfoLevel.BaseHealth;
                        }
                    }
                    if (Peashooter[k].isAlive && Peashooter[k].Y_Cell == Rose[i].Y_Cell)
                    {
                        Peashooter[k].Health = Peashooter[k].Health + 0.1f * Peashooter[k].Health;
                        if (Peashooter[k].Health >= 1.5 * Level1Info.PeashooterInfoLevel.BaseHealth)
                        {
                            Peashooter[k].Health = 1.5 * Level1Info.PeashooterInfoLevel.BaseHealth;
                        }
                    }
                    if (Chomper[k].isAlive && Chomper[k].Y_Cell == Rose[i].Y_Cell)
                    {
                        Chomper[k].Health = Chomper[k].Health + 0.1f * Chomper[k].Health;
                        if (Chomper[k].Health >= 1.5 * Level1Info.ChompertInfoLevel.BaseHealth)
                        {
                            Chomper[k].Health = 1.5 * Level1Info.ChompertInfoLevel.BaseHealth;
                        }
                    }
                    if (Rose[k].isAlive && Rose[k].Y_Cell == Rose[i].Y_Cell)
                    {
                        Rose[k].Health = Rose[k].Health + 0.1f * Rose[k].Health;
                        if (Rose[k].Health >= 1.5 * Level1Info.RosetInfoLevel.BaseHealth)
                        {
                            Rose[k].Health = 1.5 * Level1Info.RosetInfoLevel.BaseHealth;
                        }
                    }
                }
            }
            for (int k = 0; k < MAXNUMITEMS; k++)
            {
                if (Peashooter[k].isAlive && Peashooter[k].Y_Cell == Rose[i].Y_Cell)
                {
                    Peashooter[k].EffectiveFireRate *= 1.2f;
                }
            }
            Rose[i].Lifespan -= GetFrameTime();
            if (Rose[i].Lifespan <= 0)
            {
                Rose[i].isAlive = false;
                CellContent[Rose[i].Y_Cell][Rose[i].X_Cell] = EMPTY;
            }
        }
        if (Chomper[i].isAlive)
        {

            for (int j = 0; j < MAXNUZOMBIES; j++)
            {

                if (ZombieNormal[j].isAlive && ZombieNormal[j].Markaz.x < END_X &&
                    ZombieNormal[j].Y_Cell == Chomper[i].Y_Cell)
                {
                    ZombieNormal[j].slowFactor *= 2.0f / 3.0f; // هر چامپر 1/3 سرعت کم می‌کند
                }
            }

            Chomper[i].Lifespan -= GetFrameTime();
            if (Chomper[i].Lifespan <= 0)
            {
                Chomper[i].isAlive = false;
                CellContent[Chomper[i].Y_Cell][Chomper[i].X_Cell] = EMPTY;
            }
        }
    }
}
void ResetSlowFactorZombies(void)
{
    for (int j = 0; j < MAXNUZOMBIES; j++)
    {
        ZombieNormal[j].slowFactor = 1.0f;
    }
}
void ResetEffectiveFireRate(void)
{
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (Peashooter[i].isAlive)
        {
            Peashooter[i].EffectiveFireRate = 1.0f;
        }
    }
}
void UpdateSUNELEMENT(void)
{
    SunTimer += GetFrameTime();
    if (SunTimer >= Level1Info.SunElementInfoLevel.Regenerate)
    {
        SunTimer = 0;

        GenerateSun(&SunElementArray[CurrentSunIndex], GENERATERANDOM, GENERATERANDOM);
        CurrentSunIndex = (CurrentSunIndex + 1) % MAXSUNELEMENT;
    }
    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        if (SunElementArray[i].Available == true)
        {
            UpdateAnimatedObject(&SunElementArray[i].sun);
            SunElementArray[i].time += GetFrameTime();
            if (SunElementArray[i].time >= Level1Info.SunElementInfoLevel.DisplayTime)
            {
                SunElementArray[i].Available = false;
            }
        }
    }
}
void UpdateLevelItems(void)
{
    if (FirstRun)
    {
        unsigned int random = (unsigned int)(GetTime() * 1000);
        srand(random);
        FirstRun = false;
    }

    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        if (LawnMower[i].isActive)
        {
            LawnMower[i].Markaz.x = LawnMower[i].LawnMowerObj.posX + LawnMower[i].LawnMowerObj.frames[0].width / 2;
            LawnMower[i].Markaz.y = LawnMower[i].LawnMowerObj.posY + LawnMower[i].LawnMowerObj.frames[0].height / 2;
            UpdateAnimatedObject(&LawnMower[i].LawnMowerObj);
            LawnMower[i].X_Cell = (LawnMower[i].Markaz.x - START_X) / (RectangleWidth);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        UpdateAnimatedObject(&icon[i]);
    }
}
void UpdateLackSunWarning(void)
{
    LackSunWarning.timer -= GetFrameTime();
    if (LackSunWarning.timer <= 0.0f)
    {
        LackSunWarning.isActive = false; // پیام را غیرفعال کن
    }
}
void UpdateLockWarning(void)
{
    LockWarning.timer -= GetFrameTime();
    if (LockWarning.timer <= 0.0f)
    {
        LockWarning.isActive = false; // پیام را غیرفعال کن
    }
}
void UpdateSelectionItems(void)
{
    Vector2 MousePos = GetMousePosition();

    if (MousePos.x >= START_X && MousePos.x <= END_X && MousePos.y >= START_Y && MousePos.y <= END_Y)
    {
        int X_Cell = (MousePos.x - START_X) / RectangleWidth;
        int Y_Cell = (MousePos.y - START_Y) / RectangleHeight;
        if (Selection != EMPTY)
        {
            if (Selection == SUNFLOWER && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (SunFlower[i].isAlive == false)
                    {
                        GenerateSunFlower(&SunFlower[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = SUNFLOWER;
                        SunBank -= Level1Info.SunFlowertInfoLevel.price;
                        Level1Info.SunFlowertInfoLevel.Lock = true;
                        Selection = EMPTY;

                        break;
                    }
                }
            }
            else if (Selection == PEASHOOTER && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (Peashooter[i].isAlive == false)
                    {
                        GeneratePeashooter(&Peashooter[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = PEASHOOTER;
                        SunBank -= Level1Info.PeashooterInfoLevel.price;
                        Level1Info.PeashooterInfoLevel.Lock = true;
                        Selection = EMPTY;

                        break;
                    }
                }
            }
            else if (Selection == CHOMPER && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (Chomper[i].isAlive == false)
                    {
                        GenerateChomper(&Chomper[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = CHOMPER;
                        SunBank -= Level1Info.ChompertInfoLevel.price;
                        Level1Info.ChompertInfoLevel.Lock = true;
                        Selection = EMPTY;

                        break;
                    }
                }
            }
            else if (Selection == ROSE && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (Rose[i].isAlive == false)
                    {
                        GenerateRose(&Rose[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = ROSE;
                        SunBank -= Level1Info.RosetInfoLevel.price;
                        Level1Info.RosetInfoLevel.Lock = true;
                        Selection = EMPTY;
                        break;
                    }
                }
            }
        }
    }
}
void UpdatePlantsAnimation(void)
{
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (SunFlower[i].isAlive)
        {
            UpdateAnimatedObject(&SunFlower[i].SunFlowerObj);
        }
        if (Peashooter[i].isAlive)
        {
            UpdateAnimatedObject(&Peashooter[i].PeashooterObj);
        }
        if (Chomper[i].isAlive)
        {
            UpdateAnimatedObject(&Chomper[i].ChomperObj);
        }
        if (Rose[i].isAlive)
        {
            UpdateAnimatedObject(&Rose[i].RoseObj);
        }
    }
}
void CollectSunElement(void)
{
    Vector2 MousePos = GetMousePosition();

    for (int i = 0; i < MAXSUNELEMENT; i++)
    {

        if (SunElementArray[i].Available)
        {
            if (MousePos.x >= SunElementArray[i].sun.posX &&
                MousePos.x <= SunElementArray[i].sun.posX + SunElementArray[i].sun.frames[0].width &&
                MousePos.y >= SunElementArray[i].sun.posY &&
                MousePos.y <= SunElementArray[i].sun.posY + SunElementArray[i].sun.frames[0].height)
            {
                SunElementArray[i].Available = false;
                SunBank += Level1Info.SunElementInfoLevel.Value;
            }
        }
    }
}
//  ------------------------- Draw Functions-----------------------  //
void DrawPlants(void)
{
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (SunFlower[i].isAlive)
        {
            DrawAnimatedObject(&SunFlower[i].SunFlowerObj, WHITE);
        }
        if (Chomper[i].isAlive)
        {
            DrawAnimatedObject(&Chomper[i].ChomperObj, WHITE);
        }
        if (Peashooter[i].isAlive)
        {
            DrawAnimatedObject(&Peashooter[i].PeashooterObj, WHITE);
        }
        if (Rose[i].isAlive)
        {
            DrawAnimatedObject(&Rose[i].RoseObj, WHITE);
        }
    }
}
void DrawSunElement(void)
{
    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        if (SunElementArray[i].Available == true)
        {
            DrawAnimatedObject(&SunElementArray[i].sun, WHITE);
        }
    }
}
void DrawSelectionTick(void)
{
    switch (Selection)
    {
    case SUNFLOWER:
        DrawTexture(selectpic, 360 + 0 * Frame.width, 30, WHITE);
        break;
    case PEASHOOTER:
        DrawTexture(selectpic, 360 + 1 * Frame.width, 30, WHITE);
        break;
    case CHOMPER:
        DrawTexture(selectpic, 360 + 2 * Frame.width, 30, WHITE);
        break;
    case ROSE:
        DrawTexture(selectpic, 360 + 3 * Frame.width, 30, WHITE);
        break;

    default:
        break;
    }
}
void DrawLevelItems(void)
{
    DrawTexture(Map, 0, 0, WHITE);
    DrawTexture(SunBankPic, 0, 0, WHITE);
    for (int i = 0; i < 4; i++)
    {
        DrawTexture(Frame, 300 + i * Frame.width, 0, WHITE);
        DrawAnimatedObject(&icon[i], WHITE);
        DrawTexture(Price[i], 445 + i * Frame.width, 75, WHITE);
    }

    char sunbanktext[5];
    sprintf(sunbanktext, "%d", SunBank);
    DrawText(sunbanktext, 85, 40, 30, GoldOrange);
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        if (LawnMower[i].LawnMowerObj.posX == LawnMower[i].LawnMowerObj.finalX && CellContent[i][0] == LAWNMOWER)
        {

            DrawTexture(OFFlawnMowerRow, LawnMower[i].LawnMowerObj.finalX, LawnMower[i].LawnMowerObj.finalY, WHITE);
        }
        else if (LawnMower[i].isActive)
        {
            DrawAnimatedObject(&LawnMower[i].LawnMowerObj, WHITE);
        }
    }
}
void DrawLackSunWarning(void)
{

    // محاسبه زمان سپری شده از شروع نمایش (برعکس تایمر)
    float elapsed = LackSunWarning.duration - LackSunWarning.timer;

    // **افکت ۱: حرکت عمودی نوسانی (Bouncing)**
    // استفاده از sin برای نوسان نرم
    // 5.0f * sin(elapsed * 20.0f) مقدار جابجایی عمودی است.
    // 20.0f سرعت نوسان را تعیین می کند.
    float offset = 5.0f * sinf(elapsed * 20.0f);

    // **افکت ۲: بزرگ شدن/کوچک شدن (Scaling)**
    // استفاده از sin برای تغییر اندازه (اوج در وسط مدت نمایش)
    float scaleFactor = 1.0f + 0.1f * sinf(elapsed * 2 * PI / LackSunWarning.duration);

    Vector2 textPosition = LackSunWarning.startPos;
    textPosition.y += offset; // اعمال نوسان عمودی

    float currentSize = LackSunWarning.baseSize * scaleFactor;

    // برای وسط قرار گرفتن متن، ابتدا اندازه آن را بگیرید
    Vector2 measure = MeasureTextEx(HorrorFont, LackSunWarning.text, currentSize, 2.0f);
    textPosition.x -= measure.x / 2.0f; // وسط قرار دادن افقی
    textPosition.y -= measure.y / 2.0f; // وسط قرار دادن عمودی

    DrawTextEx(HorrorFont, LackSunWarning.text, textPosition, currentSize, 2.0f,
               RED // می‌توانید رنگ را به قرمز تغییر دهید
    );
}
void DrawLockWarning(void)
{

    float elapsed = LockWarning.timer;
    float offset = 5 * sinf(elapsed * 20);
    float scaleFactor = 1 + 0.1 * sinf(elapsed * 2 * PI / LockWarning.duration);
    float currentSize = LockWarning.baseSize * scaleFactor;
    Vector2 textPosition = LackSunWarning.startPos;
    textPosition.y += offset;
    Vector2 measure = MeasureTextEx(HorrorFont, LockWarning.text, currentSize, 2.0f);
    textPosition.x -= measure.x / 2.0f; // وسط قرار دادن افقی
    textPosition.y -= measure.y / 2.0f; // وسط قرار دادن عمودی
    DrawTextEx(HorrorFont, LockWarning.text, textPosition, currentSize, 2.0f, GoldOrange);
}
void CellularNetworkMap(void)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            char Coordinates[16];
            sprintf(Coordinates, "(%d , %d)", i + 1, j + 1);
            DrawRectangleLinesEx(MapCell[i][j], 1, WHITE);
            DrawText(Coordinates, MapCell[i][j].x + 5, MapCell[i][j].y + 5, 20, RED);
        }
    }
}

//--------------------------------------------------------------------------------//

// ---------------------- Init Functions-----------------------------------------  //

void InitLevel1Info(void)
{
    Level1Info.SunFlowertInfoLevel.price = 50;
    Level1Info.PeashooterInfoLevel.price = 100;
    Level1Info.ChompertInfoLevel.price = 125;
    Level1Info.RosetInfoLevel.price = 150;
    Level1Info.SunFlowertInfoLevel.Cooldown = 45;
    Level1Info.PeashooterInfoLevel.Cooldown = 2; // 45;
    Level1Info.ChompertInfoLevel.Cooldown = 2;   // 60;
    Level1Info.RosetInfoLevel.Cooldown = 0.5;    // 70;
    Level1Info.SunFlowertInfoLevel.Timer = 0;
    Level1Info.PeashooterInfoLevel.Timer = 0;
    Level1Info.ChompertInfoLevel.Timer = 0;
    Level1Info.RosetInfoLevel.Timer = 0;
    Level1Info.SunFlowertInfoLevel.BaseHealth = 100;
    Level1Info.PeashooterInfoLevel.BaseHealth = 100;
    Level1Info.ChompertInfoLevel.BaseHealth = 100;
    Level1Info.RosetInfoLevel.BaseHealth = 100;
    Level1Info.SunFlowertInfoLevel.Lock = false;
    Level1Info.PeashooterInfoLevel.Lock = false;
    Level1Info.ChompertInfoLevel.Lock = false;
    Level1Info.RosetInfoLevel.Lock = false;

    Level1Info.SunElementInfoLevel.Value = VALUESUN;
    Level1Info.SunElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level1Info.SunElementInfoLevel.Regenerate = GENERATESUN;
    Level1Info.ZombieNormal.Regenerate = 5;
    Level1Info.ZombieNormal.Timer = 0;
    Level1Info.ZombieNormal.BassSpeedX = -20;
    Level1Info.ZombieNormal.BassSpeedY = 0;
    Level1Info.ZombieNormal.BassFrameDelay = 40.0f;
    LackSunWarning.isActive = false;
    LackSunWarning.duration = 2.0f;
    LackSunWarning.baseSize = 30.0f;
    LackSunWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 150};
    LockWarning.isActive = false;
    LockWarning.duration = 2.0f;
    LockWarning.baseSize = 30.0f;
    LockWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 130};
}
void InitLevel1Texture(void)
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
}
void InitLevel1Font(void)
{
    HorrorFont = LoadFont("../assets/Level1/houseofterrormedium.ttf");
}
void InitLevel1Animation(void)
{
    for (int i = 0; i < 4; i++)
    {
        int pixel = (i == 2) ? 100 : 71;
        int pixelY = (i == 2) ? 0 : 25;
        int k = (i == 2) ? 12 : 0;
        char temp[100];
        sprintf(temp, "../assets/Level1/icon%d.png", i);
        icon[i] = LoadAnimatedObject(temp, pixel, pixel, 80, 370 - k + Frame.width * i, pixelY, 0, 0,
                                     370 - k + Frame.width * i, 25);
        sprintf(temp, "../assets/Level1/price%d.png", i);
        Price[i] = LoadTexture(temp);
    }
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        LawnMower[i].LawnMowerObj = GenerateAnimatedObject(&LawnMowerSheet, 70, 57, 80, 210, 270 + RectangleHeight * i,
                                                           50, 0, 320, 270 + RectangleHeight * i);
        LawnMower[i].Y_Cell = i;
        LawnMower[i].X_Cell = 0;
        LawnMower[i].Available = true;
        LawnMower[i].isActive = true;
        CellContent[i][0] = LAWNMOWER;
    }
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        SunFlower[i].SunFlowerObj = GenerateAnimatedObject(&SunFlowerSheet, 80, 80, 60, 0, 0, 0, 0, 0, 0);
        SunFlower[i].isAlive = false;
        SunFlower[i].Health = 100;
        Rose[i].RoseObj = GenerateAnimatedObject(&RoseSheet, 80, 80, 80, 0, 0, 0, 0, 0, 0);
        Rose[i].Health = 100;
        Rose[i].isAlive = false;
        Chomper[i].ChomperObj = GenerateAnimatedObject(&ChomperSheet, 80, 80, 80, 0, 0, 0, 0, 0, 0);
        Chomper[i].isAlive = false;
        Peashooter[i].PeashooterObj = GenerateAnimatedObject(&PeashooterSheet, 80, 80, 16.75, 0, 0, 0, 0, 0, 0);
        Peashooter[i].isAlive = false;
        Peashooter[i].FireTimer = 0;
        Peashooter[i].Firing = false;

        for (int j = 0; j < 10; j++)
        {
            Peashooter[i].Pea[j].isActive = false;
            Peashooter[i].Pea[j].Pea = GenerateAnimatedObject(&pea, 29, 32, 80, 0, 0, 0, 0, 0, 0);
            Peashooter[i].Pea[j].isActive = false;
            Peashooter[i].Pea[j].PeaBulletHit.DisplayTime = 0.1f;
            Peashooter[i].Pea[j].PeaBulletHit.DisplayTimer = 0.0;
        }
    }

    SunTimer = 0;
    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        SunElementArray[i].sun = GenerateAnimatedObject(&SunElementSheet, 79, 79, 60, 0, 0, 0, 45, 0, 0);
        SunElementArray[i].Available = false;
        SunElementArray[i].time = 0.0f;
    }
    ZombieTimer = 0;
    for (int i = 0; i < MAXNUZOMBIES; i++)
    {
        ZombieNormal[i].isAlive = false;
        ZombieNormal[i].Attack = false;
        ZombieNormal[i].ZombieObj = GenerateAnimatedObject(&ZombieNormal1, 12, 12, 0, 0, 0, 0, 0, 0, 0);
    }
}
void InitLevel1MapCell(void)
{
    for (int Y = START_Y, i = 0, j = 0; Y <= END_Y - RectangleHeight; Y = Y + RectangleHeight)
    {
        j = 0;
        for (int X = START_X; X <= END_X - RectangleWidth; X = X + RectangleWidth)
        {
            MapCell[i][j].x = X;
            MapCell[i][j].y = Y;
            MapCell[i][j].width = RectangleWidth;
            MapCell[i][j].height = RectangleHeight;
            j++;
        }
        i++;
    }
}
//------------------------------------------------------------------------------------------------//
