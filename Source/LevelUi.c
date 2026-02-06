#include "LevelUi.h"
#include "Chomper.h"
#include "Level1.h"
#include "LevelBase.h"
#include "Peashooter.h"
#include "Plant.h"
#include "PotatoMine.h"
#include "Rose.h"
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
WarningMessage LackSunWarning, LockWarning;
Rectangle MapCell[ROWS][COLUMNS];

int SunBank = 0;
float RectangleWidth = (float)(END_X - START_X) / COLUMNS; // 107.5
float RectangleHeight = (float)(END_Y - START_Y) / ROWS;   // 122
float scaleVictoryPic = 0.1f;
float scaleGameOverPic = 0.1f;
float scaleYesOrNo = 0.1f;

MapContent CellContent[ROWS][COLUMNS] = {EMPTY};
MapContent Selection = EMPTY;
CircleButton ButtonExitGameWIN = {(Vector2){460 + 90, 600 + 80}, 80, false};
CircleButton ButtonRestartWIN = {(Vector2){1060 + 90, 600 + 80}, 80, false};
CircleButton ButtonLevelSelectWIN = {(Vector2){760 + 90, 600 + 80}, 80, false};
CircleButton ButtonExitGameLOSE = {(Vector2){460 + 90, 600 + 80}, 80, false};
CircleButton ButtonRestartLOSE = {(Vector2){1060 + 90, 600 + 80}, 80, false};
CircleButton ButtonLevelSelectLOSE = {(Vector2){760 + 90, 600 + 80}, 80, false};
GameState CurrentGameState = PLAYING;
bool IsDrawVictory = false;
bool IsDrawGameOver = false;
bool IsDrawYesOrNo = false;
RowManager RowStatus[ROWS] = {0};

