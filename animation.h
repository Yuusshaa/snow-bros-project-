#pragma once
#include <SFML/Graphics.hpp>

class Animation {

public:
    Animation() : startX(0), startY(0), frameWidth(1), frameHeight(1), 
                  frameCount(1), speed(0), currentFrame(0), timer(0) {}

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

        sprite.setTextureRect(sf::IntRect(
            startX + currentFrame * frameWidth,
            startY,
            frameWidth,
            frameHeight
        ));

        if (isFlipped) {
            sprite.setScale(-scaleX, scaleY);          // negative = flip left
            sprite.setOrigin((float)frameWidth, 0.f); 
        }
        else {
            sprite.setScale(scaleX, scaleY);          
            sprite.setOrigin(0.f, 0.f);                
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

    Animation& operator=(const Animation& other) {
        startX       = other.startX;
        startY       = other.startY;
        frameWidth   = other.frameWidth;
        frameHeight  = other.frameHeight;
        frameCount   = other.frameCount;
        speed        = other.speed;
        currentFrame = other.currentFrame;
        timer        = other.timer;
        isFlipped    = other.isFlipped;

        // Re-bind texture pointer so it doesn't go stale
        sprite.setTexture(*other.sprite.getTexture());
        sprite.setTextureRect(other.sprite.getTextureRect());
        return *this;
    }

    sf::IntRect getCurrentFrame() const {
        return sf::IntRect(
            startX + currentFrame * frameWidth,
            startY,
            frameWidth,
            frameHeight
        );
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