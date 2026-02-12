#pragma once
#ifndef SHOP_H
#define SHOP_H
#include "levelselect.h"
#include "raylib.h"

extern Texture2D ShopBG, SunIcon, SnowIcon, FireIcon, PotatoMineIconOFF, PotatoMineIconON, DiamondBankFrame, MapDiamond, CircularFrame;
extern int DiamondBank;
void UpdateShop(void);
void DrawShop(void);
void InitShop(void);
typedef struct StoreItems
{
    int StoreInventory;
    int PlayerInventory;
    int Price;
    bool InfiniteInventory;

} StoreItems;
extern StoreItems FireStorm;
extern StoreItems FreezeBurst;
extern StoreItems SunPack;
extern StoreItems PotatoMineItems;
void DrawStoreItemsInfo(StoreItems *Items, int ItemsNumber);
void BuyingItems(StoreItems *Items, CircleButtonAnim *Button);
void UnloadShop(void);
#endif