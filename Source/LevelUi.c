#include "LevelUi.h"
#include "Chomper.h"
#include "Diamond.h"
#include "Level1.h"
#include "LevelBase.h"
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
WarningMessage LackSunWarning, LockWarning, LackDiamondWarning;
CircleButtonAnim FireStormButton, FreezeBurstButton, SunPackButton;
Rectangle MapCell[ROWS][COLUMNS];

int SunBank = 0;
float RectangleWidth;  //= (float)(CurrentLevelInfo->END_X - CurrentLevelInfo->START_X) / COLUMNS; // 107.5
float RectangleHeight; // = (float)(CurrentLevelInfo->END_Y - CurrentLevelInfo->START_Y) / ROWS;   // 122
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
bool FireStormEffect = false;
bool FreezeBurstEffect = false;
float FireStormEffectTimer = 4;
float FireStormEffectTimerSecondsCounter = 1;
float FreezeBurstEffectTimer = 4;

RowManager RowStatus[ROWS] = {0};

void DrawUI(void)
{
    DrawLevelItems();
    DrawSelectionTick();
    DrawWarning(&LackSunWarning, RED);
    DrawWarning(&LockWarning, GoldOrange);
    DrawWarning(&LackDiamondWarning, BLUE);
    DrawDiamondElement();
    DrawLockPicture();
    DrawSpecialItems();
}
void UpdateUI(void)
{
    UpdateLevelItems();
    UpdateWarning(&LackSunWarning);
    UpdateWarning(&LockWarning);
    UpdateWarning(&LackDiamondWarning);
    UpdateDiamondElement();
    CheckSelect();
    UpdateSelectionItems();
    UpdateBottom();
    UpdateSpecialItems();
}

