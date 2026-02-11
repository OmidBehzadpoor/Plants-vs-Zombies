#include "Shop.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "LevelBase.h"
#include "SoundandMusic.h"
#include "levelselect.h"
#include "math.h"
#include "menu.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
Texture2D ShopBG, SunIcon, SnowIcon, FireIcon, PotatoMineIconOFF, PotatoMineIconON, DiamondBankFrame, MiniDiamond,
    MapDiamond, infinityPic, CircularFrame;
StoreItems FireStorm;
StoreItems FreezeBurst;
StoreItems SunPack;
StoreItems PotatoMineItems;
CircleButtonAnim FireButton, SnowButton, SunButton, PotatoMineButton;
int DiamondBank = 0;
void InitShop(void)
{
    ShopBG = LoadTexture("../assets/Shop/Shop.png");
    SnowIcon = LoadTexture("../assets/Shop/Snow.png");
    FireIcon = LoadTexture("../assets/Shop/Fire.png");
    SunIcon = LoadTexture("../assets/Shop/sun.png");
    PotatoMineIconOFF = LoadTexture("../assets/Shop/PotatoMineIconOFF.png");
    PotatoMineIconON = LoadTexture("../assets/Shop/PotatoMineIconON.png");
    DiamondBankFrame = LoadTexture("../assets/Shop/DiamondBank.png");
    MiniDiamond = LoadTexture("../assets/Shop/MiniDiamond.png");
    infinityPic = LoadTexture("../assets/Shop/infinity.png");
    MapDiamond = LoadTexture("../assets/Shop/MapDiamond.png");
    CircularFrame = LoadTexture("../assets/Shop/CircularFrame.png");
    SnowButton.Picture = SnowIcon;
    SetTextureFilter(SnowButton.Picture, TEXTURE_FILTER_BILINEAR);
    SnowButton.Radius = 90;
    SnowButton.ScaleNow = 0.80f;
    SnowButton.DefaultScale = 0.80f;
    SnowButton.scaleSpeed = 1.3f;
    SnowButton.targetScale = 1.0f;
    SnowButton.CenterPosition.x = 945;
    SnowButton.CenterPosition.y = 410;
    SnowButton.rotation = 0;
    SnowButton.rotationSpeed = 10;
    SnowButton.rotational = true;

    FireButton.Picture = FireIcon;
    SetTextureFilter(FireButton.Picture, TEXTURE_FILTER_BILINEAR);
    FireButton.Radius = 90;
    FireButton.ScaleNow = 0.80f;
    FireButton.DefaultScale = 0.80f;
    FireButton.scaleSpeed = 1.3f;
    FireButton.targetScale = 1.0f;
    FireButton.CenterPosition.x = 655;
    FireButton.CenterPosition.y = 410;
    FireButton.rotation = 0;
    FireButton.rotational = false;

    SunButton.Picture = SunIcon;
    SetTextureFilter(SunButton.Picture, TEXTURE_FILTER_BILINEAR);
    SunButton.Radius = 90;
    SunButton.ScaleNow = 0.80f;
    SunButton.DefaultScale = 0.80f;
    SunButton.scaleSpeed = 1.3f;
    SunButton.targetScale = 1.0f;
    SunButton.CenterPosition.x = 1235;
    SunButton.CenterPosition.y = 410;
    SunButton.rotation = 0;
    SunButton.rotationSpeed = 10;
    SunButton.rotational = true;

    PotatoMineButton.Picture = PotatoMineIconON;
    SetTextureFilter(PotatoMineButton.Picture, TEXTURE_FILTER_BILINEAR);
    PotatoMineButton.Radius = 90;
    PotatoMineButton.ScaleNow = 0.60f;
    PotatoMineButton.DefaultScale = 0.60f;
    PotatoMineButton.scaleSpeed = 1.3f;
    PotatoMineButton.targetScale = 0.75f;
    PotatoMineButton.CenterPosition.x = 365;
    PotatoMineButton.CenterPosition.y = 410;
    PotatoMineButton.rotational = false;

    FireStorm.Price = 25;
    FireStorm.StoreInventory = 0;
    FireStorm.PlayerInventory = 0;
    FireStorm.InfiniteInventory = false;

    FreezeBurst.Price = 25;
    FreezeBurst.StoreInventory = 0;
    FreezeBurst.PlayerInventory = 0;
    FreezeBurst.InfiniteInventory = true;

    PotatoMineItems.Price = 25;
    PotatoMineItems.StoreInventory = 0;
    PotatoMineItems.PlayerInventory = 0;
    PotatoMineItems.InfiniteInventory = true;

    SunPack.Price = 75;
    SunPack.StoreInventory = 0;
    SunPack.PlayerInventory = 0;
    SunPack.InfiniteInventory = true;

    LackDiamondWarning.isActive = false;
    LackDiamondWarning.duration = 2.0f;
    LackDiamondWarning.baseSize = 25.0f;
    LackDiamondWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 190};
    LoadGame();
}

