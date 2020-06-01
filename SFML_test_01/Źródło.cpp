#include <SFML/Graphics.hpp>
#include "èrÛd≥o.h"

int main() {
    srand(time(NULL));
    sf::Event event;
    sf::Texture t1;
    t1.loadFromFile("images\\white.png");
    sf::Sprite sprite1(t1);

    sf::Texture t2;
    t2.loadFromFile("images\\menu.png");
    sf::Sprite sprite2(t2);

    for (int a = 0; a < count; a++) {
        textures[a].loadFromFile(colors[a]);
        Block[a].setTexture(textures[a]);
    }

    // Poczatek gry
    ClearScene();
    CreateNewObject();
    GetNewObject();
    CreateNewObject();
    while (window.isOpen())
    {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                window.close();
        }


        window.clear(sf::Color::White);
        for (int i = 0; i < w; i++)
            for (int j = 0; j < h; j++) {
                sprite1.setPosition(i * size, j * size);
                sprite2.setPosition(330, 20);
                window.draw(sprite1);
                window.draw(sprite2);
            }
        
        DrawObject();
        window.display();
        UpdateObjects();
    } 
}

void CreateNewObject() {
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            newShape[a][b] = 0;
        }
    }
    int num = rand() % 7;
    for (int a = 0; a < 4; a++) {
        int i = DefinedObjects[num][a] / 4;
        int j = DefinedObjects[num][a] % 4;
        newShape[i][j] = num + 1;
    }
}

void GetNewObject() {
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            shape[a][b] = newShape[a][b];
        }
    }
}

void DrawObject() {
    int Val;
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (shape[a][b] > 0) {
                Val = shape[a][b] - 1;
                Block[Val].setPosition(size * a + X, size * b + Y);
                window.draw(Block[Val]);
            }
            if (newShape[a][b] > 0) {
                Val = newShape[a][b] - 1;
                Block[Val].setPosition(size * a + size * w + 40, size * b + 170);
                window.draw(Block[Val]);
            }
        }
    }
    // Rysowanie sceny
    for (int a = 0; a < w; a++) {
        for (int b = 0; b < h; b++) {
            if (scene[a][b] > 0) {
                Val = scene[a][b] - 1;
                Block[Val].setPosition(size * a, size * b);
                window.draw(Block[Val]);
            }
        }
    }
}

void ClearScene() {
    for (int a = 0; a < w; a++) {
        for (int b = 0; b < h; b++) {
            scene[a][b] = 0;
        }
    }
}

void UpdateObjects() {
    float time = zegar.getElapsedTime().asSeconds();
    zegar.restart();
    chrono += time;
    if (chrono > delay) {
        chrono = 0;
        Y += size;
    }
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (shape[a][b] > 0) {
                if (b * size + Y >= size * h) {
                    JoinToScene();
                    Y = 0;
                    GetNewObject();
                    CreateNewObject();
                }
                if (scene[X / size + a][Y / size + b] > 0) {
                    JoinToScene();
                    Y = 0;
                    GetNewObject();
                    CreateNewObject();
                }
            }
        }
    }
}

void JoinToScene() {
    int x = X / size;
    int y = Y / size - 1;
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (shape[a][b] > 0) {
                scene[a + x][b + y] = shape[a][b];
            }
        }
    }
}