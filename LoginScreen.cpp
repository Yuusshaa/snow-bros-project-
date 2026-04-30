#include "LoginScreen.h"
#include <iostream>
using namespace std;

LoginScreen::LoginScreen(sf::RenderWindow& window, Login& auth) : window(window), auth(auth)
{
    font.loadFromFile("Silkscreen-Regular.ttf");

    usernameActive = true;  // username box selected by default
    statusMessage = "";


    //TRYING TO SUBTRACT 40 FROM THE SET POSITION BOX IN THE Y AXIS TO BRING EVERYTHING DOWN
    //20 more
    usernameBox.setSize(sf::Vector2f(300, 40));
    usernameBox.setPosition(250, 245); //HERE
    usernameBox.setFillColor(sf::Color::White);
    usernameBox.setOutlineThickness(2);
    usernameBox.setOutlineColor(sf::Color::Blue);  // blue = active

    passwordBox.setSize(sf::Vector2f(300, 40));
    passwordBox.setPosition(250, 335);
    passwordBox.setFillColor(sf::Color::White);
    passwordBox.setOutlineThickness(2);
    passwordBox.setOutlineColor(sf::Color::White);  // white = inactive

    loginButton.setSize(sf::Vector2f(130, 45));
    loginButton.setPosition(250, 400);
    loginButton.setFillColor(sf::Color(48, 25, 52));  // steel blue -> purple #301934

    registerButton.setSize(sf::Vector2f(130, 45));
    registerButton.setPosition(420, 400);
    registerButton.setFillColor(sf::Color(41, 7, 21));  // green

   //removed title text


    backgroundTexture.loadFromFile("loginbackground.png");  
    backgroundSprite.setTexture(backgroundTexture);

    // if image isn't exactly 800x600, this scales it to fit the window
    backgroundSprite.setScale
    (
        800.f / backgroundTexture.getSize().x,
        600.f / backgroundTexture.getSize().y
    );



    usernameLabel.setFont(font);
    usernameLabel.setString("Username:");
    usernameLabel.setCharacterSize(20);
    usernameLabel.setFillColor(sf::Color::White);
    usernameLabel.setPosition(250, 220); //HERE

    passwordLabel.setFont(font);
    passwordLabel.setString("Password:");
    passwordLabel.setCharacterSize(20);
    passwordLabel.setFillColor(sf::Color::White);
    passwordLabel.setPosition(250, 310);


    usernameDisplay.setFont(font);
    usernameDisplay.setCharacterSize(20);
    usernameDisplay.setFillColor(sf::Color::Black);
    usernameDisplay.setPosition(258, 253); //HERE

    passwordDisplay.setFont(font);
    passwordDisplay.setCharacterSize(20);
    passwordDisplay.setFillColor(sf::Color::Black);
    passwordDisplay.setPosition(258, 343);

    loginLabel.setFont(font);
    loginLabel.setString("Login");
    loginLabel.setCharacterSize(20);
    loginLabel.setFillColor(sf::Color::White);
    loginLabel.setPosition(285, 410);

    registerLabel.setFont(font);
    registerLabel.setString("Register");
    registerLabel.setCharacterSize(20);
    registerLabel.setFillColor(sf::Color::White);
    registerLabel.setPosition(435, 410);

    statusText.setFont(font);
    statusText.setCharacterSize(20);
    statusText.setFillColor(sf::Color::Red);
    statusText.setPosition(250, 460);
}


//SPLASH FRAME:::::
void LoginScreen::showSplash()
{
    sf::Texture splashTexture;
    splashTexture.loadFromFile("splash.png");  
    sf::Sprite splashSprite;
    splashSprite.setTexture(splashTexture);
    splashSprite.setScale
    (
        800.f / splashTexture.getSize().x,
        600.f / splashTexture.getSize().y
    );

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
        }

        float elapsedTime = clock.getElapsedTime().asSeconds();

        // fade out in the last 1 second
        float alpha = 255.f;
        if (elapsedTime > 4.f)
            alpha = 255.f * (1.f - (elapsedTime - 4.f));  // goes from 255 to 0 over 1 second

        if (elapsedTime >= 5.f) 
            return;  // done, go to login

        splashSprite.setColor(sf::Color(255, 255, 255, (sf::Uint8)alpha));

        window.clear(sf::Color::Black);
        window.draw(splashSprite);
        window.display();
    }
}