void UpdateShop(void)
{
    ButtonAnimation(&BackButton);
    CircleButtonAnimation(&SnowButton);
    CircleButtonAnimation(&FireButton);
    CircleButtonAnimation(&SunButton);
    CircleButtonAnimation(&PotatoMineButton);
    BuyingItems(&FreezeBurst, &SnowButton);
    BuyingItems(&FireStorm, &FireButton);
    BuyingItems(&SunPack, &SunButton);
    BuyingItems(&PotatoMineItems, &PotatoMineButton);
    UpdateWarning(&LackDiamondWarning);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(GetMousePosition(), BackButton.ClickArea))
        {
            PlaySound(BackButtonSoundClick);

            Screen = MENU;
        }
    }
}
void DrawShop(void)
{

    DrawTexture(ShopBG, 0, 0, WHITE);
    DrawWarning(&LackDiamondWarning, BLUE);
    DrawTexture(DiamondBankFrame, 0, 0, WHITE);
    char DiamondBanktext[5];
    sprintf(DiamondBanktext, "%d", DiamondBank);
    DrawTextCentered(GetFontDefault() , DiamondBanktext ,(Vector2){140,40} , 25, 1 ,(Color){243, 222, 142, 255} );
    DrawText("x  Diamond", 85, 55, 17, WHITE);

    // DrawCircleLinesV(SnowButton.CenterPosition,SnowButton.Radius, RED);
    // DrawCircleLinesV(FireButton.CenterPosition, FireButton.Radius, RED);
    // DrawCircleLinesV(SunButton.CenterPosition, SunButton.Radius, RED);

    DrawButton(&BackButton);
    if (SnowButton.IsHover)
    {
        float pulse = 0.8f - sinf(GetTime() * 2.5f) * 0.3f;

        DrawCircleGradient(SnowButton.CenterPosition.x, SnowButton.CenterPosition.y, SnowButton.Radius + pulse * 50,
                           Fade(BLUE, pulse), BLANK);
    }

    DrawCircleButton(&SnowButton);
    if (FireButton.IsHover)
    {
        float pulse = 0.8f - sinf(GetTime() * 2.5f) * 0.3f;

        DrawCircleGradient(FireButton.CenterPosition.x, FireButton.CenterPosition.y, FireButton.Radius + pulse * 50,
                           Fade(RED, pulse), BLANK);
    }
    DrawCircleButton(&FireButton);
    if (SunButton.IsHover)
    {
        float pulse = 0.8f - sinf(GetTime() * 2.5f) * 0.3f;

        DrawCircleGradient(SunButton.CenterPosition.x, SunButton.CenterPosition.y, SunButton.Radius + pulse * 50,
                           Fade(YELLOW, pulse), BLANK);
    }
    DrawCircleButton(&SunButton);

    if (PotatoMineButton.IsHover)
    {
        float pulse = 0.8f - sinf(GetTime() * 2.5f) * 0.3f;

        DrawCircleGradient(PotatoMineButton.CenterPosition.x, PotatoMineButton.CenterPosition.y,
                           PotatoMineButton.Radius + pulse * 50, Fade((Color){222, 200, 147, 255}, pulse), BLANK);
    }
    DrawCircleButton(&PotatoMineButton);
    DrawStoreItemsInfo(&PotatoMineItems, 1);
    DrawStoreItemsInfo(&FireStorm, 2);
    DrawStoreItemsInfo(&FreezeBurst, 3);
    DrawStoreItemsInfo(&SunPack, 4);
}
void DrawStoreItemsInfo(StoreItems *Items, int ItemsNumber)
{
    ItemsNumber--;
    char text[10];
    sprintf(text, "%d", Items->Price);
    DrawText(text, 352 + 290 * ItemsNumber, 550, 25, WHITE);
    DrawTexture(MiniDiamond, 320 + 290 * ItemsNumber, 550, WHITE);
    sprintf(text, "x%d", Items->PlayerInventory);
    DrawText(text, 352 + 290 * ItemsNumber, 660, 25, WHITE);
    if (Items->InfiniteInventory)
    {
        float pulse = 0.4f - sinf(GetTime() * 2.0f) * 0.3f;

        // DrawCircleGradient(315 + 31 + 290 * ItemsNumber, 627, 20 + pulse * 15, Fade(GOLD, pulse), BLANK);
        // DrawCircleGradient(315 + 62 + 290 * ItemsNumber, 627, 20 + pulse * 15, Fade(GOLD, pulse), BLANK);
        DrawCircleGradient(333 + 31 + 290 * ItemsNumber, 627, 30 + pulse * 15, Fade(SaffronYellow, pulse), BLANK);
        DrawTexture(infinityPic, 333 + 290 * ItemsNumber, 615, WHITE);
    }
    else
    {
        if (Items->StoreInventory != 0)
        {
            sprintf(text, "x%d", Items->StoreInventory);
            DrawText(text, 352 + 290 * ItemsNumber, 618, 20, WHITE);
        }
        else{
                    float pulse = 0.4f - sinf(GetTime() * 2.0f) * 0.3f;

                    DrawCircleGradient(333 + 31 + 290 * ItemsNumber, 627, 40 + pulse * 15, Fade(RED, pulse), BLANK);

              DrawText("SOLD OUT", 320 + 290 * ItemsNumber, 618, 20, RED);
        }
    }
}
void BuyingItems(StoreItems *Items, CircleButtonAnim *Button)
{

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || !Button->IsHover)
    {
        return;
    }
    if (DiamondBank >= Items->Price)
    {
        if ((Items->StoreInventory <= 0 && !Items->InfiniteInventory))
        {
            ShowWarning(&LackDiamondWarning, "Low on resources!");
            return;
        }
        DiamondBank -= Items->Price;
        Items->PlayerInventory++;
        Items->StoreInventory--;
        SaveGame();
    }
    else
    {
        ShowWarning(&LackDiamondWarning, "DIAMOND NOT ENOUGH!");
    }
}
