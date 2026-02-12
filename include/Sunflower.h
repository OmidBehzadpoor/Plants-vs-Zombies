/**
 * @file Sunflower.h
 * @brief تعاریف و ساختار داده مربوط به گیاه آفتابگردان
 * @details این فایل شامل ویژگی‌های گیاه آفتابگردان برای تولید خورشید و مدیریت زمان انتظار
 * است
 */
#pragma once
#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include "Level1.h"
#include "Plant.h"

/**
 * @struct SunflowerElement
 * @brief ساختار داده اصلی برای گیاه آفتابگردان
 * * این ساختار ویژگی‌های انیمیشنی، پایه‌ای و زمان‌بندی تولید خورشید را در بر
 * می‌گیرد
 */
typedef struct SunflowerElement
{
    AnimatedObject SunFlowerObj; // انیمیشن و ویژگی‌های ظاهری
    PlantBase Base;              // ویژگی‌های پایه گیاه
    float Cooldown;              // فاصله زمانی بین ساختن نور خورشید
} SunflowerElement;

// * آرایه سراسری برای مدیریت تمام آفتاب گردان های موجود در زمین بازی
extern SunflowerElement SunFlower[MAXNUMITEMS];

/**
 * @brief تولید یک رز جدید در مختصات مشخص شده
 * * @param obj اشاره‌گر به خانه‌ای از آرایه که رز جدید در آن ساخته
 * می‌شود
 * @param X_Cell شماره ستون در جدول بازی
 * @param Y_Cell شماره ردیف در جدول بازی
 *
 * @note  نکته: مختصات پیکسلی به طور خودکار بر اساس شماره سلول محاسبه
 * می‌شود
 */
void GenerateSunFlower(SunflowerElement *obj, int X_Cell, int Y_Cell);


/**
 * @brief به‌روزرسانی  تایمرهای آفتاب گردان برای تولید نور خورشید در هر فریم
 * 
 *  
 *  @param SunFlower اشاره‌گر به گیاه آفتاب گردان که باید آپدیت شود
 */
void UpdateSunFlower(SunflowerElement *SunFlower);


#endif