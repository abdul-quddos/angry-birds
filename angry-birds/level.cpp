#include "level.h"
#include "raylib.h" 
#include<iostream>
using namespace std;
Level::Level() : bird(nullptr), isLevelComplete(false) {}

void Level::addGameObject(GameObject* obj) {
    gameObjects.push(obj);
}

void Level::setBird(Bird* b) {
    bird = b;
    gameObjects.push(bird); 
}

void Level::update(float deltaTime) {
    isLevelComplete = true;

    for (int i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->update(deltaTime);
        Target* target = dynamic_cast<Target*>(gameObjects[i]);
        if (target && !target->getIsHit())
            isLevelComplete = false;
    }
}

void Level::draw() 
{
    for (int i = 0; i < gameObjects.size(); ++i) 
        gameObjects[i]->draw();
}

void Level::reset() {
    for (int i = 0; i < gameObjects.size(); i++) {
        delete gameObjects[i];  // Properly delete each object
    }
    gameObjects.clear();
    bird = nullptr;  // Reset pointer to avoid dangling reference
    isLevelComplete = false;
}

bool Level::levelComplete() const {
    return isLevelComplete;
}

GameObject* Level::getGameObject(int idx)
{
    if (idx < gameObjects.size())
        return gameObjects[idx];
}
int Level::getObjectCount()
{
    return gameObjects.size();
}
void Level::save(std::ofstream& out) {
    int objectCount = gameObjects.size();
    out.write((char*)&objectCount, sizeof(objectCount));

    for (int i = 0; i < objectCount; i++) {
        GameObject* obj = gameObjects[i];

        if (dynamic_cast<Bird*>(obj)) {
            int type = 1;
            out.write((char*)&type, sizeof(type));
        }
        else if (dynamic_cast<Target*>(obj)) {
            int type = 2;
            out.write((char*)&type, sizeof(type));
        }
        else if (dynamic_cast<Obstacle*>(obj)) {
            int type = 3;
            out.write((char*)&type, sizeof(type));
        }
    }
}

void Level::load(std::ifstream& in) {

    for (int i = 0; i < gameObjects.size(); i++)
        delete gameObjects[i];
    gameObjects.clear();

    int objectCount;
    in.read((char*)&objectCount, sizeof(objectCount));

    for (int i = 0; i < objectCount; i++) {
        int type;
        in.read((char*)&type, sizeof(type));

        GameObject* obj = nullptr;

        if (type == 1) obj = new Bird();
        else if (type == 2) obj = new Target();
        else if (type == 3) obj = new Obstacle();

        if (obj) {
            obj->load(in);
            gameObjects.push(obj);
        }
    }
}

Level::~Level() {
    reset(); 
}