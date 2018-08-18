#include "Game.h"

Game::Game()
{
	world = new b2World( b2Vec2(0.f, 0.f ));
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
	//TEMP undead tester
	zombieList.push_back(new Zombie(*world, b2Vec2(1, 1)));
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
		//Wyœwietlenie obrazu
		window->clear();
		window->draw( background );
		zombieList[0]->SetVelocity(b2Vec2(10, 1));
		zombieList[0]->Render(window);

		//Wyœwietlenie obrazu
		window->display();
	}
}

void Game::Render( sf::RenderWindow * window )
{
}
