#include "bird.h"
#include "raymath.h"
#include<iostream>
using namespace std;
Bird::Bird(): GameObject()
{
    isFlying = false;
    velocity = { 0, 0 };
}

Bird::Bird(Vector2 pos, float w, float h)
    : GameObject(pos, w, h), velocity({ 0, 0 }), isFlying(false) {}

void Bird::shoot(Vector2 direction) {
    velocity = direction;
    isFlying = true;
}

void Bird::reset(Vector2 pos) {
    position = pos;
    velocity = { 0, 0 };
    isFlying = false;
}

bool Bird::hasStopped() const {
    return !isFlying;
}

void Bird::update(float deltaTime) {
    if (isFlying) {
        velocity.y += 9.8f * deltaTime; 
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;

        if (position.y > 700) { 
            isFlying = false;
        }
    }
}

void Bird::draw() const 
{
    DrawCircleV(position, width / 2, RED);
}

bool Bird::checkCollision(GameObject* other) const {
    float dx = position.x - other->getPosition().x;
    float dy = position.y - other->getPosition().y;
    float distance = sqrt(dx * dx + dy * dy);
    return distance < (width / 2 + other->getWidth() / 2);
}

bool Bird::isInFlight() const {
    return isFlying;
}

void Bird::save(std::ofstream& out) const {
    
    out.write((char*)&position.x, sizeof(float));
    out.write((char*)&position.y, sizeof(float));
    out.write((char*)&width, sizeof(float));
    out.write((char*)&height, sizeof(float));

   
    out.write((char*)&velocity.x, sizeof(float));
    out.write((char*)&velocity.y, sizeof(float));
    out.write((char*)&isFlying, sizeof(bool));
}

void Bird::load(std::ifstream& in) {

    in.read((char*)&position.x, sizeof(float));
    in.read((char*)&position.y, sizeof(float));
    in.read((char*)&width, sizeof(float));
    in.read((char*)&height, sizeof(float));

    in.read((char*)&velocity.x, sizeof(float));
    in.read((char*)&velocity.y, sizeof(float));
    in.read((char*)&isFlying, sizeof(bool));
}