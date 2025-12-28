#include "gif.h"
#include "raylib.h"
#include <Level1.h>
#include <stdio.h>
#include <stdlib.h>
Texture2D Map, lawnMowerRow1_off, lawnMowerRow2_off, lawnMowerRow3_off, lawnMowerRow4_off, lawnMowerRow5_off;
AnimatedObject lawnMowerRow1, lawnMowerRow2, lawnMowerRow3, lawnMowerRow4, lawnMowerRow5;
bool SetuplawnMower = false;
float RectangleWidth = (float)(END_X - START_X) / COLUMNS;
float RectangleHeight = (float)(END_Y - START_Y) / ROWS;
Rectangle MapCell[ROWS][COLUMNS];
void InitLevel1(void)
{
    Map = LoadTexture("../assets/map/level1_map.png");
    lawnMowerRow1 =
        LoadAnimatedObject("../assets/Level1/lawnMower_Active-Sheet.png", 70, 57, 80, 210, 270, 50, 0, 320, 270);
    lawnMowerRow2 = LoadAnimatedObject("../assets/Level1/lawnMower_Active-Sheet.png", 70, 57, 80, 210,
                                       270 + RectangleHeight, 50, 0, 320, 270 + RectangleHeight);
    lawnMowerRow3 = LoadAnimatedObject("../assets/Level1/lawnMower_Active-Sheet.png", 70, 57, 80, 210,
                                       270 + RectangleHeight * 2, 50, 0, 320, 270 + RectangleHeight * 2);
    lawnMowerRow4 = LoadAnimatedObject("../assets/Level1/lawnMower_Active-Sheet.png", 70, 57, 80, 210,
                                       270 + RectangleHeight * 3, 50, 0, 320, 270 + RectangleHeight * 3);
    lawnMowerRow5 = LoadAnimatedObject("../assets/Level1/lawnMower_Active-Sheet.png", 70, 57, 80, 210,
                                       270 + RectangleHeight * 4, 50, 0, 320, 270 + RectangleHeight * 4);
    lawnMowerRow1_off = lawnMowerRow2_off = lawnMowerRow3_off = lawnMowerRow4_off = lawnMowerRow5_off =
        LoadTexture("../assets/Level1/lawnMower_Idle.png");
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
void DrawLevel1(void)
{
    DrawTexture(Map, 0, 0, WHITE);
    if (lawnMowerRow1.posX == lawnMowerRow1.finalX)
    {
        DrawTexture(lawnMowerRow1_off, lawnMowerRow1.finalX, lawnMowerRow1.finalY, WHITE);
    }
    else
    {
        DrawAnimatedObject(&lawnMowerRow1, WHITE);
    }
    if (lawnMowerRow2.posX == lawnMowerRow2.finalX)
    {
        DrawTexture(lawnMowerRow2_off, lawnMowerRow2.finalX, lawnMowerRow2.finalY, WHITE);
    }
    else
    {
        DrawAnimatedObject(&lawnMowerRow2, WHITE);
    }
    if (lawnMowerRow3.posX == lawnMowerRow3.finalX)
    {
        DrawTexture(lawnMowerRow3_off, lawnMowerRow3.finalX, lawnMowerRow3.finalY, WHITE);
    }
    else
    {
        DrawAnimatedObject(&lawnMowerRow3, WHITE);
    }
    if (lawnMowerRow4.posX == lawnMowerRow4.finalX)
    {
        DrawTexture(lawnMowerRow4_off, lawnMowerRow4.finalX, lawnMowerRow4.finalY, WHITE);
    }
    else
    {
        DrawAnimatedObject(&lawnMowerRow4, WHITE);
    }
    if (lawnMowerRow5.posX == lawnMowerRow5.finalX)
    {
        DrawTexture(lawnMowerRow5_off, lawnMowerRow5.finalX, lawnMowerRow5.finalY, WHITE);
    }
    else
    {
        DrawAnimatedObject(&lawnMowerRow5, WHITE);
    }

   //  CellularNetworkMap();  // for debug
}
void UpdateLevel1(void)
{
    UpdateAnimatedObject(&lawnMowerRow1);
    UpdateAnimatedObject(&lawnMowerRow2);
    UpdateAnimatedObject(&lawnMowerRow3);
    UpdateAnimatedObject(&lawnMowerRow4);
    UpdateAnimatedObject(&lawnMowerRow5);

    Vector2 MousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (MousePos.x >= START_X && MousePos.x <= END_X && MousePos.y >= START_Y && MousePos.y <= END_Y)
        {
            int X_Cell = (START_X - MousePos.x) / RectangleWidth;
            int Y_Cell = (START_Y - MousePos.y) / RectangleHeight;
        }
    }
}
void UnloadLevel1(void)
{
    UnloadTexture(Map);
    UnloadAnimatedObject(&lawnMowerRow1);
    UnloadAnimatedObject(&lawnMowerRow2);
    UnloadAnimatedObject(&lawnMowerRow3);
    UnloadAnimatedObject(&lawnMowerRow4);
    UnloadAnimatedObject(&lawnMowerRow5);
}
