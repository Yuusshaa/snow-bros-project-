#pragma once
#include "Enemy.h"
#include "Platform.h"
#include "MogeraChild.h"
#include "SoundManager.h"
#include "Animation.h"
#include <cmath>

class Mogera : public Enemy {
public:
    Mogera(float x, float y);
    void Update(Platform** platforms, int platformCount, float playerX, float playerY);
    void Draw(sf::RenderWindow& window, bool showHitbox) override;

    MogeraChild* children[50] = { nullptr };
    int childCount = 0;

    bool knifeActive = false;
    sf::FloatRect getKnifeRect() { return knifeRect; }
    void deactivateKnife() { knifeActive = false; }
    void Update(Platform** platforms, int platformCount) override {
        Update(platforms, platformCount, 0.f, 0.f);
    }
    void hitWithSnow() override {
        health--;
    }

    static bool loadTexture();

private:
    static sf::Texture mTexture;
    static sf::Texture playerTexture;
    sf::Sprite bodySprite;
    sf::Sprite legsSprite;

    Animation rollAnim;
    Animation hitAnim;
    Animation* currentAnim;

    float velocityY;
    bool isGrounded;
    bool droppingThrough;
    float jumpTimer;
    float spawntimer;
    int health;

    // Knife
    sf::FloatRect knifeRect;
    float knifeSpeedX;
    float knifeSpeedY;
    float knifeTimer;

    void checkPlatformCollision(sf::FloatRect p);
    void spawnChildren();
    void throwKnife(float playerX, float playerY);
};