#include "leaderboard.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include<string>
#include<SFML/Graphics.hpp>
using namespace std;

Leaderboard::Leaderboard(sf::RenderWindow& window, string filename) : window(window)
{
    this->filename = filename;
    font.loadFromFile("Silkscreen-Regular.ttf");
}

void Leaderboard::saveScore(string username, int score, int levelReached)
{
    // get today's date
    time_t now = time(0);
    tm timeInfo;
    localtime_s(&timeInfo, &now);
    string date = to_string(1900 + timeInfo.tm_year) + "-"
        + to_string(1 + timeInfo.tm_mon) + "-"
        + to_string(timeInfo.tm_mday);

    // append to file: username,score,level,date
    ofstream file(filename, ios::app);
    file << username << "," << score << "," << levelReached << "," << date << "\n";
    file.close();
}

void Leaderboard::show()
{
    // read all entries from file
    string names[250], dates[250];
    int scores[250], levels[250];
    int count = 0;

    ifstream file(filename);
    string line;
    while (getline(file, line) && count < 100)
    {
        size_t first = line.find(',');
        size_t second = line.find(',', first + 1);
        size_t third = line.find(',', second + 1);

        names[count] = line.substr(0, first);
        scores[count] = stoi(line.substr(first + 1, second - first - 1));
        levels[count] = stoi(line.substr(second + 1, third - second - 1));
        dates[count] = line.substr(third + 1);
        count++;
    }
    file.close();

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (scores[j] < scores[j + 1])
            {
                int tempScore = scores[j]; 
                scores[j] = scores[j + 1]; 
                scores[j + 1] = tempScore;


                int tempLevel = levels[j]; 
                levels[j] = levels[j + 1]; 
                levels[j + 1] = tempLevel;


                string tempName = names[j]; 
                names[j] = names[j + 1];
                names[j + 1] = tempName;


                string tempDate = dates[j]; 
                dates[j] = dates[j + 1]; 
                dates[j + 1] = tempDate;
            }
        }
    }

    int display = count < 10 ? count : 10; //only shows top 10- changed form 20 (do laterjmf)

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                return;  //ESC OT REUTNR
        }

        window.clear(sf::Color::Black);

        sf::Text title;
        title.setFont(font);
        title.setString("    LEADERBOARD    ");
        title.setCharacterSize(35);
        title.setFillColor(sf::Color::Yellow);
        title.setPosition(180, 30);
        window.draw(title);

        // column headers
        sf::Text headers;
        headers.setFont(font);
        headers.setString("RANK  NAME             SCORE   LEVEL  DATE");
        headers.setCharacterSize(16);
        headers.setFillColor(sf::Color(200, 200, 200));
        headers.setPosition(30, 90);
        window.draw(headers);

        // each entry
        for (int i = 0; i < display; i++)
        {
            string entry = to_string(i + 1) + ".    " + names[i] + string(17 - names[i].length(), ' ') + to_string(scores[i]) + string(8 - to_string(scores[i]).length(), ' ') + to_string(levels[i]) + "      "  + dates[i];

            sf::Text row;
            row.setFont(font);
            row.setString(entry);
            row.setCharacterSize(16);
            row.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);  // gold for 1st
            row.setPosition(30, 120 + i * 38);
            window.draw(row);
        }

        if (count == 0)
        {
            sf::Text empty;
            empty.setFont(font);
            empty.setString("No scores yet!");
            empty.setCharacterSize(25);
            empty.setFillColor(sf::Color::White);
            empty.setPosition(280, 300);
            window.draw(empty);
        }

        sf::Text hint;
        hint.setFont(font);
        hint.setString("Press ESC to return");
        hint.setCharacterSize(18);
        hint.setFillColor(sf::Color(150, 150, 150));
        hint.setPosition(280, 540);
        window.draw(hint);

        window.display();
    }
}