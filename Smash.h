#pragma once
#include "Character.h"
#include "Platform.h"
#include "Enemy.h"
#include "Snowball.h"
#include "Gem.h"

class Smash : public Character {
public:
    Smash(int playerNumber = 1); // 1 or 2
    void Update(Platform** platforms, int platformCount, Enemy** enemies, int enemyCount);
    void Draw(sf::RenderWindow& window, bool showHitbox) override;
    int getLives() { return lives; }
    bool isGameOver() { return lives <= 0; }
    int getScore() { return score; }
    int getGems() { return gemCurrency; }
    void reset() override;
    void hit() override;
    sf::FloatRect getRect() override { return rect; }

    Snowball* snowballs[100000] = { nullptr };
    int snowballCount = 0;

    // Shared gems for both players
    static Gem* sharedGems[1000];
    static int sharedGemCount;
    static void clearGems();

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float velocityY;
    bool isGrounded;
    bool facingRight;
    int lives;
    int score;
    int gemCurrency;
    float invincibleTimer;
    bool shootHeld;
    int playerNum; // 1 or 2

    // Controls
    sf::Keyboard::Key moveLeft;
    sf::Keyboard::Key moveRight;
    sf::Keyboard::Key jumpKey;
    sf::Keyboard::Key shootKey;

    void checkPlatformCollision(sf::FloatRect p);
    void checkEnemyCollision(Enemy** enemies, int enemyCount);
    void checkSnowballEnemyCollision(Enemy** enemies, int enemyCount);
    void throwSnowball();
};