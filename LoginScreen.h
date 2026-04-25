#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Login.h"
using namespace std;

class LoginScreen
{
private:
    sf::Font font;
    sf::RenderWindow& window;
    Login& auth;

    string usernameInput;
    string passwordInput;
    string statusMessage;

    bool usernameActive;

    sf::RectangleShape usernameBox;
    sf::RectangleShape passwordBox;
    sf::RectangleShape loginButton;
    sf::RectangleShape registerButton;


    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text titleText;
    sf::Text usernameLabel;
    sf::Text passwordLabel;
    sf::Text usernameDisplay;
    sf::Text passwordDisplay;
    sf::Text loginLabel;
    sf::Text registerLabel;
    sf::Text statusText;

public:
    LoginScreen(sf::RenderWindow& window, Login& auth);
    void showSplash();
    bool run();  
    //game runs when logjin is successful
};