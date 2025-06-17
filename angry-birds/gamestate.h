#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "level.h"
#include "myvector.h"
#include <fstream>

class GameState {
private:
    Dynamic_array<Level*> levels;
    int currentLevelIndex;
    bool running;

public:
    GameState();

    void setRunning(bool value);
    bool isRunning() const;
    void addLevel(Level* level);
    void nextLevel();
    void restartLevel();

    void update(float deltaTime);
    void draw();
    bool isGameComplete() const;

    void save(std::ofstream& out);
    void load(std::ifstream& in);

    ~GameState();
};

#endif
