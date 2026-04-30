#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

class Gem {
public:
    Gem(float x, float y, int value);
    void Update(Platform** platforms, int platformCount);
    void Draw(sf::RenderWindow& window);
    sf::FloatRect getRect() const { return rect; }
    bool isActive() const { return active; }
    int getValue() const { return value; }
    void collect() { active = false; }

    void setVelocity(float vx, float vy) { velocityX = vx; velocityY = vy; }

private:
    sf::FloatRect rect;
    float velocityX;
    float velocityY;
    bool active;
    int value;
    float spawnTimer;
};
