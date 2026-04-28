#include"1P2PScreen.h"
#include<iostream>
#include"SFML/Graphics.hpp"
using namespace std;

PlayerScreen::PlayerScreen(sf::RenderWindow& window) : window(window)
{
	font.loadFromFile("Silkscreen-Regular.ttf");
	onePlayerActive = true;


	backgroundTexture.loadFromFile("1p2p_bg.png");
	backgroundSprite.setTexture(backgroundTexture);

	backgroundSprite.setScale
	(
		800.f / backgroundTexture.getSize().x,
		600.f / backgroundTexture.getSize().y
	);

	onePlayerLabel.setFont(font);
	twoPlayerLabel.setFont(font);

	onePlayerLabel.setString("1 Player Mode");
	twoPlayerLabel.setString("2 Player Mode");

	onePlayerLabel.setCharacterSize(30);
	twoPlayerLabel.setCharacterSize(30);

	onePlayerLabel.setFillColor(sf::Color::White);
	twoPlayerLabel.setFillColor(sf::Color::White);


	//move everything 10 to the left
	onePlayerLabel.setPosition(70, 433); //-10 in x axis of both
	twoPlayerLabel.setPosition(470, 433);

	onePlayerBox.setSize(sf::Vector2f(330, 60)); //added 30 to the x axis of both +10
	twoPlayersBox.setSize(sf::Vector2f(330, 60));

	onePlayerBox.setPosition(50, 420); //-10 in x axis of both
	twoPlayersBox.setPosition(440, 420);

	onePlayerBox.setFillColor(sf::Color::Black);
	twoPlayersBox.setFillColor(sf::Color::Black);

	onePlayerBox.setOutlineThickness(4);
	twoPlayersBox.setOutlineThickness(4);

	onePlayerBox.setOutlineColor(sf::Color::Blue);
	twoPlayersBox.setOutlineColor(sf::Color::Blue);


}

bool PlayerScreen::run()
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
				if (onePlayerBox.getGlobalBounds().contains(mouse))
				{
					return true;  // 1 player mode selected
				}
				else if (twoPlayersBox.getGlobalBounds().contains(mouse))
				{
					return true;  // 2 player mode selected 
					//THIS IS ONLY TEMPORARY - CHANGE WHEN 2 PLAYER MODE IS ADDED
				}
			}
		}
		window.clear();
		window.draw(backgroundSprite);
		window.draw(onePlayerBox);
		window.draw(twoPlayersBox);
		window.draw(onePlayerLabel);
		window.draw(twoPlayerLabel);
		window.display();
	}
}