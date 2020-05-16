#include <SFML/Graphics.hpp>

int w = 10, h = 20;
int size = 32;
int width = size * w + 200; //520 
int height = size * h; //640
int shape[4][4];
int scene[10][20];
sf::RenderWindow window(sf::VideoMode(width, height), "Tetris");
float chrono = 0;
sf::Clock zegar;
float delay = 0.5;
int X = 0, Y = 0;

void CreateNewObject();
void DrawObject();
void UpdateObjects();

int DefinedObjects[7][4] = {
	{1,5,9,13},
	{1,5,9,13},
	{1,5,9,13},
	{1,5,9,13},
	{1,5,9,13},
	{1,5,9,13},
	{1,5,9,13}
};