#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <string>

const int w = 10, h = 20;
int size = 32;
int width = size * w + 200; //520 
int height = size * h; //640
int shape[4][4];
int newShape[4][4];
int scene[w][h];
const int count = 7;
sf::RenderWindow window(sf::VideoMode(width, height), "Tetris");
std::string colors[count] = {
	"images\\yellow.png",
	"images\\blue.png",
	"images\\green.png",
	"images\\orange.png",
	"images\\purple.png",
	"images\\red.png",
	"images\\black.png"
};
sf::Texture textures[count];
sf::Sprite Block[count];
float chrono = 0;
sf::Clock zegar;
float delay = 0.1;
int X = 0, Y = 0;

void CreateNewObject();
void DrawObject();
void UpdateObjects();
void GetNewObject();
void JoinToScene();
void ClearScene();

int DefinedObjects[7][4] = {
	{1,5,9,13},	// I
	{1,5,9,10},	// L
	{1,5,9,6},	// O
	{1,5,6,10},	// Z
	{1,5,6,9},  // K
	{9,10,6,2},	// L
	{5,2,9,6}	// Z
};