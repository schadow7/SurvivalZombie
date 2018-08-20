#include "Game.h"

Game::Game()
{
	world = new b2World( b2Vec2(0.f, 0.f ));
	entity_manager = new EntityManager( world );
	zombie_manager = new ZombieManager(zombieList);
	

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
	player = new Player( world, textures.at( "survivor" ), positionPixToWorld( 300, 300 ) );
	entity_manager->AddEntity( player );
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
	background.setTextureRect( sf::IntRect( 0, 0, 8000, 8000 ) );
	tmp->loadFromFile( ".\\graphics\\survivor.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "survivor", tmp ) );
}
void Game::runGame(sf::RenderWindow * window)
{
	initializeGame();
	sf::Time time;
	while ( window->isOpen() )
	{
		b2Vec2 velocity = b2Vec2_zero;
		sf::Event event;
		while ( window->pollEvent( event ) )
		{
			// Close window: exit
			if ( event.type == sf::Event::Closed )
				window->close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
				time = clock.getElapsedTime();
				if ( time > sf::milliseconds( 100 ) )
				{
					time = clock.restart();
					sf::Vector2i mousePos = sf::Mouse::getPosition( *window );
					sf::Vector2f cordPos = window->mapPixelToCoords( mousePos );
				}
			
				int mouseX = sf::Mouse::getPosition(*window).x;
				int mouseY = sf::Mouse::getPosition(*window).y;
				//zombieList[0]->ApplyForce(b2Vec2(mouseX, mouseY));
				Zombie* zombieTester = new Zombie(world, b2Vec2(mouseX, mouseY));
				zombieList.push_back(zombieTester);
				entity_manager->AddEntity(zombieTester);
		}

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
			velocity += b2Vec2( 0.f, -1.f );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
			velocity += b2Vec2( 0.f, 1.f );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
			velocity += b2Vec2( -1.f, 0.f );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
			velocity += b2Vec2( 1.f, 0.f );
		player->SetVelocity( velocity );

		//Wyświetlenie obrazu
		window->clear();
		window->draw( background );
		zombie_manager->AIStep();
		entity_manager->Update();
		entity_manager->Render(window);

		//Wyświetlenie obrazu
		window->display();
	}
}

void Game::Render( sf::RenderWindow * window )
{
}
