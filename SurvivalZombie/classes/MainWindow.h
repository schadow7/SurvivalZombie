#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <string>


class MainWindow
{
public:
	MainWindow();
	~MainWindow();

	void				runGame();
	void				newGame();
	void				loadGame(std::string filename);
	void				saveGame( std::string filename );

private:
	sf::RenderWindow *	window;
	Game *				game;
	
};