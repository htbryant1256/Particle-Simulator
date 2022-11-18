#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include <iostream>
#include "TileMap.h"

class Game
{

private:

	//Objects
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	//Objects From Headers
	TileMap tileMap;

	//Private Variables
	int windowHeight;
	int windowWidth;


	//Private Functions
	void initVariables();
	void initWindow();

public:

	sf::View view;

	//Constructors
	Game();

	//Functions
	void pollEvents();
	void update();
	void render();
	bool isRunning();

};

#endif