#include "raylib.h"
#include <iostream>

void menu() {
     while (!WindowShouldClose() && !(IsKeyPressed(KEY_ENTER)) ) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Bienvenue sur notre version de", 400, 200, 50, BLUE);
        DrawText("Bloons Tower Defense", 500, 250, 50, BLUE);
        DrawText("By Maëva, Aurélien and Alice", 650, 320, 20, DARKGRAY);
        DrawText("Press ENTER to start the game", 400, 500, 50, BLACK);
        EndDrawing();
    }
}
