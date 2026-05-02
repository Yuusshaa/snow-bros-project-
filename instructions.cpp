#include "instructions.h"
#include<iostream>
#include"leaderboard.h"
#include"loginscreen.h"
#include"login.h"
#include<SFML/Graphics.hpp>

using namespace std;

Instructions::Instructions(sf::RenderWindow& window) : window(window)
{

    font.loadFromFile("Silkscreen-Regular.ttf");

	backgroundTexture.loadFromFile("instructionsbackground.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale
	(
		800.f / backgroundTexture.getSize().x,
		600.f / backgroundTexture.getSize().y
	);

	leaderboardbutton.setRadius(100); //change to 100
	leaderboardbutton.setPosition(30, 210);   
	leaderboardbutton.setFillColor(sf::Color::Transparent);
	leaderboardbutton.setOutlineThickness(0.0001);

	startgame.setRadius(100); //changed to 100
	startgame.setPosition(550, 220);          // right circle
	startgame.setFillColor(sf::Color::Transparent);
	startgame.setOutlineThickness(0.0001);
}

bool Instructions::run(Leaderboard& leaderboard, LoginScreen& loginScreen, Login& auth)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

                if (leaderboardbutton.getGlobalBounds().contains(mouse))
                {
                    leaderboard.show();  // opens leaderboard screen
                }
                else if (startgame.getGlobalBounds().contains(mouse))
                {
                    return true;  // goes to login
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(leaderboardbutton);
        window.draw(startgame);
        window.display();
    }
    return false;
}