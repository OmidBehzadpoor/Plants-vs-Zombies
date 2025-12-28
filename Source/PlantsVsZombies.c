#include "levelselect.h"
#include "menu.h"
#include "Level1.h"
#include "raylib.h"
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define FPS 60
bool EXIT = false;
GameScreen Screen = MENU;

int main()
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Plants vs Zombies");
    SetTargetFPS(FPS);
    ClearBackground(YELLOW);
    
    InitMenu();
    Initlevelselect();
    InitLevel1();
    while (!WindowShouldClose() && Screen != EXITING)
    {
        if (Screen == MENU)
        {
            UpdateMenu();
        }
        else if (Screen == LEVEL_SELECT)
        {
            Updatelevelselect();
        }
        else if (Screen == LVL1)
        {
           UpdateLevel1();
        }
        BeginDrawing();

        ClearBackground(WHITE);

        if (Screen == MENU)
        {
            DrawMenu();
        }
        else if (Screen == LEVEL_SELECT)
        {
            Drawlevelselect();
            
        }
        else if (Screen == LVL1)
        {
            DrawLevel1();
        }
        
        MouseSelection();
        EndDrawing();
    }

    UnloadMenu();
    Unloadlevelselect();
    UnloadLevel1();
    CloseWindow();

    return 0;
}