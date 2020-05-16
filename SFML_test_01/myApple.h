#pragma once
#include <SFML/Graphics.hpp>
class myApple
{
private:
	sf::CircleShape appleRectangle;
	int Size;
	int Vertical;
	int Horizontal;
public:
	int X, Y;
	void Init(int size, sf::Color color, int vertical, int horisontal);
	void DrawApple(sf::RenderWindow* window);
	void Generate();
};

