#include "Smash.h"
#include "Mogera.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

// Static shared gems for both players
Gem* Smash::sharedGems[1000] = {};
int Smash::sharedGemCount = 0;

void Smash::clearGems() {
    for (int i = 0; i < sharedGemCount; i++) {
        if (sharedGems[i] != nullptr) {
            delete sharedGems[i];
            sharedGems[i] = nullptr;
        }
    }
    sharedGemCount = 0;
}

Smash::Smash(int playerNumber) {
    playerNum = playerNumber;

    // Player 1 starts left, Player 2 starts right
    if (playerNum == 1) {
        rect = sf::FloatRect(200, 400, 60, 80);
        moveLeft = sf::Keyboard::A;
        moveRight = sf::Keyboard::D;
        jumpKey = sf::Keyboard::Space;
        shootKey = sf::Keyboard::E;
    }
    else {
        rect = sf::FloatRect(540, 400, 60, 80);
        moveLeft = sf::Keyboard::Left;
        moveRight = sf::Keyboard::Right;
        jumpKey = sf::Keyboard::Up;
        shootKey = sf::Keyboard::RShift;
    }

    velocityY = 0.f;
    isGrounded = false;
    facingRight = true;
    lives = 10;
    score = 0;
    gemCurrency = 0;
    invincibleTimer = 0.f;
    shootHeld = false;

    // Player 2 uses a different image
    std::string imageName = (playerNum == 1) ? "Image.png" : "Image2.png";
    if (!texture.loadFromFile(imageName)) {
        // fallback to same image if Image2 doesnt exist
        texture.loadFromFile("Image.png");
    }

    sprite.setTexture(texture);
    sprite.setScale(
        rect.width / sprite.getLocalBounds().width,
        rect.height / sprite.getLocalBounds().height
    );
}

void Smash::throwSnowball() {
    if (snowballCount >= 100000) return;
    float spawnX = facingRight ? rect.left + rect.width : rect.left - 20;
    snowballs[snowballCount++] = new Snowball(spawnX, rect.top + rect.height / 2, facingRight);
}

void Smash::checkPlatformCollision(sf::FloatRect platform) {
    bool withinX = (rect.left + rect.width > platform.left) && (rect.left < platform.left + platform.width);
    bool fallingOnto = (rect.top + rect.height >= platform.top) &&
        (rect.top + rect.height <= platform.top + platform.height + velocityY);

    if (withinX && fallingOnto && velocityY >= 0) {
        rect.top = platform.top - rect.height;
        velocityY = 0.f;
        isGrounded = true;
    }
}

void Smash::checkEnemyCollision(Enemy** enemies, int enemyCount) {
    if (invincibleTimer > 0) return;

    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i]->isDead()) continue;
        if (enemies[i]->isEncased()) continue;

        sf::FloatRect enemyRect = enemies[i]->getRect();
        bool overlapX = rect.left < enemyRect.left + enemyRect.width &&
            rect.left + rect.width > enemyRect.left;
        bool overlapY = rect.top < enemyRect.top + enemyRect.height &&
            rect.top + rect.height > enemyRect.top;

        if (overlapX && overlapY) {
            lives--;
            invincibleTimer = 120.f;
        }
    }
}

void Smash::checkSnowballEnemyCollision(Enemy** enemies, int enemyCount) {
    for (int s = 0; s < snowballCount; s++) {
        if (!snowballs[s]->isActive()) continue;

        for (int e = 0; e < enemyCount; e++) {
            if (enemies[e]->isDead()) continue;

            sf::FloatRect sRect = snowballs[s]->getRect();
            sf::FloatRect eRect = enemies[e]->getRect();

            bool overlapX = sRect.left < eRect.left + eRect.width &&
                sRect.left + sRect.width > eRect.left;
            bool overlapY = sRect.top < eRect.top + eRect.height &&
                sRect.top + sRect.height > eRect.top;

            if (!overlapX || !overlapY) continue;

            Mogera* mogera = dynamic_cast<Mogera*>(enemies[e]);
            if (mogera) {
                mogera->hitWithSnow();
                snowballs[s]->deactivate();
                continue;
            }

            if (enemies[e]->isRolling()) continue;

            enemies[e]->hitWithSnow();
            if (enemies[e]->isEncased()) score += 100;
            snowballs[s]->deactivate();
        }
    }
}

