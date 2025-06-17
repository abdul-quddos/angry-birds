#include "raylib.h"
#include "game.h"

int main() {
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Angry Birds - Archery Game");
    SetTargetFPS(60);

    Game game;
    int currentLevel = 1;
    game.setupLevel(currentLevel);

    Bird* currentBird = nullptr;
    bool isDragging = false;
    Vector2 dragStart = { 0, 0 };

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // --- Handle Input ---
        Level& level = game.getCurrentLevel();
        if (currentBird && currentBird->hasStopped()) {
            currentBird = nullptr; // so we get next one in next frame
        }

        // Get the next bird if needed
        if (!currentBird) {
            for (int i = 0; i < level.getObjectCount(); i++) {
                Bird* b = dynamic_cast<Bird*>(level.getGameObject(i));
                if (b && !b->isInFlight()) {
                    currentBird = b;
                    break;
                }
            }
        }

        if (currentBird && !currentBird->isInFlight()) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                dragStart = GetMousePosition();
                isDragging = true;
            }

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && isDragging) {
                Vector2 dragEnd = GetMousePosition();
                Vector2 direction = {
                    (dragStart.x - dragEnd.x) * 1.5f,  // Adjust power
                    (dragStart.y - dragEnd.y) * 1.5f
                };
                currentBird->shoot(direction);
                isDragging = false;
            }
        }

        game.update(deltaTime);

        // Check if level complete → go to next level
        if (!game.getGameState().isRunning()) {
            currentLevel++;
            if (currentLevel <= 3) {
                game.setupLevel(currentLevel);
                currentBird = nullptr;
            }
            else {
                // Game over
                break;
            }
        }

        // --- Draw ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        game.draw();

        if (isDragging) {
            DrawLineV(dragStart, GetMousePosition(), DARKGRAY);
            DrawCircleV(dragStart, 5, BLACK);
        }

        DrawText(TextFormat("Score: %d", game.getCurrentScore()), 20, 20, 20, DARKGREEN);
        DrawText(TextFormat("Level: %d", currentLevel), 20, 50, 20, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
