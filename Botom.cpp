#include "Botom.h"
#include "Platform.h"
#include "animation.h"

// static texture definition
sf::Texture Botom::texture; 
sf::Texture Botom::snowballtexture;

bool Botom::loadTexture() {
    bool a = texture.loadFromFile("botom.png");
    bool b = snowballtexture.loadFromFile("Player_Blue.png");

    return a && b;
}


Botom::Botom(float x, float y)


    : walkAnim(texture, 0, 368, 95, 82, 3, 8.f),
      fullAnim(snowballtexture, 5, 968, 81, 84, 1, 0.f),
      idleAnim(texture, 9, 136, 83, 86, 1, 0.f),
    //Position: 92,900 Size: 68x60
      halfAnim(snowballtexture, 91, 900, 68, 60, 1, 0.f), 
    // 5,969 Size: 328x82
      rollAnim(snowballtexture, 5, 968, 81, 84, 3, 10.f),
      jumpingAnim(texture, 0, 480, 100, 92, 1, 0.f),
      currentAnim(&idleAnim)// row 4 — rolling
{
    rect = sf::FloatRect(x, y, 50, 50);
    velocityY = 0.f;
    speed = 2.f;
    direction = 1;
    directionTimer = 0;
    isGrounded = false;
    jumpTimer = 120.f;
    currentAnim = &walkAnim;
}

void Botom::checkPlatformCollision(sf::FloatRect p) {
    bool withinX = rect.left + rect.width > p.left && rect.left < p.left + p.width;
    bool fallingOnto = rect.top + rect.height >= p.top &&
        rect.top + rect.height <= p.top + p.height + velocityY;
    if (withinX && fallingOnto && velocityY >= 0) {
        rect.top = p.top - rect.height;
        velocityY = 0.f;
        isGrounded = true;
    }
}

void Botom::Update(Platform** platforms, int platformCount) {
    if (dead) return;
    updateDefrost();

    // --- pick animation based on state ---

    if (rolling)          currentAnim = &rollAnim;
    else if (isEncased()) currentAnim = &fullAnim;
    else if (isHalfFrozen()) currentAnim = &halfAnim;
    else if (direction == 0) currentAnim = &idleAnim;
    else if (!isGrounded) currentAnim = &jumpingAnim;
    else                  currentAnim = &walkAnim;

    currentAnim->update();

    // flip sprite to face movement direction
    currentAnim->flipX(direction == 1);

    if (rolling) {
        rect.left += (rollingRight ? 6.f : -6.f);
        velocityY += 0.6f;
        rect.top += velocityY;

        // bounce off walls
        if (rect.left <= 0) {
            rect.left = 0;
            rollingRight = true;
        }
        if (rect.left + rect.width >= 800) {
            rect.left = 800 - rect.width;
            rollingRight = false;
        }

        for (int i = 1; i < platformCount; i++)
            checkPlatformCollision(platforms[i]->getRect());

        if (rect.top + rect.height >= 560) {
            rect.top = 560 - rect.height;
            velocityY = 0.f;
        }

        // corner kill zones
        if (rect.left <= 0 && rect.top + rect.height >= 550 && rect.top + rect.height <= 610) {
            dead = true; return;
        }
        if (rect.left + rect.width >= 800 && rect.top + rect.height >= 550 && rect.top + rect.height <= 610) {
            dead = true; return;
        }
        return;
    }

    if (isEncased()) {
        velocityY += 0.6f;
        rect.top += velocityY;
        isGrounded = false;
        for (int i = 0; i < platformCount; i++)
            checkPlatformCollision(platforms[i]->getRect());
        return;
    }

    if (isHalfFrozen()) {
        velocityY += 0.6f;
        rect.top += velocityY;
        for (int i = 0; i < platformCount; i++)
            checkPlatformCollision(platforms[i]->getRect());
        return;
    }

    jumpTimer--;
    if (jumpTimer <= 0 && isGrounded) {
        velocityY = -14.f;
        isGrounded = false;
        jumpTimer = 120.f + rand() % 180;
    }

    directionTimer--;
    if (directionTimer <= 0) {
        int roll = rand() % 3;
        if (roll == 0) direction = 1;
        else if (roll == 1) direction = 0;
        else direction = -1;
        directionTimer = 60 + rand() % 120;
    }

    rect.left += speed * direction;
    if (rect.left <= 0) { rect.left = 0; direction = 1; }
    if (rect.left + rect.width >= 800) { rect.left = 800 - rect.width; direction = -1; }

    isGrounded = false;
    velocityY += 0.6f;
    rect.top += velocityY;

    for (int i = 0; i < platformCount; i++)
        checkPlatformCollision(platforms[i]->getRect());
}

void Botom::Draw(sf::RenderWindow& window, bool showHitbox) {
    if (dead) return;

    float drawX = rect.left;
    if (isEncased() && defrostTimer < 60.f && (int)defrostTimer % 6 < 3)
        drawX += 3.f;
    else if (isHalfFrozen() && halfDefrostTimer < 60.f && (int)halfDefrostTimer % 6 < 3)
        drawX += 3.f;

    currentAnim->draw(window, drawX, rect.top, rect.width, rect.height);

    if (showHitbox) {
        sf::RectangleShape hitbox(sf::Vector2f(rect.width, rect.height));
        hitbox.setPosition(rect.left, rect.top);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(2);
        window.draw(hitbox);
    }
}