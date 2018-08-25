#include "Game.h"

Game::Game()
{
	world = new b2World( b2Vec2(0.f, 0.f ));
	entity_manager = new EntityManager( world );
	zombie_manager = new ZombieManager(zombieList);
	menu = new Menu();
	gameState = 0;
}

Game::~Game()
{
}

void Game::initializeGame()
{
	//TEMP undead tester
	Zombie * zombieTester = new Zombie( world, b2Vec2( 1.f, 1.f ) );
	zombieList.push_back( zombieTester );
	entity_manager->AddEntity( zombieTester );

	//Player
	player = new Player( world, textures.at( "survivor" ), positionPixToWorld( sf::Vector2f(300, 300) ) );
	entity_manager->AddEntity( player );
}

void Game::loadTextures()
{
	sf::Texture * tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\background.png");
	textures.insert(std::pair<std::string, sf::Texture*>("background", tmp));
	tmp->setRepeated( true );
	tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\grad1.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "grad1", tmp ) );
	background.setTexture( *textures.at( "background" ) );
	background.setTextureRect( sf::IntRect( 0, 0, 8000, 8000 ) );
	tmp->loadFromFile( ".\\graphics\\survivor.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "survivor", tmp ) );
}
void Game::runGame(sf::RenderWindow * window)
{
	initializeGame();
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
		if (gameState == 0)
		{
			gameState = menu->runMenu(window, event);
		}

		else if (gameState == 1)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int mouseX = sf::Mouse::getPosition(*window).x;
				int mouseY = sf::Mouse::getPosition(*window).y;
				//zombieList[0]->ApplyForce(b2Vec2(mouseX, mouseY));
				Zombie* zombieTester = new Zombie(world, b2Vec2(mouseX, mouseY));
				zombieList.push_back(zombieTester);
				entity_manager->AddEntity(zombieTester);
			}
			window->draw(background);
			zombie_manager->AIStep();
			entity_manager->Update();
			entity_manager->Render(window);
		}

		//Wyœwietlenie obrazu
		window->display();
	}
}

void Game::Render( sf::RenderWindow * window )
{
}
