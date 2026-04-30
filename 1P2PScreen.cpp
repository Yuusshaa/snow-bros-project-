#include "1P2PScreen.h"
#include <iostream>
#include "SFML/Graphics.hpp"
using namespace std;

PlayerScreen::PlayerScreen(sf::RenderWindow& window) : window(window) {
    font.loadFromFile("Silkscreen-Regular.ttf");

    backgroundTexture.loadFromFile("1p2p_bg.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
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
    onePlayerLabel.setPosition(70, 433);
    twoPlayerLabel.setPosition(470, 433);

    onePlayerBox.setSize(sf::Vector2f(330, 60));
    twoPlayersBox.setSize(sf::Vector2f(330, 60));
    onePlayerBox.setPosition(50, 420);
    twoPlayersBox.setPosition(440, 420);
    onePlayerBox.setFillColor(sf::Color::Black);
    twoPlayersBox.setFillColor(sf::Color::Black);
    onePlayerBox.setOutlineThickness(4);
    twoPlayersBox.setOutlineThickness(4);
    onePlayerBox.setOutlineColor(sf::Color::Blue);
    twoPlayersBox.setOutlineColor(sf::Color::Blue);
}

int PlayerScreen::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                if (onePlayerBox.getGlobalBounds().contains(mouse))
                    return 1;
                if (twoPlayersBox.getGlobalBounds().contains(mouse))
                    return 2;
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
    return 0;
}