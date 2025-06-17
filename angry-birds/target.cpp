#include "target.h"
#include "raylib.h"

Target::Target() :GameObject()
{
    isHit = false;
}

Target::Target(Vector2 pos, float w, float h)
    : GameObject(pos, w, h), isHit(false) {}

void Target::markAsHit() {
    isHit = true;
}

bool Target::getIsHit() const {
    return isHit;
}

void Target::update(float deltaTime) {
    
}

void Target::draw() const {
    if (!isHit) {
        DrawRectangle(position.x, position.y, width, height, GREEN);
    }
    else {
        DrawRectangle(position.x, position.y, width, height, DARKGREEN);
    }
}

float square(float x) {
    return x * x;
}

float min(float a, float b) {
    if (a < b) return a;
    return b;
}

float max(float a, float b) {
    if (a > b) return a;
    return b;
}

bool Target::checkCollision(GameObject* other) const {
    Vector2 otherPos = other->getPosition();
    float otherR = other->getWidth() / 2;

    float closestX = max(position.x, min(otherPos.x, position.x + width));
    float closestY = max(position.y, min(otherPos.y, position.y + height));

    float dx = otherPos.x - closestX;
    float dy = otherPos.y - closestY;

    float distSquared = square(dx) + square(dy);
    float radiusSquared = square(otherR);

    return distSquared < radiusSquared;
}

void Target::save(std::ofstream& out) const {
  
    out.write((char*)&position.x, sizeof(float));
    out.write((char*)&position.y, sizeof(float));
    out.write((char*)&width, sizeof(float));
    out.write((char*)&height, sizeof(float));

 
    out.write((char*)&isHit, sizeof(bool));
}

void Target::load(std::ifstream& in) {
 
    in.read((char*)&position.x, sizeof(float));
    in.read((char*)&position.y, sizeof(float));
    in.read((char*)&width, sizeof(float));
    in.read((char*)&height, sizeof(float));

    in.read((char*)&isHit, sizeof(bool));
}