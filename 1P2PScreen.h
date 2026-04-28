
#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class PlayerScreen
{
private:
	sf::Font font;
	sf::RenderWindow& window;

	bool onePlayerActive;
	bool TwoPlayersActive;

	sf::RectangleShape onePlayerBox;
	sf::RectangleShape twoPlayersBox;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Text onePlayerLabel;
	sf::Text twoPlayerLabel;

public:
	PlayerScreen(sf::RenderWindow& window);
	bool run();
};
