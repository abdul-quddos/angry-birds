
#include "game.h"
#include"mystring.h"
#include <iostream>
using namespace std;

Game::Game():logger("log.txt") {
    logger.logInfo("Game initialized");
    gameState.setRunning(true);
    level = new Level();
}

void Game::update(float deltaTime) {
    for (int i = 0; i < level->getObjectCount(); i++) {
        GameObject* obj = level->getGameObject(i);
        Bird* bird = dynamic_cast<Bird*>(obj);

        if (bird && !bird->isInFlight()) {
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                if (bird && !bird->isInFlight()) {
                    Vector2 direction = {
                        (mousePos.x - bird->getPosition().x) * 0.5f,  // Adjust power
                        (mousePos.y - bird->getPosition().y) * 0.5f
                    };
                    bird->shoot(direction);
                }
            }


            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                DrawLineV(bird->getPosition(), GetMousePosition(), BLUE);
            }

            break;
        }
    }
    if (gameState.isRunning()) {
        level->update(deltaTime);
        if (level->levelComplete()) {
            scoreManager.addScore(100);
            logger.logInfo("Level completed. ");
            gameState.setRunning(false); 
        }
    }
}

void Game::draw() {
    level->draw();
}

void Game::saveGame(const char* filename) {
    ofstream out(filename, ios::binary);
    if (out.is_open()) {
        level->save(out);
        int score = scoreManager.getCurrentScore();
        out.write((char*)&score, sizeof(score));
        out.close();
        logger.logInfo("Game saved successfully.");
    }
    else {
        logger.logError("Failed to open file for saving.");
    }
}

void Game::loadGame(const char* filename) {
    ifstream in(filename, ios::binary);
    if (in.is_open()) {
        level->load(in);
        int score;
        in.read((char*)&score, sizeof(score));
        scoreManager.setScore(score);
        in.close();
        logger.logInfo("Game loaded successfully.");
    }
    else {
        logger.logError("Failed to open file for loading.");
    }
}

Level& Game::getCurrentLevel() {
    return *level;
}

GameState& Game::getGameState() {
    return gameState;
}

void Game::setupLevel(int levelNumber) {
    level->reset(); 

    if (levelNumber == 1) {
        level->addGameObject(new Bird({ 100, 500 }, 50, 50));
        level->addGameObject(new Target({ 600, 400 }, 60, 60));
        level->addGameObject(new Obstacle({ 600, 500 }, 50, 50));
        logger.logInfo("Level 1 setup: 1 Bird, 1 Target, 1 Obstacle");

    }
    else if (levelNumber == 2) {
        level->addGameObject(new Bird({ 100, 500 }, 20, 20));
        level->addGameObject(new Bird({ 120, 500 }, 20, 20)); 
        level->addGameObject(new Target({ 800, 500 }, 30, 30));
        level->addGameObject(new Target({ 850, 470 }, 30, 30)); 
        level->addGameObject(new Obstacle({ 600, 500 }, 50, 50));
        level->addGameObject(new Obstacle({ 650, 470 }, 50, 50));
        logger.logInfo("Level 2 setup: 2 Birds, 2 Targets, 2 Obstacles");

    }
    else if (levelNumber == 3) {
        level->addGameObject(new Bird({ 100, 500 }, 20, 20));
        level->addGameObject(new Bird({ 120, 500 }, 20, 20));
        level->addGameObject(new Bird({ 140, 500 }, 20, 20)); 
        level->addGameObject(new Target({ 800, 500 }, 30, 30));
        level->addGameObject(new Target({ 850, 470 }, 30, 30));
        level->addGameObject(new Target({ 900, 440 }, 30, 30));
        level->addGameObject(new Obstacle({ 600, 500 }, 50, 50));
        level->addGameObject(new Obstacle({ 650, 470 }, 50, 50));
        level->addGameObject(new Obstacle({ 700, 440 }, 50, 50));
        logger.logInfo("Level 3 setup: 3 Birds, 3 Targets, 3 Obstacles");
    }
    gameState.setRunning(true);
}

Game::~Game() {
    delete level;
}

int Game::getCurrentScore() const {
    return scoreManager.getCurrentScore();
}