#pragma once
#include <SFML/Graphics.hpp>
#include "myApple.h"

class mySnake
{
private:
	int Size;
	int Vertical;
	int Horizontal;

	int Direction;
	int Body;
	sf::RectangleShape snakeRectangle;
	int X[1024], Y[1024];

public:
	void Init(sf::Vector2f wektor, sf::Color kolor, int size, int vertical, int horizontal);
	void UpdateInput();
	void DrawSnake(sf::RenderWindow* window);
	int UpdateAction(myApple* apple);
	int EndGame();
};

