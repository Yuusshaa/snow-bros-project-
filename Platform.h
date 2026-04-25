#pragma once
#include <SFML/Graphics.hpp>

class Platform {
public:
    Platform(float initialX, float initialY, float initialWidth, float initialHeight);
    void Draw(sf::RenderWindow& window, bool showHitbox);
    sf::FloatRect getRect();

private:
    sf::FloatRect rect;
    sf::RectangleShape shape;
};

