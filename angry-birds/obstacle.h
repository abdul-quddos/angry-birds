#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "gameobject.h"

class Obstacle : public GameObject {
public:
    Obstacle();
    Obstacle(Vector2 pos, float w, float h);

    void update(float deltaTime) override;
    void draw() const override;
    bool checkCollision(GameObject* other) const override;

    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
};

#endif
