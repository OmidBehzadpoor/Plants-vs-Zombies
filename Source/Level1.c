#include "Level1.h"
#include "gif.h"
#include "levelselect.h"
#include "menu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Texture2D Map, OFFlawnMowerRow[ROWLAWNMOWER], SunBankPic, Frame, selectpic, Price[4];
AnimatedObject LawnMower[ROWLAWNMOWER], icon[4];
bool SetuplawnMower = false;
bool FirstRun = true;
LevelInfo Level1Info;
Color GoldOrange = {255, 188, 0, 255};
int SunBank = 0;
float RectangleWidth = (float)(END_X - START_X) / COLUMNS; // 107.5
float RectangleHeight = (float)(END_Y - START_Y) / ROWS;   // 122
float SunTimer;
Font HorrorFont;
WarningMessage LackSunWarning;
double lvl1Runtime = 0;
int CurrentSunIndex = 0;
Rectangle MapCell[ROWS][COLUMNS];
MapContent CellContent[ROWS][COLUMNS] = {EMPTY};
SunElement SunElementArray[MAXSUNELEMENT];
MapContent Selection = EMPTY;
SunflowerElement SunFlower[MAXNUMITEMS];
PeashooterElement Peashooter[MAXNUMITEMS];
RoseElement Rose[MAXNUMITEMS];
ChomperElement Chomper[MAXNUMITEMS];
void InitLevel1(void)
{
    Map = LoadTexture("../assets/map/level1_map.png");
    SunBankPic = LoadTexture("../assets/Level1/SunBack.png");
    selectpic = LoadTexture("../assets/Level1/Select.png");
    Frame = LoadTexture("../assets/Level1/Frame.png");
    LackSunWarning.isActive = false;
    LackSunWarning.duration = 2.0f;
    LackSunWarning.baseSize = 30.0f;
    LackSunWarning.startPos = (Vector2){(float)GetScreenWidth() / 2.0f, 150};
    HorrorFont = LoadFont("../assets/Level1/houseofterrormedium.ttf");
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        LawnMower[i] = LoadAnimatedObject("../assets/Level1/lawnMower_Active-Sheet.png", 70, 57, 80, 210,
                                          270 + RectangleHeight * i, 50, 0, 320, 270 + RectangleHeight * i);
        OFFlawnMowerRow[i] = LoadTexture("../assets/Level1/lawnMower_Idle.png");
        CellContent[i][0] = LAWNMOWER;
    }
    for (int i = 0; i < 4; i++)
    {
        int pixel = (i == 2) ? 100 : 71;
        int pixelY = (i == 2) ? 0 : 25;
        int k = (i == 2) ? 12 : 0;
        char temp[100];
        sprintf(temp, "../assets/Level1/icon%d.png", i);
        icon[i] = LoadAnimatedObject(temp, pixel, pixel, 80, 370 - k + Frame.width * i, pixelY, 0, 0,
                                     370 - k + Frame.width * i, 25);
        sprintf(temp, "../assets/Level1/price%d.png", i);
        Price[i] = LoadTexture(temp);
    }
    //-------------------------------------------------
    Level1Info.SunFlowertInfoLevel.price = 50;
    Level1Info.PeashooterInfoLevel.price = 100;
    Level1Info.ChompertInfoLevel.price = 125;
    Level1Info.RosetInfoLevel.price = 150;
    Level1Info.SunFlowertInfoLevel.Cooldown = 45;
    Level1Info.PeashooterInfoLevel.Cooldown = 45;
    Level1Info.ChompertInfoLevel.Cooldown = 60;
    Level1Info.RosetInfoLevel.Cooldown = 70;
    Level1Info.SunFlowertInfoLevel.Timer = 0;
    Level1Info.PeashooterInfoLevel.Timer = 0;
    Level1Info.ChompertInfoLevel.Timer = 0;
    Level1Info.RosetInfoLevel.Timer = 0;
    Level1Info.SunFlowertInfoLevel.Lock = false;
    Level1Info.PeashooterInfoLevel.Lock = false;
    Level1Info.ChompertInfoLevel.Lock = false;
    Level1Info.RosetInfoLevel.Lock = false;
    Level1Info.SunElementInfoLevel.Value = VALUESUN;
    Level1Info.SunElementInfoLevel.DisplayTime = DISPLAYSUN;
    Level1Info.SunElementInfoLevel.Regenerate = GENERATESUN;

    for (int Y = START_Y, i = 0, j = 0; Y <= END_Y - RectangleHeight; Y = Y + RectangleHeight)
    {
        j = 0;
        for (int X = START_X; X <= END_X - RectangleWidth; X = X + RectangleWidth)
        {
            MapCell[i][j].x = X;
            MapCell[i][j].y = Y;
            MapCell[i][j].width = RectangleWidth;
            MapCell[i][j].height = RectangleHeight;
            j++;
        }
        i++;
    }
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        SunFlower[i].SunFlowerObj = LoadAnimatedObject("../assets/Level1/SunFlower.png", 80, 80, 80, 0, 0, 0, 0, 0, 0);
        SunFlower[i].isAlive = false;
        SunFlower[i].Health = 100;
        Rose[i].RoseObj = LoadAnimatedObject("../assets/Level1/SunFlower.png", 80, 80, 80, 0, 0, 0, 0, 0, 0);
        Rose[i].Health = 100;
        Rose[i].isAlive = false;
        Chomper[i].ChomperObj = LoadAnimatedObject("../assets/Level1/SunFlower.png", 80, 80, 80, 0, 0, 0, 0, 0, 0);
        Chomper[i].isAlive = false;
        Peashooter[i].PeashooterObj =
            LoadAnimatedObject("../assets/Level1/SunFlower.png", 80, 80, 80, 0, 0, 0, 0, 0, 0);
        Peashooter[i].isAlive = false;
    }

    //------------- SUN ELEMENT   INFO -----------------
    SunTimer = 0;
    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        SunElementArray[i].sun = LoadAnimatedObject("../assets/Level1/Sun_Sheet.png", 79, 79, 60, 0, 0, 0, 45, 0, 0);
        SunElementArray[i].Available = false;
        SunElementArray[i].time = 0.0f;
    }
    //------------------------------
}

