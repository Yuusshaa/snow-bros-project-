#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

class Snowball {
public:
    Snowball(float initialX, float initialY, bool goingRight);
    void Update(Platform** platforms, int platformCount);
    void Draw(sf::RenderWindow& window, bool showHitbox);
    sf::FloatRect getRect() { return rect; }
    bool isActive() { return active; }
    void deactivate() { active = false; }

private:
    sf::FloatRect rect;
    float speedX;
    float speedY;
    float distanceTravelled;
    float maxDistance;
    bool goingRight;
    bool active;
};