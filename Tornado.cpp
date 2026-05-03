#include "Tornado.h"
#include <cmath>
#include <cstdlib>

sf::Texture Tornado::tTexture;

bool Tornado::loadTexture() {
    return tTexture.loadFromFile("Tornado_Blue.png");
}

Tornado::Tornado(float initialX, float initialY) : FlyingFoogaFoog(initialX, initialY) {
    knifeTimer = 180.f;
    teleportTimer = 120.f + rand() % 120;
    knifeActive = false;
    knifeSpeedX = 0.f;
    knifeSpeedY = 0.f;

    // Setup sprite
    tSprite.setTexture(tTexture);
    tSprite.setTextureRect(sf::IntRect(0, 36, 129, 124));
    tSprite.setScale(rect.width / 129.f, rect.height / 124.f);

    // Override inherited animations with Player_Blue snowball animations
    fullAnim = Animation(Botom::snowballtexture, 5, 968, 81, 84, 1, 0.f);
    halfAnim = Animation(Botom::snowballtexture, 91, 900, 68, 60, 1, 0.f);
    rollAnim = Animation(Botom::snowballtexture, 5, 968, 81, 84, 3, 10.f);
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
    if (dead) return;

    updateDefrost();

    // Rolling handled first
    if (rolling) {
        rect.left += (rollingRight ? 6.f : -6.f);
        velocityY += 0.6f;
        rect.top += velocityY;

        if (rect.left <= 0) rect.left = 0, rollingRight = true;
        if (rect.left + rect.width >= 800) rect.left = 800 - rect.width, rollingRight = false;

        if (rect.top + rect.height >= 560) {
            dead = true;
            return;
        }

        for (int i = 0; i < platformCount; i++)
            checkPlatformCollision(platforms[i]->getRect());
        return;
    }

    // Encased — just gravity no teleport
    if (isEncased()) {
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
        if (knifeRect.left <= 0 || knifeRect.left >= 800 ||
            knifeRect.top <= 0 || knifeRect.top >= 600) {
            knifeActive = false;
        }
    }

    // Throw knife
    knifeTimer--;
    if (knifeTimer <= 0) {
        throwKnife(playerX, playerY);
        knifeTimer = 180.f + rand() % 120;
    }

    // Teleport — sets position directly, skip gravity this frame
    teleportTimer--;
    if (teleportTimer <= 0) {
        rect.left = 50.f + rand() % 700;
        rect.top = 50.f + rand() % 400;
        velocityY = 0.f; // reset velocity so it doesnt shoot down after teleport
        teleportTimer = 120.f + rand() % 120;
        return; // skip gravity this frame
    }

    // Normal gravity when not teleporting
    isGrounded = false;
    velocityY += 0.6f;
    rect.top += velocityY;

    for (int i = 0; i < platformCount; i++)
        checkPlatformCollision(platforms[i]->getRect());

    // Screen bounds
    if (rect.left < 0) rect.left = 0;
    if (rect.left + rect.width > 800) rect.left = 800 - rect.width;
    if (rect.top + rect.height >= 560) {
        rect.top = 560 - rect.height;
        velocityY = 0.f;
        isGrounded = true;
    }
}

void Tornado::Draw(sf::RenderWindow& window, bool showHitbox) {
    if (dead) 
        return;

    // Draw knife
    if (knifeActive) {
        sf::RectangleShape knife(sf::Vector2f(knifeRect.width, knifeRect.height));
        knife.setPosition(knifeRect.left, knifeRect.top);
        knife.setFillColor(sf::Color(150, 150, 150));
        window.draw(knife);
    }

    tSprite.setPosition(rect.left, rect.top);
    window.draw(tSprite);

    if (showHitbox) {
        sf::RectangleShape hitbox(sf::Vector2f(rect.width, rect.height));
        hitbox.setPosition(rect.left, rect.top);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(2);
        window.draw(hitbox);
    }
}