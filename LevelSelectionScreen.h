#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;

class LevelSelection
{
private:
    sf::Font font;
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::RectangleShape level1button;
    sf::RectangleShape level2button;
    sf::RectangleShape level3button;
    sf::RectangleShape level4button;
    sf::RectangleShape level5button;
    sf::RectangleShape level6button;
    sf::RectangleShape level7button;
    sf::RectangleShape level8button;
    sf::RectangleShape level9button;
    sf::RectangleShape level10button;

public:
    LevelSelection(sf::RenderWindow& window);
    int run();

};