#include "myMenu.h"

void myMenu::AddText(std::string str, int fontsize, int offset, sf::RenderWindow* window)
{
    Offset += offset;
    Text[TextNum].setFont(Font);
    Text[TextNum].setString(str);
    Text[TextNum].setCharacterSize(fontsize);
    Text[TextNum].setFillColor(sf::Color::Red);
    Text[TextNum].setStyle(sf::Text::Bold);
    Text[TextNum].setPosition(Width / 2 - fontsize * 1.5, Offset);
    window->draw(Text[TextNum]);
    TextNum++;
    Offset += fontsize;
}

void myMenu::Init(std::string str, int width)
{
    Width = width;
    TextNum = 0;
    Offset = 0;
    if (!Font.loadFromFile(str))
    {
        // error...
    }
}

int myMenu::GetSelect(int start, sf::RenderWindow* window)
{
    int select = start;
    bool up = false, down = false;
    SelectText(window, start);
    while (window->isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and !up) {
            select--;
            if (select < start) { 
                select = TextNum - 1; 
            }
            SelectText(window, select);
            up = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) up = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and !down) {
            select++;
            if (select >= TextNum) {
                select = start;
            }
            SelectText(window, select);
            down = true;
        } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
                down = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            return select;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return -1;
        }
  
    }

    return 0;
}

void myMenu::SelectText(sf::RenderWindow* window, int select)
{
    window->clear();
    std::string old = Text[select].getString();
    Text[select].setString("-- " + old);
    for (int a = 0; a < TextNum; a++) {
        window->draw(Text[a]);
    }
    window->display();
    Text[select].setString(old);
}
