#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class SoundManager {
public:
    static SoundManager& get() {
        static SoundManager instance;
        return instance;
    }

    bool load() {
        bool success = true;

        if (!bufSnowball.loadFromFile("snowball.wav")) {
            std::cout << "Failed to load: snowball.wav" << std::endl;
            success = false;
        } else std::cout << "Loaded: snowball.wav" << std::endl;

        if (!bufEnemyHit.loadFromFile("enemyhit.wav")) {
            std::cout << "Failed to load: enemyhit.wav" << std::endl;
            success = false;
        } else std::cout << "Loaded: enemyhit.wav" << std::endl;

        if (!bufPlayerHit.loadFromFile("playerhit.wav")) {
            std::cout << "Failed to load: playerhit.wav" << std::endl;
            success = false;
        } else std::cout << "Loaded: playerhit.wav" << std::endl;

        if (!bufMogeraChild.loadFromFile("mogerachid.wav")) {
            std::cout << "Failed to load: mogerachild.wav" << std::endl;
            success = false;
        } else std::cout << "Loaded: mogerachild.wav" << std::endl;

        if (!bufWin.loadFromFile("winning.wav")) {
            std::cout << "Failed to load: winning.wav" << std::endl;
            success = false;
        } else std::cout << "Loaded: winning.wav" << std::endl;

        sndSnowball.setBuffer(bufSnowball);
        sndEnemyHit.setBuffer(bufEnemyHit);
        sndPlayerHit.setBuffer(bufPlayerHit);
        sndMogeraChild.setBuffer(bufMogeraChild);
        sndWin.setBuffer(bufWin);

        return success;
    }

    void playSnowball()    { if (sndSnowball.getBuffer()) sndSnowball.play(); }
    void playEnemyHit()    { if (sndEnemyHit.getBuffer()) sndEnemyHit.play(); }
    void playPlayerHit()   { if (sndPlayerHit.getBuffer()) sndPlayerHit.play(); }
    void playMogeraChild() { if (sndMogeraChild.getBuffer()) sndMogeraChild.play(); }
    void playWin()         { if (sndWin.getBuffer()) sndWin.play(); }

private:
    sf::SoundBuffer bufSnowball, bufEnemyHit, bufPlayerHit, bufMogeraChild, bufWin;
    sf::Sound sndSnowball, sndEnemyHit, sndPlayerHit, sndMogeraChild, sndWin;
};
