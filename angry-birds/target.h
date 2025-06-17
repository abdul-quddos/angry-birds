#ifndef TARGET_H
#define TARGET_H

#include "gameobject.h"

class Target : public GameObject {
private:
    bool isHit;

public:
    Target();
    Target(Vector2 pos, float w, float h);

    void markAsHit();
    bool getIsHit() const;

    void update(float deltaTime) override;
    void draw() const override;
    bool checkCollision(GameObject* other) const override;

    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
};

#endif
