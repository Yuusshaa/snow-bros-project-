#include "Gem.h"

Gem::Gem(float x, float y, int value)
    : value(value), active(true), velocityY(-8.f), spawnTimer(30.f) {
    rect = sf::FloatRect(x, y, 15, 15);
}

void Gem::Update(Platform** platforms, int platformCount) {
    if (!active) return;

    // Spawn animation - float up slightly
    if (spawnTimer > 0) {
        spawnTimer--;
        rect.top -= 1.5f;
        velocityY = -8.f;
    }

    velocityY += 0.6f;
    rect.top += velocityY;

    // Platform collision
    for (int i = 0; i < platformCount; i++) {
        sf::FloatRect pRect = platforms[i]->getRect();
        bool withinX = rect.left + rect.width > pRect.left && rect.left < pRect.left + pRect.width;
        bool fallingOnto = rect.top + rect.height >= pRect.top &&
            rect.top + rect.height <= pRect.top + pRect.height + velocityY;
        if (withinX && fallingOnto && velocityY >= 0) {
            rect.top = pRect.top - rect.height;
            velocityY = 0.f;
        }
    }

    // Fall off screen
    if (rect.top > 600) {
        active = false;
    }
}

void Gem::Draw(sf::RenderWindow& window) {
    if (!active) return;

    sf::RectangleShape gem(sf::Vector2f(rect.width, rect.height));
    gem.setPosition(rect.left, rect.top);

    // Bright cyan color
    gem.setFillColor(sf::Color::Cyan);

    window.draw(gem);
}
