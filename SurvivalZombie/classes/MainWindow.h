#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <string>
#include <fstream>

#define MAX_NUMBER_OF_ITEMS 8



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
	GameState								runMenu(sf::Event event);

private:
	void									loadTextures();
	void									runDefaultMenu();
	void									runNewGameMenu();
	void									runLoadGameMenu();
	GameState								runDefaultMenuClicked();
	GameState								runNewGameMenuClicked();
	GameState								runLoadGameMenuClicked();
	bool									checkSlot( SaveSlot slot );
	void									formatText( sf::Text & text );
	void									setTextSlot();
	sf::RenderWindow *						window;
	Game *									game;
	sf::Sprite								backgroundMenu, button[MAX_NUMBER_OF_ITEMS * 2];
	int										shadow, posX, posY, spacing, dposY, width, height1, height2, mouseX, mouseY, selectedButton;
	double									dspacing;
	bool									clicked;
	int										action;
	sf::Cursor *							cursor;
	MenuType								menuType;
	GameState								gameState;
	sf::Font								fontType;
	level_state								bufor;
	sf::Text								textSlot[3];
	sf::View *								view;
	SaveSlot								currentSlot;
	sf::Sound								sound;
	sf::Text								loadText;
};