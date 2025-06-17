#include "gamestate.h"

GameState::GameState() : currentLevelIndex(0), running(true) {}

void GameState::addLevel(Level* level)
{
    levels.push(level);
}

void GameState::setRunning(bool value)
{
    running = value;
}
bool GameState::isRunning() const
{
    return running;
}
void GameState::nextLevel() {
    if (currentLevelIndex + 1 < levels.size())
        currentLevelIndex++;
}

void GameState::restartLevel() {
    if (currentLevelIndex >= 0 && currentLevelIndex < levels.size())
        levels[currentLevelIndex]->reset(); 
}

void GameState::update(float deltaTime) {
    if (currentLevelIndex >= 0 && currentLevelIndex < levels.size()) {
        levels[currentLevelIndex]->update(deltaTime);
        if (levels[currentLevelIndex]->levelComplete()) {
            nextLevel();
        }
    }
}

void GameState::draw() {
    if (currentLevelIndex >= 0 && currentLevelIndex < levels.size())
        levels[currentLevelIndex]->draw();
}

bool GameState::isGameComplete() const {
    return currentLevelIndex >= levels.size();
}

void GameState::save(std::ofstream& out) {
    out.write((char*)&currentLevelIndex, sizeof(currentLevelIndex));
    int levelCount = levels.size();
    out.write((char*)&levelCount, sizeof(levelCount));
    for (int i = 0; i < levelCount; ++i) {
        levels[i]->save(out);
    }
}

void GameState::load(std::ifstream& in) {
    for (int i = 0; i < levels.size(); ++i)
        delete levels[i];
    levels.clear();

    in.read((char*)&currentLevelIndex, sizeof(currentLevelIndex));
    int levelCount;
    in.read((char*)&levelCount, sizeof(levelCount));

    for (int i = 0; i < levelCount; ++i) {
        Level* level = new Level();
        level->load(in);
        levels.push(level);
    }
}

GameState::~GameState() {
    for (int i = 0; i < levels.size(); ++i)
        delete levels[i];
}
