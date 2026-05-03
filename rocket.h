#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

class Rocket {
public:
    Rocket(float x, float y, float dirX, float dirY, float speed);
    void Update(Platform** platforms, int platformCount);
    void Draw(sf::RenderWindow& window, bool showHitbox);

    sf::FloatRect getRect() { return rect; }
    bool isActive() { return active; }
    bool hasExploded() { return exploding; }
    sf::FloatRect getExplosionRect() { return explosionRect; }
    void deactivate() { active = false; exploding = false; }

private:
    sf::FloatRect rect;
    sf::FloatRect explosionRect;
    float speedX;
    float speedY;
    bool active;
    bool exploding;
    float explosionTimer;

    void explode();
};