#include <SFML/Graphics.hpp>
#include "èrÛd≥o.h"

int main() {
   
    sf::Event event;
    sf::Texture t1;
    t1.loadFromFile("images\\white.png");
    sf::Sprite sprite1(t1);

    sf::Texture t2;
    t2.loadFromFile("images\\menu.png");
    sf::Sprite sprite2(t2);

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
        
        CreateNewObject();
        DrawObject();
        window.display();
        UpdateObjects();
    } 
}

void CreateNewObject() {
    for (int a = 0; a < 4; a++) {
        int i = DefinedObjects[0][a] / 4;
        int j = DefinedObjects[0][a] % 4;
        shape[i][j] = 1;
    }
}

void DrawObject() {
    sf::Texture texture;
    texture.loadFromFile("images\\yellow.png");
    sf::Sprite Block(texture);
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (shape[b][a] > 0) {
                Block.setPosition(size * a + X, size * b + Y);
                window.draw(Block);
            }
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
}