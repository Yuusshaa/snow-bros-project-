#pragma once
#include "Flyingshit.h"
#include "Animation.h"

class Tornado : public FlyingFoogaFoog {
public:
    Tornado(float initialX, float initialY);
    void Update(Platform** platforms, int platformCount, float playerX, float playerY);
    void Draw(sf::RenderWindow& window, bool showHitbox) override;
    sf::FloatRect getKnifeRect() { return knifeRect; }
    bool knifeActive = false;

    static bool loadTexture();

private:
    static sf::Texture tTexture;
    sf::Sprite tSprite;

    sf::FloatRect knifeRect;
    float knifeSpeedX;
    float knifeSpeedY;
    float knifeTimer;
    float teleportTimer;
    void throwKnife(float playerX, float playerY);
};
