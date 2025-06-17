#include "obstacle.h"
#include "raylib.h"



Obstacle::Obstacle(): GameObject() {}
Obstacle::Obstacle(Vector2 pos, float w, float h)
    : GameObject(pos, w, h) {}

void Obstacle::update(float deltaTime) {
    
}

void Obstacle::draw() const {
    DrawRectangle(position.x, position.y, width, height, GRAY);
}



float Square(float x) {
    return x * x;
}

float Min(float a, float b) {
    return (a < b) ? a : b;
}

float Max(float a, float b) {
    return (a > b) ? a : b;
}

bool Obstacle::checkCollision(GameObject* other) const {
    Vector2 otherPos = other->getPosition();
    float otherR = other->getWidth() / 2;

    float closestX = Max(position.x, Min(otherPos.x, position.x + width));
    float closestY = Max(position.y, Min(otherPos.y, position.y + height));

    float dx = otherPos.x - closestX;
    float dy = otherPos.y - closestY;

    float distSquared = Square(dx) + Square(dy);
    float radiusSquared = Square(otherR);

    return distSquared < radiusSquared;
}

void Obstacle::save(std::ofstream& out) const {
   
    out.write((char*)&position.x, sizeof(float));
    out.write((char*)&position.y, sizeof(float));
    out.write((char*)&width, sizeof(float));
    out.write((char*)&height, sizeof(float));

}

void Obstacle::load(std::ifstream& in) {
    
    in.read((char*)&position.x, sizeof(float));
    in.read((char*)&position.y, sizeof(float));
    in.read((char*)&width, sizeof(float));
    in.read((char*)&height, sizeof(float));
}
