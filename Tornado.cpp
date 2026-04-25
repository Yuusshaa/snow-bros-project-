#include "Tornado.h"
#include <cmath>
#include <cstdlib>

Tornado::Tornado(float initialX, float initialY) : FlyingFoogaFoog(initialX, initialY) {
    knifeTimer = 180.f;
    teleportTimer = 120.f + rand() % 120;
    knifeActive = false;
    knifeSpeedX = 0.f;
    knifeSpeedY = 0.f;

}

void Tornado::throwKnife(float playerX, float playerY) {
    knifeRect = sf::FloatRect(rect.left, rect.top, 15, 8);
    knifeActive = true;

    float dx = playerX - rect.left;
    float dy = playerY - rect.top;
    float length = sqrt(dx * dx + dy * dy);
    float speed = 5.f;
    knifeSpeedX = (dx / length) * speed;
    knifeSpeedY = (dy / length) * speed;
}

void Tornado::Update(Platform** platforms, int platformCount, float playerX, float playerY) {
    if (dead) 
        return;
    updateDefrost();

    if (isHalfFrozen()) {  // ADD THIS
        velocityY += 0.6f;
        rect.top += velocityY;
        for (int i = 0; i < platformCount; i++)
            checkPlatformCollision(platforms[i]->getRect());
        return;
    }
    // Update knife
    if (knifeActive) {
        knifeRect.left += knifeSpeedX;
        knifeRect.top += knifeSpeedY;

        if ((knifeRect.left <= 0) || (knifeRect.left >= 800) || 
            (knifeRect.top <= 0) || (knifeRect.top >= 600)) {
            knifeActive = false;
        }
    }


    // Throw knife every 3-5 seconds
    knifeTimer--;
    if (knifeTimer <= 0) {
        throwKnife(playerX, playerY);
        knifeTimer = 180.f + rand() % 120;
    }

    // Teleport to random position on screen every 2-4 seconds
    if ((!isEncased()) && (!rolling)) {
        teleportTimer--;
        if (teleportTimer <= 0) {
            rect.left = 50.f + rand() % 700;
            rect.top = 50.f + rand() % 400;
            teleportTimer = 120.f + rand() % 120;
        }
    }

    // Still use gravity and platform collision when on ground
    velocityY += 0.6f;
    rect.top += velocityY;

    for (int platformIndex = 0; platformIndex < platformCount; platformIndex++)
        checkPlatformCollision(platforms[platformIndex]->getRect());
}

void Tornado::Draw(sf::RenderWindow& window, bool showHitbox) {
    if (dead) 
        return;

    float drawX = rect.left;
    if (isEncased() && defrostTimer < 60.f && (int)defrostTimer % 6 < 3)
        drawX += 3.f;


    // Draw knife
    if (knifeActive) {
        sf::RectangleShape knife(sf::Vector2f(knifeRect.width, knifeRect.height));
        knife.setPosition(knifeRect.left, knifeRect.top);
        knife.setFillColor(sf::Color(150, 150, 150));
        window.draw(knife);
    }

    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
    shape.setPosition(rect.left, rect.top);

    if (rolling)
        shape.setFillColor(sf::Color(200, 200, 255));
    else if (isEncased())
        shape.setFillColor(sf::Color::White);
    else
        shape.setFillColor(sf::Color(128, 0, 128)); // purple

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