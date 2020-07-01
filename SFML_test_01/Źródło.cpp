#include <SFML/Graphics.hpp>
#include "èrÛd≥o.h"
#include "menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

menu menu1;

int main() {
    srand(time(NULL));
    sf::Event event;
    sf::Texture t1;
    t1.loadFromFile("images\\white.png");
    sf::Sprite sprite1(t1);

    sf::Texture t2;
    t2.loadFromFile("images\\menu.png");
    sf::Sprite sprite2(t2);

    for (int i = 0; i < count; i++) {
        textures[i].loadFromFile(colors[i]);
        Block[i].setTexture(textures[i]);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        delay = 0.1;
    }
    std::ifstream input("score.txt");
    if (!input.is_open()) {
        std::ofstream output("score.txt");
        output.close();
    }
    input >> bestscore;
    input.close();
    // Poczatek gry


    X = size * 3;
    Menu();
    ClearScene();
    CreateNewObject();
    GetNewObject();
    CreateNewObject();

    while (window.isOpen())
    {
        bool movedY = false;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                Y += size;
                movedY = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                MoveX(-size);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                MoveX(size);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                Rotate();
            }
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
        score1();
        window.display();
        UpdateObject(movedY);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            Pause();
        }
    }
}

void score1() {
    sf::Font myfont;
    if (!myfont.loadFromFile("arial.ttf"))
    {
        // error...
    }

    sf::Text Score, HScore;
    Score.setFillColor(sf::Color::Black);
    Score.setCharacterSize(30);
    Score.setPosition({ 365, 55 });
    Score.setFont(myfont);
    Score.setString("Score: " + std::to_string(score));
    HScore.setFillColor(sf::Color::Black);
    HScore.setCharacterSize(20);
    HScore.setPosition({ 345, 110 });
    HScore.setFont(myfont);
    HScore.setString("Best score:  " + std::to_string(bestscore));
    window.draw(Score);
    window.draw(HScore);
}

void score2() {
    sf::Font myfont;
    if (!myfont.loadFromFile("arial.ttf"))
    {
        // error...
    }

    sf::Text Score, HScore;
    Score.setFillColor(sf::Color::White);
    Score.setCharacterSize(30);
    Score.setPosition({ 200, 200 });
    Score.setFont(myfont);
    HScore.setFillColor(sf::Color::White);
    HScore.setCharacterSize(20);
    HScore.setPosition({ 200, 250 });
    HScore.setFont(myfont);



    if (score > bestscore) {
        Score.setString("New Best Score!: " + std::to_string(score));
        
    }
    else {
        Score.setString("Your Score!: " + std::to_string(score));
        HScore.setString("Best score:  " + std::to_string(bestscore));
        window.draw(HScore);
        
    }
    window.draw(Score);
    window.display();
    while (true) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            return;
        }
    }
}

bool Endgame() {
    window.clear();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        Menu();
        return true;
    }
    score2();
    window.display();
    return false;
}

void Menu() {
    int fontsize = Size * 4;

    menu1.init("arial.ttf", width);
    menu1.addtext("TETRIS", fontsize * 1.5, height / 8, &window);
    menu1.addtext("Easy", fontsize, 0, &window);
    menu1.addtext("Normal", fontsize, 0, &window);
    menu1.addtext("Hard", fontsize, 0, &window);
    menu1.addtext("Exit", fontsize, 0, &window);

    int select = menu1.getselect(1, &window);
    switch (select) {
    case -1: {window.close(); return; }
    case 4: {window.close(); return; }
    case 1: {delay; break; }
    case 2: {delay = delay / 2; break; }
    case 3: {delay = delay / 3; break; }
    }

    window.clear();
    window.display();
}