void DrawUI(void)
{
    DrawLevelItems();
    DrawSelectionTick();
    DrawLackSunWarning();
    DrawLockWarning();
    DrawLockPicture();
}
void UpdateUI(void)
{
    UpdateLevelItems();
    UpdateLackSunWarning();

    UpdateLockWarning();

    CheckSelect();
    UpdateSelectionItems();
    UpdateBottom();
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
//----------------------------------------------------------------------------//
// ---------------------- Update Functions-----------------------  //

void CheckSelect(void)
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }
    Vector2 MousePos = GetMousePosition();

    for (int i = 0; i < 5; i++)
    {
        if (MousePos.y >= 0 && MousePos.y <= Frame.height && MousePos.x >= 300 + i * Frame.width &&
            MousePos.x <= 300 + i * Frame.width + Frame.width)
        {
            switch (i)
            {
            case 0:
                if (CurrentLevelInfo->SunFlowertInfoLevel.IsAvailable && !CurrentLevelInfo->SunFlowertInfoLevel.Lock)
                {
                    if (SunBank >= CurrentLevelInfo->SunFlowertInfoLevel.price)
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
                if (CurrentLevelInfo->PeashooterInfoLevel.IsAvailable && !CurrentLevelInfo->PeashooterInfoLevel.Lock)
                {
                    if (SunBank >= CurrentLevelInfo->PeashooterInfoLevel.price)
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
                if (CurrentLevelInfo->ChompertInfoLevel.IsAvailable && !CurrentLevelInfo->ChompertInfoLevel.Lock)
                {
                    if (SunBank >= CurrentLevelInfo->ChompertInfoLevel.price)
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
                if (CurrentLevelInfo->RosetInfoLevel.IsAvailable && !CurrentLevelInfo->RosetInfoLevel.Lock)
                {
                    if (SunBank >= CurrentLevelInfo->RosetInfoLevel.price)
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
            case 4:
                if (CurrentLevelInfo->PotatoMineInfoLevel.IsAvailable && !CurrentLevelInfo->PotatoMineInfoLevel.Lock)
                {
                    if (SunBank >= CurrentLevelInfo->PotatoMineInfoLevel.price) //? اصلاح
                    {
                        Selection = POTATOMINE;
                    }
                    else
                    {
                        ShowLackSunWarning(); //? اصلاح
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
void UpdateLevelItems(void)
{
    if (FirstRun)
    {
        unsigned int random = (unsigned int)(GetTime() * 1000);
        srand(random);
        FirstRun = false;
        for (int i = 0; i < ROWS; i++)
        {
            if (CellContent[i][0] == LAWNMOWER)
            {
                PlaySound(SetupLawnMowerSound);
                break;
            }
        }
    }
    for (int i = 0; i < 5; i++)
    {
        UpdateAnimatedObject(&icon[i]);
    }
    UpdateLoseNowButton();
    if (Screen == LVL4)
        CalculateSurvivalTimeHMS();
}
void UpdateLackSunWarning(void)
{
    if (!LackSunWarning.isActive)
    {
        return;
    }
    LackSunWarning.timer -= GetFrameTime();
    if (LackSunWarning.timer <= 0.0f)
    {
        LackSunWarning.isActive = false;
    }
}
void UpdateLockWarning(void)
{
    if (!LockWarning.isActive)
    {
        return;
    }
    LockWarning.timer -= GetFrameTime();
    if (LockWarning.timer <= 0.0f)
    {
        LockWarning.isActive = false;
    }
}
void UpdateSelectionItems(void)
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }
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
                    if (SunFlower[i].Base.isAlive == false)
                    {
                        GenerateSunFlower(&SunFlower[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = SUNFLOWER;
                        RowStatus[Y_Cell].plantCount++;
                        RowStatus[Y_Cell].rowChanged = true;
                        RowStatus[Y_Cell].WeightChanged = true;

                        SunBank -= CurrentLevelInfo->SunFlowertInfoLevel.price;
                        CurrentLevelInfo->SunFlowertInfoLevel.Lock = true;
                        Selection = EMPTY;
                        PlaySound(PlantingSound[rand() % 3]);
                        break;
                    }
                }
            }
            else if (Selection == PEASHOOTER && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (Peashooter[i].Base.isAlive == false)
                    {
                        GeneratePeashooter(&Peashooter[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = PEASHOOTER;
                        RowStatus[Y_Cell].plantCount++;
                        RowStatus[Y_Cell].rowChanged = true;
                        RowStatus[Y_Cell].WeightChanged = true;

                        SunBank -= CurrentLevelInfo->PeashooterInfoLevel.price;
                        CurrentLevelInfo->PeashooterInfoLevel.Lock = true;
                        Selection = EMPTY;
                        PlaySound(PlantingSound[rand() % 3]);

                        break;
                    }
                }
            }
            else if (Selection == CHOMPER && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (Chomper[i].Base.isAlive == false)

                    {
                        GenerateChomper(&Chomper[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = CHOMPER;
                        RowStatus[Y_Cell].plantCount++;
                        RowStatus[Y_Cell].rowChanged = true;
                        RowStatus[Y_Cell].WeightChanged = true;

                        SunBank -= CurrentLevelInfo->ChompertInfoLevel.price;
                        CurrentLevelInfo->ChompertInfoLevel.Lock = true;
                        Selection = EMPTY;
                        PlaySound(PlantingSound[rand() % 3]);

                        break;
                    }
                }
            }
            else if (Selection == ROSE && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (Rose[i].Base.isAlive == false)
                    {
                        GenerateRose(&Rose[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = ROSE;
                        RowStatus[Y_Cell].plantCount++;
                        RowStatus[Y_Cell].rowChanged = true;
                        RowStatus[Y_Cell].WeightChanged = true;

                        SunBank -= CurrentLevelInfo->RosetInfoLevel.price;
                        CurrentLevelInfo->RosetInfoLevel.Lock = true;
                        Selection = EMPTY;
                        PlaySound(PlantingSound[rand() % 3]);

                        break;
                    }
                }
            }
            else if (Selection == POTATOMINE && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (PotatoMine[i].Base.isAlive == false &&PotatoMine[i].Explosion == false)
                    {
                        GeneratePotatoMine(&PotatoMine[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = POTATOMINE;
                        RowStatus[Y_Cell].plantCount++;
                        RowStatus[Y_Cell].rowChanged = true;
                        RowStatus[Y_Cell].WeightChanged = true;

                        SunBank -= CurrentLevelInfo->PotatoMineInfoLevel.price;
                        CurrentLevelInfo->PotatoMineInfoLevel.Lock = true;
                        Selection = EMPTY;
                        PlaySound(PlantingSound[rand() % 3]);

                        break;
                    }
                }
            }
        }
    }
}
//  ------------------------- Draw Functions-----------------------  //
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
    case POTATOMINE:
        DrawTexture(selectpic, 360 + 4 * Frame.width, 30, WHITE);
        break;

    default:
        break;
    }
}
void DrawLevelItems(void)
{
    DrawTexture(Map, 0, 0, WHITE);
    DrawTexture(SunBankPic, 0, 0, WHITE);
    for (int i = 0; i < 5; i++)
    {
        DrawTexture(Frame, 300 + i * Frame.width, 0, WHITE);
        DrawAnimatedObject(&icon[i], WHITE);
        DrawTexture(Price[i], 445 + i * Frame.width, 75, WHITE);
    }

    char sunbanktext[5];
    sprintf(sunbanktext, "%d", SunBank);
    DrawText(sunbanktext, 85, 40, 30, GoldOrange);
    if (CurrentGameState == PLAYING)
    {
        DrawTexture(LoseNowpic, 1490, 780, WHITE);
        DrawText("Lose Now !!!", 1495, 880, 15, GoldOrange);
    }
    if (Screen == LVL4)
    {
        DrawTexture(TimeFramePic, 1380, 0, WHITE);

        DrawTextEx(HorrorFont, "Best :", (Vector2){1405, 25}, 25, 2.0f,
                   (BestSurvivalTime > SurvivalTimer) ? GREEN : RED);
        char TimeText[16];
        snprintf(TimeText, sizeof(TimeText), "%02d:%02d:%02d", bestHours, bestMinutes, bestSeconds);
        DrawTextEx(HorrorFont, TimeText, (Vector2){1473, 30}, 20, 2.0f,
                   (BestSurvivalTime > SurvivalTimer) ? GREEN : RED);
        snprintf(TimeText, sizeof(TimeText), "%02d:%02d:%02d", SurvivalHours, SurvivalMinutes, SurvivalSeconds);

        DrawTextEx(HorrorFont, "Time :", (Vector2){1405, 50}, 23, 2.0f,
                   (BestSurvivalTime > SurvivalTimer) ? GRAY : GREEN);
        DrawTextEx(HorrorFont, TimeText, (Vector2){1473, 55}, 18, 2.0f,
                   (BestSurvivalTime > SurvivalTimer) ? GRAY : GREEN);
    }
}
void DrawLackSunWarning(void)
{
    if (!LackSunWarning.isActive)
    {
        return;
    }
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
    if (!LockWarning.isActive)
    {
        return;
    }

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
void DrawGameOver(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, scaleGameOverPic * 0.6f));

    static float scaleSpeed = 0.02f;
    Vector2 center = {1600 / 2.0f + 60, 900 / 2.0f + 100};
    float scaledWidth = GameOver.width * scaleGameOverPic;
    float scaledHeight = GameOver.height * scaleGameOverPic;
    Vector2 pos = {center.x - scaledWidth / 2, center.y - scaledHeight / 2};

    DrawTexturePro(GameOver, (Rectangle){0, 0, GameOver.width, GameOver.height},
                   (Rectangle){pos.x, pos.y, scaledWidth, scaledHeight}, (Vector2){0, 0}, 0.0f, WHITE);

    if (scaleGameOverPic < 1.0f)
        scaleGameOverPic += scaleSpeed;
    else
    {
        scaleGameOverPic = 1.0f;
        IsDrawGameOver = true;
    }
}
void DrawVictory(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, scaleVictoryPic * 0.6f));

    static float scaleSpeed = 0.02f;
    Vector2 center = {1600 / 2.0f + 60, 900 / 2.0f};
    float scaledWidth = Victory.width * scaleVictoryPic;
    float scaledHeight = Victory.height * scaleVictoryPic;
    Vector2 pos = {center.x - scaledWidth / 2, center.y - scaledHeight / 2};

    DrawTexturePro(Victory, (Rectangle){0, 0, Victory.width, Victory.height},
                   (Rectangle){pos.x, pos.y, scaledWidth, scaledHeight}, (Vector2){0, 0}, 0.0f, WHITE);

    if (scaleVictoryPic < 1.0f)
        scaleVictoryPic += scaleSpeed;
    else
    {
        scaleVictoryPic = 1.0f;
        IsDrawVictory = true;
    }
}
void DrawYesOrNop(char *Question)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, scaleYesOrNo * 0.6f));

    Vector2 MousePos = GetMousePosition();
    static float scaleSpeed = 0.05f;
    Vector2 center = {1600 / 2.0f + 60, 900 / 2.0f};
    float scaledWidth = YesOrNopic.width * scaleYesOrNo;
    float scaledHeight = YesOrNopic.height * scaleYesOrNo;
    Vector2 pos = {center.x - scaledWidth / 2, center.y - scaledHeight / 2};

    DrawTexturePro(YesOrNopic, (Rectangle){0, 0, YesOrNopic.width, YesOrNopic.height},
                   (Rectangle){pos.x, pos.y, scaledWidth, scaledHeight}, (Vector2){0, 0}, 0.0f, WHITE);

    if (scaleYesOrNo < 1.0f)
        scaleYesOrNo += scaleSpeed;
    else
    {
        scaleYesOrNo = 1.0f;
        IsDrawYesOrNo = true;
        DrawText("No", 620, 585, 50, CheckCollisionPointRec(MousePos, NoButton) ? GREEN : WHITE);

        DrawText("Yes", 1020, 585, 50, CheckCollisionPointRec(MousePos, YesButton) ? RED : WHITE);
        DrawText(Question, 530, 260, 38, WHITE);
    }
}
void UpdateYesOrNop(void)
{

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 MousePos = GetMousePosition();
        if (CheckCollisionPointRec(MousePos, NoButton))
        {
            CurrentGameState = PLAYING;
            scaleYesOrNo = 0.1f;
        }
        if (CheckCollisionPointRec(MousePos, YesButton))
        {
            CurrentGameState = LOSE;
            PlaySound(EndGameSound);
        }
    }
}

