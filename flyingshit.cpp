#include "flyingshit.h"
#include <cstdlib>

sf::Texture FlyingFoogaFoog::flyTexture;


bool FlyingFoogaFoog::loadFlyTexture() {
    return flyTexture.loadFromFile("flying_Blue.png");
}




FlyingFoogaFoog::FlyingFoogaFoog(float initialX, float initialY)
    : Botom(initialX, initialY),
    flyAnim(FlyingFoogaFoog::flyTexture, 219, 21, 162, 166, 1, 0.f)
{
    flying = false;
    flyTimer = 180.f;
    flyDuration = 0.f;
    flySpeedX = 0.f;
    flySpeedY = 0.f;
    flyRotation = 0.f;

    // Movement anims — your flyTexture coords
    walkAnim = Animation(FlyingFoogaFoog::flyTexture, 429, 24, 139, 159, 1, 0.f);
    idleAnim = Animation(FlyingFoogaFoog::flyTexture, 54, 29, 103, 158, 1, 0.f);
    jumpingAnim = Animation(FlyingFoogaFoog::flyTexture, 429, 24, 139, 159, 1, 0.f); // fix your jump coords

    // Snowball anims — same sheet as Botom

    fullAnim = Animation(snowballtexture, 5, 968, 81, 84, 1, 0.f);
    halfAnim = Animation(Botom::snowballtexture, 91, 900, 68, 60, 1, 0.f);

    rollAnim = Animation(Botom::snowballtexture, 5, 968, 81, 84, 3, 10.f);
}

void FlyingFoogaFoog::Update(Platform** platforms, int platformCount) {
    if (dead) 
        return;

    updateDefrost();

    if (rolling) {
        currentAnim = &rollAnim;
        currentAnim->update();

        rect.left += (rollingRight ? 6.f : -6.f);
        velocityY += 0.6f;
        rect.top += velocityY;

        if (rect.left <= 0) 
            rect.left = 0, rollingRight = true;
        if (rect.left + rect.width >= 800) 
            rect.left = 800 - rect.width, rollingRight = false;

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
        flying = false;
        velocityY += 0.6f;
        rect.top += velocityY;
        for (int i = 0; i < platformCount; i++)
            checkPlatformCollision(platforms[i]->getRect());

        Botom::Update(platforms, platformCount);
        return;
    }

    if (isHalfFrozen()) {
        currentAnim = &halfAnim;  // add this
        velocityY += 0.6f;
        rect.top += velocityY;
        for (int i = 0; i < platformCount; i++)
            checkPlatformCollision(platforms[i]->getRect());
        return;
    }

    if (flying) {
        // Set rotation based on direction
        if (flySpeedX > 0 && flySpeedY < 0)  flyRotation = 0.f;   // up-right
        else if (flySpeedX > 0 && flySpeedY == 0)  flyRotation = 45.f;  // right
        else if (flySpeedX > 0 && flySpeedY > 0)   flyRotation = 90.f;  // down-right
        else if (flySpeedX == 0 && flySpeedY > 0)   flyRotation = 135.f; // down
        else if (flySpeedX < 0 && flySpeedY > 0)   flyRotation = 180.f; // down-left
        else if (flySpeedX < 0 && flySpeedY == 0)  flyRotation = 225.f; // left
        else if (flySpeedX < 0 && flySpeedY < 0)   flyRotation = 270.f; // up-left
        else if (flySpeedX == 0 && flySpeedY < 0)   flyRotation = 315.f; // up


        currentAnim = &flyAnim;

        currentAnim->update();

        rect.left += flySpeedX;
        rect.top += flySpeedY;

        if (rect.left <= 0 || rect.left + rect.width >= 800) flySpeedX = -flySpeedX;
        if (rect.top <= 0 || rect.top + rect.height >= 540) flySpeedY = -flySpeedY;

        flyDuration--;
        if (flyDuration <= 0) {
            flying = false;
            flyTimer = 180.f + rand() % 120;
            velocityY = 0.f;
        }
        return;
    }

    // Count down to next flight
    flyTimer--;
    if (flyTimer <= 0) {
        flying = true;
        flyDuration = 120.f + rand() % 120; // fly for 2-4 seconds

        // Pick a random direction to fly in (8 directions)
        int directionChoice = rand() % 8;
        float speed = 3.f;
        float directions[8][2] = {
            {speed, 0},    // right
            {-speed, 0},   // left
            {0, -speed},   // up
            {0, speed},    // down
            {speed, -speed}, // up right
            {-speed,-speed}, // up left
            {speed, speed},  // down right
            {-speed, speed}  // down left
        };
        flySpeedX = directions[directionChoice][0];
        flySpeedY = directions[directionChoice][1];
        return;
    }

    // Normal Botom movement when on ground
    Botom::Update(platforms, platformCount);
}

void FlyingFoogaFoog::Draw(sf::RenderWindow& window, bool showHitbox) {
    if (dead) return;

    if (flying) {
        sf::Sprite flySprite;
        flySprite.setTexture(FlyingFoogaFoog::flyTexture);
        flySprite.setTextureRect(flyAnim.getCurrentFrame());
        flySprite.setScale(
            rect.width / flySprite.getLocalBounds().width,
            rect.height / flySprite.getLocalBounds().height
        );
        // Rotate around center
        flySprite.setOrigin(
            flySprite.getLocalBounds().width / 2,
            flySprite.getLocalBounds().height / 2
        );
        flySprite.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
        flySprite.setRotation(flyRotation);
        window.draw(flySprite);
    }
    else {
        float drawX = rect.left;
        if (isEncased() && defrostTimer < 60.f && (int)defrostTimer % 6 < 3)
            drawX += 3.f;
        currentAnim->draw(window, drawX, rect.top, rect.width, rect.height);
    }

    if (showHitbox) {
        sf::RectangleShape hitbox(sf::Vector2f(rect.width, rect.height));
        hitbox.setPosition(rect.left, rect.top);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(2);
        window.draw(hitbox);
    }
}