#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <string>
#include <fstream>

#define MAX_NUMBER_OF_ITEMS 3

enum class SaveSlot { SLOT_1 = 1, SLOT_2 = 2, SLOT_3 = 3 };

class MainWindow
{
public:
	MainWindow();
	~MainWindow();

	void									run();
	void									newGame();
	void									loadGame( SaveSlot slot );
	void									saveGame( SaveSlot slot );
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