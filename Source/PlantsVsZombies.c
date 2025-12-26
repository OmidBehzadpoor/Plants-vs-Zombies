#include "levelselect.h"
#include "menu.h"
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
        MouseSelection();
        EndDrawing();
    }

    UnloadMenu();
    Unloadlevelselect();
    CloseWindow();

    return 0;
}