void Smash::Update(Platform** platforms, int platformCount, Enemy** enemies, int enemyCount) {
    float speed = 5.0f;
    float gravity = 0.6f;
    float jumpForce = -14.f;

    if (invincibleTimer > 0) invincibleTimer--;

    if (sf::Keyboard::isKeyPressed(moveLeft)) {
        rect.left -= speed;
        facingRight = false;
    }
    if (sf::Keyboard::isKeyPressed(moveRight)) {
        rect.left += speed;
        facingRight = true;
    }
    if (sf::Keyboard::isKeyPressed(jumpKey) && isGrounded) {
        velocityY = jumpForce;
        isGrounded = false;
    }
    if (sf::Keyboard::isKeyPressed(shootKey)) {
        if (!shootHeld) {
            throwSnowball();
            shootHeld = true;
        }
    }
    else {
        shootHeld = false;
    }

    for (int i = 0; i < snowballCount; i++) {
        if (snowballs[i]->isActive())
            snowballs[i]->Update(platforms, platformCount);
    }

    for (int i = 0; i < sharedGemCount; i++) {
        if (sharedGems[i]->isActive())
            sharedGems[i]->Update(platforms, platformCount);
    }

    for (int i = 0; i < sharedGemCount; i++) {
        if (!sharedGems[i]->isActive()) continue;
        sf::FloatRect gRect = sharedGems[i]->getRect();
        bool overlapX = rect.left < gRect.left + gRect.width && rect.left + rect.width > gRect.left;
        bool overlapY = rect.top < gRect.top + gRect.height && rect.top + rect.height > gRect.top;
        if (overlapX && overlapY) {
            gemCurrency += sharedGems[i]->getValue();
            sharedGems[i]->collect();
        }
    }

    // Kick encased enemies
    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i]->isEncased() || enemies[i]->isRolling() || enemies[i]->isDead()) continue;
        sf::FloatRect eRect = enemies[i]->getRect();
        bool overlapX = rect.left < eRect.left + eRect.width && rect.left + rect.width > eRect.left;
        bool overlapY = rect.top < eRect.top + eRect.height && rect.top + rect.height > eRect.top;
        if (overlapX && overlapY)
            enemies[i]->startRolling(facingRight);
    }

    // Rolling kills enemies
    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i]->isRolling() || enemies[i]->isDead()) continue;
        for (int j = 0; j < enemyCount; j++) {
            if (i == j || enemies[j]->isDead()) continue;
            sf::FloatRect r1 = enemies[i]->getRect();
            sf::FloatRect r2 = enemies[j]->getRect();
            bool overlapX = r1.left < r2.left + r2.width && r1.left + r1.width > r2.left;
            bool overlapY = r1.top < r2.top + r2.height && r1.top + r1.height > r2.top;
            if (overlapX && overlapY) {
                Mogera* mogera = dynamic_cast<Mogera*>(enemies[j]);
                if (mogera) {
                    for (int g = 0; g < 25; g++) {
                        if (sharedGemCount < 1000) {
                            float offsetX = r2.left + (rand() % (int)r2.width);
                            float offsetY = r2.top + (rand() % (int)r2.height);
                            Gem* newGem = new Gem(offsetX, offsetY, 8);

                            // Random velocity in all directions with upward bias
                            float angle = (rand() % 360) * 3.14159f / 180.f;
                            float speed = 4.f + (rand() % 4); // 4-8 speed
                            float vx = cosf(angle) * speed;
                            float vy = sinf(angle) * speed; // positive = upward initially
                            // Make sure they go up initially
                            if (vy > 0) vy = -vy; // force upward
                            newGem->setVelocity(vx, vy);

                            sharedGems[sharedGemCount++] = newGem;
                        }
                    }
                }
                else {
                    if (sharedGemCount < 1000)
                        sharedGems[sharedGemCount++] = new Gem(r2.left + r2.width / 2, r2.top, 3);
                }
                enemies[j]->kill();
                score += 100 + rand() % 400;
            }
        }
    }

    checkSnowballEnemyCollision(enemies, enemyCount);
    checkEnemyCollision(enemies, enemyCount);

    velocityY += gravity;
    rect.top += velocityY;
    isGrounded = false;

    for (int i = 0; i < platformCount; i++)
        checkPlatformCollision(platforms[i]->getRect());

    if (rect.left < 0) rect.left = 0;
    if (rect.left + rect.width > 800) rect.left = 800 - rect.width;

    sprite.setPosition(rect.left, rect.top);

    if (!facingRight) {
        sprite.setScale(-rect.width / sprite.getLocalBounds().width, rect.height / sprite.getLocalBounds().height);
        sprite.setOrigin(sprite.getLocalBounds().width, 0);
    }
    else {
        sprite.setScale(rect.width / sprite.getLocalBounds().width, rect.height / sprite.getLocalBounds().height);
        sprite.setOrigin(0, 0);
    }

    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i]->isDead() && !enemies[i]->scoreCounted) {
            Mogera* mogera = dynamic_cast<Mogera*>(enemies[i]);
            if (mogera) {
                for (int g = 0; g < 25; g++) {
                    if (sharedGemCount < 1000) {
                        float offsetX = mogera->getRect().left + (rand() % (int)mogera->getRect().width);
                        float offsetY = mogera->getRect().top + (rand() % (int)mogera->getRect().height);
                        Gem* newGem = new Gem(offsetX, offsetY, 8);

                        // Random velocity in all directions with upward bias
                        float angle = (rand() % 360) * 3.14159f / 180.f;
                        float speed = 4.f + (rand() % 4); // 4-8 speed
                        float vx = cosf(angle) * speed;
                        float vy = sinf(angle) * speed; // positive = upward initially
                        // Make sure they go up initially
                        if (vy > 0) vy = -vy; // force upward
                        newGem->setVelocity(vx, vy);

                        sharedGems[sharedGemCount++] = newGem;
                    }
                }
            }
            score += 200;
            enemies[i]->scoreCounted = true;
        }
    }
}

void Smash::Draw(sf::RenderWindow& window, bool showHitbox) {
    if (invincibleTimer > 0 && (int)invincibleTimer % 10 < 5) return;

    window.draw(sprite);

    for (int i = 0; i < snowballCount; i++) {
        if (snowballs[i]->isActive())
            snowballs[i]->Draw(window, showHitbox);
    }

    for (int i = 0; i < sharedGemCount; i++) {
        if (sharedGems[i]->isActive())
            sharedGems[i]->Draw(window);
    }

    if (showHitbox) {
        sf::RectangleShape hitbox(sf::Vector2f(rect.width, rect.height));
        hitbox.setPosition(rect.left, rect.top);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(playerNum == 1 ? sf::Color::Green : sf::Color::Cyan);
        hitbox.setOutlineThickness(2);
        window.draw(hitbox);
    }
}

void Smash::reset() {
    if (playerNum == 1) {
        rect.left = 200;
    }
    else {
        rect.left = 540;
    }
    rect.top = 470;
    velocityY = 0.f;
    isGrounded = false;
}

void Smash::hit() {
    if (invincibleTimer > 0) return;
    lives--;
    invincibleTimer = 120.f;
}