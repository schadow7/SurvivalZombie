#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu();
	~Menu();

	void									loadTextures();
	int									    runMenu(sf::RenderWindow* window, sf::Event event);
	void									draw(sf::RenderWindow* window);

private:
	sf::Sprite								backgroundMenu, button[MAX_NUMBER_OF_ITEMS*2];
	std::map<std::string, sf::Texture *>	textures;
	int										posX, posY, spacing, width, height, selectedButton;
	bool									clicked;
};

