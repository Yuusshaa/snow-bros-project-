#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class PlayerScreen {
public:
    PlayerScreen(sf::RenderWindow& window);
    int run(); // returns 1 or 2 players

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text onePlayerLabel;
    sf::Text twoPlayerLabel;
    sf::RectangleShape onePlayerBox;
    sf::RectangleShape twoPlayersBox;
};