#pragma once
#include <SFML/Graphics.hpp>

class Background
{
private:
    sf::Texture frames[43];
    int totalFrames;
    sf::Sprite sprite;
    int currentFrame;
    float timer;
    float frameSpeed;  // seconds per frame

public:
    Background();
    void loadLevel(int level);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
};