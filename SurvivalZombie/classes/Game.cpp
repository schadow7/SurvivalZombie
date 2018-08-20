#include "Game.h"

Game::Game()
{
	world = new b2World( b2Vec2(0.f, 0.f ));
	entity_manager = new EntityManager( world );
	zombie_manager = new ZombieManager(zombieList);
	
	//TEMP undead tester
	Zombie* zombieTester = new Zombie(world, b2Vec2(1.f, 1.f));
	zombieList.push_back(zombieTester);
	entity_manager->AddEntity(zombieTester);
}

Game::~Game()
{
}

void Game::initializeGame()
{
}

void Game::loadTextures()
{
	sf::Texture * tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\background.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "background", tmp ) );
	tmp->setRepeated( true );
	tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\grad1.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "grad1", tmp ) );
	background.setTexture( *textures.at( "background" ) );
	background.setTextureRect( sf::IntRect( 0, 0, 20000, 20000 ) );
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
				int mouseX = sf::Mouse::getPosition(*window).x;
				int mouseY = sf::Mouse::getPosition(*window).y;
				//zombieList[0]->ApplyForce(b2Vec2(mouseX, mouseY));
				Zombie* zombieTester = new Zombie(world, b2Vec2(mouseX, mouseY));
				zombieList.push_back(zombieTester);
				entity_manager->AddEntity(zombieTester);
		}
		//Wyœwietlenie obrazu
		window->clear();
		window->draw( background );
		zombie_manager->AIStep();
		entity_manager->Update();
		entity_manager->Render(window);

		//Wyœwietlenie obrazu
		window->display();
	}
}

void Game::Render( sf::RenderWindow * window )
{
}
