#pragma once
#include "Enemy.h"
#include "Platform.h"

class MogeraChild : public Enemy {
public:
    MogeraChild(float x, float y);
    void Update(Platform** platforms, int platformCount) override;
    void Draw(sf::RenderWindow& window, bool showHitbox) override;
    float velocityX;

private:
private:
    float velocityY;
    float waitTimer;
    bool waiting;
    void checkPlatformCollision(sf::FloatRect p);
};