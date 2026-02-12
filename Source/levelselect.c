#include "levelselect.h"
#include "SoundandMusic.h"
#include "menu.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

Texture2D BackgroundLevelselect;
Texture2D LVL1Picture;
Texture2D LVL2Picture;
Texture2D LVL3Picture;
Texture2D LVL4Picture;
Vector2 CircleLvl1;
Vector2 CircleLvl2;
Vector2 CircleLvl3;
Vector2 CircleLvl4;
// Vector2 CircleBackButton;
float Radius1;
float Radius2;
float Radius3;
float Radius4;
// float RadiusBackButton;
Button BackButton;
void Initlevelselect(void)
{

    BackgroundLevelselect = LoadTexture("../assets/levelselect/4-button_levelselect.png");
    LVL1Picture = LoadTexture("../assets/levelselect/LVL1.png");
    LVL2Picture = LoadTexture("../assets/levelselect/LVL2.png");
    LVL3Picture = LoadTexture("../assets/levelselect/LVL3.png");
    LVL4Picture = LoadTexture("../assets/levelselect/LVL4.png");

    // BackButton
    BackButton.Picture = LoadTexture("../assets/levelselect/BackButton.png");
    SetTextureFilter(BackButton.Picture, TEXTURE_FILTER_BILINEAR);
    BackButton.ClickArea.x = 100.0f;
    BackButton.ClickArea.y = 780.0f;
    BackButton.ClickArea.width = 115.0f;
    BackButton.ClickArea.height = 120.0f;
    BackButton.ScaleNow = 1.0f;
    BackButton.DefaultScale = 1.0f;
    BackButton.scaleSpeed = 1.3f;
    BackButton.targetScale = 1.2f;
    BackButton.CenterPosition.x = BackButton.ClickArea.x + BackButton.ClickArea.width / 2.0f;
    BackButton.CenterPosition.y = BackButton.ClickArea.y + BackButton.ClickArea.height / 2.0f;
    // Circle  1
    CircleLvl1.x = 645;
    CircleLvl1.y = 385;
    Radius1 = 102;

    // Circle  2

    CircleLvl2.x = 952;
    CircleLvl2.y = 385;
    Radius2 = 102;

    // Circle  3

    CircleLvl3.x = 645;
    CircleLvl3.y = 635;
    Radius3 = 102;

    // Circle  4

    CircleLvl4.x = 952;
    CircleLvl4.y = 635;
    Radius4 = 102;

    /*
            CircleL1          CircleL2



            CircleL3           CircleL4
    */

    //  Circle Back Button
}

