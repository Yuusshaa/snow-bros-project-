#include "PowerUp.h"

PowerUp::PowerUp(float x, float y, PowerUpType type) {
    rect = sf::FloatRect(x, y, 15, 15);
    this->type = type;
    active = true;
    velocityY = 0.f;
}

void PowerUp::Update() {
    if (!active) return;

    // Fall down
    velocityY += 0.4f;
    rect.top += velocityY;

    // Stop at ground
    if (rect.top + rect.height >= 560) {
        rect.top = 560 - rect.height;
        velocityY = 0.f;
    }
}

void PowerUp::Draw(sf::RenderWindow& window) {
    if (!active) return;

    // Golden box
    sf::RectangleShape box(sf::Vector2f(rect.width, rect.height));
    box.setPosition(rect.left, rect.top);
    box.setFillColor(sf::Color(255, 215, 0));
    box.setOutlineColor(sf::Color(200, 150, 0));
    box.setOutlineThickness(1);
    window.draw(box);
}
