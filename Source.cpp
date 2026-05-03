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
#include "Gamakichi.h"
#include "Gem.h"
#include "1P2PScreen.h"
#include "backgrounds.h"
#include "SoundManager.h"
#include "leaderboard.h"
#include "store.h"
#include "instructions.h"
#include "LevelSelectionScreen.h"
#include "Pause.h"
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

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
    else if (level == 6) {
        platforms[platformCount++] = new Platform(50, 130, 180, 15);
        platforms[platformCount++] = new Platform(225, 215, 175, 15);
        platforms[platformCount++] = new Platform(400, 270, 180, 15);
        platforms[platformCount++] = new Platform(50, 450, 260, 15);
        platforms[platformCount++] = new Platform(450, 450, 260, 15);
        platforms[platformCount++] = new Platform(50, 375, 260, 15);
        platforms[platformCount++] = new Platform(450, 375, 260, 15);
    }
    else if (level == 7) {
        platforms[platformCount++] = new Platform(80, 180, 230, 20);
        platforms[platformCount++] = new Platform(440, 180, 230, 20);
        platforms[platformCount++] = new Platform(110, 330, 160, 20);
        platforms[platformCount++] = new Platform(530, 330, 130, 20);
        platforms[platformCount++] = new Platform(140, 480, 460, 20);
    }
    else if (level == 8) {
        platforms[platformCount++] = new Platform(50, 150, 120, 20);
        platforms[platformCount++] = new Platform(140, 250, 120, 20);
        platforms[platformCount++] = new Platform(240, 350, 120, 20);
        platforms[platformCount++] = new Platform(50, 450, 120, 20);
        platforms[platformCount++] = new Platform(470, 200, 120, 20);
        platforms[platformCount++] = new Platform(570, 280, 120, 20);
        platforms[platformCount++] = new Platform(620, 430, 120, 20);
    }
    else if (level == 9) {
        platforms[platformCount++] = new Platform(350, 150, 100, 20);
        platforms[platformCount++] = new Platform(200, 280, 100, 20);
        platforms[platformCount++] = new Platform(500, 280, 100, 20);
        platforms[platformCount++] = new Platform(350, 410, 100, 20);
        platforms[platformCount++] = new Platform(170, 520, 100, 20);
        platforms[platformCount++] = new Platform(530, 520, 100, 20);
    }
    else if (level == 10) {
        // Boss level — platforms on sides only so rockets have room
        platforms[platformCount++] = new Platform(0, 400, 150, 15);
        platforms[platformCount++] = new Platform(650, 400, 150, 15);
        platforms[platformCount++] = new Platform(0, 250, 120, 15);
        platforms[platformCount++] = new Platform(680, 250, 120, 15);
        platforms[platformCount++] = new Platform(250, 200, 300, 15);
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
    }
    else if (level == 2) {
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new FlyingFoogaFoog(600, 100);
    }
    else if (level == 3) {
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new FlyingFoogaFoog(400, 100);
    }
    else if (level == 4) {
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new Tornado(499, 120);
    }
    else if (level == 5) {
        enemies[enemyCount++] = new Mogera(20, 320);
    }
    else if (level == 6) {
        enemies[enemyCount++] = new Tornado(500, 220);
        enemies[enemyCount++] = new Tornado(499, 120);
    }
    else if (level == 7) {
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new Tornado(499, 120);
        enemies[enemyCount++] = new Tornado(500, 220);
        enemies[enemyCount++] = new FlyingFoogaFoog(600, 100);
    }
    else if (level == 8) {
        enemies[enemyCount++] = new Tornado(499, 120);
        enemies[enemyCount++] = new Tornado(499, 120);
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new FlyingFoogaFoog(600, 100);
        enemies[enemyCount++] = new FlyingFoogaFoog(600, 100);
    }
    else if (level == 9) {
        enemies[enemyCount++] = new Mogera(20, 320);
        enemies[enemyCount++] = new Tornado(499, 120);
        enemies[enemyCount++] = new FlyingFoogaFoog(600, 100);
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new Botom(200, 100);
        enemies[enemyCount++] = new Tornado(499, 120);
        enemies[enemyCount++] = new FlyingFoogaFoog(600, 100);
    }
    else if (level == 10) {
        enemies[enemyCount++] = new Gamakichi();
    }
}

