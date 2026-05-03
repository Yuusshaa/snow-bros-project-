#pragma once
#include <SFML/Graphics.hpp>

enum PowerUpType { SPEED_BOOST, SNOWBALL_POWER, DISTANCE_INCREASE, BALLOON_MODE };

class PowerUp {
public:
    PowerUp(float x, float y, PowerUpType type);
    void Update();
    void Draw(sf::RenderWindow& window);
    sf::FloatRect getRect() { return rect; }
    bool isActive() { return active; }
    void collect() { active = false; }
    PowerUpType getType() { return type; }

private:
    sf::FloatRect rect;
    PowerUpType type;
    bool active;
    float velocityY;
};
