
#ifndef GAME_H
#define GAME_H

#include "level.h"
#include "gamestate.h"
#include "logger.h"
#include "scoremanager.h"
#include <fstream>

class Game {
private:
    Level* level;
    GameState gameState;
    Logger logger;
    ScoreManager<int> scoreManager;

public:
    Game();
    void update(float deltaTime);
    void draw();
    void setupLevel(int levelNumber);
    void saveGame(const char* filename);
    void loadGame(const char* filename);


    int getCurrentScore() const;
    Level& getCurrentLevel();
    GameState& getGameState();
    ~Game();
};

#endif // GAME_H
