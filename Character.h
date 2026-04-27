#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Enemy.h"

class Character {
public:
    virtual void Update(Platform** platforms, int platformCount, Enemy** enemies, int enemyCount) = 0;
    virtual void Draw(sf::RenderWindow& window, bool showHitbox) = 0;
    virtual int getLives() = 0;
    virtual bool isGameOver() = 0;
    virtual int getScore() = 0;
    virtual void reset() = 0;
    virtual sf::FloatRect getRect() = 0;
    virtual void hit() = 0;
    void setPosition(float x, float y) {
        rect.left = x;
        rect.top = y;
    }
protected:
    sf::FloatRect rect;
};