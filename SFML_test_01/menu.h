#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class menu
{
public:
	void addtext(std::string str, int fontsize, int offset, sf::RenderWindow* window);
	void init(std::string myfont, int width);
	void selecttext(sf::RenderWindow* window, int select);
	int getselect(int start, sf::RenderWindow* window);
private:
	int Width;
	int Offset;
	int Number;
	sf::Text Texttable[20];
	sf::Font Font;
};