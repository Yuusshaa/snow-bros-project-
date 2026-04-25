#include "Platform.h"

Platform::Platform(float initialX, float initialY, float initialWidth, float initialHeight) {

    rect = sf::FloatRect(initialX, initialY, initialWidth, initialHeight);

    shape.setSize(sf::Vector2f(initialWidth, initialHeight));

    shape.setPosition(initialX, initialY);

    shape.setFillColor(sf::Color(100, 60, 20));
}

void Platform::Draw(sf::RenderWindow& window, bool showHitbox) {
    window.draw(shape);

    if (showHitbox) {
        sf::RectangleShape hitbox(sf::Vector2f(rect.width, rect.height));

        hitbox.setPosition(rect.left, rect.top);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Blue);
        hitbox.setOutlineThickness(2);

        window.draw(hitbox);
    }
}

sf::FloatRect Platform::getRect() {
    return rect;
}

