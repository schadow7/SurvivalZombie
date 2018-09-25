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



private:
	void									newGame();
	void									loadGame( SaveSlot slot );
	void									saveGame( SaveSlot slot );
	void									saveGameDefault( SaveSlot slot );
	void									draw();
	GameState								runMenu(sf::Event event);

private:	
	/// <summary>
	/// Loads the textures.
	/// </summary>
	void									loadTextures();	
	/// <summary>
	/// Runs the default menu.
	/// </summary>
	void									runDefaultMenu();	
	/// <summary>
	/// Runs the new game menu.
	/// </summary>
	void									runNewGameMenu();	
	/// <summary>
	/// Runs the load game menu.
	/// </summary>
	void									runLoadGameMenu();	
	/// <summary>
	/// Runs the default menu clicked.
	/// </summary>
	/// <returns></returns>
	GameState								runDefaultMenuClicked();	
	/// <summary>
	/// Runs the new game menu clicked.
	/// </summary>
	/// <returns></returns>
	GameState								runNewGameMenuClicked();	
	/// <summary>
	/// Runs the load game menu clicked.
	/// </summary>
	/// <returns></returns>
	GameState								runLoadGameMenuClicked();	
	/// <summary>
	/// Checks the save slot.
	/// </summary>
	/// <param name="slot">The save slot.</param>
	/// <returns></returns>
	bool									checkSlot(SaveSlot slot);	
	/// <summary>
	/// Formats the text.
	/// </summary>
	/// <param name="text">The text.</param>
	void									formatText(sf::Text & text);
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