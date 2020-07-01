const int w = 10, h = 20;
int size = 32;
int Size = 20;
int width = size * w + 200; //520 
int height = size * h; //640
int shape[4][4];
int newShape[4][4];
int scene[w][h];
const int count = 7;
int shapeType = 0;
int score = 0;
int bestscore = 0;
int rot = 0;
sf::RenderWindow window(sf::VideoMode(width, height), "tetris");

std::string colors[count] = {
	"images\\yellow.png",
	"images\\orange.png",
	"images\\red.png",
	"images\\purple.png",
	"images\\green.png",
	"images\\blue.png",
	"images\\black.png"
};

sf::Texture textures[count];
sf::Sprite Block[count];

float chrono = 0;
sf::Clock zegar;
float delay = 0.5;
int X = 0;
int Y = 0;

void CreateNewObject();
void DrawObject();
void UpdateObject(bool moved);
void GetNewObject();
void JoinToScene();
void ClearScene();
void MoveX(int x);
void Rotate();
bool IsCollision();
bool IsOutside();
void Menu();
void Pause();
bool Endgame();
void score1();

int DefineObject[7][4][4] = {
	{{1,5,9,13},{8,9,10,11},{1,5,9 ,13},{8,9,10,11}},//I 
	{{1,5,9,10},{4,5,6 ,8 },{0,1,5 ,9 },{2,4,5 ,6 }},//L 
	{{1,2,5,6 },{1,2,5 ,6 },{1,2,5 ,6 },{1,2,5 ,6 }},//O 
	{{1,5,6,10},{6,7,9 ,10},{5,9,10,14},{5,6,8 ,9 }},//Z 
	{{1,5,6,9 },{8,9,10,13},{1,4,5 ,9 },{1,4,5 ,6 }},//T 
	{{2,6,9,10},{1,5,6 ,7 },{2,3,6 ,10},{5,6,7 ,11}},//L2 
	{{2,5,6,9 },{5,6,10,11},{6,9,10,13},{4,5,9 ,10}} //Z2 
};