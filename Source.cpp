#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Smash.h"
#include "Platform.h"
#include "Botom.h"
#include "Flyingshit.h"
#include "Tornado.h"
#include "LoginScreen.h"
#include "Login.h"
#include "Mogera.h"
#include"1P2PScreen.h"
#include"backgrounds.h"
#include <cstdlib>
#include <ctime>
#include <string>

void spawnPlatforms(Platform** platforms, int& platformCount, int level) {
    for (int i = 0; i < platformCount; i++) {
        delete platforms[i];
        platforms[i] = nullptr;
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
        platforms[platformCount++] = new Platform(50, 150, 300, 15);
        platforms[platformCount++] = new Platform(450, 150, 300, 15);
        platforms[platformCount++] = new Platform(50, 420, 300, 15);
        platforms[platformCount++] = new Platform(450, 420, 300, 15);
        platforms[platformCount++] = new Platform(150, 300, 200, 15);
        platforms[platformCount++] = new Platform(450, 300, 200, 15);
    }
    else if (level == 5) {
        platforms[platformCount++] = new Platform(0, 380, 280, 15);
        platforms[platformCount++] = new Platform(500, 100, 300, 15);
        platforms[platformCount++] = new Platform(400, 200, 300, 15);
        platforms[platformCount++] = new Platform(500, 300, 300, 15);
        platforms[platformCount++] = new Platform(400, 400, 300, 15);
        platforms[platformCount++] = new Platform(500, 500, 300, 15);
    }
}

