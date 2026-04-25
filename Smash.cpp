#include "Smash.h"
#include <iostream>

Smash::Smash() {
    rect = sf::FloatRect(100, 400, 60, 80);
    velocityY = 0.f;
    isGrounded = false;
    facingRight = true;
    lives = 10;
    score = 0;
    invincibleTimer = 0.f;
    spaceHeld = false;

    if (!texture.loadFromFile("Image.png")) {
        std::cout << "Failed to load image!" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setScale(
        rect.width / sprite.getLocalBounds().width,
        rect.height / sprite.getLocalBounds().height
    );
}

void Smash::throwSnowball() {
    if (snowballCount >= 100000) 
        return;
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
    if (invincibleTimer > 0) 
        return;

    for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++) {
        if (enemies[enemyIndex]->isDead()) 
            continue;
        if (enemies[enemyIndex]->isEncased()) 
            continue; // cant hurt you when encased

        sf::FloatRect enemyRect = enemies[enemyIndex]->getRect();
        bool overlapX = (rect.left < enemyRect.left + enemyRect.width) && 
                        (rect.left + rect.width > enemyRect.left);
        bool overlapY = (rect.top < enemyRect.top + enemyRect.height) && 
                        (rect.top + rect.height > enemyRect.top);

        if (overlapX && overlapY) {
            lives--;
            invincibleTimer = 120.f;
        }
    }
}

void Smash::checkSnowballEnemyCollision(Enemy** enemies, int enemyCount) {
    for (int snowballIndex = 0; snowballIndex < snowballCount; snowballIndex++) {
        if (!snowballs[snowballIndex]->isActive()) 
            continue;

        for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++) {
            if (enemies[enemyIndex]->isDead()) 
                continue;
            if (enemies[enemyIndex]->isRolling()) 
                continue;

            sf::FloatRect snowballRect = snowballs[snowballIndex]->getRect();
            sf::FloatRect enemyRect = enemies[enemyIndex]->getRect();

            bool overlapX = (snowballRect.left < enemyRect.left + enemyRect.width) && 
                            (snowballRect.left + snowballRect.width > enemyRect.left);
            bool overlapY = (snowballRect.top < enemyRect.top + enemyRect.height) && 
                            (snowballRect.top + snowballRect.height > enemyRect.top);

            if (overlapX && overlapY) {
                enemies[enemyIndex]->hitWithSnow();
                if (enemies[enemyIndex]->isEncased()) {
                    score += 100;
                }
                snowballs[snowballIndex]->deactivate();
            }
        }
    }
}

void Smash::Update(Platform** platforms, int platformCount, Enemy** enemies, int enemyCount) {
    float speed = 5.0f;
    float gravity = 0.6f;
    float jumpForce = -14.f;

    if (invincibleTimer > 0) invincibleTimer--;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        rect.left -= speed;
        facingRight = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        rect.left += speed;
        facingRight = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded) {
        velocityY = jumpForce;
        isGrounded = false;
    }

    // Throw snowball with J - spaceHeld prevents holding J to spam
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        if (!spaceHeld) {
            throwSnowball();
            spaceHeld = true;
        }
    }
    else {
        spaceHeld = false;
    }

    // Update snowballs
    for (int i = 0; i < snowballCount; i++) {
        if (snowballs[i]->isActive())
            snowballs[i]->Update(platforms, platformCount);
    }

    // Check if player walks into encased enemy to start rolling
    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i]->isEncased() || enemies[i]->isRolling() || enemies[i]->isDead()) continue;

        sf::FloatRect eRect = enemies[i]->getRect();
        bool overlapX = rect.left < eRect.left + eRect.width &&
            rect.left + rect.width > eRect.left;
        bool overlapY = rect.top < eRect.top + eRect.height &&
            rect.top + rect.height > eRect.top;

        if (overlapX && overlapY) {
            // Kick in direction player is facing
            enemies[i]->startRolling(facingRight);
        }
    }

    // Check rolling enemy kills other enemies
    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i]->isRolling() || enemies[i]->isDead()) continue;

        for (int j = 0; j < enemyCount; j++) {
            if (i == j) continue;
            if (enemies[j]->isDead()) continue;

            sf::FloatRect r1 = enemies[i]->getRect();
            sf::FloatRect r2 = enemies[j]->getRect();

            bool overlapX = r1.left < r2.left + r2.width && r1.left + r1.width > r2.left;
            bool overlapY = r1.top < r2.top + r2.height && r1.top + r1.height > r2.top;

            if (overlapX && overlapY) {
                enemies[j]->kill();
                score += 100 + rand() % 400; // 100-500 points\

            }
            
        }
    }

    checkSnowballEnemyCollision(enemies, enemyCount);
    checkEnemyCollision(enemies, enemyCount);

    velocityY += gravity;
    rect.top += velocityY;
    isGrounded = false;

    for (int i = 0; i < platformCount; i++) {
        checkPlatformCollision(platforms[i]->getRect());
    }

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
            score += 200;
            enemies[i]->scoreCounted = true;
        }
    }
}

void Smash::Draw(sf::RenderWindow& window, bool showHitbox) {
    if (invincibleTimer > 0 && (int)invincibleTimer % 10 < 5) return;

    window.draw(sprite);

    // Draw snowballs
    for (int i = 0; i < snowballCount; i++) {
        if (snowballs[i]->isActive())
            snowballs[i]->Draw(window, showHitbox);
    }

    if (showHitbox) {
        sf::RectangleShape hitbox(sf::Vector2f(rect.width, rect.height));
        hitbox.setPosition(rect.left, rect.top);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Green);
        hitbox.setOutlineThickness(2);
        window.draw(hitbox);
    }
}
void Smash::reset() {
    rect.left = 370;  // middle of screen
    rect.top = 470;   // near bottom
    velocityY = 0.f;
    isGrounded = false;
}
void Smash::hit() {
    if (invincibleTimer > 0) return;
    lives--;
    invincibleTimer = 120.f;
}