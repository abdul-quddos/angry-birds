#ifndef BIRD_H
#define BIRD_H

#include "gameobject.h"

class Bird : public GameObject {
private:
    Vector2 velocity;
    bool isFlying;

public:
    Bird();
    Bird(Vector2 pos, float w, float h);

    void shoot(Vector2 direction);
    void reset(Vector2 pos);
    bool hasStopped() const;

    void update(float deltaTime) override;
    void draw() const override;
    bool checkCollision(GameObject* other) const override;

    bool isInFlight() const;

    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
};

#endif
