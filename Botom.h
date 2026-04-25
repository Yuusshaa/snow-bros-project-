#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Platform.h"
#include "Animation.h"

class Botom : public Enemy {
public:
    Botom(float x, float y);
    void Update(Platform** platforms, int platformCount) override;
    void Draw(sf::RenderWindow& window, bool showHitbox) override;
    void checkPlatformCollision(sf::FloatRect p);

    // call once before creating any Botom — loads the sprite sheet
    static sf::Texture texture;  // declaration only in .h
    static bool loadTexture();

private:
    // --- physics ---
    float speed;
    int direction;
    int directionTimer;
    bool isGrounded;
    float jumpTimer;

    // --- sprite sheet (shared across all Botom instances) ---
    

    // --- animations ---
    // replace these startX/startY/frameWidth/frameHeight/frameCount values
    // with the real pixel coords you measure from your sheet
    Animation walkAnim;    // normal walking
    Animation idleAnim;  // fully encased in snow
    Animation halfAnim;    // one snowball hit
    Animation rollAnim;    // rolling after kick
    Animation* currentAnim;
};