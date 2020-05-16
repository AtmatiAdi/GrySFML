#include "mySnake.h"

void mySnake::Init(sf::Vector2f wektor, sf::Color kolor,
    int size, int vertical, int horizontal)
{
    Body = 3;
    Direction = 2;
    Size = size;
    Vertical = vertical;
    Horizontal = horizontal;
    snakeRectangle.setSize(wektor);
    snakeRectangle.setFillColor(kolor);
    snakeRectangle.setOutlineThickness(1);
    snakeRectangle.setOutlineColor(sf::Color::Black);
}

void mySnake::UpdateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        Direction = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        Direction = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        Direction = 2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        Direction = 3;
    }
}

void mySnake::DrawSnake(sf::RenderWindow* window)
{
    for (int i = 0; i < Body; i++) {
        snakeRectangle.setPosition(X[i] * Size, Y[i] * Size);
        window->draw(snakeRectangle);
    }
}

int mySnake::UpdateAction(myApple* apple) {
    for (int i = Body; i > 0; --i) {
        X[i] = X[i - 1];
        Y[i] = Y[i - 1];
    }
    if (Direction == 0) {
        Y[0] += 1;
    }
    else if (Direction == 1) {
        X[0] -= 1;
    }
    else if (Direction == 2) {
        X[0] += 1;
    }
    else if (Direction == 3) {
        Y[0] -= 1;
    }
    if (X[0] == apple->X and Y[0] == apple->Y) {
        Body++;
        bool isapple = true;
        while (isapple) {
            isapple = false;
            apple->Generate();
            for (int i = 1; i < Body; i++) {
                if (X[i] == apple->X and Y[i] == apple->Y) {
                    isapple = true;
                    break;
                }
            }
        }
    }
    if (X[0] >= Horizontal) {
        return EndGame();
    }
    if (Y[0] >= Vertical) {
        return EndGame();
    }
    if (X[0] < 0) {
        return EndGame();
    }
    if (Y[0] < 0) {
        return EndGame();
    }
    for (int i = 1; i < Body; i++) {
        if (X[0] == X[i] && Y[0] == Y[i]) {
            return EndGame();
        }
    }
    
    return -1;
}

int mySnake::EndGame()
{
    X[0] = 0;
    Y[0] = 0;
    Direction = 2;
    int score = Body - 3;
    Body = 3;
    return score;
}


