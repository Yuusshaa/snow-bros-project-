#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

class Enemy {
public:
    virtual void Update(Platform** platforms, int platformCount) = 0;

    virtual void Draw(sf::RenderWindow& window, bool showHitbox) = 0;
    sf::FloatRect getRect() { return rect; }
    bool isDead() { return dead; }
    bool isEncased() { return snowHits >= maxSnowHits && !defrosted; }
    bool isRolling() { return rolling; }
    bool isDefrosted() { return defrosted; }

    bool isHalfFrozen() { return snowHits == 1; }


void hitWithSnow() {
    if (!isEncased() && !defrosted) {
        snowHits++;
        if (snowHits == 1) {
            velocityY = 0.f;
            halfDefrostTimer = 120.f;
            defrosted = false;
        }
        if (isEncased()) {
            defrostTimer = 180.f;
            halfDefrostTimer = 0.f;
        }
    }
}

 
    void updateDefrost() {
        if (snowHits == 1 && halfDefrostTimer > 0) {
            halfDefrostTimer--;
            if (halfDefrostTimer <= 0) {
                snowHits = 0;
                defrosted = false; 
            }
        }
        if (isEncased() && !rolling) {
            defrostTimer--;
            if (defrostTimer <= 0) {
                snowHits = 0;
                defrosted = false; 
                halfDefrostTimer = 0.f;
            }
        }
    }



    bool isRollingRight() { return rollingRight; }
    void kill() { dead = true; }

    virtual void startRolling(bool goRight) {
        rolling = true;
        rollingRight = goRight;
    }
    bool scoreCounted = false;

protected:
    sf::FloatRect rect;
    bool dead = false;
    int snowHits = 0;
    int maxSnowHits = 2;
    bool rolling = false;
    bool rollingRight = false;
    bool defrosted = false;
    float defrostTimer = 0.f;
    float halfDefrostTimer = 0.f;
    float velocityY = 0.f;
};