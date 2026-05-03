#include "Gamakichi.h"
#include <cstdlib>
#include <cmath>

sf::Texture Gamakichi::gTexture;

bool Gamakichi::loadTexture() {
    return gTexture.loadFromFile("gamakichi.png");
}

Gamakichi::Gamakichi() {
    rect = sf::FloatRect(204, 435, 392, 105);
    health = 80;
    maxHealth = 80;
    phase = 1;
    attackTimer = 120.f;
    dead = false;
    playerX = 400.f;
    playerY = 300.f;
    knifeActive = false;
    knifeTimer = 180.f;
    knifeSpeedX = 0.f;
    knifeSpeedY = 0.f;

    // Setup sprite (Position: 112,0 Size: 1116x648)
    gSprite.setTexture(gTexture);
    gSprite.setTextureRect(sf::IntRect(112, 0, 1116, 648));
    gSprite.setScale(rect.width / 1116.f, rect.height / 648.f);
}

void Gamakichi::updatePhase() {
    phase = getPhase();
}

void Gamakichi::throwKnife(float playerX, float playerY) {
    float startX = rect.left + rect.width / 2;
    float startY = rect.top + rect.height / 2;

    knifeRect = sf::FloatRect(startX, startY, 15, 8);
    knifeActive = true;

    float dx = playerX - startX;
    float dy = playerY - startY;
    float length = sqrt(dx * dx + dy * dy);

    float speed = (phase == 1) ? 4.f : (phase == 2) ? 6.f : 8.f;
    knifeSpeedX = (dx / length) * speed;
    knifeSpeedY = (dy / length) * speed;
}

int Gamakichi::addRocket(float centerX, float centerY, float dirX, float dirY, float speed) {
    // Try to find an inactive rocket slot to reuse
    for (int i = 0; i < rocketCount; i++) {
        if (!rockets[i]->isActive() && !rockets[i]->hasExploded()) {
            delete rockets[i];
            rockets[i] = new Rocket(centerX, centerY, dirX, dirY, speed);
            return i;
        }
    }
    // If no inactive slot, add new one (up to 50)
    if (rocketCount < 50) {
        rockets[rocketCount] = new Rocket(centerX, centerY, dirX, dirY, speed);
        return rocketCount++;
    }
    return -1; // Array full
}

void Gamakichi::fireRockets() {
    float centerX = rect.left + rect.width / 2;
    float centerY = rect.top;
    float armY = rect.top + 42;
    float leftArmX = rect.left - 28;
    float rightArmX = rect.left + rect.width + 28;

    if (phase == 1) {
        // Fire 3 up, 2 from arms
        float dirs[3][2] = {
            {-0.5f, -1.f},
            {0.f,  -1.f},
            {0.5f, -1.f}
        };
        float speed = 4.f;
        for (int i = 0; i < 3; i++) {
            float len = sqrt(dirs[i][0] * dirs[i][0] + dirs[i][1] * dirs[i][1]);
            addRocket(centerX, centerY, dirs[i][0] / len, dirs[i][1] / len, speed);
        }
        // Left and right arm rockets
        addRocket(leftArmX, armY, -1.f, 0.f, speed);
        addRocket(rightArmX, armY, 1.f, 0.f, speed);
    }
    else if (phase == 2) {
        // Fire 3 up, 2 from arms
        float dirs[3][2] = {
            {-0.7f, -0.7f},
            {0.f,  -1.f},
            {0.7f, -0.7f}
        };
        float speed = 6.f;
        for (int i = 0; i < 3; i++) {
            float len = sqrt(dirs[i][0] * dirs[i][0] + dirs[i][1] * dirs[i][1]);
            addRocket(centerX, centerY, dirs[i][0] / len, dirs[i][1] / len, speed);
        }
        // Left and right arm rockets
        addRocket(leftArmX, armY, -1.f, 0.f, speed);
        addRocket(rightArmX, armY, 1.f, 0.f, speed);
    }
    else if (phase == 3) {
        // Fire 8 rockets in all directions, very fast
        float dirs[8][2] = {
            {1.f,   0.f},
            {-1.f,  0.f},
            {0.f,  -1.f},
            {0.7f, -0.7f},
            {-0.7f,-0.7f},
            {0.7f,  0.7f},
            {-0.7f, 0.7f},
            {0.f,   1.f}
        };
        float speed = 10.f;
        for (int i = 0; i < 8; i++) {
            float len = sqrt(dirs[i][0] * dirs[i][0] + dirs[i][1] * dirs[i][1]);
            addRocket(centerX, centerY, dirs[i][0] / len, dirs[i][1] / len, speed);
        }
    }
}

