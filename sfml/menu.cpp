#include "Menu.h"



Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("Data/font.otf"))
    {
    }


    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color(128, 128, 128));
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_ITEMS + 1) * 3));

    selectecItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_NUMBER_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp()
{
    if (selectecItemIndex - 1 >= 0)
    {
        menu[selectecItemIndex].setFillColor(sf::Color::White);
        selectecItemIndex--;
        menu[selectecItemIndex].setFillColor(sf::Color(128, 128, 128));
    }
}

void Menu::MoveDown()
{
    if (selectecItemIndex + 1 < MAX_NUMBER_ITEMS)
    {
        menu[selectecItemIndex].setFillColor(sf::Color::White);
        selectecItemIndex++;
        menu[selectecItemIndex].setFillColor(sf::Color(128, 128, 128));
    }
}