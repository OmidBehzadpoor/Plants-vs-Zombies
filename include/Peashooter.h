/**
 * @file Peashooter.h
 * @brief تعاریف و ساختارهای مربوط به گیاه لوبیاشلیک کننده  و سیستم شلیک
 * @details  این فایل شامل ویژگی‌های گیاه لوبیاشلیک کننده برای تولید
 * تیر و مدیریت تایمر ها و وضعیت شلیک بولت هیت و اعمال دمیج و سایر موارد
 */
#pragma once
#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "Level1.h"
#include "Plant.h"

/**
 * @struct BulletHit
 * @brief ساختار مربوط به افکت بصری برخورد تیر به زامبی.
 */
struct BulletHit
{
    AnimatedObject BulletHitObj; // انیمیشنی برای نمایش انفجار تیر در محل برخورد
    bool isActive;               // وضعیت فعال بودن افکت روی صفحه
    float DisplayTime;           // کل زمان مجاز برای نمایش انیمیشن برخورد
    float DisplayTimer;          // تایمر داخلی برای پیگیری زمان سپری شده نمایش
};

/**
 * @struct PeaFire
 * @brief ساختار مربوط به هر دانه تیر (لوبیا) شلیک شده.
 */
struct PeaFire
{
    AnimatedObject Pea;            // انیمیشن و ویژگی‌های فیزیکی حرکت تیر
    struct BulletHit PeaBulletHit; // افکت برخورد اختصاصی برای هر تیر
    int X_Cell;                    // ستون فعلی که تیر در آن قرار دارد
    Vector2 Markaz;                // مختصات مرکز هندسی تیر برای چک کردن وعضیت برخورد و خارج شدن از مپ
    float Radius;                  // شعاع هر تیر
    int Y_Cell;                    // ردیفی که تیر در آن شلیک شده است
                                   //  Rectangle CollisionBox; // !منسوخ شد
    bool isActive;                 // وضعیت فعال بودن تیر در زمین بازی
};

/**
 * @struct PeashooterElement
 * @brief ساختار داده اصلی برای گیاه لوبیاشلیک کننده.
 */
typedef struct PeashooterElement
{
    AnimatedObject PeashooterObj; // انیمیشن و ویژگی‌های ظاهری
    struct PeaFire Pea[10];       // !   حداکثر ۱۰ تیر همزمان برای هر گیاه
    PlantBase Base;               // ویژگی‌های پایه گیاه
    float Firingspeed;            // * فاصله زمانی پایه بین هر دو شلیک (ثانیه)
    float FireTimer;              // تایمر داخلی برای زمان‌بندی شلیک بعدی
    float EffectiveFireRate;      // ضریب نرخ شلیک (قابل تغییر توسط سایر گیاهان مثل رز)
    float peaDamege;              // مقدار آسیبی که هر تیر به زامبی وارد می‌کند
    bool Firing;                  // وضعیت فعال بودن حالت شلیک (در صورت وجود زامبی در ردیف)
    // ! تیر زدن زمانی شروع میشه که زامبی وارد چمن زار شده باشه
} PeashooterElement;

// * آرایه سراسری برای مدیریت تمام لوبیاهای شلیک کننده کاشته شده
extern PeashooterElement Peashooter[MAXNUMITEMS];

/** @brief ریست کردن ضریب نرخ شلیک تمام گیاهان به مقدار پیش‌فرض (1.0) */
void ResetEffectiveFireRate(void);

/** @brief ترسیم تمام تیرهای فعال و افکت‌های برخورد آن‌ها در صفحه */
void DrawPeashooterBullets(void);

/**
 * @brief تولید یک  لوبیا شلیک کننده جدید در مختصات مشخص شده
 * * @param obj اشاره‌گر به خانه‌ای از آرایه که لوبیا شلیک کننده جدید در
 * آن ساخته می‌شود
 * @param X_Cell شماره ستون در جدول بازی
 * @param Y_Cell شماره ردیف در جدول بازی
 *
 * @note  نکته: مختصات پیکسلی به طور خودکار بر اساس شماره سلول محاسبه
 * می‌شود
 */
void GeneratePeashooter(PeashooterElement *obj, int X_Cell, int Y_Cell);

/** @brief ایجاد یک تیر جدید در صورت آماده بودن تایمر
 *
 * @param obj اشاره‌گر به خانه‌ای از آرایه  لوبیا شلیک کننده
 *
 * @note  نکته: مختصات پیکسلی به طور خودکار بر اساس شماره سلول محاسبه
 * می‌شود
 */
void GeneratePea(PeashooterElement *obj);

/** @brief به‌روزرسانی وضعیت شلیک گیاه بر اساس حضور زامبی در ردیف
 *
 * @param obj اشاره‌گر به خانه‌ای از آرایه  لوبیا شلیک کننده
 *
 *  @note  اپدیت تیر و زیاد شدن سرعت تیر در این تابع انجام میشود
 */
void UpdatePeashooterFiring(PeashooterElement *Peashooter);

/** @brief آپدیت وضعیت تمام تیرهای یک گیاه (حرکت و برخورد) */
void UpdatePeashooterPeas(PeashooterElement *Peashooter);

/** @brief آپدیت  موقعیت و سلول فعلی یک تیر مشخص */
void UpdatePeashooterSinglePea(PeashooterElement *Peashooter, int PeaNumber);

/** @brief بررسی برخورد تیر با زامبی‌ها و اعمال Damage
 *! @warning این تابع از منطق برخورد استفاده میکند

 * ! منطق اول : برای زامبی هایبه گیاه لوبیا نرسیدن

 * ! منطق دوم : برای زامبی هایی که کمی از گیاه عبور کردن اما هنوز در سلول گیاه هستند

 * @note فارغ از نوع زامبی به جلو ترین زامبی آسیب میزند
*/
void HandlePeaZombieCollision(PeashooterElement *Peashooter, int PeaNumber);

/** @brief  مدیریت زمان نمایش افکت بصری برخورد تیر و حرکت دادن ان */
void UpdatePeaHitEffect(struct BulletHit *PeaBulletHit);

#endif