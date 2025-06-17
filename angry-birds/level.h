#ifndef LEVEL_H
#define LEVEL_H

#include "gameobject.h"
#include "bird.h"
#include "obstacle.h"
#include "target.h"
#include "myvector.h"

class Level {
private:
    Dynamic_array<GameObject*> gameObjects;
    Bird* bird;
    bool isLevelComplete;

public:
    Level();

    void addGameObject(GameObject* obj);
    void setBird(Bird* b);
    void update(float deltaTime);
    void draw();
    void reset();

    bool levelComplete() const;

    void save(std::ofstream& out);
    void load(std::ifstream& in);

};

#endif
