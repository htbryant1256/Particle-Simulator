#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <cstdlib>

//Private Functions---------------------------------------------------------------------------------
void Game::initVariables()
{
	window = nullptr;

    windowWidth = tileMap.getMapWidth();
    windowHeight = tileMap.getMapHeight();
    videoMode.width = windowWidth;
    videoMode.height = windowHeight;

}

void Game::initWindow()
{
    window = new sf::RenderWindow(videoMode, "Particle Simulator", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(120);

}

void Game::pollEvents()
{    
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
            {
                window->close();
                break;
            }
        }
    }
}

//Public Functions----------------------------------------------------------------------------------
void Game::update()
{
    pollEvents();

    tileMap.updateMap(window);

}

void Game::render()
{
    window->clear();

    tileMap.drawMap(window);
  
    window->display();

}

bool Game::isRunning()
{
    return window->isOpen();

}

//Constructors--------------------------------------------------------------------------------------
Game::Game()
{
    initVariables();
	initWindow();

}