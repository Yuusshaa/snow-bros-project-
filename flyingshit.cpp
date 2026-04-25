#include "flyingshit.h"
#include <cstdlib>

FlyingFoogaFoog::FlyingFoogaFoog(float initialX, float initialY) : Botom(initialX, initialY) {
    flying = false;
    flyTimer = 180.f;       // takes flight after 3 seconds
    flyDuration = 0.f;
    flySpeedX = 0.f;
    flySpeedY = 0.f;
}

void FlyingFoogaFoog::Update(Platform** platforms, int platformCount) {
    if (dead) 
        return;

    updateDefrost();

    if (rolling) {
        rect.left += (rollingRight ? 6.f : -6.f);
        velocityY += 0.6f;
        rect.top += velocityY;

        if (rect.left <= 0) 
            rect.left = 0, rollingRight = true;
        if (rect.left + rect.width >= 800) 
            rect.left = 800 - rect.width, rollingRight = false;

        if (rect.top + rect.height >= 550) {
            dead = true;
            return;
        }

        for (int platformIndex = 0; platformIndex < platformCount; platformIndex++)
            checkPlatformCollision(platforms[platformIndex]->getRect());
        return;
    }

    if (isEncased()) {
        flying = false;
        velocityY += 0.6f;
        rect.top += velocityY;
        for (int platformIndex = 0; platformIndex < platformCount; platformIndex++)
            checkPlatformCollision(platforms[platformIndex]->getRect());
        return;
    }
    if (isHalfFrozen()) {  // ADD THIS
        velocityY += 0.6f;
        rect.top += velocityY;
        for (int i = 0; i < platformCount; i++)
            checkPlatformCollision(platforms[i]->getRect());
        return;
    }

    if (flying) {
        // Move freely in chosen direction
        rect.left += flySpeedX;
        rect.top += flySpeedY;

        // Bounce off screen edges
        if ((rect.left <= 0) || (rect.left + rect.width >= 800)) 
            flySpeedX = -flySpeedX;
        if ((rect.top <= 0) || (rect.top + rect.height >= 540)) 
            flySpeedY = -flySpeedY;

        // Count down flight duration
        flyDuration--;
        if (flyDuration <= 0) {
            flying = false;
            flyTimer = 180.f + rand() % 120; // wait 3-5 seconds before flying again
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
    if (dead) 
        return;

    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));

    
    float drawX = rect.left;
    if (isEncased() && defrostTimer < 60.f && (int)defrostTimer % 6 < 3)
        drawX += 3.f;


    shape.setPosition(drawX, rect.top);

    if (rolling)
        shape.setFillColor(sf::Color(200, 200, 255));
    else if (isEncased())
        shape.setFillColor(sf::Color::White);
    else if (flying)
        shape.setFillColor(sf::Color(100, 255, 100)); // green when flying
    else if (snowHits == 1)
        shape.setFillColor(sf::Color(100, 200, 100)); // lighter green when partially hit
    else
        shape.setFillColor(sf::Color(0, 150, 0)); // dark green normally

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