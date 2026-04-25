#include "Snowball.h"

Snowball::Snowball(float initialX, float initialY, bool goingRight) {
    rect = sf::FloatRect(initialX, initialY, 20, 20);
    speedX = 8.f;
    speedY = 0.f;
    distanceTravelled = 0.f;
    maxDistance = 500.f;
    this->goingRight = goingRight;
    active = true;
}

void Snowball::Update(Platform** platforms, int platformCount) {
    if (!active) 
        return;

    // gravity to the snowball
    speedY += 0.3f;

    // left or right check
    if (goingRight)
        rect.left += speedX;
    else
        rect.left -= speedX;

    rect.top += speedY;

    // Track distance travelled
    distanceTravelled += speedX;

    // Kill if travelled max distance
    if (distanceTravelled >= maxDistance) {
        active = false;
        return;
    }

    // Kill if hits left or right wall
    if ((rect.left <= 0) || (rect.left + rect.width >= 800)) {
        active = false;
        return;
    }

    // Kill if hits a platform
    for (int platformIndex = 0; platformIndex < platformCount; platformIndex++) {
        sf::FloatRect platform = platforms[platformIndex]->getRect();

        bool overlapX = (rect.left + rect.width > platform.left) && (rect.left < platform.left + platform.width);
        bool overlapY = (rect.top + rect.height >= platform.top) && (rect.top < platform.top + platform.height);

        if (overlapX && overlapY) {
            active = false;
            return;
        }
    }
}

void Snowball::Draw(sf::RenderWindow& window, bool showHitbox) {
    if (!active) 
        return;

    sf::CircleShape shape(10);
    shape.setPosition(rect.left, rect.top);
    shape.setFillColor(sf::Color::White);
    window.draw(shape);

    if (showHitbox) {
        sf::RectangleShape hitbox(sf::Vector2f(rect.width, rect.height));
        hitbox.setPosition(rect.left, rect.top);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color(180, 140, 0));
        hitbox.setOutlineThickness(2);
        window.draw(hitbox);
    }
}