#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Smash.h"
#include "Platform.h"
#include "Botom.h"
#include "Flyingshit.h"
#include "Tornado.h"
#include"LoginScreen.h"
#include"Login.h"
#include <cstdlib>
#include <ctime>
#include <string>



void spawnPlatforms(Platform** platforms, int& platformCount, int level) {
    // clear old platforms
    for (int platformIndex = 0; platformIndex < platformCount; platformIndex++) {
        delete platforms[platformIndex];
        platforms[platformIndex] = nullptr;
    }
    platformCount = 0;

  
    platforms[platformCount++] = new Platform(0, 560, 800, 20);

    if (level == 1) {
       platforms[platformCount++] = new Platform(20, 430, 280, 15);
        platforms[platformCount++] = new Platform(500, 430, 280, 15);
        platforms[platformCount++] = new Platform(200, 300, 400, 15);
        platforms[platformCount++] = new Platform(200, 170, 400, 15);
    }
    else if (level == 2) {
        platforms[platformCount++] = new Platform(50, 450, 200, 15);
        platforms[platformCount++] = new Platform(350, 380, 150, 15);
        platforms[platformCount++] = new Platform(600, 300, 180, 15);
        platforms[platformCount++] = new Platform(100, 220, 250, 15);
        platforms[platformCount++] = new Platform(450, 160, 200, 15);
    }
    else if (level == 3) {
        platforms[platformCount++] = new Platform(0, 400, 150, 15);
        platforms[platformCount++] = new Platform(650, 400, 150, 15);
        platforms[platformCount++] = new Platform(250, 320, 300, 15);
        platforms[platformCount++] = new Platform(100, 210, 180, 15);
        platforms[platformCount++] = new Platform(520, 210, 180, 15);
        platforms[platformCount++] = new Platform(300, 120, 200, 15);

    }
    else if (level == 4) {
        // Top
        platforms[platformCount++] = new Platform(50, 150, 300, 15); // top left
        platforms[platformCount++] = new Platform(450, 150, 300, 15); // top right

        // Sides (tall thin platforms acting as walls)


        // Bottom of the rectangle
        platforms[platformCount++] = new Platform(50, 420, 300, 15); // bottom left
        platforms[platformCount++] = new Platform(450, 420, 300, 15); // bottom right

        // Inner platforms (the two small ones in your sketch)
        platforms[platformCount++] = new Platform(150, 300, 200, 15); // inner mid left
        platforms[platformCount++] = new Platform(450, 300, 200, 15); // inner mid right

 /*       platforms[platformCount++] = new Platform(50, 150, 300, 15); // top left long
        platforms[platformCount++] = new Platform(450, 150, 300, 15); // top right long
        platforms[platformCount++] = new Platform(150, 300, 200, 15); // mid left
        platforms[platformCount++] = new Platform(150, 420, 200, 15); // lower left
        platforms[platformCount++] = new Platform(500, 420, 200, 15); // lower right
        platforms[platformCount++] = new Platform(500, 300, 200, 15); // mid right*/
    }

}

void spawnEnemies(Enemy** enemies, int& enemyCount, int level) {

    for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++) {
        delete enemies[enemyIndex];
        enemies[enemyIndex] = nullptr;
    }
    enemyCount = 0;

    if (level == 1) {
        enemies[enemyCount++] = new Botom(300, 100);
        enemies[enemyCount++] = new Botom(500, 100);

    }
    else if (level == 2) {
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new Botom(400, 100);
        enemies[enemyCount++] = new FlyingFoogaFoog(600, 100);
        enemies[enemyCount++] = new FlyingFoogaFoog(600, 100);

    }
    else if (level == 3) {
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new FlyingFoogaFoog(400, 100);
        enemies[enemyCount++] = new FlyingFoogaFoog(600, 100);
        enemies[enemyCount++] = new Tornado(499, 120);
    }
    else if (level == 4) {
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new Tornado(499, 120);

    }

}

