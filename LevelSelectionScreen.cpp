#include "LevelSelectionScreen.h"
#include<SFML/Graphics.hpp>
#include <iostream>
using namespace std;

LevelSelection::LevelSelection(sf::RenderWindow& window) : window(window)
{
    font.loadFromFile("Silkscreen-Regular.ttf");

    backgroundTexture.loadFromFile("levelsbackground.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale
    (
        800.f / backgroundTexture.getSize().x,
        600.f / backgroundTexture.getSize().y
    );

    // row 1 — levels 1 to 5
    level1button.setSize(sf::Vector2f(110, 110));
    level1button.setPosition(10, 210);

    level2button.setSize(sf::Vector2f(110, 110));
    level2button.setPosition(180, 210);

    level3button.setSize(sf::Vector2f(110, 110));
    level3button.setPosition(350, 210);

    level4button.setSize(sf::Vector2f(110, 110));
    level4button.setPosition(510, 210);

    level5button.setSize(sf::Vector2f(110, 110));
    level5button.setPosition(665, 210);

    // row 2 — levels 6 to 10
    level6button.setSize(sf::Vector2f(110, 110));
    level6button.setPosition(10, 370);

    level7button.setSize(sf::Vector2f(110, 110));
    level7button.setPosition(180, 370);

    level8button.setSize(sf::Vector2f(110, 110));
    level8button.setPosition(350, 370);

    level9button.setSize(sf::Vector2f(110, 110));
    level9button.setPosition(510, 370);

    level10button.setSize(sf::Vector2f(110, 110));
    level10button.setPosition(665, 370);

    // all transparent so background numbers show through
    level1button.setFillColor(sf::Color::Transparent);
    level2button.setFillColor(sf::Color::Transparent);
    level3button.setFillColor(sf::Color::Transparent);
    level4button.setFillColor(sf::Color::Transparent);
    level5button.setFillColor(sf::Color::Transparent);
    level6button.setFillColor(sf::Color::Transparent);
    level7button.setFillColor(sf::Color::Transparent);
    level8button.setFillColor(sf::Color::Transparent);
    level9button.setFillColor(sf::Color::Transparent);
    level10button.setFillColor(sf::Color::Transparent);

    // yellow outlines so you can see them while testing — remove after
    level1button.setOutlineThickness(2);  level1button.setOutlineColor(sf::Color::Yellow);
    level2button.setOutlineThickness(2);  level2button.setOutlineColor(sf::Color::Yellow);
    level3button.setOutlineThickness(2);  level3button.setOutlineColor(sf::Color::Yellow);
    level4button.setOutlineThickness(2);  level4button.setOutlineColor(sf::Color::Yellow);
    level5button.setOutlineThickness(2);  level5button.setOutlineColor(sf::Color::Yellow);
    level6button.setOutlineThickness(2);  level6button.setOutlineColor(sf::Color::Yellow);
    level7button.setOutlineThickness(2);  level7button.setOutlineColor(sf::Color::Yellow);
    level8button.setOutlineThickness(2);  level8button.setOutlineColor(sf::Color::Yellow);
    level9button.setOutlineThickness(2);  level9button.setOutlineColor(sf::Color::Yellow);
    level10button.setOutlineThickness(2); level10button.setOutlineColor(sf::Color::Yellow);
}

int LevelSelection::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

                if (level1button.getGlobalBounds().contains(mouse))  return 1;
                if (level2button.getGlobalBounds().contains(mouse))  return 2;
                if (level3button.getGlobalBounds().contains(mouse))  return 3;
                if (level4button.getGlobalBounds().contains(mouse))  return 4;
                if (level5button.getGlobalBounds().contains(mouse))  return 5;
                if (level6button.getGlobalBounds().contains(mouse))  return 6;
                if (level7button.getGlobalBounds().contains(mouse))  return 7;
                if (level8button.getGlobalBounds().contains(mouse))  return 8;
                if (level9button.getGlobalBounds().contains(mouse))  return 9;
                if (level10button.getGlobalBounds().contains(mouse)) return 10;
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(level1button);
        window.draw(level2button);
        window.draw(level3button);
        window.draw(level4button);
        window.draw(level5button);
        window.draw(level6button);
        window.draw(level7button);
        window.draw(level8button);
        window.draw(level9button);
        window.draw(level10button);
        window.display();
    }
    return 0;
}