#pragma once
#include "Botom.h"

class FlyingFoogaFoog : public Botom {
public:
    FlyingFoogaFoog(float initialX, float initialY);
    void Update(Platform** platforms, int platformCount) override;
    void Draw(sf::RenderWindow& window, bool showHitbox) override;

private:
    bool flying;
    float flyTimer;      // how long until it takes flight
    float flyDuration;   // how long it stays in the air
    float flySpeedX;
    float flySpeedY;
};