void ShowWarning(WarningMessage *Warning, char *text)
{

    strcpy(Warning->text, text);
    Warning->isActive = true;
    Warning->timer = Warning->duration; // ریست تایمر
}
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
                        PlaySound(UiClickFX);
                    }
                    else
                    {
                        ShowWarning(&LackSunWarning, "SUN NOT ENOUGH!");
                        PlaySound(UiErrorFX);
                    }
                }
                else
                {
                    ShowWarning(&LockWarning, "Lock!");
                    PlaySound(LockErrorFX);
                }
                break;
            case 1:
                if (CurrentLevelInfo->PeashooterInfoLevel.IsAvailable && !CurrentLevelInfo->PeashooterInfoLevel.Lock)
                {
                    if (SunBank >= CurrentLevelInfo->PeashooterInfoLevel.price)
                    {
                        Selection = PEASHOOTER;
                        PlaySound(UiClickFX);
                    }
                    else
                    {
                        ShowWarning(&LackSunWarning, "SUN NOT ENOUGH!");
                        PlaySound(UiErrorFX);
                    }
                }
                else
                {
                    ShowWarning(&LockWarning, "Lock!");
                    PlaySound(LockErrorFX);
                }
                break;
            case 2:
                if (CurrentLevelInfo->ChompertInfoLevel.IsAvailable && !CurrentLevelInfo->ChompertInfoLevel.Lock)
                {
                    if (SunBank >= CurrentLevelInfo->ChompertInfoLevel.price)
                    {
                        Selection = CHOMPER;
                        PlaySound(UiClickFX);
                    }
                    else
                    {
                        ShowWarning(&LackSunWarning, "SUN NOT ENOUGH!");
                        PlaySound(UiErrorFX);
                    }
                }
                else
                {
                    ShowWarning(&LockWarning, "Lock!");
                    PlaySound(LockErrorFX);
                }
                break;
            case 3:
                if (CurrentLevelInfo->RosetInfoLevel.IsAvailable && !CurrentLevelInfo->RosetInfoLevel.Lock)
                {
                    if (SunBank >= CurrentLevelInfo->RosetInfoLevel.price)
                    {
                        Selection = ROSE;
                        PlaySound(UiClickFX);
                    }
                    else
                    {
                        ShowWarning(&LackSunWarning, "SUN NOT ENOUGH!");
                        PlaySound(UiErrorFX);
                    }
                }
                else
                {
                    ShowWarning(&LockWarning, "Lock!");
                    PlaySound(LockErrorFX);
                }
                break;
            case 4:
                if (CurrentLevelInfo->PotatoMineInfoLevel.IsAvailable && !CurrentLevelInfo->PotatoMineInfoLevel.Lock)
                {
                    if (PotatoMineItems.PlayerInventory > 0)
                    {
                        if (SunBank >= CurrentLevelInfo->PotatoMineInfoLevel.price)
                        {
                            Selection = POTATOMINE;
                            PlaySound(UiClickFX);
                        }
                        else
                        {
                            ShowWarning(&LackSunWarning, "SUN NOT ENOUGH!");
                            PlaySound(UiErrorFX);
                        }
                    }
                    else
                    {
                        ShowWarning(&LackDiamondWarning, "NOT ENOUGH INVENTORY!");
                        PlaySound(UiErrorFX);
                    }
                }
                else
                {
                    ShowWarning(&LockWarning, "Lock!");
                    PlaySound(LockErrorFX);
                }
                break;
            default:
                Selection = EMPTY;
            }
            return;
        }
        else if (MousePos.y >= Frame.height - 25 && MousePos.y <= Frame.height - 25 + Frame.height &&
                 MousePos.x >= 300 && MousePos.x <= 300 + Frame.width)
        {
            if (CurrentLevelInfo->IcePeashooterInfoLevel.IsAvailable && !CurrentLevelInfo->IcePeashooterInfoLevel.Lock)
            {
                if (SunBank >= CurrentLevelInfo->IcePeashooterInfoLevel.price)
                {
                    Selection = ICEPEASHOOTER;
                    PlaySound(UiClickFX);
                }
                else
                {
                    ShowWarning(&LackSunWarning, "SUN NOT ENOUGH!");
                    PlaySound(UiErrorFX);
                }
            }
            else
            {
                ShowWarning(&LockWarning, "Lock!");
                PlaySound(LockErrorFX);
            }
        }
        else
        {
            if (!(MousePos.x >= CurrentLevelInfo->START_X && MousePos.x <= CurrentLevelInfo->END_X &&
                  MousePos.y >= CurrentLevelInfo->START_Y && MousePos.y <= CurrentLevelInfo->END_Y))
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
    for (int i = 0; i < 6; i++)
    {
        UpdateAnimatedObject(&icon[i]);
    }
    UpdateLoseNowButton();
    if (Screen == LVL4)
        CalculateSurvivalTimeHMS();
}
void UpdateWarning(WarningMessage *Warning)
{
    if (!Warning->isActive)
    {
        return;
    }
    Warning->timer -= GetFrameTime();
    if (Warning->timer <= 0.0f)
    {
        Warning->isActive = false;
    }
}

