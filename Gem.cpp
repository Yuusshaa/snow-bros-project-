#include "Gem.h"
#include <cstdlib>

Gem::Gem(float x, float y, int value)
    : value(value), active(true), velocityY(-8.f), velocityX(0.f), spawnTimer(30.f) {
    rect = sf::FloatRect(x, y, 15, 15);
}

void Gem::Update(Platform** platforms, int platformCount) {
    if (!active) return;

    // Apply gravity
    velocityY += 0.6f;
    rect.left += velocityX;
    rect.top += velocityY;

    // Bounce off screen edges (don't leave screen)
    if (rect.left <= 0) {
        rect.left = 0;
        velocityX = -velocityX * 0.8f; // Bounce with slight damping
    }
    if (rect.left + rect.width >= 800) {
        rect.left = 800 - rect.width;
        velocityX = -velocityX * 0.8f;
    }
    if (rect.top <= 0) {
        rect.top = 0;
        velocityY = -velocityY * 0.8f;
    }

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

    // Fall off bottom of screen (remove gem)
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