void DrawBottom(void)
{
    if (IsDrawVictory)
    {
        DrawTexture(ButtonWin, 1060, 600, WHITE);
        DrawTexture(ButtonWin, 760, 600, WHITE);
        DrawTexture(ButtonWin, 460, 600, WHITE);
        DrawTextEx(HorrorFont, "Exit", (Vector2){415 + (ButtonWin.width) / 2, 565 + (ButtonWin.height) / 2}, 50, 0,
                   ButtonExitGameWIN.hovered ? RED : WHITE);
        DrawTextEx(HorrorFont, "Level Select", (Vector2){705 + (ButtonWin.width) / 2, 575 + (ButtonWin.height) / 2}, 25,
                   0, ButtonLevelSelectWIN.hovered ? BLUE : WHITE);
        DrawTextEx(HorrorFont, "Next Level", (Vector2){1005 + (ButtonWin.width) / 2, 575 + (ButtonWin.height) / 2}, 27,
                   0, ButtonRestartWIN.hovered ? GREEN : WHITE);
    }
    else if (IsDrawGameOver)
    {
        DrawTexture(ButtonLose, 1060, 660, WHITE);
        DrawTexture(ButtonLose, 760, 660, WHITE);
        DrawTexture(ButtonLose, 460, 660, WHITE);
        DrawTextEx(HorrorFont, "Exit", (Vector2){420 + (ButtonLose.width) / 2, 623 + (ButtonLose.height) / 2}, 50, 0,
                   ButtonExitGameLOSE.hovered ? RED : WHITE);
        DrawTextEx(HorrorFont, "Level Select", (Vector2){710 + (ButtonLose.width) / 2, 635 + (ButtonLose.height) / 2},
                   22, 0, ButtonLevelSelectLOSE.hovered ? BLUE : WHITE);
        DrawTextEx(HorrorFont, "Restart Level", (Vector2){1012 + (ButtonLose.width) / 2, 635 + (ButtonLose.height) / 2},
                   20, 0, ButtonRestartLOSE.hovered ? GREEN : WHITE);
    }
}

