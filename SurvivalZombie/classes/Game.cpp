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
	view = new sf::View( sf::FloatRect( 0, 0, 1280, 720 ) );
	menu = new Menu();
	cursor = new sf::Cursor;
	gameState = 0;
}

Game::~Game()
{
	
}

void Game::initializeGame()
{
	//Player
	player = new Player( world, textures.at( "survivor" ), positionPixToWorld( sf::Vector2f(300, 300) ) );
	entity_manager->AddEntity( player );

	//TEMP undead tester
	Zombie * zombieTester = new Zombie(world, b2Vec2(1.f, 1.f));
	entity_manager->AddEntity(zombieTester);
	zombieTester->SetTarget(player);
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
void Game::Controls( sf::RenderWindow * window )
{
	//Przygotowanie wektorów
	b2Vec2 velocity = b2Vec2_zero;
	b2Vec2 normalize_direction = b2Vec2_zero;
	//Odczytanie pozycji kursora
	sf::Vector2i mousePos = sf::Mouse::getPosition( *window );
	sf::Vector2f cordPos = window->mapPixelToCoords( mousePos );
	//Wyznaczenie znormalizowanego wektora wyznaczającego kierunek od gracza do pozycycji myszki
	normalize_direction = positionPixToWorld( cordPos ) - positionPixToWorld( player->GetPosition() );
	normalize_direction.Normalize();
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Q ) )
	{
		Zombie* zombieTester = new Zombie( world, positionPixToWorld( cordPos ) );
		zombieTester->SetTarget( player );
		entity_manager->AddEntity( zombieTester );

	}

	if ( sf::Mouse::isButtonPressed( sf::Mouse::Right ) )
	{
		Brick* obstacle = new Brick( world, textures.at( "grad1" ), cordPos.x, cordPos.y );
		entity_manager->AddEntity( obstacle );

	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
		velocity += b2Vec2( normalize_direction );
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
		velocity += b2Vec2( -normalize_direction );
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
		velocity += b2Vec2( normalize_direction.y, -normalize_direction.x );
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
		velocity += b2Vec2( -normalize_direction.y, normalize_direction.x );
	player->SetVelocity( velocity );
	player->SetAngle( atan2f( normalize_direction.y, normalize_direction.x ) );
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


		//Wyświetlenie obrazu
		if (gameState == 0)
		{
			cursor->loadFromSystem( sf::Cursor::Arrow );
			window->setMouseCursor( *cursor );
			gameState = menu->runMenu(window, event);
			
		}

		else if (gameState == 1)
		{
			cursor->loadFromSystem( sf::Cursor::Cross );
			window->setMouseCursor( *cursor );
			window->clear();
			view->setCenter( player->GetPosition() );
			window->setView( *view );
			
			//Sterowanie graczem i nie tylko
			Controls( window );

			window->draw(background);
			entity_manager->Update();
			entity_manager->Render(window);
			sf::Vertex line[] =
			{
				sf::Vertex( player->GetPosition() ),
				sf::Vertex( window->mapPixelToCoords( sf::Mouse::getPosition( *window ) ) )
			};
			window->draw( line, 2, sf::Lines );
		}

		//Wyświetlenie obrazu
		window->display();
	}
}

void Game::Render( sf::RenderWindow * window )
{
}
