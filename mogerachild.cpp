#include "MogeraChild.h"

MogeraChild::MogeraChild(float x, float y) {
    rect = sf::FloatRect(x, y, 30, 30);
    dead = false;
    waiting = true;
    waitTimer = 90.f; // 1.5 seconds
    velocityX = (float)(rand() % 15 + 2); // always negative = always goes left
    velocityY = -(float)(rand() % 13 + 10);
}

void MogeraChild::checkPlatformCollision(sf::FloatRect p) {
    bool withinX = rect.left + rect.width > p.left && rect.left < p.left + p.width;
    bool fallingOnto = rect.top + rect.height >= p.top &&
        rect.top + rect.height <= p.top + p.height + velocityY;

    if (withinX && fallingOnto && velocityY >= 0) {
        rect.top = p.top - rect.height;
        velocityY = 0.f;
    }
}

void MogeraChild::Update(Platform** platforms, int platformCount) {
    if (dead) return;

    velocityY += 1.0f;
    rect.top += velocityY;
    rect.left += velocityX;  // move this OUTSIDE the waiting check

    for (int i = 0; i < platformCount; i++)
        checkPlatformCollision(platforms[i]->getRect());

    // Wait after landing
    if (waiting && velocityY == 0.f) {
        waitTimer--;
        if (waitTimer <= 0) {
            waiting = false;
            velocityX = (float)(rand() % 25 + 15);
        }
    }

    if (rect.left + rect.width >= 800) {
        dead = true;
        return;
    }

    if (rect.top >= 600)
        dead = true;
}


void MogeraChild::Draw(sf::RenderWindow& window, bool showHitbox) {
    if (dead) return;

    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
    shape.setPosition(rect.left, rect.top);
    shape.setFillColor(sf::Color(255, 165, 0));
    window.draw(shape);

    if (showHitbox) {
        sf::RectangleShape hitbox(sf::Vector2f(rect.width, rect.height));
        hitbox.setPosition(rect.left, rect.top);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(2);
        window.draw(hitbox);
    }
}