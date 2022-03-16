#ifndef LINE_H
#define LINE_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include <iostream>
#include<cstdlib>

class Line
{
public:
	sf::RectangleShape vectorLine;
	sf::CircleShape triangle;

	void recursiveTree(float length, int angle, int xCord, int yCord, sf::RenderWindow* window, int angleMod);
	
	void serpinskiTriangle(float radius, int xCord, int yCord, sf::RenderWindow* window);


};

#endif