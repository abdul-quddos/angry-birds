#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"
#include<fstream>


class GameObject {
protected:
    Vector2 position;
    float width;
    float height;

public:
    GameObject();
    GameObject(Vector2 pos, float w, float h);
    virtual ~GameObject() {}

    virtual void update(float deltaTime) = 0;
    virtual void draw() const = 0;
    virtual bool checkCollision(GameObject* other) const = 0;

    Vector2 getPosition() const;
    float getWidth() const;
    float getHeight() const;

    virtual void save(std::ofstream& out) const = 0;
    virtual void load(std::ifstream& in) = 0;
};

#endif
