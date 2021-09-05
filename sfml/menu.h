#pragma once
#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_ITEMS 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectecItemIndex; }

private:
	int selectecItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_ITEMS];
};
