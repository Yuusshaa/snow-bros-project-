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
#include "Gem.h"
#include "1P2PScreen.h"
#include "backgrounds.h"
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
    srand((unsigned int)time(0));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("Silkscreen-Regular.ttf");

    // ---- 1P/2P SCREEN ----
    PlayerScreen playerScreen(window);
    int numPlayers = playerScreen.run();
    if (numPlayers == 0) return 0;

    // ---- LOGIN ----
    Login auth("users.txt");
    LoginScreen loginScreen(window, auth);

    loginScreen.showSplash();

    // Player 1 login
    sf::Text loginTitle;
    loginTitle.setFont(font);
    loginTitle.setCharacterSize(40);
    loginTitle.setFillColor(sf::Color::White);
    loginTitle.setPosition(200, 50);
    loginTitle.setString("PLAYER 1 - LOGIN");
    window.clear(sf::Color::Black);
    window.draw(loginTitle);
    window.display();

    bool loggedIn1 = loginScreen.run();
    if (!loggedIn1) return 0;

    // Player 2 login if 2 player mode
    if (numPlayers == 2) {
        loginScreen.clearInputs();  // Clear inputs for Player 2
        loginTitle.setString("PLAYER 2 - LOGIN");
        window.clear(sf::Color::Black);
        window.draw(loginTitle);
        window.display();

        bool loggedIn2 = loginScreen.run();
        if (!loggedIn2) return 0;
    }

    // ---- SETUP ----
    Character* characters[10] = { nullptr };
    int characterCount = 0;
    characters[characterCount++] = new Smash(1);
    if (numPlayers == 2)
        characters[characterCount++] = new Smash(2);

    int currentLevel = 5;

    Platform* platforms[15] = { nullptr };
    int platformCount = 0;
    spawnPlatforms(platforms, platformCount, currentLevel);

    Enemy* enemies[20] = { nullptr };
    int enemyCount = 0;

    int maxLevels = 5;
    bool levelComplete = false;
    float levelCompleteTimer = 1.0f;

    spawnEnemies(enemies, enemyCount, currentLevel);

    Background background;
    background.loadLevel(currentLevel);

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
        bool allPlayersGameOver = true;
        for (int i = 0; i < characterCount; i++) {
            if (!characters[i]->isGameOver()) {
                allPlayersGameOver = false;
                break;
            }
        }

        if (allPlayersGameOver) {
            window.clear(sf::Color::Black);
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("GAME OVER\nP1 Score: " + std::to_string(characters[0]->getScore()));
            gameOverText.setCharacterSize(50);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(200, 200);
            window.draw(gameOverText);

            if (characterCount > 1) {
                sf::Text p2ScoreText;
                p2ScoreText.setFont(font);
                p2ScoreText.setString("P2 Score: " + std::to_string(characters[1]->getScore()));
                p2ScoreText.setCharacterSize(50);
                p2ScoreText.setFillColor(sf::Color::Cyan);
                p2ScoreText.setPosition(200, 320);
                window.draw(p2ScoreText);
            }

            window.display();
            continue;
        }

        // ---- LEVEL COMPLETE ----
        if (levelComplete) {
            levelCompleteTimer--;
            window.clear(sf::Color::Black);

            sf::Text lvlText;
            lvlText.setFont(font);
            lvlText.setString("LEVEL " + std::to_string(currentLevel) + " COMPLETE!\nP1 Score: " + std::to_string(characters[0]->getScore()));
            lvlText.setCharacterSize(45);
            lvlText.setFillColor(sf::Color::Green);
            lvlText.setPosition(150, 200);
            window.draw(lvlText);

            if (characterCount > 1) {
                sf::Text p2lvlText;
                p2lvlText.setFont(font);
                p2lvlText.setString("P2 Score: " + std::to_string(characters[1]->getScore()));
                p2lvlText.setCharacterSize(45);
                p2lvlText.setFillColor(sf::Color::Cyan);
                p2lvlText.setPosition(150, 320);
                window.draw(p2lvlText);
            }

            window.display();

            if (levelCompleteTimer <= 0) {
                currentLevel++;
                if (currentLevel > maxLevels) {
                    window.clear(sf::Color::Black);
                    sf::Text winText;
                    winText.setFont(font);
                    winText.setString("YOU WIN!\nP1 Score: " + std::to_string(characters[0]->getScore()));
                    winText.setCharacterSize(50);
                    winText.setFillColor(sf::Color::Yellow);
                    winText.setPosition(200, 200);
                    window.draw(winText);

                    if (characterCount > 1) {
                        sf::Text p2WinText;
                        p2WinText.setFont(font);
                        p2WinText.setString("P2 Score: " + std::to_string(characters[1]->getScore()));
                        p2WinText.setCharacterSize(50);
                        p2WinText.setFillColor(sf::Color::Cyan);
                        p2WinText.setPosition(200, 320);
                        window.draw(p2WinText);
                    }

                    window.display();
                    sf::sleep(sf::seconds(3));
                    window.close();
                }
                else {
                    levelComplete = false;
                    spawnPlatforms(platforms, platformCount, currentLevel);
                    spawnEnemies(enemies, enemyCount, currentLevel);
                    background.loadLevel(currentLevel);
                    for (int i = 0; i < characterCount; i++)
                        characters[i]->reset();
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

        // Check active gems (shared between all players)
        int activeGemCount = 0;
        for (int i = 0; i < Smash::sharedGemCount; i++) {
            if (Smash::sharedGems[i]->isActive())
                activeGemCount++;
        }

        if (allDead && activeGemCount == 0 && enemyCount > 0) {
            levelComplete = true;
            levelCompleteTimer = 120.f;
        }

        // ---- UPDATE PLAYERS ----
        for (int i = 0; i < characterCount; i++) {
            if (!characters[i]->isGameOver())
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

                // Knife hits any player
                if (mogera->knifeActive) {
                    sf::FloatRect k = mogera->getKnifeRect();
                    for (int p = 0; p < characterCount; p++) {
                        sf::FloatRect pRect = characters[p]->getRect();
                        bool ox = k.left < pRect.left + pRect.width && k.left + k.width > pRect.left;
                        bool oy = k.top < pRect.top + pRect.height && k.top + k.height > pRect.top;
                        if (ox && oy) {
                            mogera->deactivateKnife();
                            characters[p]->hit();
                            break;
                        }
                    }
                }

                // Children hit any player
                for (int c = 0; c < mogera->childCount; c++) {
                    if (mogera->children[c]->isDead()) continue;
                    sf::FloatRect cRect = mogera->children[c]->getRect();
                    for (int p = 0; p < characterCount; p++) {
                        sf::FloatRect pRect = characters[p]->getRect();
                        bool ox = cRect.left < pRect.left + pRect.width && cRect.left + cRect.width > pRect.left;
                        bool oy = cRect.top < pRect.top + pRect.height && cRect.top + cRect.height > pRect.top;
                        if (ox && oy) {
                            characters[p]->hit();
                            mogera->children[c]->kill();
                            break;
                        }
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
                    for (int p = 0; p < characterCount; p++) {
                        sf::FloatRect pRect = characters[p]->getRect();
                        bool ox = k.left < pRect.left + pRect.width && k.left + k.width > pRect.left;
                        bool oy = k.top < pRect.top + pRect.height && k.top + k.height > pRect.top;
                        if (ox && oy) {
                            tornado->knifeActive = false;
                            characters[p]->hit();
                            break;
                        }
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
        // P1 top left
        sf::Text livesText;
        livesText.setFont(font);
        livesText.setString("P1 Lives: " + std::to_string(characters[0]->getLives()));
        livesText.setCharacterSize(25);
        livesText.setFillColor(sf::Color::White);
        livesText.setPosition(10, 10);
        window.draw(livesText);

        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("P1 Score: " + std::to_string(characters[0]->getScore()));
        scoreText.setCharacterSize(25);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 40);
        window.draw(scoreText);

        sf::Text gemsText;
        gemsText.setFont(font);
        gemsText.setString("P1 Gems: " + std::to_string(dynamic_cast<Smash*>(characters[0])->getGems()));
        gemsText.setCharacterSize(25);
        gemsText.setFillColor(sf::Color(255, 215, 0));
        gemsText.setPosition(10, 70);
        window.draw(gemsText);

        // P2 top right
        if (characterCount > 1) {
            sf::Text lives2Text;
            lives2Text.setFont(font);
            lives2Text.setString("P2 Lives: " + std::to_string(characters[1]->getLives()));
            lives2Text.setCharacterSize(25);
            lives2Text.setFillColor(sf::Color::Cyan);
            lives2Text.setPosition(590, 10);
            window.draw(lives2Text);

            sf::Text score2Text;
            score2Text.setFont(font);
            score2Text.setString("P2 Score: " + std::to_string(characters[1]->getScore()));
            score2Text.setCharacterSize(25);
            score2Text.setFillColor(sf::Color::Cyan);
            score2Text.setPosition(590, 40);
            window.draw(score2Text);

            sf::Text gems2Text;
            gems2Text.setFont(font);
            gems2Text.setString("P2 Gems: " + std::to_string(dynamic_cast<Smash*>(characters[1])->getGems()));
            gems2Text.setCharacterSize(25);
            gems2Text.setFillColor(sf::Color(255, 215, 0));
            gems2Text.setPosition(590, 70);
            window.draw(gems2Text);
        }

        // Level top center
        sf::Text levelText;
        levelText.setFont(font);
        levelText.setString("Level: " + std::to_string(currentLevel));
        levelText.setCharacterSize(25);
        levelText.setFillColor(sf::Color::White);
        levelText.setPosition(350, 10);
        window.draw(levelText);

        window.display();
    }

    for (int i = 0; i < characterCount; i++) delete characters[i];
    for (int i = 0; i < platformCount; i++) delete platforms[i];
    for (int i = 0; i < enemyCount; i++) delete enemies[i];
}