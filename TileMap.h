#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include <iostream>
#include "WaterTile.h"
#include "SandTile.h"
#include "Tile.h"
#include "BrickTile.h"
#include "FireTile.h"
class TileMap
{

public:

	TileMap();
	void initMap();
	void updateUserInput(sf::RenderWindow* window);
	void updateWaterTilePhysics(sf::RenderWindow* window);
	void updateFireTilePhysics(sf::RenderWindow* window);
	void updateSandTilePhysics(sf::RenderWindow* window);
	void updateMap(sf::RenderWindow*);
	bool tileCanMoveDown(Tile elementTile);
	bool tileCanMoveLeft(Tile elementTile);
	bool tileCanMoveRight(Tile elementTile);
	bool tileCanMoveDownLeft(Tile elementTile);
	bool tileCanMoveDownRight(Tile elementTile);
	void drawWaterTiles(sf::RenderWindow* window);
	void drawSandTiles(sf::RenderWindow* window);
	void drawBrickTiles(sf::RenderWindow* window);
	void drawFireTiles(sf::RenderWindow* window);
	void drawMap(sf::RenderWindow*);
	int getTileSize();
	int getMapWidth();
	int getMapHeight();

private:
	bool finalTile = false;
	bool addFireTile = false;

	Tile tile;
	
	char mapArray[1920/4][1080/4];

	std::vector<Tile> tileVector;

	std::vector<WaterTile> waterVector;
	std::vector<SandTile> sandVector;
	std::vector<BrickTile> brickVector;
	std::vector<FireTile> fireVector;

	std::vector<FireTile> deleteVector;

	sf::RectangleShape mouseCursor;

};

