#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class myMenu
{
private:
	int Width;
	int Offset;
	int TextNum;
	sf::Text Text[20];
	sf::Font Font;
public:
	void AddText(std::string str, int fontsize,  int offset, sf::RenderWindow* window);
	void Init(std::string str, int width);
	int GetSelect(int start, sf::RenderWindow* window);
	void SelectText(sf::RenderWindow* window, int select);
};

