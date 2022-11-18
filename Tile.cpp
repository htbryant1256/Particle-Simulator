#include "Tile.h"

int Tile::getTileSize()
{
	return tileSize;
}

Tile::Tile()
{
	tileSize = 2;

	xCord = 0;

	yCord = 0;

	tile.setSize(sf::Vector2f(tileSize, tileSize));

}