void UpdateSelectionItems(void)
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }
    Vector2 MousePos = GetMousePosition();

    if (MousePos.x >= CurrentLevelInfo->START_X && MousePos.x <= CurrentLevelInfo->END_X &&
        MousePos.y >= CurrentLevelInfo->START_Y && MousePos.y <= CurrentLevelInfo->END_Y)
    {
        int X_Cell = (MousePos.x - CurrentLevelInfo->START_X) / RectangleWidth;
        int Y_Cell = (MousePos.y - CurrentLevelInfo->START_Y) / RectangleHeight;
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
                        GeneratePeashooter(&Peashooter[i], X_Cell, Y_Cell, PLANT_PEASHOOTER,
                                           &CurrentLevelInfo->PeashooterInfoLevel);
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
            else if (Selection == ICEPEASHOOTER && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (ICEPeashooter[i].Base.isAlive == false)
                    {
                        GeneratePeashooter(&ICEPeashooter[i], X_Cell, Y_Cell, PLANT_ICEPEASHOOTER,
                                           &CurrentLevelInfo->IcePeashooterInfoLevel);
                        CellContent[Y_Cell][X_Cell] = PEASHOOTER;
                        RowStatus[Y_Cell].plantCount++;
                        RowStatus[Y_Cell].rowChanged = true;
                        RowStatus[Y_Cell].WeightChanged = true;

                        SunBank -= CurrentLevelInfo->IcePeashooterInfoLevel.price;
                        CurrentLevelInfo->IcePeashooterInfoLevel.Lock = true;
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
                    if (PotatoMine[i].Base.isAlive == false && PotatoMine[i].Explosion == false)
                    {
                        GeneratePotatoMine(&PotatoMine[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = POTATOMINE;
                        RowStatus[Y_Cell].plantCount++;
                        RowStatus[Y_Cell].rowChanged = true;
                        RowStatus[Y_Cell].WeightChanged = true;
                        SunBank -= CurrentLevelInfo->PotatoMineInfoLevel.price;
                        PotatoMineItems.PlayerInventory--;
                        SaveGame();

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
    case ICEPEASHOOTER:
        DrawTexture(selectpic, 360, Frame.height + 5, WHITE);
        break;

    default:
        break;
    }
}
void DrawLevelItems(void)
{
    char text[5];

    if (Screen == LVL1 || Screen == LVL2 || Screen == LVL4)
    {
        DrawTexture(Map, 0, 0, WHITE);
    }
    else if (Screen == LVL3)
    {
        DrawTexture(map_naght, 0, 0, WHITE);
    }
    for (int i = 0; i < 10; i++)
    {
        if (DiamondElementArray[i].IsCollected)
        {
            DrawTexture(DiamondBankFrame, 0, SunBankPic.height - 20, WHITE);
            sprintf(text, "%d", DiamondBank);
            DrawTextCentered(GetFontDefault(), text, (Vector2){140, 122}, 25, 1, (Color){243, 222, 142, 255});
            DrawText("x  Diamond", 85, 35 + SunBankPic.height, 17, WHITE);
            break;
        }
    }

    DrawTexture(SunBankPic, 0, 0, WHITE);
    sprintf(text, "%d", SunBank);
    //  DrawText(text, 85, 40, 30, GoldOrange);
    DrawTextCentered(GetFontDefault(), text, (Vector2){103, 60}, 30, 1, GoldOrange);

    for (int i = 0; i < 5; i++)
    {
        DrawTexture(Frame, 300 + i * Frame.width, 0, WHITE);
        DrawAnimatedObject(&icon[i], WHITE);
        DrawTexture(Price[i], 445 + i * Frame.width, 75, WHITE);
    }
    DrawTexture(Frame, 300, Frame.height - 25, WHITE);
    DrawAnimatedObject(&icon[5], WHITE);
    DrawTexture(Price[2], 445, Frame.height - 25 + 75, WHITE);

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
void DrawWarning(WarningMessage *Warning, Color color)
{
    if (!Warning->isActive)
    {
        return;
    }
    // محاسبه زمان سپری شده از شروع نمایش (برعکس تایمر)
    float elapsed = Warning->duration - Warning->timer;

    // **افکت ۱: حرکت عمودی نوسانی (Bouncing)**
    // استفاده از sin برای نوسان نرم
    // 5.0f * sin(elapsed * 20.0f) مقدار جابجایی عمودی است.
    // 20.0f سرعت نوسان را تعیین می کند.
    float offset = 5.0f * sinf(elapsed * 20.0f);

    // **افکت ۲: بزرگ شدن/کوچک شدن (Scaling)**
    // استفاده از sin برای تغییر اندازه (اوج در وسط مدت نمایش)
    float scaleFactor = 1.0f + 0.1f * sinf(elapsed * 2 * PI / Warning->duration);

    Vector2 textPosition = Warning->startPos;
    textPosition.y += offset; // اعمال نوسان عمودی

    float currentSize = Warning->baseSize * scaleFactor;

    // برای وسط قرار گرفتن متن، ابتدا اندازه آن را بگیرید
    Vector2 measure = MeasureTextEx(HorrorFont, Warning->text, currentSize, 2.0f);
    textPosition.x -= measure.x / 2.0f; // وسط قرار دادن افقی
    textPosition.y -= measure.y / 2.0f; // وسط قرار دادن عمودی

    DrawTextEx(HorrorFont, Warning->text, textPosition, currentSize, 2.0f,
               color // می‌توانید رنگ را به قرمز تغییر دهید
    );
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
    {
        scaleVictoryPic += scaleSpeed;
    }
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
                PlayRandomMenuMusic();
                restart = true; //? اصلاح؟
            }
            else if (ButtonRestartWIN.hovered)
            {
                Screen += 1;
                restart = true;
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
                PlayRandomMenuMusic();

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
    if (!CurrentLevelInfo->IcePeashooterInfoLevel.IsAvailable || CurrentLevelInfo->IcePeashooterInfoLevel.Lock)
    {
        DrawTexture(LockPic, 370, Frame.height + 5, WHITE);
        int frame =
            (CurrentLevelInfo->IcePeashooterInfoLevel.Timer / CurrentLevelInfo->IcePeashooterInfoLevel.Cooldown) *
                100.0f -
            1;

        if (frame < 0)
            frame = 0;
        if (frame > 99)
            frame = 99;

        Rectangle FramePic = (Rectangle){58 * frame, 0, 58, 58};
        Vector2 Pos = (Vector2){441, 46 + Frame.height};
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
    if (!CurrentLevelInfo->PotatoMineInfoLevel.IsAvailable || CurrentLevelInfo->PotatoMineInfoLevel.Lock ||
        PotatoMineItems.PlayerInventory == 0)
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
    RectangleWidth = (float)(CurrentLevelInfo->END_X - CurrentLevelInfo->START_X) / COLUMNS; // 107.5
    RectangleHeight = (float)(CurrentLevelInfo->END_Y - CurrentLevelInfo->START_Y) / ROWS;   // 122
    IsDrawVictory = false;
    IsDrawGameOver = false;
    RestartBattelMusic = true;
    ZombiesSpawned = 0;
    ZombiesKilled = 0;
    SunBank = 150;
    CurrentSunIndex = 0;
    SunTimer = 0;
    SurvivalTimer = 0;
    ZombieTimer = 0;
    CurrentLevelInfo->SunFlowertInfoLevel.Timer = 0;
    CurrentLevelInfo->PeashooterInfoLevel.Timer = 0;
    CurrentLevelInfo->ChompertInfoLevel.Timer = 0;
    CurrentLevelInfo->RosetInfoLevel.Timer = 0;
    CurrentLevelInfo->IcePeashooterInfoLevel.Timer = 0;

    CurrentLevelInfo->ThinkingZombie.ZombieSpawned = 0;
    CurrentLevelInfo->ZombieNormal.ZombieSpawned = 0;

    CurrentLevelInfo->SunFlowertInfoLevel.Lock = false;
    CurrentLevelInfo->PeashooterInfoLevel.Lock = false;
    CurrentLevelInfo->ChompertInfoLevel.Lock = false;
    CurrentLevelInfo->RosetInfoLevel.Lock = false;
    CurrentLevelInfo->IcePeashooterInfoLevel.Lock = false;

    ResetRowManager();
    FireStormEffect = false;
    FreezeBurstEffect = false;
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
            PlaySound(pause);
            return;
        }
    }
}
void InitSpecialItems(void)
{
    FreezeBurstButton.Picture = SnowIcon;
    SetTextureFilter(FreezeBurstButton.Picture, TEXTURE_FILTER_BILINEAR);
    FreezeBurstButton.Radius = 25;
    FreezeBurstButton.ScaleNow = 0.80f;
    FreezeBurstButton.DefaultScale = 0.80f;
    FreezeBurstButton.scaleSpeed = 1.3f;
    FreezeBurstButton.targetScale = 1.0f;
    FreezeBurstButton.CenterPosition.x = 245;
    FreezeBurstButton.CenterPosition.y = 35;
    FreezeBurstButton.rotation = 0;
    FreezeBurstButton.rotationSpeed = 10;
    FreezeBurstButton.rotational = true;

    FireStormButton.Picture = FireIcon;
    SetTextureFilter(FireStormButton.Picture, TEXTURE_FILTER_BILINEAR);
    FireStormButton.Radius = 25;
    FireStormButton.ScaleNow = 0.80f;
    FireStormButton.DefaultScale = 0.80f;
    FireStormButton.scaleSpeed = 1.3f;
    FireStormButton.targetScale = 1.0f;
    FireStormButton.CenterPosition.x = 245;
    FireStormButton.CenterPosition.y = 85;
    FireStormButton.rotation = 0;
    FireStormButton.rotational = false;

    SunPackButton.Picture = SunIcon;
    SetTextureFilter(SunPackButton.Picture, TEXTURE_FILTER_BILINEAR);
    SunPackButton.Radius = 25;
    SunPackButton.ScaleNow = 0.80f;
    SunPackButton.DefaultScale = 0.80f;
    SunPackButton.scaleSpeed = 1.3f;
    SunPackButton.targetScale = 1.0f;
    SunPackButton.CenterPosition.x = 245;
    SunPackButton.CenterPosition.y = 135;
    SunPackButton.rotation = 0;
    SunPackButton.rotationSpeed = 10;
    SunPackButton.rotational = true;
}
void UpdateSpecialItems(void)
{
    if (CurrentGameState != PLAYING)
    {
        return;
    }
    CircleButtonAnimation(&FreezeBurstButton);
    CircleButtonAnimation(&FireStormButton);
    CircleButtonAnimation(&SunPackButton);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (FreezeBurstButton.IsHover && !FreezeBurstEffect)
        {
            if (FreezeBurst.PlayerInventory > 0)
            {
                FreezeBurstEffect = true;
                FreezeBurstEffectTimer = 4;
                FreezeBurst.PlayerInventory--;
                PlaySound(FreezeFX);
                SaveGame();
            }
            else
            {
                ShowWarning(&LackDiamondWarning, "NOT ENOUGH INVENTORY!");
                PlaySound(ErrorItemFX);
            }
        }
        if (FireStormButton.IsHover && !FireStormEffect)
        {
            if (FireStorm.PlayerInventory > 0)

            {
                FireStormEffect = true;
                FireStormEffectTimer = 4;
                FireStormEffectTimerSecondsCounter = 1;
                FireStorm.PlayerInventory--;
                PlaySound(FireFX);
                SaveGame();
            }
            else
            {
                ShowWarning(&LackDiamondWarning, "NOT ENOUGH INVENTORY!");
                PlaySound(ErrorItemFX);
            }
        }
        if (SunPackButton.IsHover)
        {
            if (SunPack.PlayerInventory > 0)

            {
                SunPack.PlayerInventory--;
                SunBank += 250;
                PlaySound(SunPackCollectFX);
                SaveGame();
            }
            else
            {
                ShowWarning(&LackDiamondWarning, "NOT ENOUGH INVENTORY!");
                PlaySound(ErrorItemFX);
            }
        }
    }
    float dt = GetFrameTime();
    if (FireStormEffect)
    {
        FireStormEffectTimer -= dt;
        FireStormEffectTimerSecondsCounter -= dt;
        if (FireStormEffectTimerSecondsCounter <= 0)
        {
            FireStormEffectTimerSecondsCounter = 1;
            ApplyDamageFireStorm();
        }
        if (FireStormEffectTimer <= 0)
        {
            FireStormEffect = false;
        }
    }
    if (FreezeBurstEffect)
    {
        FreezeBurstEffectTimer -= dt;
        if (FreezeBurstEffectTimer < 0)
        {
            FreezeBurstEffect = false;
        }
    }
}
void DrawSpecialItems(void)
{
    if (CurrentGameState == PLAYING)
    {
        // DrawCircleLinesV(FireStormButton.CenterPosition, FireStormButton.Radius, RED);
        // DrawCircleLinesV(FreezeBurstButton.CenterPosition, FreezeBurstButton.Radius, RED);
        // DrawCircleLinesV(SunPackButton.CenterPosition, SunPackButton.Radius, RED);
        DrawTexture(CircularFrame, FireStormButton.CenterPosition.x - FireStormButton.Radius,
                    FireStormButton.CenterPosition.y - FireStormButton.Radius, WHITE);
        DrawTexture(CircularFrame, FreezeBurstButton.CenterPosition.x - FreezeBurstButton.Radius,
                    FreezeBurstButton.CenterPosition.y - FreezeBurstButton.Radius, WHITE);
        DrawTexture(CircularFrame, SunPackButton.CenterPosition.x - SunPackButton.Radius,
                    SunPackButton.CenterPosition.y - SunPackButton.Radius, WHITE);

        if (FreezeBurstButton.IsHover)
        {
            float pulse = 0.8f - sinf(GetTime() * 2.5f) * 0.3f;

            DrawCircleGradient(FreezeBurstButton.CenterPosition.x, FreezeBurstButton.CenterPosition.y,
                               FreezeBurstButton.Radius + pulse * 15, Fade(BLUE, pulse), BLANK);
        }

        DrawCircleButton(&FreezeBurstButton);
        if (FireStormButton.IsHover)
        {
            float pulse = 0.8f - sinf(GetTime() * 2.5f) * 0.3f;

            DrawCircleGradient(FireStormButton.CenterPosition.x, FireStormButton.CenterPosition.y,
                               FireStormButton.Radius + pulse * 15, Fade(RED, pulse), BLANK);
        }
        DrawCircleButton(&FireStormButton);
        if (SunPackButton.IsHover)
        {
            float pulse = 0.8f - sinf(GetTime() * 2.5f) * 0.3f;

            DrawCircleGradient(SunPackButton.CenterPosition.x, SunPackButton.CenterPosition.y,
                               SunPackButton.Radius + pulse * 15, Fade(YELLOW, pulse), BLANK);
        }
        DrawCircleButton(&SunPackButton);
    }
}
void ApplyDamageFireStorm(void)
{
    for (int i = 0; i < CurrentLevelInfo->MaxZombieNormalAllowed; i++)
    {
        if (ZombieNormal[i].isAlive)
        {
            ZombieNormal[i].Health -= 15;
            if (ZombieNormal[i].Health <= 0)
            {
                ZombieNormal[i].isAlive = false;
                CreatingDiamondLuck(DiamondElementArray, ZombieNormal[i].Markaz.x, ZombieNormal[i].Markaz.y, 10);

                ZombiesKilled++;
            }
        }
    }
    for (int i = 0; i < CurrentLevelInfo->MaxThinkingZombieAllowed; i++)
    {
        if (ThinkingZombie[i].isAlive)
        {
            ThinkingZombie[i].Health -= 15;
            if (ThinkingZombie[i].Health <= 0)
            {
                ThinkingZombie[i].isAlive = false;
                CreatingDiamondLuck(DiamondElementArray, ThinkingZombie[i].Markaz.x, ThinkingZombie[i].Markaz.y, 10);

                ZombiesKilled++;
            }
        }
    }
}