bool LoginScreen::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

                if (usernameBox.getGlobalBounds().contains(mouse))
                {
                    usernameActive = true;
                    usernameBox.setOutlineColor(sf::Color::Blue);
                    passwordBox.setOutlineColor(sf::Color::White);
                }
                else if (passwordBox.getGlobalBounds().contains(mouse))
                {
                    usernameActive = false;
                    passwordBox.setOutlineColor(sf::Color::Blue);
                    usernameBox.setOutlineColor(sf::Color::White);
                }

                else if (loginButton.getGlobalBounds().contains(mouse))
                {
                    if ((usernameInput.empty()) || (passwordInput.empty()))
                    {
                        statusMessage = "Please fill in both fields!";
                    }
                    else if (auth.loginUser(usernameInput, passwordInput))
                    {
                        return true;  // successful login — go to game
                    }
                    else
                    {
                        statusMessage = "Invalid username or password!";
                    }
                }

                else if (registerButton.getGlobalBounds().contains(mouse))
                {
                    if ((usernameInput.empty()) || (passwordInput.empty()))
                    {
                        statusMessage = "Please fill in both fields!";
                    }
                    else if (auth.registerUser(usernameInput, passwordInput))
                    {
                        statusMessage = "Registered! You can now login.";
                        statusText.setFillColor(sf::Color::Green);
                    }
                    else
                    {
                        statusMessage = "Username already exists!";
                        statusText.setFillColor(sf::Color::Red);
                    }
                }
            }

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8)
                {
                    if ((usernameActive) && (!usernameInput.empty()))
                        usernameInput = usernameInput.substr(0, usernameInput.length() - 1);
                    else if ((!usernameActive) && (!passwordInput.empty()))
                        passwordInput = passwordInput.substr(0, passwordInput.length() - 1);
                }
                else if ((event.text.unicode >= 32) && (event.text.unicode < 128))
                {
                    if ((usernameActive) && (usernameInput.length() < 20))
                        usernameInput += (char)event.text.unicode;
                    else if ((!usernameActive) && (passwordInput.length() < 20))
                        passwordInput += (char)event.text.unicode;
                }
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tab))
            {
                usernameActive = !usernameActive;
                if (usernameActive)
                {
                    usernameBox.setOutlineColor(sf::Color::Blue);
                    passwordBox.setOutlineColor(sf::Color::White);
                }
                else
                {
                    passwordBox.setOutlineColor(sf::Color::Blue);
                    usernameBox.setOutlineColor(sf::Color::White);
                }
            }
        }

        usernameDisplay.setString(usernameInput);
        passwordDisplay.setString(string(passwordInput.length(), '*'));  // show ****
        statusText.setString(statusMessage);

        window.clear();
        window.draw(backgroundSprite);  // draw background 


        window.draw(usernameLabel);
        window.draw(passwordLabel);
        window.draw(usernameBox);
        window.draw(passwordBox);
        window.draw(usernameDisplay);
        window.draw(passwordDisplay);
        window.draw(loginButton);
        window.draw(registerButton);
        window.draw(loginLabel);
        window.draw(registerLabel);
        window.draw(statusText);

        window.display();
    }
    return false;
}

void LoginScreen::clearInputs() {
    usernameInput = "";
    passwordInput = "";
    statusMessage = "";
    usernameActive = true;
    usernameBox.setOutlineColor(sf::Color::Blue);
    passwordBox.setOutlineColor(sf::Color::White);
    statusText.setFillColor(sf::Color::Red);
}