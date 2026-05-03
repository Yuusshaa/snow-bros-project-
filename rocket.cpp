#include "Rocket.h"

Rocket::Rocket(float x, float y, float dirX, float dirY, float speed) {
    rect = sf::FloatRect(x, y, 15, 15);
    speedX = dirX * speed;
    speedY = dirY * speed;
    active = true;
    exploding = false;
    explosionTimer = 0.f;
}

void Rocket::explode() {
    exploding = true;
    active = false;
    explosionTimer = 30.f; // 0.5 seconds
    // Explosion zone is bigger than rocket
    explosionRect = sf::FloatRect(rect.left - 30, rect.top - 30, 75, 75);
}

void Rocket::Update(Platform** platforms, int platformCount) {
    if (exploding) {
        explosionTimer--;
        if (explosionTimer <= 0)
            exploding = false;
        return;
    }

    if (!active) return;

    rect.left += speedX;
    rect.top += speedY;

    // Hit screen edges
    if (rect.left <= 0 || rect.left >= 800 || rect.top <= 0 || rect.top >= 600) {
        explode();
        return;
    }

    // Hit platforms
    for (int i = 0; i < platformCount; i++) {
        sf::FloatRect p = platforms[i]->getRect();
        bool ox = rect.left + rect.width > p.left && rect.left < p.left + p.width;
        bool oy = rect.top + rect.height > p.top && rect.top < p.top + p.height;
        if (ox && oy) {
            explode();
            return;
        }
    }
}

void Rocket::Draw(sf::RenderWindow& window, bool showHitbox) {
    if (exploding) {
        // Draw explosion
        sf::CircleShape explosion(37.f);
        explosion.setPosition(explosionRect.left, explosionRect.top);
        explosion.setFillColor(sf::Color(255, 100, 0, 180));
        window.draw(explosion);

        // Inner bright core
        sf::CircleShape core(20.f);
        core.setPosition(explosionRect.left + 17, explosionRect.top + 17);
        core.setFillColor(sf::Color(255, 255, 0, 200));
        window.draw(core);
        return;
    }

    if (!active) return;

    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
    shape.setPosition(rect.left, rect.top);
    shape.setFillColor(sf::Color(255, 80, 0));
    window.draw(shape);

    if (showHitbox) {
        sf::RectangleShape hitbox(sf::Vector2f(rect.width, rect.height));
        hitbox.setPosition(rect.left, rect.top);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Yellow);
        hitbox.setOutlineThickness(2);
        window.draw(hitbox);
    }
}