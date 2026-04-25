#pragma once
#include "Character.h"
#include "Platform.h"
#include "Enemy.h"
#include "Snowball.h"

class Smash : public Character {
public:
    Smash();
    void Update(Platform** platforms, int platformCount, Enemy** enemies, int enemyCount);
    void Draw(sf::RenderWindow& window, bool showHitbox) override;
    int getLives() { return lives; }
    bool isGameOver() { return lives <= 0; }
    int getScore() { return score; }


    Snowball* snowballs[100000] = { nullptr };
    int snowballCount = 0;

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float velocityY;
    bool isGrounded;
    bool facingRight;
    int lives;
    int score;
    float invincibleTimer;
    bool spaceHeld;


    void checkPlatformCollision(sf::FloatRect p);
    void checkEnemyCollision(Enemy** enemies, int enemyCount);
    void checkSnowballEnemyCollision(Enemy** enemies, int enemyCount);
    void throwSnowball();
    void reset();
    sf::FloatRect getRect() override { return rect; }
    void hit() override;
};