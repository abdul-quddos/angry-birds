#include "raylib.h"
#include "game.h"
#include <iostream>
using namespace std;

int main() {
    InitWindow(1024, 768, "Angry Birds Style Game");
    SetTargetFPS(60);

    Game game;
    int currentLevel = 1;
    const int maxLevels = 3;
    bool allLevelsComplete = false;

    
    game.setupLevel(currentLevel);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!allLevelsComplete) {
            if (game.getGameState().isRunning()) {
                game.update(deltaTime);
            }
            game.draw();

            if (!game.getGameState().isRunning()) {
                currentLevel++;
                if (currentLevel <= maxLevels) {
                    game.setupLevel(currentLevel);
                }
                else {
                    allLevelsComplete = true;
                }
            }
        }
        else {
            DrawText("All Levels Completed! Press ESC to Exit.", 280, 380, 20, DARKGREEN);
        }

        
        if (IsKeyPressed(KEY_S)) {
            game.saveGame("save.dat");
        }
        if (IsKeyPressed(KEY_L)) {
            game.loadGame("save.dat");
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