void Pause() {
    int fontsize = Size * 4;

    menu1.init("arial.ttf", width);
    menu1.addtext("PAUSE", fontsize * 1.5, height / 8, &window);
    menu1.addtext("Continue", fontsize, 0, &window);
    menu1.addtext("Exit", fontsize, 0, &window);
    int select = menu1.getselect(1, &window);
    switch (select) {
    case -1: {window.close(); return; }
    case 1: { break; }
    case 2: {window.close(); return; }
    }

    window.clear();
    window.display();
}

void Rotate() {
    rot++;
    int tmp[4][4];
    if (rot > 3) rot = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tmp[i][j] = shape[i][j];
            shape[i][j] = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        int a = DefineObject[shapeType][rot][i] / 4;
        int b = DefineObject[shapeType][rot][i] % 4;
        shape[b][a] = shapeType + 1;
    }
    if (IsOutside()) {
        rot--;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                shape[i][j] = tmp[i][j];
            }
        }
    }
}

bool IsOutside() {
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (shape[a][b] > 0) {
                if (a * size + X >= size * w) {
                    return true;
                }
                if (a * size + X < 0) {
                    return true;
                }
                if (scene[X / size + a][Y / size + b] > 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

void MoveX(int x) {
    X += x;
    if (IsOutside()) X -= x;
}

void CreateNewObject() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            newShape[i][j] = 0;
        }
    }
    int num = rand() % 7;
    //int num = 6;
    for (int i = 0; i < 4; i++) {
        int a = DefineObject[num][0][i] / 4;
        int b = DefineObject[num][0][i] % 4;
        newShape[b][a] = num + 1;
    }
}
//klocek menu
void GetNewObject() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            shape[i][j] = newShape[i][j];
            if (newShape[i][j] > 0)
                shapeType = newShape[i][j] - 1;
        }
    }
}

void DrawObject() {
    int val;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] > 0) {
                val = shape[i][j] - 1;
                Block[val].setPosition(size * i + X, size * j + Y);
                window.draw(Block[val]);
            }
            //klocek menu
            if (newShape[i][j] > 0) {
                val = newShape[i][j] - 1;
                Block[val].setPosition(size * i + size * w + 45, size * j + 225);
                window.draw(Block[val]);
            }
        }
    }
    // Rysowanie sceny
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (scene[i][j] > 0) {
                val = scene[i][j] - 1;
                Block[val].setPosition(size * i, size * j);
                window.draw(Block[val]);
            }
        }
    }
}

void ClearScene() {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {       
                scene[i][j] = 0;
        }
    }
}

void UpdateObject(bool moved) {
    float time = zegar.getElapsedTime().asSeconds();
    zegar.restart();
    chrono += time;
    if ((chrono > delay) && (!moved)) {
        chrono = 0;
        Y += size;
    }
    if (IsCollision()) JoinToScene();
}

bool IsCollision() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] > 0) {
                if (j * size + Y >= size * h) {
                    return true;
                }
                if (scene[X / size + i][Y / size + j] > 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

void JoinToScene() {
    int x = X / size;
    int y = Y / size - 1;
    score += 1;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] > 0) {
                scene[i + x][j + y] = shape[i][j];
            }
        }
    }
    X = size * 3;
    Y = 0;
    GetNewObject();
    CreateNewObject();
    if (IsCollision()) {
        ClearScene();
        score2();
        if (score > bestscore)
            bestscore = score;
        std::ofstream output;
        output.open(("score.txt"), std::ofstream::out | std::ofstream::trunc);
        output << bestscore;
        output.close();
        score = 0;
        rot = 0;
        Menu();
    }

    bool isFull;
    for (int y = h - 1; y >= 0; y--) {
        isFull = true;
        for (int x = 0; x < w; x++) {
            if (scene[x][y] == 0) {
                isFull = false;
                break;
            }
        }
        if (isFull) {
            score += 10;

            for (int Y = y; Y > 0; Y--) {
                for (int X = 0; X < w; X++) {
                    scene[X][Y] = scene[X][Y - 1];

                }
            }
            y++;
        }
    }
}