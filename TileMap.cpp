#include "TileMap.h"

void TileMap::initMap()
{
    mouseCursor.setSize(sf::Vector2f(tile.getTileSize()*2, tile.getTileSize()*2));
    mouseCursor.setFillColor(sf::Color::Red);

    int rows = sizeof(mapArray) / sizeof(mapArray[0]);
    int col = sizeof(mapArray[0]);

    for (int y = 0; y <= col - 1; y++) {
        for (int x = 0; x <= rows - 1; x++) {
            if (x == 0 || (x == rows - 1) || y == 0 || y == col - 1) {
                BrickTile tempTile;
                tempTile.xCord = x;
                tempTile.yCord = y;

                brickVector.push_back(tempTile);
                mapArray[x][y] = 'B';

            }
            else {

                mapArray[x][y] = ' ';

            }
        }
    }
}

void TileMap::updateUserInput(sf::RenderWindow* window) {
    int counter = 3;

    sf::Vector2f worldPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    mouseCursor.setPosition(sf::Vector2f(worldPos.x - (mouseCursor.getSize().x / 2), worldPos.y - (mouseCursor.getSize().y / 2)));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        for (int i = counter; i >= 0; i--) {
            WaterTile tempTile;
            tempTile.xCord = int((worldPos.x / tile.getTileSize()) + rand() % counter * 2 - counter);
            tempTile.yCord = int((worldPos.y / tile.getTileSize()) + rand() % counter * 2 - counter);

            if (mapArray[tempTile.xCord][tempTile.yCord] == ' ') {

                waterVector.push_back(tempTile);

                mapArray[tempTile.xCord][tempTile.yCord] = '#';
            }
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && worldPos.x > 0 && worldPos.x < getMapWidth() && worldPos.y > 0 && worldPos.y < getMapHeight()) {

        for (int i = counter; i >= 0; i--) {
            SandTile tempTile;
            tempTile.xCord = int((worldPos.x / tile.getTileSize()) + rand() % counter * 2 - counter);
            tempTile.yCord = int((worldPos.y / tile.getTileSize()) + rand() % counter * 2 - counter);

            if (mapArray[tempTile.xCord][tempTile.yCord] == ' ') {

                sandVector.push_back(tempTile);

                mapArray[tempTile.xCord][tempTile.yCord] = 'S';
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

        for (int i = 20; i >= 0; i--) {
            BrickTile tempTile;
            tempTile.xCord = int((worldPos.x / tile.getTileSize()) + rand() % counter - counter / 2);
            tempTile.yCord = int((worldPos.y / tile.getTileSize()) + rand() % counter - counter / 2);

            if (mapArray[tempTile.xCord][tempTile.yCord] != 'B') {

                brickVector.push_back(tempTile);

                mapArray[tempTile.xCord][tempTile.yCord] = 'B';
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {

        for (int i = 20; i >= 0; i--) {
            FireTile tempTile;
            tempTile.xCord = int((worldPos.x / tile.getTileSize()) + rand() % counter - counter / 2);
            tempTile.yCord = int((worldPos.y / tile.getTileSize()) + rand() % counter - counter / 2);

            if (mapArray[tempTile.xCord][tempTile.yCord] == ' ') {

                fireVector.push_back(tempTile);

                mapArray[tempTile.xCord][tempTile.yCord] = 'F';
            }
        }
    }

}

void TileMap::updateWaterTilePhysics(sf::RenderWindow* window) {

    for (auto& element : waterVector) {
        int x = element.xCord;
        int y = element.yCord;

        if (tileCanMoveDown(element)) {
            mapArray[x][y + 1] = '#';
            mapArray[x][y] = ' ';
            element.yCord += 1;
        }

        else if (tileCanMoveLeft(element) && tileCanMoveRight(element)) {
            if (rand() % 2 + 1 == 2) {
                mapArray[x - 1][y] = '#';
                mapArray[x][y] = ' ';
                element.xCord--;
            }
            else {
                mapArray[x + 1][y] = '#';
                mapArray[x][y] = ' ';
                element.xCord++;
            }

        }
        else if (tileCanMoveLeft(element)) {
            mapArray[x - 1][y] = '#';
            mapArray[x][y] = ' ';
            element.xCord -= 1;

        }
        else if (tileCanMoveRight(element)) {
            mapArray[x + 1][y] = '#';
            mapArray[x][y] = ' ';
            element.xCord += 1;

        }
    }
}

void TileMap::updateFireTilePhysics(sf::RenderWindow* window) {
    int vectorCounter = 0;
    int finalCount = 0;

    for (auto& element : fireVector) {
        int x = element.xCord;
        int y = element.yCord;

        finalCount = vectorCounter;

        vectorCounter++;

        if (tileCanMoveDown(element)) {
            mapArray[x][y + 1] = 'F';
            mapArray[x][y] = ' ';
            element.yCord += 1;
        }

        else if (tileCanMoveLeft(element) && tileCanMoveRight(element) && rand() % 10 <= 1) {
            if (rand() % 2 + 1 == 2) {
                mapArray[x - 1][y] = 'F';
                mapArray[x][y] = ' ';
                element.xCord--;

            }
            else {
                mapArray[x + 1][y] = 'F';
                mapArray[x][y] = ' ';
                element.xCord++;

            }
        }
        else if (mapArray[x][y - 1] == ' ') {
            mapArray[x][y - 1] = 'F';
            mapArray[x][y] = ' ';
            element.yCord -= 1;

        }
        else if (tileCanMoveLeft(element)) {
            mapArray[x - 1][y] = 'F';
            mapArray[x][y] = ' ';
            element.xCord -= 1;

        }
        else if (tileCanMoveRight(element)) {
            mapArray[x + 1][y] = 'F';
            mapArray[x][y] = ' ';
            element.xCord += 1;

        }

    }

    //Fire Delete ------------------------------------------------------------


    if (finalCount != 0) {
        Tile temp;
        temp = fireVector.at((fireVector.size() - finalCount));
        mapArray[temp.xCord][temp.yCord] = ' ';
        fireVector.erase(fireVector.begin() + (fireVector.size() - finalCount));


        finalTile = true;

    }
    else if (finalTile) {

        Tile temp;
        temp = fireVector.at(finalCount);
        mapArray[temp.xCord][temp.yCord] = ' ';
        fireVector.erase(fireVector.begin() + finalCount);
        finalTile = false;

    }

    vectorCounter = 0;
    finalCount = 0;


    FireTile tempFire;
    bool fireSpread = false;

    // Fire Tile Spread Physics-----------------------------------------------------------------------------------------------------------------------------------
    for (auto& element : fireVector) {
        int x = element.xCord;
        int y = element.yCord;

        finalCount = vectorCounter;

        vectorCounter++;

        if (mapArray[x][y + 1] == 'S') {
            int deleteSand = 0;
            for (auto& elementToCompare : sandVector) {
                if (elementToCompare.xCord == x && elementToCompare.yCord == y + 1) {
                    mapArray[x][y + 1] = 'F';
                    mapArray[x][y] = 'F';

                    tempFire.xCord = x;
                    tempFire.yCord = y + 1;
                    fireSpread = true;
                    break;
                }
                deleteSand++;

            }

            sandVector.erase(sandVector.begin() + deleteSand);

        }
        else if (mapArray[x][y - 1] == 'S') {
            int deleteSand = 0;
            for (auto& elementToCompare : sandVector) {
                if (elementToCompare.xCord == x && elementToCompare.yCord == y - 1) {
                    mapArray[x][y - 1] = 'F';
                    mapArray[x][y] = 'F';

                    tempFire.xCord = x;
                    tempFire.yCord = y - 1;
                    fireSpread = true;
                    break;
                }
                deleteSand++;

            }

            sandVector.erase(sandVector.begin() + deleteSand);

        }
        else if (mapArray[x - 1][y] == 'S') {
            int deleteSand = 0;
            for (auto& elementToCompare : sandVector) {
                if (elementToCompare.xCord == x - 1 && elementToCompare.yCord == y) {
                    mapArray[x - 1][y] = 'F';
                    mapArray[x][y] = 'F';
                    tempFire.xCord = x - 1;
                    tempFire.yCord = y;
                    fireSpread = true;
                    break;
                }
                deleteSand++;

            }
            sandVector.erase(sandVector.begin() + deleteSand);

        }
        else if (mapArray[x + 1][y] == 'S') {
            int deleteSand = 0;

            for (auto& elementToCompare : sandVector) {
                if (elementToCompare.xCord == x + 1 && elementToCompare.yCord == y) {
                    mapArray[x + 1][y] = ' ';
                    mapArray[x][y] = 'F';
                    tempFire.xCord = x + 1;
                    tempFire.yCord = y;
                    fireSpread = true;
                    break;
                }
                deleteSand++;
            }
            sandVector.erase(sandVector.begin() + deleteSand);
        }

        if (fireSpread) {
            break;
        }

    }
    if (fireSpread) {
        mapArray[tempFire.xCord][tempFire.yCord] = 'F';

        fireVector.push_back(tempFire);
    }

}

void TileMap::updateSandTilePhysics(sf::RenderWindow* window) {

    for (auto& element : sandVector) {

        int x = element.xCord;
        int y = element.yCord;

        if (tileCanMoveDown(element)) {
            mapArray[x][y + 1] = 'S';
            mapArray[x][y] = ' ';

            element.yCord += 1;

        }
        else if (tileCanMoveDownLeft(element) && mapArray[x][y + 1] != 'B') {

            mapArray[x - 1][y + 1] = 'S';
            mapArray[x][y] = ' ';
            element.xCord -= 1;
            element.yCord += 1;

        }
        else if (tileCanMoveDownRight(element) && mapArray[x][y + 1] != 'B') {

            mapArray[x + 1][y + 1] = 'S';
            mapArray[x][y] = ' ';
            element.xCord += 1;
            element.yCord += 1;

        }
        else if (mapArray[x][y + 1] == '#') {
            for (auto& elementToCompare : waterVector) {
                if (elementToCompare.xCord == x && elementToCompare.yCord == y + 1) {

                    mapArray[x][y + 1] = 'S';
                    mapArray[x][y] = '#';
                    elementToCompare.yCord = y;
                    element.yCord += 1;

                    break;
                }
            }
        }
        else if (mapArray[x - 1][y + 1] == '#') {

            for (auto& elementToCompare : waterVector) {
                if (elementToCompare.xCord == x - 1 && elementToCompare.yCord == y + 1) {
                    mapArray[x - 1][y + 1] = 'S';
                    mapArray[x][y] = '#';
                    elementToCompare.yCord = y;
                    elementToCompare.xCord = x;

                    element.yCord += 1;
                    element.xCord -= 1;

                    break;
                }
            }
        }
        else if (mapArray[x + 1][y + 1] == '#') {

            for (auto& elementToCompare : waterVector) {
                if (elementToCompare.xCord == x + 1 && elementToCompare.yCord == y + 1) {
                    mapArray[x + 1][y + 1] = 'S';
                    mapArray[x][y] = '#';
                    elementToCompare.yCord = y;
                    elementToCompare.xCord = x;

                    element.yCord += 1;
                    element.xCord += 1;

                    break;
                }
            }
        }
    }
}


bool TileMap::tileCanMoveDown(Tile elementTile) {
    
    return mapArray[elementTile.xCord][elementTile.yCord + 1] == ' ';

}

bool TileMap::tileCanMoveLeft(Tile elementTile) {

    return mapArray[elementTile.xCord - 1][elementTile.yCord] == ' ';

}

bool TileMap::tileCanMoveRight(Tile elementTile) {

    return mapArray[elementTile.xCord + 1][elementTile.yCord] == ' ';

}

bool TileMap::tileCanMoveDownLeft(Tile elementTile) {

    return mapArray[elementTile.xCord - 1][elementTile.yCord + 1] == ' ';

}
bool TileMap::tileCanMoveDownRight(Tile elementTile) {

    return mapArray[elementTile.xCord + 1][elementTile.yCord + 1] == ' ';

}


void TileMap::drawWaterTiles(sf::RenderWindow* window) {

    for (auto& element : waterVector) {

        element.tile.setPosition(sf::Vector2f(element.xCord * tile.getTileSize(), element.yCord * tile.getTileSize()));
        element.tile.setFillColor(element.tileColor);
        window->draw(element.tile);

    }
}


void TileMap::drawSandTiles(sf::RenderWindow* window) {
    for (auto& element : sandVector) {

        element.tile.setPosition(sf::Vector2f(element.xCord * tile.getTileSize(), element.yCord * tile.getTileSize()));
        element.tile.setFillColor(element.tileColor);
        window->draw(element.tile);

    }
}

void TileMap::drawBrickTiles(sf::RenderWindow* window) {
    for (auto& element : brickVector) {

        element.tile.setPosition(sf::Vector2f(element.xCord * tile.getTileSize(), element.yCord * tile.getTileSize()));
        element.tile.setFillColor(element.tileColor);
        window->draw(element.tile);

    }
}

void TileMap::drawFireTiles(sf::RenderWindow* window) {
    for (auto& element : fireVector) {

        element.tile.setPosition(sf::Vector2f(element.xCord * tile.getTileSize(), element.yCord * tile.getTileSize()));
        element.tile.setFillColor(element.tileColor);
        window->draw(element.tile);

    }

}

void TileMap::updateMap(sf::RenderWindow* window)
{
    updateUserInput(window);

    updateWaterTilePhysics(window);
    updateFireTilePhysics(window);
    updateSandTilePhysics(window);
    
}




void TileMap::drawMap(sf::RenderWindow* window)
{
    drawWaterTiles(window);
    drawSandTiles(window);
    drawBrickTiles(window);
    drawFireTiles(window);

    window->draw(mouseCursor);
}


int TileMap::getTileSize()
{
    return tile.getTileSize();
}

int TileMap::getMapWidth()
{
    return sizeof(mapArray) / sizeof(mapArray[0]) * tile.getTileSize();

}

int TileMap::getMapHeight()
{
    return sizeof(mapArray[0]) * tile.getTileSize();

}

TileMap::TileMap()
{
	initMap();

}