int main() {
    Botom::loadTexture();
    FlyingFoogaFoog::loadFlyTexture();
    Mogera::loadTexture();
    Tornado::loadTexture();
    Gamakichi::loadTexture();
    srand((unsigned int)time(0));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    SoundManager::get().load();

    sf::Font font;
    font.loadFromFile("Silkscreen-Regular.ttf");

    PauseMenu pauseMenu(window);
    Store store(window);

    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("pause.png");
    sf::Sprite pauseSprite;
    pauseSprite.setTexture(pauseTexture);
    pauseSprite.setScale(40.f / pauseTexture.getSize().x, 40.f / pauseTexture.getSize().y);
    pauseSprite.setPosition(750, 90);

    bool paused = false;

    Leaderboard leaderboard(window, "leaderboard.txt");
    Instructions instructions(window);

    Login auth("users.txt");
    LoginScreen loginScreen(window, auth);
    loginScreen.showSplash();

    bool proceed = instructions.run(leaderboard, loginScreen, auth);
    if (!proceed) return 0;

    LevelSelection levelSelect(window);
    int selectedLevel = levelSelect.run();
    if (selectedLevel == 0) return 0;

    PlayerScreen playerScreen(window);
    int numPlayers = playerScreen.run();
    if (numPlayers == 0) return 0;

    loginScreen.setTitle("1ST PLAYER LOGIN");
    bool loggedIn1 = loginScreen.run();
    if (!loggedIn1) return 0;

    string player1Username = auth.getCurrentLoggedInUser();

    if (numPlayers == 2) {
        loginScreen.clearInputs();
        loginScreen.setTitle("2ND PLAYER LOGIN");
        while (true) {
            bool loggedIn2 = loginScreen.run();
            if (!loggedIn2) return 0;
            if (auth.getCurrentLoggedInUser() == player1Username) {
                loginScreen.clearInputs();
                loginScreen.setStatusMessage("Same account as P1! Use a different account.");
            }
            else break;
        }
    }

    Character* characters[10] = { nullptr };
    int characterCount = 0;
    characters[characterCount++] = new Smash(1);
    if (numPlayers == 2)
        characters[characterCount++] = new Smash(2);

    int currentLevel = selectedLevel;

    Platform* platforms[15] = { nullptr };
    int platformCount = 0;
    spawnPlatforms(platforms, platformCount, currentLevel);

    Enemy* enemies[20] = { nullptr };
    int enemyCount = 0;

    int maxLevels = 10;
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
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                if (pauseSprite.getGlobalBounds().contains(mouse))
                    paused = true;
            }
        }

        if (paused) {
            int choice = pauseMenu.run();
            if (choice == 1)
                paused = false;
            else if (choice == 2) {
                Smash* player = (Smash*)characters[0];
                store.run(*player);
                paused = true;
            }
            else if (choice == 3) {
                window.close();
                break;
            }
            continue;
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
            gameOverText.setString("GAME OVER\nP1 Score: " + to_string(characters[0]->getScore()));
            gameOverText.setCharacterSize(50);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(200, 200);
            window.draw(gameOverText);
            leaderboard.saveScore(auth.getCurrentLoggedInUser(), characters[0]->getScore(), currentLevel);

            if (characterCount > 1) {
                sf::Text p2ScoreText;
                p2ScoreText.setFont(font);
                p2ScoreText.setString("P2 Score: " + to_string(characters[1]->getScore()));
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
            lvlText.setString("LEVEL " + to_string(currentLevel) + " COMPLETE!\nP1 Score: " + to_string(characters[0]->getScore()));
            lvlText.setCharacterSize(45);
            lvlText.setFillColor(sf::Color::Green);
            lvlText.setPosition(150, 200);
            window.draw(lvlText);

            if (characterCount > 1) {
                sf::Text p2lvlText;
                p2lvlText.setFont(font);
                p2lvlText.setString("P2 Score: " + to_string(characters[1]->getScore()));
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
                    winText.setString("YOU WIN!\nP1 Score: " + to_string(characters[0]->getScore()));
                    winText.setCharacterSize(50);
                    winText.setFillColor(sf::Color::Yellow);
                    winText.setPosition(200, 200);
                    window.draw(winText);
                    leaderboard.saveScore(auth.getCurrentLoggedInUser(), characters[0]->getScore(), currentLevel);
                    SoundManager::get().playWin();

                    if (characterCount > 1) {
                        sf::Text p2WinText;
                        p2WinText.setFont(font);
                        p2WinText.setString("P2 Score: " + to_string(characters[1]->getScore()));
                        p2WinText.setCharacterSize(50);
                        p2WinText.setFillColor(sf::Color::Cyan);
                        p2WinText.setPosition(200, 320);
                        window.draw(p2WinText);
                    }

                    window.display();
                    bool waiting = true;
                    while (waiting && window.isOpen()) {
                        sf::Event e;
                        while (window.pollEvent(e)) {
                            if (e.type == sf::Event::Closed)
                                window.close();
                            if (e.type == sf::Event::KeyPressed)
                                waiting = false;
                        }
                    }
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

            // --- GAMAKICHI ---
            Gamakichi* gama = dynamic_cast<Gamakichi*>(enemies[i]);
            if (gama) {
                gama->Update(platforms, platformCount, playerCX, playerCY);

                // Knife hits player
                if (gama->knifeActive) {
                    sf::FloatRect k = gama->getKnifeRect();
                    for (int p = 0; p < characterCount; p++) {
                        sf::FloatRect pRect = characters[p]->getRect();
                        bool ox = k.left < pRect.left + pRect.width && k.left + k.width > pRect.left;
                        bool oy = k.top < pRect.top + pRect.height && k.top + k.height > pRect.top;
                        if (ox && oy) {
                            gama->deactivateKnife();
                            characters[p]->hit();
                            break;
                        }
                    }
                }

                // Rockets hit player
                for (int r = 0; r < gama->rocketCount; r++) {
                    if (gama->rockets[r]->isActive()) {
                        sf::FloatRect rRect = gama->rockets[r]->getRect();
                        for (int p = 0; p < characterCount; p++) {
                            sf::FloatRect pRect = characters[p]->getRect();
                            bool ox = rRect.left < pRect.left + pRect.width && rRect.left + rRect.width > pRect.left;
                            bool oy = rRect.top < pRect.top + pRect.height && rRect.top + rRect.height > pRect.top;
                            if (ox && oy) {
                                gama->rockets[r]->deactivate();
                                characters[p]->hit();
                                break;
                            }
                        }
                    }

                    // Explosion zone hits player
                    if (gama->rockets[r]->hasExploded()) {
                        sf::FloatRect eRect = gama->rockets[r]->getExplosionRect();
                        for (int p = 0; p < characterCount; p++) {
                            sf::FloatRect pRect = characters[p]->getRect();
                            bool ox = eRect.left < pRect.left + pRect.width && eRect.left + eRect.width > pRect.left;
                            bool oy = eRect.top < pRect.top + pRect.height && eRect.top + eRect.height > pRect.top;
                            if (ox && oy)
                                characters[p]->hit();
                        }
                    }
                }
                continue;
            }

            // --- MOGERA ---
            Mogera* mogera = dynamic_cast<Mogera*>(enemies[i]);
            if (mogera) {
                mogera->Update(platforms, platformCount, playerCX, playerCY);

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
        sf::Text livesText;
        livesText.setFont(font);
        livesText.setString("P1 Lives: " + to_string(characters[0]->getLives()));
        livesText.setCharacterSize(25);
        livesText.setFillColor(sf::Color::White);
        livesText.setPosition(10, 10);
        window.draw(livesText);

        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("P1 Score: " + to_string(characters[0]->getScore()));
        scoreText.setCharacterSize(25);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 40);
        window.draw(scoreText);

        sf::Text gemsText;
        gemsText.setFont(font);
        gemsText.setString("P1 Gems: " + to_string(dynamic_cast<Smash*>(characters[0])->getGems()));
        gemsText.setCharacterSize(25);
        gemsText.setFillColor(sf::Color(255, 215, 0));
        gemsText.setPosition(10, 70);
        window.draw(gemsText);

        if (characterCount > 1) {
            sf::Text lives2Text;
            lives2Text.setFont(font);
            lives2Text.setString("P2 Lives: " + to_string(characters[1]->getLives()));
            lives2Text.setCharacterSize(25);
            lives2Text.setFillColor(sf::Color::Cyan);
            lives2Text.setPosition(590, 10);
            window.draw(lives2Text);

            sf::Text score2Text;
            score2Text.setFont(font);
            score2Text.setString("P2 Score: " + to_string(characters[1]->getScore()));
            score2Text.setCharacterSize(25);
            score2Text.setFillColor(sf::Color::Cyan);
            score2Text.setPosition(590, 40);
            window.draw(score2Text);

            sf::Text gems2Text;
            gems2Text.setFont(font);
            gems2Text.setString("P2 Gems: " + to_string(dynamic_cast<Smash*>(characters[1])->getGems()));
            gems2Text.setCharacterSize(25);
            gems2Text.setFillColor(sf::Color(255, 215, 0));
            gems2Text.setPosition(590, 70);
            window.draw(gems2Text);
        }

        sf::Text levelText;
        levelText.setFont(font);
        levelText.setString("Level: " + to_string(currentLevel));
        levelText.setCharacterSize(25);
        levelText.setFillColor(sf::Color::White);
        levelText.setPosition(350, 10);
        window.draw(levelText);

        // Boss phase indicator for boss levels
        if (currentLevel == 5 || currentLevel == 9) {
            for (int i = 0; i < enemyCount; i++) {
                Mogera* mogera = dynamic_cast<Mogera*>(enemies[i]);
                if (mogera && !mogera->isDead()) {
                    sf::Text bossLabel;
                    bossLabel.setFont(font);
                    bossLabel.setString("MOGERA");
                    bossLabel.setCharacterSize(20);
                    bossLabel.setFillColor(sf::Color::White);
                    bossLabel.setPosition(340, 570);
                    window.draw(bossLabel);
                }
            }
        }

        if (currentLevel == 10) {
            for (int i = 0; i < enemyCount; i++) {
                Gamakichi* gama = dynamic_cast<Gamakichi*>(enemies[i]);
                if (gama && !gama->isDead()) {
                    sf::Text bossLabel;
                    bossLabel.setFont(font);
                    bossLabel.setString("GAMAKICHI");
                    bossLabel.setCharacterSize(20);
                    bossLabel.setFillColor(sf::Color::Red);
                    bossLabel.setPosition(320, 570);
                    window.draw(bossLabel);

                    sf::Text phaseText;
                    phaseText.setFont(font);
                    phaseText.setString("PHASE " + to_string(gama->getPhase()));
                    phaseText.setCharacterSize(20);
                    phaseText.setFillColor(gama->getPhase() == 1 ? sf::Color::Green :
                        gama->getPhase() == 2 ? sf::Color::Yellow :
                        sf::Color::Red);
                    phaseText.setPosition(340, 548);
                    window.draw(phaseText);
                }
            }
        }

        // Active powerup display
        Smash* p1 = dynamic_cast<Smash*>(characters[0]);
        if (p1) {
            string powerupName = "";
            if (p1->speedBoostTimer > 0)  powerupName = "SPEED BOOST";
            if (p1->balloonMode)          powerupName = "BALLOON MODE";
            if (p1->snowballPower)        powerupName = "SNOWBALL POWER";
            if (p1->distanceIncrease)     powerupName = "DISTANCE INCREASE";

            if (powerupName != "") {
                sf::Text powerupText;
                powerupText.setFont(font);
                powerupText.setString("P1: " + powerupName);
                powerupText.setCharacterSize(20);
                powerupText.setFillColor(sf::Color(255, 215, 0));
                powerupText.setPosition(10, 535);
                window.draw(powerupText);
            }
        }

        if (characterCount > 1) {
            Smash* p2 = dynamic_cast<Smash*>(characters[1]);
            if (p2) {
                string powerupName = "";
                if (p2->speedBoostTimer > 0)  powerupName = "SPEED BOOST";
                if (p2->balloonMode)          powerupName = "BALLOON MODE";
                if (p2->snowballPower)        powerupName = "SNOWBALL POWER";
                if (p2->distanceIncrease)     powerupName = "DISTANCE INCREASE";

                if (powerupName != "") {
                    sf::Text powerupText;
                    powerupText.setFont(font);
                    powerupText.setString("P2: " + powerupName);
                    powerupText.setCharacterSize(20);
                    powerupText.setFillColor(sf::Color(255, 215, 0));
                    powerupText.setPosition(550, 535);
                    window.draw(powerupText);
                }
            }
        }

        window.draw(pauseSprite);
        window.display();
    }

    for (int i = 0; i < characterCount; i++) delete characters[i];
    for (int i = 0; i < platformCount; i++) delete platforms[i];
    for (int i = 0; i < enemyCount; i++) delete enemies[i];
}