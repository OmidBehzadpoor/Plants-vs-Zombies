/**
 * @file Plant.h
 * @brief هسته مرکزی و تعاریف پایه‌ای سیستم گیاهان
 * @details این فایل شامل ساختارهای مشترک برای تمام گیاهان، سیستم سلامت و تایمرهای عمومی است
 */
#pragma once
#ifndef PLANT_H
#define PLANT_H
#include "raylib.h"
/**
 * @enum PlantType
 * @brief شناسه‌های عددی برای انواع گیاهان موجود در بازی
 *  * این لیست برای تشخیص نوع گیاه در حلقه‌های پردازشی استفاده
 * می‌شود
 */
typedef enum PlantType
{
    PLANT_SUNFLOWER,
    PLANT_PEASHOOTER,
    PLANT_CHOMPER,
    PLANT_ROSE,
    PLANT_POTATOMINE
} PlantType; // ! فعلا استفاده نمیشود

/**
 * @struct HealthMeter
 * @brief دیریت بصری نوار سلامت
 */
typedef struct HealthMeter
{
    Rectangle frameHP;          // فریم گرافیکی نوار سلامت استاندارد
    Vector2 posHP;              // موقعیت نمایش نوار سلامت روی نقشه
    Rectangle frameOverhealBar; // فریم مربوط به نوار سلامت اضافی
    Vector2 posOverhealBar;     // موقعیت مربوط به نوار سلامت اضافی
    float HpPercentage;         // درصد سلامت فعلی
} HealthMeter;

/**
 * @struct PlantBase
 * @brief ویژگی‌های مشترک که در تمام گیاهان وجود دارد
 * @note تمام استراکت گیاهان باید یک نمونه از این ساختار را داشته باشند
 */
typedef struct PlantBase
{
    PlantType Type;        // نوع گیاه // ! فعلا استفاده نمی شود
    float Health;          //  سلامت  فعلی
    int X_Cell;            // ستون هدف در جدول بازی
    int Y_Cell;            // ردیف هدف در جدول بازی
                           //  Rectangle Coordinates; // ! منسوخ شد
    HealthMeter HpDisplay; // اجزای نوار سلامت
    bool isAlive;          // نشان‌دهنده زنده یا مرده بودن گیاه
} PlantBase;
/**
 * @struct ActiveTimeBar
 * @brief نوار نمایش اضافی
 */
typedef struct ActiveTimeBar
{
    Rectangle frameBAR;
    Vector2 posBar;
    float TimePercentage;
} ActiveTimeBar;

struct Zombies;

/** @brief فراخوانی توابع اپدیت هر گیاه و تایمر های انها */
void UpdatePlantsTimer(void);

/** @brief به‌روزرسانی فریم‌های انیمیشن تمام گیاهان فعال */
void UpdatePlantsAnimation(void);

/** @brief آپدیت زمان انتظار  برای خرید مجدد گیاهان در بازی */
void CooldownUpdate(void);

/** @brief رسم کلی تمام گیاهان*/
void DrawPlantsObject(void);

/** @brief تابع اصلی برای آپدیت منطقی تمام گیاهان در هر فریم */
void UpdatePlants(void);

/** @brief رسم گیاهانی که باید زیرِ لایه زامبی‌ها نمایش داده شوند */
void DrawPlantsUnderZombie(void);

/** @brief رسم گیاهانی که روی لایه زامبی‌ها قرار می‌گیرند (مثل افکت‌ها)
 */
void DrawPlantsOverZombie(void);

/** * @brief رسم نوار سلامت
 * @param bar اشاره‌گر به ساختار
 *  HealthMeter
 */
void DrawHpBar(HealthMeter *bar);

/** * @brief به‌روزرسانی نوار طول عمر (برای گیاهان موقت)
 * @param life مقدار عمر فعلی
 * @param maxLife سقف عمر تعریف شده
 */
void UpdateLifetimeBar(ActiveTimeBar *bar, float life, float maxLife);

/** * @brief محاسبه و به‌روزرسانی نوار سلامت بر اساس آسیب دریافتی
 * @param Plant اشاره‌گر به گیاه هدف
 * @param BaseHp سلامت پایه لول (برای محاسبه درصد)
 */
void UpdateHpBar(PlantBase *Plant, float BaseHp);

/** * @brief تولید ویژگی‌های پایه‌ای گیاه
 * @warning این تابع باید توسط تمام توابع ساخت گیاهان صدا زده شود.
 */
void GeneratePlantBase(PlantBase *obj, PlantType Type, float HP, int X_Cell, int Y_Cell);

#endif