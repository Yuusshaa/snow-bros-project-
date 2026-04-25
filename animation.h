// Animation.h
#pragma once
#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(sf::Texture& texture, int startX, int startY,
        int fWidth, int fHeight, int fCount, float spd) {
        sprite.setTexture(texture);
        this->startX = startX;
        this->startY = startY;
        this->frameWidth = fWidth;
        this->frameHeight = fHeight;
        this->frameCount = fCount;
        this->speed = spd;
        currentFrame = 0;
        timer = 0;
    }
    void draw(sf::RenderWindow& window, float x, float y, float targetWidth, float targetHeight) {
        float scaleX = targetWidth / frameWidth;
        float scaleY = targetHeight / frameHeight;

        if (isFlipped) {
            sprite.setScale(-scaleX, scaleY);          // negative = flip left
            sprite.setOrigin((float)frameWidth, 0.f);  // origin at right edge
        }
        else {
            sprite.setScale(scaleX, scaleY);           // normal
            sprite.setOrigin(0.f, 0.f);                // origin at left edge
        }

        sprite.setPosition(x, y);
        window.draw(sprite);
    }
    void update() {
        timer++;
        if (timer >= speed) {
            timer = 0;
            currentFrame = (currentFrame + 1) % frameCount;
        }
        sprite.setTextureRect(sf::IntRect(
            startX + currentFrame * frameWidth,
            startY,
            frameWidth,
            frameHeight
        ));
    }




    void flipX(bool flipped) {
        isFlipped = flipped;
    }

    void reset() { currentFrame = 0; timer = 0; }

private:
    bool isFlipped = false;
    sf::Sprite sprite;
    int startX, startY;
    int frameWidth, frameHeight;
    int frameCount;
    float speed;
    int currentFrame;
    float scaleX = 1.f, scaleY = 1.f;
    float timer;
};