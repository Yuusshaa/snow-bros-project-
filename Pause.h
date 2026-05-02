#pragma once
#include"store.h"
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;


class PauseMenu
{
private:
    sf::Font font;
    sf::RenderWindow& window;

    sf::RectangleShape resumeButton;
    sf::RectangleShape storeButton;
    sf::RectangleShape exitButton;

    sf::Text resumeLabel;
    sf::Text storeLabel;
    sf::Text exitLabel;
    sf::Text titleLabel;

public:
    PauseMenu(sf::RenderWindow& window);
    int run();  // returns 1 = resume, 2 = store, 3 = exit
};