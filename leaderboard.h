#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Leaderboard
{
private:
    sf::Font font;
    sf::RenderWindow& window;
    string filename;

public:
    Leaderboard(sf::RenderWindow& window, string filename);
    void saveScore(string username, int score, int levelReached);
    void show();  // displays leaderboard screen
};