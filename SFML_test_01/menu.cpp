#include "menu.h"

void menu::addtext(std::string str, int fontsize, int offset, sf::RenderWindow* window)
{
    Texttable[Number].setFont(Font);
    Texttable[Number].setString(str);
    Texttable[Number].setCharacterSize(fontsize);
    Texttable[Number].setFillColor(sf::Color::White);
    Texttable[Number].setStyle(sf::Text::Bold);
    Texttable[Number].setPosition(Width / 2 - fontsize * 1.5, Offset += offset);
    window->draw(Texttable[Number]);
    Number++;
    Offset += fontsize;
}

void menu::init(std::string myfont, int width)
{
    if (!Font.loadFromFile(myfont))
    {
        // error...
    }
    Number = 0;
    Offset = 0;
    Width = width;
}

void menu::selecttext(sf::RenderWindow* window, int select)
{
    window->clear();
    std::string old = Texttable[select].getString();
    Texttable[select].setString("--" + old);
    for (int i = 0;i < Number;i++) {
        window->draw(Texttable[i]);
    }
    window->display();
    Texttable[select].setString(old);
}

int menu::getselect(int start, sf::RenderWindow* window)
{
    int select = start;
    bool up = 0;
    bool down = 0;
    selecttext(window, start);

    while (window->isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and !up) {
            select--;
            if (select < start)
            {
                select = Number - 1;
            }
            selecttext(window, select);
            up = 1;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            up = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and !down) {
            select++;
            if (select >= Number)
            {
                select = start;
            }
            selecttext(window, select);
            down = 1;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            down = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            return select;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return -1;
        }

    }
    return 0;
}