void Gamakichi::Update(Platform** platforms, int platformCount, float pX, float pY) {
    if (dead) return;

    playerX = pX;
    playerY = pY;

    updatePhase();

    // Update and clean up rockets
    for (int i = 0; i < rocketCount; i++) {
        if (rockets[i]->isActive() || rockets[i]->hasExploded()) {
            rockets[i]->Update(platforms, platformCount);
        }
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

    // Attack timer — faster in higher phases
    float timerMax = (phase == 1) ? 120.f : (phase == 2) ? 70.f : 40.f;

    attackTimer--;
    if (attackTimer <= 0) {
        fireRockets();
        attackTimer = timerMax;
    }

    if (health <= 0) dead = true;
}

void Gamakichi::Draw(sf::RenderWindow& window, bool showHitbox) {
    if (dead) return;

    // Draw rockets
    for (int i = 0; i < rocketCount; i++) {
        if (rockets[i]->isActive() || rockets[i]->hasExploded())
            rockets[i]->Draw(window, showHitbox);
    }

    // Draw knife
    if (knifeActive) {
        sf::RectangleShape knife(sf::Vector2f(knifeRect.width, knifeRect.height));
        knife.setPosition(knifeRect.left, knifeRect.top);
        knife.setFillColor(sf::Color(150, 150, 150));
        window.draw(knife);
    }

    // Draw sprite
    gSprite.setPosition(rect.left, rect.top);
    window.draw(gSprite);

    // Phase color
    sf::Color bodyColor;
    if (phase == 1)      bodyColor = sf::Color(180, 100, 20);  // brown
    else if (phase == 2) bodyColor = sf::Color(200, 60, 20);  // orange red
    else                 bodyColor = sf::Color(220, 20, 20);  // bright red enraged

    // Eyes (two white circles with black pupils)
    sf::CircleShape eye1(17.5f);
    eye1.setPosition(rect.left + 91, rect.top + 14);
    eye1.setFillColor(sf::Color::White);
    window.draw(eye1);

    sf::CircleShape pupil1(8.4f);
    pupil1.setPosition(rect.left + 100, rect.top + 23);
    pupil1.setFillColor(sf::Color::Black);
    window.draw(pupil1);

    sf::CircleShape eye2(17.5f);
    eye2.setPosition(rect.left + 273, rect.top + 14);
    eye2.setFillColor(sf::Color::White);
    window.draw(eye2);

    sf::CircleShape pupil2(8.4f);
    pupil2.setPosition(rect.left + 282, rect.top + 23);
    pupil2.setFillColor(sf::Color::Black);
    window.draw(pupil2);

    // Mechanical arms (left and right)
    sf::RectangleShape leftArm(sf::Vector2f(56, 14));
    leftArm.setPosition(rect.left - 56, rect.top + 42);
    leftArm.setFillColor(sf::Color(100, 100, 100));
    window.draw(leftArm);

    sf::RectangleShape rightArm(sf::Vector2f(56, 14));
    rightArm.setPosition(rect.left + rect.width, rect.top + 42);
    rightArm.setFillColor(sf::Color(100, 100, 100));
    window.draw(rightArm);

    // Health bar - stays red
    sf::RectangleShape healthBg(sf::Vector2f(392, 20));
    healthBg.setPosition(rect.left, rect.top - 30);
    healthBg.setFillColor(sf::Color::Red);
    window.draw(healthBg);

    sf::RectangleShape healthBar(sf::Vector2f(392.f * ((float)health / maxHealth), 20));
    healthBar.setPosition(rect.left, rect.top - 30);
    healthBar.setFillColor(sf::Color::Green);
    window.draw(healthBar);

    // Phase markers on health bar
    sf::RectangleShape marker1(sf::Vector2f(3, 20));
    marker1.setPosition(rect.left + 392 * 0.33f, rect.top - 30);
    marker1.setFillColor(sf::Color::White);
    window.draw(marker1);

    sf::RectangleShape marker2(sf::Vector2f(3, 20));
    marker2.setPosition(rect.left + 392 * 0.66f, rect.top - 30);
    marker2.setFillColor(sf::Color::White);
    window.draw(marker2);

    if (showHitbox) {
        sf::RectangleShape hitbox(sf::Vector2f(rect.width, rect.height));
        hitbox.setPosition(rect.left, rect.top);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(2);
        window.draw(hitbox);
    }
}