int main() {
    Botom::loadTexture();
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    sf::Font font;

    font.loadFromFile("Silkscreen-Regular.ttf");

    Login auth("users.txt");
    LoginScreen loginScreen(window, auth);
    loginScreen.showSplash();
    bool loggedIn = loginScreen.run();
    if (!loggedIn) return 0;


    Character* characters[10] = { nullptr };
    int characterCount = 0;
    characters[characterCount++] = new Smash();

    int currentLevel = 1;

    Platform* platforms[15] = { nullptr };
    int platformCount = 0;
    spawnPlatforms(platforms, platformCount, currentLevel);  

    Enemy* enemies[20] = { nullptr };
    int enemyCount = 0;

    
    int maxLevels = 4;
    bool levelComplete = false;
    float levelCompleteTimer = 1.0f;

    spawnEnemies(enemies, enemyCount, currentLevel);

    bool showHitboxes = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::H)) {
                showHitboxes = !showHitboxes;
            }
        }

        // Game over screen
        if (characters[0]->isGameOver()) {
            window.clear(sf::Color::Black);
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("GAME OVER\nScore: " + std::to_string(characters[0]->getScore()));
            gameOverText.setCharacterSize(60);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(200, 250);
            window.draw(gameOverText);
            window.display();
            continue;
        }
        // Level complete screen
        if (levelComplete) {
            levelCompleteTimer--;

            window.clear(sf::Color::Black);
            sf::Text lvlText;
            lvlText.setFont(font);
            lvlText.setString(std::string("LEVEL ") + std::to_string(currentLevel) + " COMPLETE!\n" + "Score: " + std::to_string(characters[0]->getScore()));
            lvlText.setCharacterSize(50);
            lvlText.setFillColor(sf::Color::Green);
            lvlText.setPosition(150, 250);
            window.draw(lvlText);
            window.display();

            // 2sec timer
            if (levelCompleteTimer <= 0) {
                currentLevel++;

                if (currentLevel > maxLevels) {
                    //endcresds
                    window.clear(sf::Color::Black);
                    sf::Text winText;
                    winText.setFont(font);
                    winText.setString(std::string("YOU WIN!\n") + "Final Score : " + std::to_string(characters[0]->getScore()));
                    winText.setCharacterSize(60);
                    winText.setFillColor(sf::Color::Yellow);
                    winText.setPosition(200, 250);
                    window.draw(winText);
                    window.display();
                    sf::sleep(sf::seconds(3));
                    window.close();
                }
                else {
                    levelComplete = false;
                    spawnPlatforms(platforms, platformCount, currentLevel);
                    spawnEnemies(enemies, enemyCount, currentLevel);
                    characters[0]->reset();
                }
            }
            continue;
        }

        // Checker for if all enemies died
        bool allDead = true;
        for (int i = 0; i < enemyCount; i++) {
            if (!enemies[i]->isDead()) {
                allDead = false;
                break;
            }
        }

        if (allDead && enemyCount > 0) {
            levelComplete = true;
            levelCompleteTimer = 120.f; // 2sec before new screen loads
        }

        // Normal update
        for (int characterIndex = 0; characterIndex < characterCount; characterIndex++) {
            characters[characterIndex]->Update(platforms, platformCount, enemies, enemyCount);
        }
        for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++) {
            enemies[enemyIndex]->Update(platforms, platformCount);
        }
        sf::FloatRect playerRect = characters[0]->getRect();

        for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++) {
            Tornado* tornadoEnemy = dynamic_cast<Tornado*>(enemies[enemyIndex]);
            if (!tornadoEnemy) 
                continue;

            tornadoEnemy->Update(platforms, platformCount,
                playerRect.left + playerRect.width / 2,
                playerRect.top + playerRect.height / 2);

            // Check knife hits player
            if (tornadoEnemy->knifeActive) {
                sf::FloatRect knifeRect = tornadoEnemy->getKnifeRect();
                bool overlapX = (knifeRect.left < playerRect.left + playerRect.width) && 
                                (knifeRect.left + knifeRect.width > playerRect.left);
                bool overlapY = (knifeRect.top < playerRect.top + playerRect.height) && 
                                (knifeRect.top + knifeRect.height > playerRect.top);
                if (overlapX && overlapY) {
                    tornadoEnemy->knifeActive = false;
                    characters[0]->hit();
                }
            }
        }

        window.clear(sf::Color(135, 206, 235));

        for (int platformIndex = 0; platformIndex < platformCount; platformIndex++) {
            platforms[platformIndex]->Draw(window, showHitboxes);
        }
        for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++) {
            enemies[enemyIndex]->Draw(window, showHitboxes);
        }
        for (int characterIndex = 0; characterIndex < characterCount; characterIndex++) {
            characters[characterIndex]->Draw(window, showHitboxes);
        }

        // HUD
        sf::Text livesText;
        livesText.setFont(font);
        livesText.setString("Lives: " + std::to_string(characters[0]->getLives()));
        livesText.setCharacterSize(30);
        livesText.setFillColor(sf::Color::White);
        livesText.setPosition(10, 10);
        window.draw(livesText);

        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(characters[0]->getScore()));
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 50);
        window.draw(scoreText);

        sf::Text levelText;
        levelText.setFont(font);
        levelText.setString("Level: " + std::to_string(currentLevel));
        levelText.setCharacterSize(30);
        levelText.setFillColor(sf::Color::White);
        levelText.setPosition(350, 10);
        window.draw(levelText);

        window.display();
    }

    for (int characterIndex = 0; characterIndex < characterCount; characterIndex++) 
        delete characters[characterIndex];


    for (int platformIndex = 0; platformIndex < platformCount; platformIndex++) 
        delete platforms[platformIndex];

    for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++) 
        delete enemies[enemyIndex];
}