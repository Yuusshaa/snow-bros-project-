#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Platform.h"
#include "Animation.h"

class Botom : public Enemy {
public:
    bool isGrounded;
    Botom(float x, float y);
    void Update(Platform** platforms, int platformCount) override;
    void Draw(sf::RenderWindow& window, bool showHitbox) override;
    void checkPlatformCollision(sf::FloatRect p);

    // call once before creating any Botom — loads the sprite sheet
    static sf::Texture texture;  // declaration only in .h
    static sf::Texture snowballtexture;
    static bool loadTexture();
    Animation* currentAnim;


private:
    // --- physics ---
    float speed;
    int direction;
    int directionTimer;

    float jumpTimer;
    Animation halfAnim;
    Animation fullAnim;

    // --- sprite sheet (shared across all Botom instances) ---
protected:

    // --- animations ---
    // replace these startX/startY/frameWidth/frameHeight/frameCount values
    // with the real pixel coords you measure from your sheet
    Animation walkAnim;    // normal walking
    Animation idleAnim;  // fully encased in snow
   // one snowball hit
    Animation rollAnim;  

    Animation jumpingAnim;// rolling after kick

   
};