void ButtonAnimation(Button *Button)
{
    float Time = GetFrameTime();

    int WidthBackButtonPic = Button->ClickArea.width;
    int HeightBackButtonPic = Button->ClickArea.height;
    float FinalWidthBackButton = (float)WidthBackButtonPic * Button->targetScale;
    float FinalHeightBackButton = (float)HeightBackButtonPic * Button->targetScale;
    if (CheckCollisionPointRec(GetMousePosition(), Button->ClickArea))
    {

        if (Button->ScaleNow < Button->targetScale)
        {
            Button->ScaleNow += Button->scaleSpeed * Time;
            if (Button->ScaleNow > Button->targetScale)
            {
                Button->ScaleNow = Button->targetScale;
            }
        }
    }
    else
    {
        if (Button->ScaleNow > Button->DefaultScale)
        {
            Button->ScaleNow -= Button->scaleSpeed * Time;
            if (Button->ScaleNow < Button->DefaultScale)
            {
                Button->ScaleNow = Button->DefaultScale;
            }
        }
    }
}
void DrawButton(Button *Button)
{
    float scaledWidth = Button->ClickArea.width * Button->ScaleNow;
    float scaledHeight = Button->ClickArea.height * Button->ScaleNow;

    // حالا origin واقعاً مرکز بافت میشه
    Vector2 origin = {scaledWidth / 2.0f, scaledHeight / 2.0f};

    DrawTexturePro(Button->Picture,
                   (Rectangle){0.0f, 0.0f, (float)Button->Picture.width, (float)Button->Picture.height},

                   // ❗ اینجا باید مختصات مرکز بدی، نه گوشه
                   (Rectangle){Button->CenterPosition.x, Button->CenterPosition.y, scaledWidth, scaledHeight},

                   origin, // مرکز واقعی
                   0.0f, WHITE);
}
void DrawCircleButton(CircleButtonAnim *btn)
{
    float diameter = btn->Radius * 2.0f * btn->ScaleNow;

    Vector2 origin = {diameter / 2.0f, diameter / 2.0f};

    DrawTexturePro(btn->Picture, (Rectangle){0, 0, (float)btn->Picture.width, (float)btn->Picture.height},
                   (Rectangle){btn->CenterPosition.x, btn->CenterPosition.y, diameter, diameter}, origin, btn->rotation,
                   WHITE);
}
void CircleButtonAnimation(CircleButtonAnim *btn)
{
    float dt = GetFrameTime();

    float scaledRadius = btn->Radius * btn->ScaleNow;
    if (btn->rotational)
    {
        btn->rotation += dt * btn->rotationSpeed;
        if (btn->rotation >= 360)
        {
            btn->rotation = 0;
        }
    }
    // بررسی برخورد موس با دایره
    if (CheckCollisionPointCircle(GetMousePosition(), btn->CenterPosition, scaledRadius))
    {
        if (btn->ScaleNow < btn->targetScale && btn->scaleSpeed > 0 ||
            btn->ScaleNow > btn->targetScale && btn->scaleSpeed < 0)
        {
            btn->ScaleNow += btn->scaleSpeed * dt;
            if (btn->ScaleNow > btn->targetScale && btn->scaleSpeed > 0 ||
                btn->ScaleNow < btn->targetScale && btn->scaleSpeed < 0)
                btn->ScaleNow = btn->targetScale;
        }
        btn->IsHover = true;
        if (btn->rotational)
        {
            btn->rotation += dt * btn->rotationSpeed;
            if (btn->rotation >= 360)
            {
                btn->rotation = 0;
            }
        }
    }
    else
    {
        if (btn->ScaleNow > btn->DefaultScale && btn->scaleSpeed > 0 ||
            btn->ScaleNow < btn->DefaultScale && btn->scaleSpeed < 0)
        {
            btn->ScaleNow -= btn->scaleSpeed * dt;
            if (btn->ScaleNow < btn->DefaultScale && btn->scaleSpeed > 0 ||
                btn->ScaleNow > btn->DefaultScale && btn->scaleSpeed < 0)
                btn->ScaleNow = btn->DefaultScale;
        }
        btn->IsHover = false;
        btn->rotation = 0;
    }
}

void Drawlevelselect(void)
{

    DrawTexture(BackgroundLevelselect, 0, 0, WHITE);
    // BackButton

    DrawButton(&BackButton);

    //
    if (CheckCollisionPointCircle(GetMousePosition(), CircleLvl1, Radius1))
    {
        DrawTexture(LVL1Picture, 557, 285, WHITE);
        DrawText("LEVEL 1", 625, 430, 12, WHITE);
    }
    if (CheckCollisionPointCircle(GetMousePosition(), CircleLvl2, Radius2))
    {
        DrawTexture(LVL2Picture, 865, 285, WHITE);
        DrawText("LEVEL 2", 930, 435, 12, WHITE);
    }
    if (CheckCollisionPointCircle(GetMousePosition(), CircleLvl3, Radius3))
    {
        DrawTexture(LVL3Picture, 557, 532, WHITE);
        DrawText("LEVEL 3", 625, 680, 12, WHITE);
    }
    if (CheckCollisionPointCircle(GetMousePosition(), CircleLvl4, Radius4))
    {
        DrawTexture(LVL4Picture, 895, 560, WHITE);
        DrawText("LEVEL 4", 930, 680, 12, WHITE);
    }
    // DrawRectangleLinesEx();
}

void Updatelevelselect(void)
{
    ButtonAnimation(&BackButton);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointCircle(GetMousePosition(), CircleLvl1, Radius1))
        {
            Screen = LVL1;
        }
        else if (CheckCollisionPointCircle(GetMousePosition(), CircleLvl2, Radius2))
        {
            Screen = LVL2;
        }
        else if (CheckCollisionPointCircle(GetMousePosition(), CircleLvl3, Radius3))
        {
            Screen = LVL3;
        }
        else if (CheckCollisionPointCircle(GetMousePosition(), CircleLvl4, Radius4))
        {
            PlaySound(Clocks);
            Screen = LVL4;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), BackButton.ClickArea))
        {
            PlaySound(BackButtonSoundClick);

            Screen = MENU;
        }
    }
}
void Unloadlevelselect(void)
{
    UnloadTexture(BackgroundLevelselect);
    UnloadTexture(BackButton.Picture);
    UnloadTexture(LVL1Picture);
    UnloadTexture(LVL2Picture);
    UnloadTexture(LVL3Picture);
    UnloadTexture(LVL4Picture);
}
