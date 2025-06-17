#include "gameobject.h"

GameObject::GameObject()
{
    position = { 0, 0 };
    width = 10;
    height = 10;
}

GameObject::GameObject(Vector2 pos, float w, float h)
    : position(pos), width(w), height(h) {}

Vector2 GameObject::getPosition() const {
    return position;
}

float GameObject::getWidth() const {
    return width;
}

float GameObject::getHeight() const {
    return height;
}
