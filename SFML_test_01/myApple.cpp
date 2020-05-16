#include "myApple.h"

void myApple::Init(int size, sf::Color color, int vertical, int horisontal)
{
	Size = size;
	appleRectangle.setRadius(size/2);
	appleRectangle.setFillColor(color);
	Vertical = vertical;
	Horizontal = horisontal;
}

void myApple::DrawApple(sf::RenderWindow* window)
{
	appleRectangle.setPosition(X * Size, Y * Size);
	window->draw(appleRectangle);
}

void myApple::Generate()
{
	X = rand() % Horizontal;
	Y = rand() % Vertical;
}

