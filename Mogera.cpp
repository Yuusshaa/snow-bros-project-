#include "Mogera.h"
#include <cstdlib>
#include <cmath>

Mogera::Mogera(float x, float y) {
    rect = sf::FloatRect(x, y, 150, 175);
    velocityY = 0.f;
    isGrounded = false;
    jumpTimer = 120.f + rand() % 180;
    health = 30;
    droppingThrough = false;
    dead = false;
    spawntimer = 120.f;
    knifeActive = false;
    knifeTimer = 180.f;
    knifeSpeedX = 0.f;
    knifeSpeedY = 0.f;
}

void Mogera::checkPlatformCollision(sf::FloatRect p) {
    if (droppingThrough) return;

    bool withinX = rect.left + rect.width > p.left && rect.left < p.left + p.width;
    bool fallingOnto = rect.top + rect.height >= p.top &&
        rect.top + rect.height <= p.top + p.height + velocityY;

    if (withinX && fallingOnto && velocityY >= 0) {
        rect.top = p.top - rect.height;
        velocityY = 0.f;
        isGrounded = true;
    }
}

void Mogera::spawnChildren() {
    int count = rand() % 4;
    for (int i = 0; i < count; i++) {
        if (childCount >= 50) break;
        float spawnX = rect.left + (rand() % (int)rect.width);
        MogeraChild* child = new MogeraChild(spawnX, rect.top - 30);
        if (child->velocityX < 0) child->velocityX = -child->velocityX;
        children[childCount++] = child;
    }
}

void Mogera::throwKnife(float playerX, float playerY) {
    float startX = rect.left + rect.width / 2;
    float startY = rect.top + rect.height / 2;

    knifeRect = sf::FloatRect(startX, startY, 15, 8);
    knifeActive = true;

    float dx = playerX - startX;
    float dy = playerY - startY;
    float length = sqrt(dx * dx + dy * dy);
    float speed = 6.f;
    knifeSpeedX = (dx / length) * speed;
    knifeSpeedY = (dy / length) * speed;
}

void Mogera::Update(Platform** platforms, int platformCount, float playerX, float playerY) {
    if (dead) return;

    for (int i = 0; i < childCount; i++) {
        if (!children[i]->isDead())
            children[i]->Update(platforms, platformCount);
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

    // Throw knife every 3-5 seconds
    knifeTimer--;
    if (knifeTimer <= 0) {
        throwKnife(playerX, playerY);
        knifeTimer = 180.f + rand() % 120;
    }

    isGrounded = false;
    velocityY += 0.8f;
    rect.top += velocityY;

    for (int i = 0; i < platformCount; i++)
        checkPlatformCollision(platforms[i]->getRect());

    if (rect.top + rect.height >= 560) {
        rect.top = 560 - rect.height;
        velocityY = 0.f;
        isGrounded = true;
        droppingThrough = false;
    }

    spawntimer--;
    if (spawntimer <= 0) {
        spawnChildren();
        spawntimer = 120.f;
    }

    if (isGrounded) {
        jumpTimer--;
        if (jumpTimer <= 0) {
            if (rand() % 10 < 4) {
                droppingThrough = true;
                velocityY = 3.f;
            }
            else {
                velocityY = -20.f;
            }
            isGrounded = false;
            jumpTimer = 120.f + rand() % 180;
        }
    }

    if (health <= 0) dead = true;
}

void Mogera::Draw(sf::RenderWindow& window, bool showHitbox) {
    if (dead) return;

    for (int i = 0; i < childCount; i++) {
        if (!children[i]->isDead())
            children[i]->Draw(window, showHitbox);
    }

    // Draw knife
    if (knifeActive) {
        sf::RectangleShape knife(sf::Vector2f(knifeRect.width, knifeRect.height));
        knife.setPosition(knifeRect.left, knifeRect.top);
        knife.setFillColor(sf::Color(150, 150, 150));
        window.draw(knife);
    }

    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
    shape.setPosition(rect.left, rect.top);
    shape.setFillColor(sf::Color(0, 100, 0));
    window.draw(shape);

    sf::RectangleShape healthBg(sf::Vector2f(150, 20));
    healthBg.setPosition(rect.left, rect.top - 25);
    healthBg.setFillColor(sf::Color::Red);
    window.draw(healthBg);

    sf::RectangleShape healthBar(sf::Vector2f(150.f * (health / 30.f), 20));
    healthBar.setPosition(rect.left, rect.top - 25);
    healthBar.setFillColor(sf::Color::Green);
    window.draw(healthBar);

    if (showHitbox) {
        sf::RectangleShape hitbox(sf::Vector2f(rect.width, rect.height));
        hitbox.setPosition(rect.left, rect.top);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(2);
        window.draw(hitbox);
    }
}