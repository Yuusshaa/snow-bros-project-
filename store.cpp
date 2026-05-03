#include "store.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Smash.h"
using namespace std;

Store::Store(sf::RenderWindow& window) : window(window)
{
    font.loadFromFile("Silkscreen-Regular.ttf");

    backgroundTexture.loadFromFile("storebackground.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale
    (
        800.f / backgroundTexture.getSize().x,
        600.f / backgroundTexture.getSize().y
    );

    usainboltmode.setSize(sf::Vector2f(145, 135));
    usainboltmode.setPosition(50, 135);

    abominablesnowball.setSize(sf::Vector2f(145, 135));
    abominablesnowball.setPosition(450, 130);

    powersnow.setSize(sf::Vector2f(200, 55));
    powersnow.setPosition(150, 320);

    balloonmode.setSize(sf::Vector2f(145, 135));
    balloonmode.setPosition(50, 420);

    nayizindagi.setSize(sf::Vector2f(145, 135));
    nayizindagi.setPosition(455, 420);



    usainboltmode.setFillColor(sf::Color::Transparent);
    abominablesnowball.setFillColor(sf::Color::Transparent);
    powersnow.setFillColor(sf::Color::Transparent);
    balloonmode.setFillColor(sf::Color::Transparent);
    nayizindagi.setFillColor(sf::Color::Transparent);




    backButton.setSize(sf::Vector2f(150, 45));
    backButton.setPosition(30, 45);
    backButton.setFillColor(sf::Color::Transparent);
    backButton.setOutlineThickness(2);
    backButton.setOutlineColor(sf::Color::Transparent);

}

void Store::run(Smash& player)
{
    sf::Text statusText;
    statusText.setFont(font);
    statusText.setCharacterSize(18);
    statusText.setFillColor(sf::Color::Green);
    statusText.setPosition(250, 560);

    string statusMessage = "";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // press Escape to leave shop
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                return;

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

                if (backButton.getGlobalBounds().contains(mouse))
                    return;  // goes back to pause menu


                // Usain Bolt Mode — Speed Boost 30s — 20 gems
                if (usainboltmode.getGlobalBounds().contains(mouse))
                {
                    if (player.getGems() >= 20)
                    {
                        player.spendGems(20);
                        player.activateSpeedBoost(30);
                        statusMessage = "Speed boost activated!";
                    }
                    else
                        statusMessage = "Not enough gems!";
                }

                // Abominable Snowball — Distance Increase — 25 gems
                else if (abominablesnowball.getGlobalBounds().contains(mouse))
                {
                    if (player.getGems() >= 25)
                    {
                        player.spendGems(25);
                        player.activateDistanceBoost();
                        statusMessage = "Max range snowball!";
                    }
                    else
                        statusMessage = "Not enough gems!";
                }

                // Power Snow — One hit encasing — 30 gems
                else if (powersnow.getGlobalBounds().contains(mouse))
                {
                    if (player.getGems() >= 30)
                    {
                        player.spendGems(30);
                        player.activatePowerSnow();
                        statusMessage = "One-hit encasing active!";
                    }
                    else
                        statusMessage = "Not enough gems!";
                }

                // Allah Ke Paas — Balloon Mode 30s — 35 gems
                else if (balloonmode.getGlobalBounds().contains(mouse))
                {
                    if (player.getGems() >= 35)
                    {
                        player.spendGems(35);
                        player.activateBalloonMode(30);
                        statusMessage = "Balloon mode activated!";
                    }
                    else
                        statusMessage = "Not enough gems!";
                }

                // Nayi Zindagi — Extra Life — 50 gems
                else if (nayizindagi.getGlobalBounds().contains(mouse))
                {
                    if (player.getGems() >= 50)
                    {
                        player.spendGems(50);
                        player.addLife();
                        statusMessage = "+1 life added!";
                    }
                    else
                        statusMessage = "Not enough gems!";
                }
            }
        }

        statusText.setString(statusMessage);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(usainboltmode);
        window.draw(abominablesnowball);
        window.draw(powersnow);
        window.draw(balloonmode);
        window.draw(nayizindagi);
        window.draw(statusText);
        window.draw(backButton);
        window.display();
    }
}