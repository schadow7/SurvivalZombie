#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <string>

#define MAX_NUMBER_OF_ITEMS 3

class MainWindow
{
public:
	MainWindow();
	~MainWindow();

	void									run();
	void									newGame();
	void									loadGame( std::string filename );
	void									saveGame( std::string filename );
	void									draw();
	int										runMenu(sf::Event event);

private:
	void									loadTextures();

	sf::RenderWindow *						window;
	Game *									game;
	sf::Sprite								backgroundMenu, button[MAX_NUMBER_OF_ITEMS * 2];
	int										posX, posY, spacing, width, height, selectedButton;
	bool									clicked;
	int										gameState;
	sf::Cursor *							cursor;
};