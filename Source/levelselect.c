#include "menu.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <levelselect.h>
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

void ButtonAnimation(void)
{
    float Time = GetFrameTime();

    int WidthBackButtonPic = BackButton.Picture.width;
    int HeightBackButtonPic = BackButton.Picture.height;
    float FinalWidthBackButton = (float)WidthBackButtonPic * BackButton.targetScale;
    float FinalHeightBackButton = (float)HeightBackButtonPic * BackButton.targetScale;
    if (CheckCollisionPointRec(GetMousePosition(), BackButton.ClickArea))
    {

        if (BackButton.ScaleNow < BackButton.targetScale)
        {
            BackButton.ScaleNow += BackButton.scaleSpeed * Time;
            if (BackButton.ScaleNow > BackButton.targetScale)
            {
                BackButton.ScaleNow = BackButton.targetScale;
            }
        }
    }
    else
    {
        if (BackButton.ScaleNow > BackButton.DefaultScale)
        {
            BackButton.ScaleNow -= BackButton.scaleSpeed * Time;
            if (BackButton.ScaleNow < BackButton.DefaultScale)
            {
                BackButton.ScaleNow = BackButton.DefaultScale;
            }
        }
    }
}
void Drawlevelselect(void)
{

    DrawTexture(BackgroundLevelselect, 0, 0, WHITE);
    //BackButton
    Vector2 origin = {(float)BackButton.Picture.width / 2.0f, (float)BackButton.Picture.height / 2.0f}; // مرکز تصویر
    ButtonAnimation();
    DrawTexturePro(
        BackButton.Picture,
        (Rectangle){0.0f, 0.0f, (float)BackButton.Picture.width, (float)BackButton.Picture.height}, // منبع (تمام بافت)
        (Rectangle){BackButton.CenterPosition.x, BackButton.CenterPosition.y, (float)BackButton.Picture.width * BackButton.ScaleNow,
                    (float)BackButton.Picture.height * BackButton.ScaleNow}, // مقصد (با مقیاس)
        origin,                                 // نقطه مبدأ (Origin)
        0.0f,                                   // چرخش
        WHITE);

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
            Screen = LVL4;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), BackButton.ClickArea))
        {
            Screen = MENU;
        }
    }
}
void Unloadlevelselect(void)
{
    UnloadTexture(BackgroundLevelselect);
}
