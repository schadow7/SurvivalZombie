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

	//Stworzenie gry
	game = new Game;
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

		//Wyświetlenie obrazu
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


	//////MENU
	AssetManager::AddTexture( "backgroundMenu", ".\\graphics\\menu\\backgroundMenu.png" );
	backgroundMenu.setTexture( *AssetManager::GetTexture( "backgroundMenu" ) );

	AssetManager::AddTexture( "button[0]", ".\\graphics\\menu\\buttonPlayOff.png" );
	button[0].setTexture( *AssetManager::GetTexture( "button[0]" ) );
	button[0].setPosition( sf::Vector2f( posX, posY ) );

	AssetManager::AddTexture( "button[1]", ".\\graphics\\menu\\buttonPlayOn.png" );
	button[1].setTexture( *AssetManager::GetTexture( "button[1]" ) );
	button[1].setPosition( sf::Vector2f( posX, posY ) );

	AssetManager::AddTexture("button[2]", ".\\graphics\\menu\\buttonOptionsOff.png");
	button[2].setTexture( *AssetManager::GetTexture( "button[2]") );
	button[2].setPosition( sf::Vector2f( posX, posY + spacing ) );

	AssetManager::AddTexture("button[3]", ".\\graphics\\menu\\buttonOptionsOn.png");
	button[3].setTexture( *AssetManager::GetTexture( "button[3]" ) );
	button[3].setPosition( sf::Vector2f( posX, posY + spacing ) );
	
	AssetManager::AddTexture("button[4]", ".\\graphics\\menu\\buttonExitOff.png");
	button[4].setTexture( *AssetManager::GetTexture( "button[4]" ) );
	button[4].setPosition( sf::Vector2f( posX, posY + spacing * 2 ) );
	
	AssetManager::AddTexture("button[5]", ".\\graphics\\menu\\buttonExitOn.png");
	button[5].setTexture( *AssetManager::GetTexture( "button[5]" ) );
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

	this->draw();

	return 0;
}




void MainWindow::draw()
{
	window->draw( backgroundMenu );
	for ( int i = 0; i < MAX_NUMBER_OF_ITEMS; i++ )
	{
		window->draw( button[i * 2] );
	}
	if ( clicked ) window->draw( button[selectedButton] );
}