void spawnEnemies(Enemy** enemies, int& enemyCount, int level) {
    for (int i = 0; i < enemyCount; i++) {
        delete enemies[i];
        enemies[i] = nullptr;
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
    else if (level == 5) {
        enemies[enemyCount++] = new Mogera(20, 320);
    }
}

int main() {
    Botom::loadTexture();
    FlyingFoogaFoog::loadFlyTexture();
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("Silkscreen-Regular.ttf");

    Login auth("users.txt");
    LoginScreen loginScreen(window, auth);
    loginScreen.showSplash();


    PlayerScreen playerScreen(window);
    bool playerSelected = playerScreen.run();
    if (!playerSelected) return 0;


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
    //ehheehhehehehehehee
    int maxLevels = 5;
    bool levelComplete = false;
    float levelCompleteTimer = 1.0f;

    spawnEnemies(enemies, enemyCount, currentLevel);

    /////////////////////////////////////////
    Background background;
    background.loadLevel(currentLevel);
    /////////////////////////////////////////





    bool showHitboxes = false;

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        background.update(deltaTime);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H)
                showHitboxes = !showHitboxes;
        }

        // ---- GAME OVER ----
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

        // ---- LEVEL COMPLETE ----
        if (levelComplete) {
            levelCompleteTimer--;
            window.clear(sf::Color::Black);
            sf::Text lvlText;
            lvlText.setFont(font);
            lvlText.setString("LEVEL " + std::to_string(currentLevel) + " COMPLETE!\nScore: " + std::to_string(characters[0]->getScore()));
            lvlText.setCharacterSize(50);
            lvlText.setFillColor(sf::Color::Green);
            lvlText.setPosition(150, 250);
            window.draw(lvlText);
            window.display();

            if (levelCompleteTimer <= 0) {
                currentLevel++;
                if (currentLevel > maxLevels) {
                    window.clear(sf::Color::Black);
                    sf::Text winText;
                    winText.setFont(font);
                    winText.setString("YOU WIN!\nFinal Score: " + std::to_string(characters[0]->getScore()));
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
                    background.loadLevel(currentLevel);
                    characters[0]->reset();
                }
            }
            continue;
        }

        // ---- ALL ENEMIES DEAD CHECK ----
        bool allDead = true;
        for (int i = 0; i < enemyCount; i++) {
            if (!enemies[i]->isDead()) {
                allDead = false;
                break;
            }

            // Also check Mogera's children
            Mogera* mogera = dynamic_cast<Mogera*>(enemies[i]);
            if (mogera) {
                for (int c = 0; c < mogera->childCount; c++) {
                    if (!mogera->children[c]->isDead()) {
                        allDead = false;
                        break;
                    }
                }
                if (!allDead) break;
            }
        }

        // Count active gems
        Smash* playerSmash = dynamic_cast<Smash*>(characters[0]);
        int activeGemCount = 0;
        if (playerSmash) {
            for (int i = 0; i < playerSmash->gemCount; i++) {
                if (playerSmash->gems[i]->isActive()) {
                    activeGemCount++;
                }
            }
        }

        // Level complete only if all enemies dead AND all gems collected
        if (allDead && activeGemCount == 0 && enemyCount > 0) {
            levelComplete = true;
            levelCompleteTimer = 120.f;
        }

        // ---- UPDATE PLAYER ----
        for (int i = 0; i < characterCount; i++) {
            characters[i]->Update(platforms, platformCount, enemies, enemyCount);
        }

        // ---- UPDATE ENEMIES ----
        sf::FloatRect playerRect = characters[0]->getRect();
        float playerCX = playerRect.left + playerRect.width / 2;
        float playerCY = playerRect.top + playerRect.height / 2;

        for (int i = 0; i < enemyCount; i++) {

            // --- MOGERA ---
            Mogera* mogera = dynamic_cast<Mogera*>(enemies[i]);
            if (mogera) {
                mogera->Update(platforms, platformCount, playerCX, playerCY);

                // Knife hits player
                if (mogera->knifeActive) {
                    sf::FloatRect k = mogera->getKnifeRect();
                    bool ox = k.left < playerRect.left + playerRect.width && k.left + k.width > playerRect.left;
                    bool oy = k.top < playerRect.top + playerRect.height && k.top + k.height > playerRect.top;
                    if (ox && oy) {
                        mogera->deactivateKnife();
                        characters[0]->hit();
                    }
                }

                // Children hit player
                for (int c = 0; c < mogera->childCount; c++) {
                    if (mogera->children[c]->isDead()) continue;
                    sf::FloatRect cRect = mogera->children[c]->getRect();
                    bool ox = cRect.left < playerRect.left + playerRect.width && cRect.left + cRect.width > playerRect.left;
                    bool oy = cRect.top < playerRect.top + playerRect.height && cRect.top + cRect.height > playerRect.top;
                    if (ox && oy) {
                        characters[0]->hit();
                        mogera->children[c]->kill();
                    }
                }
                continue;
            }

            // --- TORNADO ---
            Tornado* tornado = dynamic_cast<Tornado*>(enemies[i]);
            if (tornado) {
                tornado->Update(platforms, platformCount, playerCX, playerCY);

                if (tornado->knifeActive) {
                    sf::FloatRect k = tornado->getKnifeRect();
                    bool ox = k.left < playerRect.left + playerRect.width && k.left + k.width > playerRect.left;
                    bool oy = k.top < playerRect.top + playerRect.height && k.top + k.height > playerRect.top;
                    if (ox && oy) {
                        tornado->knifeActive = false;
                        characters[0]->hit();
                    }
                }
                continue;
            }

            // --- ALL OTHER ENEMIES ---
            enemies[i]->Update(platforms, platformCount);
        }

        // ---- DRAW ----
        window.clear();
        background.draw(window);

        for (int i = 0; i < platformCount; i++)
            platforms[i]->Draw(window, showHitboxes);

        for (int i = 0; i < enemyCount; i++)
            enemies[i]->Draw(window, showHitboxes);

        for (int i = 0; i < characterCount; i++)
            characters[i]->Draw(window, showHitboxes);

        // ---- HUD ----
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

        sf::Text gemsText;
        gemsText.setFont(font);
        gemsText.setString("Gems: " + std::to_string(dynamic_cast<Smash*>(characters[0])->getGems()));
        gemsText.setCharacterSize(30);
        gemsText.setFillColor(sf::Color(255, 215, 0));
        gemsText.setPosition(350, 50);
        window.draw(gemsText);

        window.display();
    }

    for (int i = 0; i < characterCount; i++) delete characters[i];
    for (int i = 0; i < platformCount; i++) delete platforms[i];
    for (int i = 0; i < enemyCount; i++) delete enemies[i];
}