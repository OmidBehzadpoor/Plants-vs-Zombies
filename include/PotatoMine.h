/**
 * @file PotatoMine.h
 * @brief تعاریف و ساختار داده مربوط به گیاه سیب‌زمینی انفجاری
 * @details این فایل شامل مکانیزم‌های زمان‌بندی برای مسلح شدن بمب و
 * مدیریت انفجار تماسی است.
 */
#pragma once
#ifndef POTATOMINE_H
#define POTATOMINE_H
#include "Level1.h"
#include "Plant.h"
typedef struct Zombies Zombies;

/**
 * @struct PotatoMineElement
 * @brief ساختار داده اصلی برای گیاه بمب سیب‌زمینی.
 * * این ساختار وضعیت‌های مختلف گیاه از مرحله کاشت تا انفجار را
 * مدیریت می‌کند
 */
typedef struct PotatoMineElement
{
    AnimatedObject PotatoMineObj;    // انیمیشن و ویژگی‌های ظاهری
    PlantBase Base;                  // ویژگی‌های پایه گیاه
    ActiveTimeBar ActivationDisplay; // نوار نمایش زمان باقی مانده تا فعال شدن
    float Timer;                     // ! تایمر داخلی برای محاسبه زمان مسلح شدن
    bool Active;                     // * بعد گذشت مدتی فعال میشود
    bool Explosion;                  //  وضعیت فعلی انفجار (برای نمایش افکت بصری انفجار)
    float TamirShowsExplosion; // مدت زمانی که افکت انفجار روی صفحه باقی می‌ماند
} PotatoMineElement;

// * آرایه سراسری برای مدیریت تمام سیب زمین های انفجاری موجود در صحنه بازی
extern PotatoMineElement PotatoMine[MAXNUMITEMS];

/**
 * @brief تولید و مقداردهی اولیه سیب‌زمینی انفجاری
 * @param obj اشاره‌گر به خانه مورد نظر در آرایه گیاه
 * @param X_Cell ستون هدف در جدول بازی
 * @param Y_Cell ردیف هدف در جدول بازی
 * @note پس از کاشت، مدتی زمان لازم است تا بمب به وضعیت فعال برسد
 * @note  نکته: مختصات پیکسلی به طور خودکار بر اساس شماره سلول محاسبه
 * می‌شود */
void GeneratePotatoMine(PotatoMineElement *obj, int X_Cell, int Y_Cell);

/**
 * @brief به‌روزرسانی وضعیت بمب در هر فریم

 * @param PotatoMine اشاره‌گر به نمونه بمب مورد نظر
 *
 * @note این تابع تایمر مسلح شدن مدیریت میکند و سیستم تشخیص برخورد با
 زامبی‌ها را
 *  فراخوانی میکند
 *
 */
void UpdatePotatoMine(PotatoMineElement *PotatoMine);

/**
 * @brief مدیریت منطق انفجار و اعمال آسیب به زامبی‌های اطراف
 * @param PotatoMine بمبی که منفجر شده است
 * @warning این تابع تمام زامبی‌های هم‌سلول با بمب را بلافاصله نابود
 * می‌کند
 * ! @warning نزدیک ترین زامبی فارغ از نوع ان می میرد (فقط یک زامبی)
 */
void PotatoMineExplosion(PotatoMineElement *PotatoMine);

/**
 * @brief به‌روزرسانی تایمر و فریم‌های مربوط به افکت بصری انفجار.
 * @param PotatoMine اشاره‌گر به بمب در حال انفجار
 * ! @warning در حالت انفجار گیاه نمیتواند در سلول کاشته شود اما زامبی از روی انفجار عبور میکند

 */
void UpdatePotatoMineExplosionEffect(PotatoMineElement *PotatoMine);

/**
 * @brief ترسیم گرافیکی افکت انفجار
 * @param PotatoMine اشاره‌گر به ارایه سیب زمینی انفجاری  برای دسترسی به مختصات
 * ترسیم
 */
void DrawPotatoMineExplosionEffect(PotatoMineElement *PotatoMine);

#endif