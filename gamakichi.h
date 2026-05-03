#pragma once
#include "Enemy.h"
#include "Platform.h"
#include "Rocket.h"

class Gamakichi : public Enemy {
public:
    Gamakichi();
    void Update(Platform** platforms, int platformCount, float playerX, float playerY);
    void Update(Platform** platforms, int platformCount) {
        Update(platforms, platformCount, 400.f, 300.f);
    }
    void Draw(sf::RenderWindow& window, bool showHitbox) override;

    Rocket* rockets[50] = { nullptr };
    int rocketCount = 0;

    bool knifeActive = false;
    sf::FloatRect getKnifeRect() { return knifeRect; }
    void deactivateKnife() { knifeActive = false; }

    void hitWithSnow() override { health--; }
    int getPhase() { 
        float healthPercent = (float)health / maxHealth;
        if (healthPercent > 0.66f) return 1;
        if (healthPercent > 0.33f) return 2;
        return 3;
    }

    static bool loadTexture();

private:
    static sf::Texture gTexture;
    sf::Sprite gSprite;

    int health;
    int maxHealth;
    int phase; // 1, 2, or 3
    float attackTimer;
    float playerX;
    float playerY;

    void fireRockets();
    void updatePhase();
    void throwKnife(float playerX, float playerY);

    int addRocket(float centerX, float centerY, float dirX, float dirY, float speed);

    // Knife
    sf::FloatRect knifeRect;
    float knifeSpeedX;
    float knifeSpeedY;
    float knifeTimer;
};