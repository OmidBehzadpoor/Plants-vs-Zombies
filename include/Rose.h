/**
 * @file Rose.h
 * @brief تعاریف مربوط به گیاه رز 
 * @details شامل ساختار داده رز و توابع حمایتی برای سایر گیاهان هم‌ردیف
 */
#pragma once
#ifndef ROSE_H
#define ROSE_H
#include "Plant.h"
#include"Level1.h"
typedef struct RoseElement
{
    AnimatedObject RoseObj;  // انیمیشن و ویژگی‌های ظاهری
    ActiveTimeBar LifetimeDisplay;  // نوار نمایش طول عمر
    PlantBase Base;  // ویژگی‌های پایه گیاه
    float Lifespan;   // طول عمر
    float Timer;   // ! این تامیر به صورت ثانیه شمار عمل میکند
} RoseElement;

// * آرایه سراسری برای مدیریت تمام رز های موجود در زمین بازی
extern RoseElement Rose[MAXNUMITEMS];

/**
 * @brief اعمال اثر درمانی بر روی یک گیاهان هم ردیف
 * 
 * ! @warning به روی گل رز اثر نمیکند
 * 
 * * این تابع سلامت گیاه هدف را در صورت نیاز افزایش می‌دهد
 * 
 * * @param rose اشاره‌گر به گیاه رز که منبع درمان است
 * 
 * @param Plant اشاره‌گر به بخش پایه گیاه هدف که باید درمان شود
 * 
 * @param BaseHp سلامت پایه آن نوع گیاه (برای تعیین سقف درمان)
 */
void ApplyRoseHealEffect(RoseElement *rose, PlantBase *Plant, float BaseHp);

/**
 * @brief مدیریت چرخه‌ی کلی افکت‌های رز
 * 
 * * این تابع در هر فریم فراخوانی شده و تایمر درمان و اثر تقویتی را مدیریت می‌کند
 * 
 * * @param rose اشاره‌گر به گیاه رز مورد نظر
 */
void RoseEffect(RoseElement *rose);

/**
 * @brief تقویت سرعت شلیک لوبیا شلیک کننده هم‌ردیف
 * 
 *  ! توجه: این تابع نرخ شلیک لوبیا شلیک کننده را 20% بهبود می‌دهد
 * 
 * * @param rose اشاره‌گر به گیاه رز
 */
void ApplyRoseFireingEffect(RoseElement *rose);

/**
 * @brief به‌روزرسانی وضعیت حیات و تایمرهای رز در هر فریم
 * 
 * * شامل چک کردن زمان مرگ گیاه و فراخوانی توابع افکت رز 
 *  
 * * @param rose اشاره‌گر به گیاه رزی که باید آپدیت شود
 */
void UpdateRose(RoseElement *rose);

/**
 * @brief تولید یک رز جدید در مختصات مشخص شده
 * * @param obj اشاره‌گر به خانه‌ای از آرایه که رز جدید در آن ساخته
 * می‌شود
 * @param X_Cell شماره ستون در جدول بازی
 * @param Y_Cell شماره ردیف در جدول بازی
 * 
 * ? نکته: مختصات پیکسلی به طور خودکار بر اساس شماره سلول محاسبه
 * می‌شود
 */
void GenerateRose(RoseElement *obj, int X_Cell, int Y_Cell);

#endif