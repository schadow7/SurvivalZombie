#include "MainWindow.h"

MainWindow::MainWindow()
{
	//Przygotowanie okna
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window = new sf::RenderWindow( sf::VideoMode( 1280, 720, 32 ), "SurvivalZombie", sf::Style::Default, settings );
	window->setFramerateLimit( 60 );
}

MainWindow::~MainWindow()
{
	delete this->window;
	delete this->game;
}

void MainWindow::runGame(  )
{
	game->runGame( window );
}

void MainWindow::newGame()
{
	game = new Game;
	game->loadTextures();
	runGame();
}

void MainWindow::loadGame( std::string filename )
{
}

void MainWindow::saveGame( std::string filename )
{
}
