/**
 * @file Chomper.h
 * @brief تعاریف و توابع مربوط به چامپر
 * @details این فایل شامل ساختار داده چامپر و توابع مربوط به تولید، آپدیت و تعامل آن با
 * زامبی‌ها است
 */
#pragma once
#ifndef CHOMPER_H
#define CHOMPER_H
#include "Level1.h"
#include "Plant.h"
typedef struct Zombies Zombies;

/**
 * @struct ChomperElement
 * @brief ساختار داده اصلی برای گیاه چامپر
 *
 * * این ساختار تمام ویژگی‌های فیزیکی، زمانی و پایه‌ای گیاه چامپر
 * را در
 * * خود نگه
 * * می‌دارد
 */
typedef struct ChomperElement
{
    AnimatedObject ChomperObj;     // انیمیشن و ویژگی‌های ظاهری
    ActiveTimeBar LifetimeDisplay; // نوار نمایش طول عمر
    PlantBase Base;                // ویژگی‌های پایه گیاه
    float Lifespan;                // طول عمر
} ChomperElement;

// * آرایه سراسری برای مدیریت تمام چامپرهای موجود در زمین بازی
extern ChomperElement Chomper[MAXNUMITEMS];

/**
 * @brief اعمال اثر چامپر بر روی زامبی‌های هم ردیف با چامپر
 *
 *  @param chomper اشاره‌گر به چامپر مورد نظر
 * @param zombieArray آرایه زامبی‌هایی که باید بررسی شوند
 * @param count حداکثر زامبی های فعال در ان مپ
 *
 * ! @return توجه: این تابع سرعت زامبی را به توجه به تعداد چامپر به صورت نمایی 2/3 برابر میکند
 */
void ChomperEffect(ChomperElement *chomper, Zombies *zombieArray, int count);

/**
 * @brief به‌روزرسانی وضعیت داخلی چامپر در هر فریم
 *
 * * این تابع مقدار عمر سپری شده را بروزرسانی میکند
 *
 * * تابع مربوط به کاهش سرعت زامبی را فراخوانی میکند
 *
 * * در تمام شدن عمر چامپر سلول مربوطه را ازاد میکند
 *
 * * @param chomper اشاره‌گر به چامپری که باید آپدیت شود
 */
void UpdateChomper(ChomperElement *chomper);

/**
 * @brief تولید یک چامپر جدید در مختصات مشخص شده
 * * @param obj اشاره‌گر به خانه‌ای از آرایه که چامپر جدید در آن ساخته
 * می‌شود
 * @param X_Cell شماره ستون در جدول بازی
 * @param Y_Cell شماره ردیف در جدول بازی
 * ? نکته: مختصات پیکسلی به طور خودکار بر اساس شماره سلول محاسبه
 * می‌شود
 */
void GenerateChomper(ChomperElement *obj, int X_Cell, int Y_Cell);

#endif