void UpdateBottom(void)
{
    Vector2 mousePos = GetMousePosition();
    if (CurrentGameState == WIN)
    {
        if (CheckCollisionPointCircle(mousePos, ButtonExitGameWIN.center, ButtonExitGameWIN.radius))
        {
            ButtonExitGameWIN.hovered = true;
        }
        else
        {
            ButtonExitGameWIN.hovered = false;
        }
        if (CheckCollisionPointCircle(mousePos, ButtonLevelSelectWIN.center, ButtonLevelSelectWIN.radius))
        {
            ButtonLevelSelectWIN.hovered = true;
        }
        else
        {
            ButtonLevelSelectWIN.hovered = false;
        }
        if (CheckCollisionPointCircle(mousePos, ButtonRestartWIN.center, ButtonRestartWIN.radius))
        {
            ButtonRestartWIN.hovered = true;
        }
        else
        {
            ButtonRestartWIN.hovered = false;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (ButtonExitGameWIN.hovered)
            {
                Screen = EXITING;
            }
            else if (ButtonLevelSelectWIN.hovered)
            {
                Screen = LEVEL_SELECT;
                restart = true; //? اصلاح؟
            }
            else if (ButtonRestartWIN.hovered)
            {
                Screen += 1;
            }
        }
    }
    else if (CurrentGameState == LOSE)
    {
        if (CheckCollisionPointCircle(mousePos, ButtonExitGameLOSE.center, ButtonExitGameLOSE.radius))
        {
            ButtonExitGameLOSE.hovered = true;
        }
        else
        {
            ButtonExitGameLOSE.hovered = false;
        }
        if (CheckCollisionPointCircle(mousePos, ButtonLevelSelectLOSE.center, ButtonLevelSelectLOSE.radius))
        {
            ButtonLevelSelectLOSE.hovered = true;
        }
        else
        {
            ButtonLevelSelectLOSE.hovered = false;
        }
        if (CheckCollisionPointCircle(mousePos, ButtonRestartLOSE.center, ButtonRestartLOSE.radius))
        {
            ButtonRestartLOSE.hovered = true;
        }
        else
        {
            ButtonRestartLOSE.hovered = false;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (ButtonExitGameLOSE.hovered)
            {
                Screen = EXITING;
            }
            else if (ButtonLevelSelectLOSE.hovered)
            {
                Screen = LEVEL_SELECT;
                restart = true;
            }
            else if (ButtonRestartLOSE.hovered)
            {
                restart = true;
            }
        }
    }
}
void DrawLockPicture(void)
{
    if (CurrentLevelInfo == NULL)
    {
        return;
    }
    if (!CurrentLevelInfo->SunFlowertInfoLevel.IsAvailable || CurrentLevelInfo->SunFlowertInfoLevel.Lock)
    {
        DrawTexture(LockPic, 370 + 0 * Frame.width, 30, WHITE);
        int frame =
            (CurrentLevelInfo->SunFlowertInfoLevel.Timer / CurrentLevelInfo->SunFlowertInfoLevel.Cooldown) * 100.0f - 1;

        if (frame < 0)
            frame = 0;
        if (frame > 99)
            frame = 99;

        Rectangle FramePic = (Rectangle){58 * frame, 0, 58, 58};
        Vector2 Pos = (Vector2){441 + 0 * Frame.width, 71};
        DrawTextureRec(RingBar, FramePic, Pos, WHITE);
    }
    if (!CurrentLevelInfo->PeashooterInfoLevel.IsAvailable || CurrentLevelInfo->PeashooterInfoLevel.Lock)
    {
        DrawTexture(LockPic, 370 + 1 * Frame.width, 30, WHITE);
        int frame =
            (CurrentLevelInfo->PeashooterInfoLevel.Timer / CurrentLevelInfo->PeashooterInfoLevel.Cooldown) * 100.0f - 1;

        if (frame < 0)
            frame = 0;
        if (frame > 99)
            frame = 99;

        Rectangle FramePic = (Rectangle){58 * frame, 0, 58, 58};
        Vector2 Pos = (Vector2){441 + 1 * Frame.width, 71};
        DrawTextureRec(RingBar, FramePic, Pos, WHITE);
    }
    if (!CurrentLevelInfo->ChompertInfoLevel.IsAvailable || CurrentLevelInfo->ChompertInfoLevel.Lock)
    {
        DrawTexture(LockPic, 370 + 2 * Frame.width, 30, WHITE);
        int frame =
            (CurrentLevelInfo->ChompertInfoLevel.Timer / CurrentLevelInfo->ChompertInfoLevel.Cooldown) * 100.0f - 1;

        if (frame < 0)
            frame = 0;
        if (frame > 99)
            frame = 99;

        Rectangle FramePic = (Rectangle){58 * frame, 0, 58, 58};
        Vector2 Pos = (Vector2){441 + 2 * Frame.width, 71};
        DrawTextureRec(RingBar, FramePic, Pos, WHITE);
    }
    if (!CurrentLevelInfo->RosetInfoLevel.IsAvailable || CurrentLevelInfo->RosetInfoLevel.Lock)
    {
        DrawTexture(LockPic, 370 + 3 * Frame.width, 30, WHITE);
        int frame = (CurrentLevelInfo->RosetInfoLevel.Timer / CurrentLevelInfo->RosetInfoLevel.Cooldown) * 100.0f - 1;

        if (frame < 0)
            frame = 0;
        if (frame > 99)
            frame = 99;

        Rectangle FramePic = (Rectangle){58 * frame, 0, 58, 58};
        Vector2 Pos = (Vector2){441 + 3 * Frame.width, 71};
        DrawTextureRec(RingBar, FramePic, Pos, WHITE);
    }
    if (!CurrentLevelInfo->PotatoMineInfoLevel.IsAvailable || CurrentLevelInfo->PotatoMineInfoLevel.Lock)
    {
        DrawTexture(LockPic, 370 + 4 * Frame.width, 30, WHITE);
        int frame =
            (CurrentLevelInfo->PotatoMineInfoLevel.Timer / CurrentLevelInfo->PotatoMineInfoLevel.Cooldown) * 100.0f - 1;

        if (frame < 0)
            frame = 0;
        if (frame > 99)
            frame = 99;

        Rectangle FramePic = (Rectangle){58 * frame, 0, 58, 58};
        Vector2 Pos = (Vector2){441 + 4 * Frame.width, 71};
        DrawTextureRec(RingBar, FramePic, Pos, WHITE);
    }
}

