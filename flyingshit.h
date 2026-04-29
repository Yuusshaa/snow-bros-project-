#pragma once
#include "Botom.h"
#include "Animation.h"

class FlyingFoogaFoog : public Botom {
public:
    static sf::Texture flyTexture;
    static bool loadFlyTexture();

    FlyingFoogaFoog(float initialX, float initialY);
    void Update(Platform** platforms, int platformCount) override;
    void Draw(sf::RenderWindow& window, bool showHitbox) override;

private:
    bool flying;
    float flyTimer;
    float flyDuration;
    float flySpeedX;
    float flySpeedY;
    float flyRotation;
protected:
    Animation flyAnim;
    Animation halfAnim;
    Animation fullAnim;
};