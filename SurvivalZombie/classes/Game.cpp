#include "Game.h"

Game::Game()
{
	b2World * world = new b2World( b2Vec2(0.f, 0.f ));
	entity_manager = new EntityManager( world );
	sf::Texture * tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\background.png" );
	textures.insert( std::pair<std::string, sf::Texture*> ("background", tmp) );
	tmp->setRepeated(true);
	tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\grad1.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "grad1", tmp ) );
	background.setTexture( *textures.at( "background" ) );
	background.setTextureRect( sf::IntRect( 0, 0, 20000, 20000 ) );
}

Game::~Game()
{
}

void Game::initializeGame()
{
}

void Game::runGame(sf::RenderWindow * window)
{
	while ( window->isOpen() )
	{
		sf::Event event;
		while ( window->pollEvent( event ) )
		{
			// Close window: exit
			if ( event.type == sf::Event::Closed )
				window->close();
		}
		//Wyświetlenie obrazu
		window->clear();
		window->draw( background );

		//Wyświetlenie obrazu
		window->display();
	}
}

void Game::Render( sf::RenderWindow * window )
{
}