void ResetRowManager(void)
{
    for (int i = 0; i < ROWS; i++)
    {
        RowStatus[i].plantCount = 0;
        RowStatus[i].rowChanged = true;
        RowStatus[i].WeightChanged = true;

        RowStatus[i].ThinkingZombiesDeterminant = 0;
        RowStatus[i].RowWeights = 100;
    }
}
void ResetUi(void)
{
    Selection = EMPTY;
    CurrentGameState = PLAYING;
    scaleVictoryPic = 0.1f;
    scaleGameOverPic = 0.1f;
    scaleYesOrNo = 0.1f;
    IsDrawVictory = false;
    IsDrawGameOver = false;
    ZombiesSpawned = 0;
    ZombiesKilled = 0;
    SunBank = 9999;
    CurrentSunIndex = 0;
    SunTimer = 0;
    SurvivalTimer = 0;
    ZombieTimer = 0;
    CurrentLevelInfo->SunFlowertInfoLevel.Timer = 0;
    CurrentLevelInfo->PeashooterInfoLevel.Timer = 0;
    CurrentLevelInfo->ChompertInfoLevel.Timer = 0;
    CurrentLevelInfo->RosetInfoLevel.Timer = 0;
    CurrentLevelInfo->ThinkingZombie.ZombieSpawned = 0;
    CurrentLevelInfo->ZombieNormal.ZombieSpawned = 0;

    CurrentLevelInfo->SunFlowertInfoLevel.Lock = false;
    CurrentLevelInfo->PeashooterInfoLevel.Lock = false;
    CurrentLevelInfo->ChompertInfoLevel.Lock = false;
    CurrentLevelInfo->RosetInfoLevel.Lock = false;
    ResetRowManager();
}
void UpdateLoseNowButton(void)
{

    if (!CurrentGameState == PLAYING)
    {
        return;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, LoseNowButton))
        {
            CurrentGameState = YesNo;
            return;
        }
    }
}