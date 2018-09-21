#include "MainWindow.h"

MainWindow::MainWindow()
{
	//Przygotowanie okna
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window = new sf::RenderWindow( sf::VideoMode( 1280, 720, 32 ), "SurvivalZombie", sf::Style::Default, settings );
	window->setFramerateLimit( 60 );
	cursor = new sf::Cursor;
	gameState = 0;

	//Przygotowanie menu
	selectedButton = 0;
	clicked = false;
	loadTextures();

	//Test ³adowania tekstur asset managerem
	sf::Texture * tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\background.png" );
	//textures.insert(std::pair<std::string, sf::Texture*>("background", tmp));
	tmp->setRepeated( true );
	AssetManager::AddTexture( "background", tmp );

	AssetManager::AddTexture( "grad2", ".\\graphics\\grad2.png" );


	//Stworzenie gry
	game = new Game;



	game->loadTextures();
	game->initializeGame();
}

MainWindow::~MainWindow()
{
	delete this->window;
	delete this->game;
}

void MainWindow::run(  )
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
		if ( gameState == 0 )
		{
			cursor->loadFromSystem( sf::Cursor::Arrow );
			window->setMouseCursor( *cursor );
			gameState = runMenu( event );

		}
		else if ( gameState == 1 )
		{
			cursor->loadFromSystem( sf::Cursor::Cross );
			window->setMouseCursor( *cursor );
			game->runGame( window );
			
		}

		//Wyœwietlenie obrazu
		window->display();
	}
	
}

void MainWindow::newGame()
{

}

void MainWindow::loadGame( std::string filename )
{
}

void MainWindow::saveGame( std::string filename )
{
}


void MainWindow::loadTextures()
{
	posX = 100;
	posY = 200;
	spacing = 100;
	width = 304;
	height = 79;


	sf::Texture * tmp = new sf::Texture;
	tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\backgroundMenu.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "backgroundMenu", tmp ) );
	backgroundMenu.setTexture( *textures.at( "backgroundMenu" ) );


	tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\buttonPlayOff.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "button[0]", tmp ) );
	button[0].setTexture( *textures.at( "button[0]" ) );
	button[0].setPosition( sf::Vector2f( posX, posY ) );

	tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\buttonPlayOn.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "button[1]", tmp ) );
	button[1].setTexture( *textures.at( "button[1]" ) );
	button[1].setPosition( sf::Vector2f( posX, posY ) );


	tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\buttonOptionsOff.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "button[2]", tmp ) );
	button[2].setTexture( *textures.at( "button[2]" ) );
	button[2].setPosition( sf::Vector2f( posX, posY + spacing ) );

	tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\buttonOptionsOn.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "button[3]", tmp ) );
	button[3].setTexture( *textures.at( "button[3]" ) );
	button[3].setPosition( sf::Vector2f( posX, posY + spacing ) );


	tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\buttonExitOff.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "button[4]", tmp ) );
	button[4].setTexture( *textures.at( "button[4]" ) );
	button[4].setPosition( sf::Vector2f( posX, posY + spacing * 2 ) );

	tmp = new sf::Texture;
	tmp->loadFromFile( ".\\graphics\\buttonExitOn.png" );
	textures.insert( std::pair<std::string, sf::Texture*>( "button[5]", tmp ) );
	button[5].setTexture( *textures.at( "button[5]" ) );
	button[5].setPosition( sf::Vector2f( posX, posY + spacing * 2 ) );
}


int MainWindow::runMenu( sf::Event event )
{
	if ( !clicked && sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
	{
		int mouseX = sf::Mouse::getPosition( *window ).x;
		int mouseY = sf::Mouse::getPosition( *window ).y;

		if ( ( mouseX >= posX && mouseX <= posX + width ) &&
			( mouseY >= posY && mouseY <= posY + height ) )
		{
			selectedButton = 1;
			clicked = true;
		}
		else if ( ( mouseX >= posX && mouseX <= posX + width ) &&
			( mouseY >= posY + spacing && mouseY <= posY + spacing + height ) )
		{
			selectedButton = 3;
			clicked = true;
		}
		else if ( ( mouseX >= posX && mouseX <= posX + width ) &&
			( mouseY >= posY + spacing * 2 && mouseY <= posY + spacing * 2 + height ) )
		{
			selectedButton = 5;
			clicked = true;
		}
	}

	if ( clicked && event.type == sf::Event::MouseButtonReleased )
	{
		if ( event.mouseButton.button == sf::Mouse::Left )
		{
			int mouseX = sf::Mouse::getPosition( *window ).x;
			int mouseY = sf::Mouse::getPosition( *window ).y;
			clicked = false;

			if ( ( mouseX >= posX && mouseX <= posX + width ) &&
				( mouseY >= posY && mouseY <= posY + height ) )
			{
				return 1;
			}
			else if ( ( mouseX >= posX && mouseX <= posX + width ) &&
				( mouseY >= posY + spacing && mouseY <= posY + spacing + height ) )
			{
				selectedButton = 3;
			}
			else if ( ( mouseX >= posX && mouseX <= posX + width ) &&
				( mouseY >= posY + spacing * 2 && mouseY <= posY + spacing * 2 + height ) )
			{
				window->close();
			}
		}
	}

	this->draw( );

	return 0;
}




void MainWindow::draw( )
{
	window->draw( backgroundMenu );
	for ( int i = 0; i < MAX_NUMBER_OF_ITEMS; i++ )
	{
		window->draw( button[i * 2] );
	}
	if ( clicked ) window->draw( button[selectedButton] );
}
