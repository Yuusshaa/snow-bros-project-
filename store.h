#pragma once 
#include<iostream> 
#include<SFML/Graphics.hpp> 
#include<string> 
#include"Smash.h" 
using namespace std;  

class Store 
{
private:
sf::Font font;     
sf::RenderWindow& window;      
sf::RectangleShape usainboltmode;     
sf::RectangleShape abominablesnowball;     
sf::RectangleShape powersnow;     
sf::RectangleShape balloonmode;     
sf::RectangleShape nayizindagi;   
sf::Texture backgroundTexture;   
sf::Sprite backgroundSprite;
sf::RectangleShape backButton;


public:   
	Store(sf::RenderWindow& window);  
	void run(Smash& player); 
};
