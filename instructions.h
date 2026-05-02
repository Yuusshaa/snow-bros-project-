#pragma once
#include<iostream>
#include"leaderboard.h"
#include"loginscreen.h"
#include"login.h"
#include<SFML/Graphics.hpp>

using namespace std;

class Instructions
{
private:
    sf::Font font;
    sf::RenderWindow& window;
    sf::CircleShape leaderboardbutton;
    sf::CircleShape startgame;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;


public:
	Instructions(sf::RenderWindow& window);
	bool run(Leaderboard& leaderboard, LoginScreen& loginScreen, Login& auth);
};