#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include <iostream>

class Tile
{
public:

	int xCord, yCord;

	sf::RectangleShape tile;

	Tile();

	int getTileSize();

	sf::Color tileColor;

private:

	int tileSize;

};

