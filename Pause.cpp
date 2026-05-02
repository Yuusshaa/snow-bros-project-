#include"Pause.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include<string>
using namespace std;

PauseMenu::PauseMenu(sf::RenderWindow& window) : window(window)
{
    font.loadFromFile("Silkscreen-Regular.ttf");

    // title
    titleLabel.setFont(font);
    titleLabel.setString("PAUSED");
    titleLabel.setCharacterSize(50);
    titleLabel.setFillColor(sf::Color::Yellow);
    titleLabel.setPosition(310, 100);

    // resume button
    resumeButton.setSize(sf::Vector2f(300, 60));
    resumeButton.setPosition(250, 220);
    resumeButton.setFillColor(sf::Color(48, 25, 52));
    resumeButton.setOutlineThickness(2);
    resumeButton.setOutlineColor(sf::Color::White);

    resumeLabel.setFont(font);
    resumeLabel.setString("RESUME");
    resumeLabel.setCharacterSize(28);
    resumeLabel.setFillColor(sf::Color::White);
    resumeLabel.setPosition(320, 232);

    // store button
    storeButton.setSize(sf::Vector2f(300, 60));
    storeButton.setPosition(250, 320);
    storeButton.setFillColor(sf::Color(48, 25, 52));
    storeButton.setOutlineThickness(2);
    storeButton.setOutlineColor(sf::Color::White);

    storeLabel.setFont(font);
    storeLabel.setString("STORE");
    storeLabel.setCharacterSize(28);
    storeLabel.setFillColor(sf::Color::White);
    storeLabel.setPosition(330, 332);

    // exit button
    exitButton.setSize(sf::Vector2f(300, 60));
    exitButton.setPosition(250, 420);
    exitButton.setFillColor(sf::Color(100, 10, 10));
    exitButton.setOutlineThickness(2);
    exitButton.setOutlineColor(sf::Color::White);

    exitLabel.setFont(font);
    exitLabel.setString("EXIT GAME");
    exitLabel.setCharacterSize(28);
    exitLabel.setFillColor(sf::Color::White);
    exitLabel.setPosition(295, 432);
}

int PauseMenu::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 3;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

                if (resumeButton.getGlobalBounds().contains(mouse))
                    return 1;  // resume

                else if (storeButton.getGlobalBounds().contains(mouse))
                    return 2;  // go to store

                else if (exitButton.getGlobalBounds().contains(mouse))
                    return 3;  // exit
            }
        }

        window.clear(sf::Color(0, 0, 0));
        window.draw(titleLabel);
        window.draw(resumeButton);
        window.draw(resumeLabel);
        window.draw(storeButton);
        window.draw(storeLabel);
        window.draw(exitButton);
        window.draw(exitLabel);
        window.display();
    }
    return 3;
}