void DrawLevel1(void)
{

    DrawLevelItems();
    if (Selection != EMPTY)
    {
        DrawSelectionTick();
    }
    DrawPlants();
    DrawSunElement();
    if (LackSunWarning.isActive)
    {
        DrawLackSunWarning();
    }

    CellularNetworkMap(); // for debug
}
void UpdateLevel1(void)
{

    UpdateLevelItems();
    UpdateSUNELEMENT();
    UpdatePlantsTimer();
    UpdatePlantsAnimation();
    CooldownUpdate();
    if (LackSunWarning.isActive)
    {
        UpdateLackSunWarning();
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        CheckSelect();
        UpdateSelectionItems();
        CollectSunElement();
    }
}
void UnloadLevel1(void)
{
    UnloadTexture(Map);
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        UnloadAnimatedObject(&LawnMower[i]);
        UnloadTexture(OFFlawnMowerRow[i]);
    }
    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        UnloadAnimatedObject(&SunElementArray[i].sun);
    }
    for (int i = 0; i < 4; i++)
    {
        UnloadAnimatedObject(&icon[i]);
    }
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        UnloadAnimatedObject(&SunFlower[i].SunFlowerObj);
        UnloadAnimatedObject(&Chomper[i].ChomperObj);
        UnloadAnimatedObject(&Peashooter[i].PeashooterObj);
        UnloadAnimatedObject(&Rose[i].RoseObj);
    }
    UnloadFont(HorrorFont);
}
void GenerateSun(SunElement *obj, int x, int y)
{
    if (x == GENERATERANDOM && y == GENERATERANDOM)
    {
        int xstart = rand() % SCREEN_WIDTH;
        int yfinal = rand() % SCREEN_HEIGHT;
        obj->sun.posY = 0;
        obj->sun.speedY = 45;
        obj->sun.posX = obj->sun.finalX = xstart;
        obj->sun.finalY = yfinal;
        obj->Available = true;
        obj->time = 0;
        return;
    }
    else
    {
        int rand1 = rand() % 2;
        int rand2 = rand() % 2;
        obj->sun.posY = y - 40;
        if (rand1)
        {
            obj->sun.posX = x + 30;
        }
        else
        {
            obj->sun.posX = x - 30;
        }
        obj->sun.speedY = 5;

        obj->sun.finalX = x;
        obj->sun.finalY = y + 35;
        obj->Available = true;
        obj->time = 0;
        return;
    }
}
void CheckSelect()
{
    Vector2 MousePos = GetMousePosition();

    for (int i = 0; i < 4; i++)
    {
        if (MousePos.y >= 0 && MousePos.y <= Frame.height && MousePos.x >= 300 + i * Frame.width &&
            MousePos.x <= 300 + i * Frame.width + Frame.width)
        {
            switch (i)
            {
            case 0:
                if (!Level1Info.SunFlowertInfoLevel.Lock)
                {
                    if (SunBank >= Level1Info.SunFlowertInfoLevel.price)
                    {

                        Selection = SUNFLOWER;
                    }
                    else
                    {
                        ShowLackSunWarning();
                    }
                }
                else
                {
                }
                break;
            case 1:
                if (!Level1Info.PeashooterInfoLevel.Lock)
                {
                    if (SunBank >= Level1Info.PeashooterInfoLevel.price)
                    {
                        Selection = PEASHOOTER;
                    }
                    else
                    {
                        ShowLackSunWarning();
                    }
                }
                else
                {
                }
                break;
            case 2:
                if (!Level1Info.ChompertInfoLevel.Lock)
                {
                    if (SunBank >= Level1Info.ChompertInfoLevel.price)
                    {
                        Selection = CHOMPER;
                    }
                    else
                    {
                        ShowLackSunWarning();
                    }
                }
                else
                {
                }
                break;
            case 3:
                if (!Level1Info.RosetInfoLevel.Lock)
                {
                    if (SunBank >= Level1Info.RosetInfoLevel.price)
                    {
                        Selection = ROSE;
                    }
                    else
                    {
                        ShowLackSunWarning();
                    }
                }
                else
                {
                }
                break;
            default:
                Selection = EMPTY;
            }
            return;
        }
        else
        {
            if (!(MousePos.x >= START_X && MousePos.x <= END_X && MousePos.y >= START_Y && MousePos.y <= END_Y))
            {
                Selection = EMPTY;
            }
        }
    }
}
void GenerateSunFlower(SunflowerElement *obj, int X_Cell, int Y_Cell)
{
    obj->Cooldown = 30;
    obj->Health = 100;
    obj->SunFlowerObj.posX = obj->SunFlowerObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->SunFlowerObj.posY = obj->SunFlowerObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;
    obj->isAlive = true;

    return;
}
void GenerateRose(RoseElement *obj, int X_Cell, int Y_Cell)
{
    obj->Lifespan = 10;
    obj->Health = 100;
    obj->RoseObj.posX = obj->RoseObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->RoseObj.posY = obj->RoseObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;
    obj->isAlive = true;

    return;
}
void GenerateChomper(ChomperElement *obj, int X_Cell, int Y_Cell)
{
    obj->Lifespan = 20;
    obj->Health = 100;
    obj->ChomperObj.posX = obj->ChomperObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->ChomperObj.posY = obj->ChomperObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;
    obj->isAlive = true;

    return;
}
void GeneratePeashooter(PeashooterElement *obj, int X_Cell, int Y_Cell)
{
    obj->Health = 100;
    obj->Firingspeed = 15;
    obj->PeashooterObj.posX = obj->PeashooterObj.finalX = MapCell[Y_Cell][X_Cell].x + 10;
    obj->PeashooterObj.posY = obj->PeashooterObj.finalY = MapCell[Y_Cell][X_Cell].y + 15;
    obj->isAlive = true;

    return;
}
void ShowLackSunWarning(void)
{

    strcpy(LackSunWarning.text, "SUN NOT ENOUGH!");
    LackSunWarning.isActive = true;
    LackSunWarning.timer = LackSunWarning.duration; // ریست تایمر
}
void DrawLackSunWarning(void)
{

    // محاسبه زمان سپری شده از شروع نمایش (برعکس تایمر)
    float elapsed = LackSunWarning.duration - LackSunWarning.timer;

    // **افکت ۱: حرکت عمودی نوسانی (Bouncing)**
    // استفاده از sin برای نوسان نرم
    // 5.0f * sin(elapsed * 20.0f) مقدار جابجایی عمودی است.
    // 20.0f سرعت نوسان را تعیین می کند.
    float offset = 5.0f * sinf(elapsed * 20.0f);

    // **افکت ۲: بزرگ شدن/کوچک شدن (Scaling)**
    // استفاده از sin برای تغییر اندازه (اوج در وسط مدت نمایش)
    float scaleFactor = 1.0f + 0.1f * sinf(elapsed * 2 * PI / LackSunWarning.duration);

    Vector2 textPosition = LackSunWarning.startPos;
    textPosition.y += offset; // اعمال نوسان عمودی

    float currentSize = LackSunWarning.baseSize * scaleFactor;

    // برای وسط قرار گرفتن متن، ابتدا اندازه آن را بگیرید
    Vector2 measure = MeasureTextEx(HorrorFont, LackSunWarning.text, currentSize, 2.0f);
    textPosition.x -= measure.x / 2.0f; // وسط قرار دادن افقی
    textPosition.y -= measure.y / 2.0f; // وسط قرار دادن عمودی

    DrawTextEx(HorrorFont, LackSunWarning.text, textPosition, currentSize, 2.0f,
               RED // می‌توانید رنگ را به قرمز تغییر دهید
    );
}
void CooldownUpdate(void)
{
    if (Level1Info.SunFlowertInfoLevel.Lock)
    {
        Level1Info.SunFlowertInfoLevel.Timer += GetFrameTime();
        if (Level1Info.SunFlowertInfoLevel.Timer >= Level1Info.SunFlowertInfoLevel.Cooldown)
        {
            Level1Info.SunFlowertInfoLevel.Lock = false;
            Level1Info.SunFlowertInfoLevel.Timer = 0;
        }
    }
    if (Level1Info.PeashooterInfoLevel.Lock)
    {
        Level1Info.PeashooterInfoLevel.Timer += GetFrameTime();
        if (Level1Info.PeashooterInfoLevel.Timer >= Level1Info.PeashooterInfoLevel.Cooldown)
        {
            Level1Info.PeashooterInfoLevel.Lock = false;
            Level1Info.PeashooterInfoLevel.Timer = 0;
        }
    }
    if (Level1Info.ChompertInfoLevel.Lock)
    {
        Level1Info.ChompertInfoLevel.Timer += GetFrameTime();
        if (Level1Info.ChompertInfoLevel.Timer >= Level1Info.ChompertInfoLevel.Cooldown)
        {
            Level1Info.ChompertInfoLevel.Lock = false;
            Level1Info.ChompertInfoLevel.Timer = 0;
        }
    }
    if (Level1Info.RosetInfoLevel.Lock)
    {
        Level1Info.RosetInfoLevel.Timer += GetFrameTime();
        if (Level1Info.RosetInfoLevel.Timer >= Level1Info.RosetInfoLevel.Cooldown)
        {
            Level1Info.RosetInfoLevel.Lock = false;
            Level1Info.RosetInfoLevel.Timer = 0;
        }
    }
}
void DrawPlants(void)
{
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (SunFlower[i].isAlive)
        {
            DrawAnimatedObject(&SunFlower[i].SunFlowerObj, WHITE);
        }
        if (Chomper[i].isAlive)
        {
            DrawAnimatedObject(&Chomper[i].ChomperObj, WHITE);
        }
        if (Peashooter[i].isAlive)
        {
            DrawAnimatedObject(&Peashooter[i].PeashooterObj, WHITE);
        }
        if (Rose[i].isAlive)
        {
            DrawAnimatedObject(&Rose[i].RoseObj, WHITE);
        }
    }
}
void DrawSunElement(void)
{
    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        if (SunElementArray[i].Available == true)
        {
            DrawAnimatedObject(&SunElementArray[i].sun, WHITE);
        }
    }
}
void DrawSelectionTick(void)
{
    switch (Selection)
    {
    case SUNFLOWER:
        DrawTexture(selectpic, 360 + 0 * Frame.width, 30, WHITE);
        break;
    case PEASHOOTER:
        DrawTexture(selectpic, 360 + 1 * Frame.width, 30, WHITE);
        break;
    case CHOMPER:
        DrawTexture(selectpic, 360 + 2 * Frame.width, 30, WHITE);
        break;
    case ROSE:
        DrawTexture(selectpic, 360 + 3 * Frame.width, 30, WHITE);
        break;

    default:
        break;
    }
}
void DrawLevelItems(void)
{
    DrawTexture(Map, 0, 0, WHITE);
    DrawTexture(SunBankPic, 0, 0, WHITE);
    for (int i = 0; i < 4; i++)
    {
        DrawTexture(Frame, 300 + i * Frame.width, 0, WHITE);
        DrawAnimatedObject(&icon[i], WHITE);
        DrawTexture(Price[i], 445 + i * Frame.width, 75, WHITE);
    }

    char sunbanktext[5];
    sprintf(sunbanktext, "%d", SunBank);
    DrawText(sunbanktext, 85, 40, 30, GoldOrange);
    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        if (LawnMower[i].posX == LawnMower[i].finalX)
        {
            DrawTexture(OFFlawnMowerRow[i], LawnMower[i].finalX, LawnMower[i].finalY, WHITE);
        }
        else
        {
            DrawAnimatedObject(&LawnMower[i], WHITE);
        }
    }
}
void UpdatePlantsTimer(void)
{
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (SunFlower[i].isAlive)
        {
            SunFlower[i].Cooldown -= GetFrameTime();
            if (SunFlower[i].Cooldown <= 0)
            {
                SunFlower[i].Cooldown = 30;
                GenerateSun(&SunElementArray[CurrentSunIndex], SunFlower[i].SunFlowerObj.posX,
                            SunFlower[i].SunFlowerObj.posY);
                CurrentSunIndex = (CurrentSunIndex + 1) % MAXSUNELEMENT;
            }
        }
        if (Rose[i].isAlive)
        {
            Rose[i].Lifespan -= GetFrameTime();
            if (Rose[i].Lifespan <= 0)
            {
                Rose[i].isAlive = false;
                Selection = EMPTY;
            }
        }
        if (Chomper[i].isAlive)
        {
            Chomper[i].Lifespan -= GetFrameTime();
            if (Chomper[i].Lifespan <= 0)
            {
                Chomper[i].isAlive = false;
                Selection = EMPTY;
            }
        }
    }
}
void UpdateSUNELEMENT(void)
{
    SunTimer += GetFrameTime();
    if (SunTimer >= Level1Info.SunElementInfoLevel.Regenerate)
    {
        SunTimer = 0;

        GenerateSun(&SunElementArray[CurrentSunIndex], GENERATERANDOM, GENERATERANDOM);
        CurrentSunIndex = (CurrentSunIndex + 1) % MAXSUNELEMENT;
    }
    for (int i = 0; i < MAXSUNELEMENT; i++)
    {
        if (SunElementArray[i].Available == true)
        {
            UpdateAnimatedObject(&SunElementArray[i].sun);
            SunElementArray[i].time += GetFrameTime();
            if (SunElementArray[i].time >= Level1Info.SunElementInfoLevel.DisplayTime)
            {
                SunElementArray[i].Available = false;
            }
        }
    }
}
void UpdateLevelItems(void)
{
    if (FirstRun)
    {
        unsigned int random = (unsigned int)(GetTime() * 1000);
        srand(random);
        FirstRun = false;
    }

    for (int i = 0; i < ROWLAWNMOWER; i++)
    {
        UpdateAnimatedObject(&LawnMower[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        UpdateAnimatedObject(&icon[i]);
    }
}
void UpdateLackSunWarning(void)
{
    LackSunWarning.timer -= GetFrameTime();
    if (LackSunWarning.timer <= 0.0f)
    {
        LackSunWarning.isActive = false; // پیام را غیرفعال کن
    }
}
void UpdateSelectionItems(void)
{
    Vector2 MousePos = GetMousePosition();

    if (MousePos.x >= START_X && MousePos.x <= END_X && MousePos.y >= START_Y && MousePos.y <= END_Y)
    {
        int X_Cell = (MousePos.x - START_X) / RectangleWidth;
        int Y_Cell = (MousePos.y - START_Y) / RectangleHeight;
        if (Selection != EMPTY)
        {
            if (Selection == SUNFLOWER && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (SunFlower[i].isAlive == false)
                    {
                        GenerateSunFlower(&SunFlower[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = SUNFLOWER;
                        SunBank -= Level1Info.SunFlowertInfoLevel.price;
                        Level1Info.SunFlowertInfoLevel.Lock = true;
                        Selection = EMPTY;

                        break;
                    }
                }
            }
            else if (Selection == PEASHOOTER && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (Peashooter[i].isAlive == false)
                    {
                        GeneratePeashooter(&Peashooter[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = PEASHOOTER;
                        SunBank -= Level1Info.PeashooterInfoLevel.price;
                        Level1Info.PeashooterInfoLevel.Lock = true;
                        Selection = EMPTY;

                        break;
                    }
                }
            }
            else if (Selection == CHOMPER && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (Chomper[i].isAlive == false)
                    {
                        GenerateChomper(&Chomper[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = CHOMPER;
                        SunBank -= Level1Info.ChompertInfoLevel.price;
                        Level1Info.ChompertInfoLevel.Lock = true;
                        Selection = EMPTY;

                        break;
                    }
                }
            }
            else if (Selection == ROSE && CellContent[Y_Cell][X_Cell] == EMPTY)
            {
                for (int i = 0; i < MAXNUMITEMS; i++)
                {
                    if (Rose[i].isAlive == false)
                    {
                        GenerateRose(&Rose[i], X_Cell, Y_Cell);
                        CellContent[Y_Cell][X_Cell] = ROSE;
                        SunBank -= Level1Info.RosetInfoLevel.price;
                        Level1Info.RosetInfoLevel.Lock = true;
                        Selection = EMPTY;
                        break;
                    }
                }
            }
        }
    }
}
void UpdatePlantsAnimation(void)
{
    for (int i = 0; i < MAXNUMITEMS; i++)
    {
        if (SunFlower[i].isAlive)
        {
            UpdateAnimatedObject(&SunFlower[i].SunFlowerObj);
        }
        if (Peashooter[i].isAlive)
        {
            UpdateAnimatedObject(&Peashooter[i].PeashooterObj);
        }
        if (Chomper[i].isAlive)
        {
            UpdateAnimatedObject(&Chomper[i].ChomperObj);
        }
        if (Rose[i].isAlive)
        {
            UpdateAnimatedObject(&Rose[i].RoseObj);
        }
    }
}
void CollectSunElement(void)
{
    Vector2 MousePos = GetMousePosition();

    for (int i = 0; i < MAXSUNELEMENT; i++)
    {

        if (SunElementArray[i].Available)
        {
            if (MousePos.x >= SunElementArray[i].sun.posX &&
                MousePos.x <= SunElementArray[i].sun.posX + SunElementArray[i].sun.frames->width &&
                MousePos.y >= SunElementArray[i].sun.posY &&
                MousePos.y <= SunElementArray[i].sun.posY + SunElementArray[i].sun.frames->height)
            {
                SunElementArray[i].Available = false;
                SunBank += Level1Info.SunElementInfoLevel.Value;
            }
        }
    }
}
void CellularNetworkMap(void)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            char *Coordinates;
            Coordinates = (char *)malloc(10 * sizeof(char));
            sprintf(Coordinates, "(%d , %d)", i + 1, j + 1);
            DrawRectangleLinesEx(MapCell[i][j], 1, WHITE);
            DrawText(Coordinates, MapCell[i][j].x + 5, MapCell[i][j].y + 5, 20, RED);
            free(Coordinates);
        }
    }
}