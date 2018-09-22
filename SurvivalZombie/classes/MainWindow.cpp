#include "MainWindow.h"
#include <iostream>
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
	newGame();


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
			if ( event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::K )
			{
				saveGame( SaveSlot::SLOT_2 );
				loadGame( SaveSlot::SLOT_2 );
			}
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
	game = new Game;
}

void MainWindow::loadGame( SaveSlot slot )
{
	level_state lvlState;
	player_state playerState;
	std::vector<weapon_features> weapons;
	weapon_features tmp;
	std::string filename = "savegames\\saveslot" + std::to_string( static_cast< int >( slot ) ) + ".bin";

	std::ifstream file( filename.c_str(), std::ios::binary );

	file.read( (  char * )& lvlState, sizeof level_state );
	file.read( (  char * )& playerState, sizeof player_state );

	while ( !file.eof() )
	{
		file.read( ( char * )& tmp, sizeof weapon_features );
		if ( file.eof() )
			break;
		weapons.push_back( tmp );
	}

	file.close();

	std::cout << "Level: " << lvlState.level << std::endl;
	std::cout << "Points: " << lvlState.points << std::endl;
	std::cout << "Base level: " << lvlState.base_level << std::endl;
	std::cout << "Maxhitpoints: " << playerState.max_hitpoints << std::endl;
	std::cout << "Armor: " << playerState.armor << std::endl;
	std::cout << "Speed: " << playerState.speed << std::endl;

	for ( auto & it : weapons )
	{
		std::cout << "Type: " <<				static_cast<int>(it.type)	<< std::endl;
		std::cout << "MaxMagazineAmmo: " <<		it.maxMagazineAmmo			<< std::endl;
		std::cout << "MagazineAmmo: " <<		it.magazineAmmo				<< std::endl;
		std::cout << "CarriedAmmo: " <<			it.carriedAmmo				<< std::endl;
		std::cout << "RecoilTime " <<			it.cooldown.asMilliseconds()	<< std::endl;
		std::cout << "ReloadTime: " <<			it.reload_cooldown.asMilliseconds()	<< std::endl;
		std::cout << "Damage " <<				it.damage					<< std::endl;
		std::cout << "BulletSpeed: " <<			it.bullet_speed				<< std::endl;
	}
}

void MainWindow::saveGame( SaveSlot slot )
{
	level_state lvlState = game->GetLevelState();
	player_state playerState = game->GetPlayerState();
	std::vector<weapon_features> weapons = game->GetWeaponState();
	//weapon_features weaponState = { WeaponType::PISTOL, 10, 6, 120, sf::milliseconds( 400 ), sf::milliseconds( 1000 ), 20.0, 10.0 };	weapons.push_back( weaponState );
	//weaponState = { WeaponType::RIFLE, 30, 16, 150, sf::milliseconds( 300 ), sf::milliseconds( 1000 ), 40.0, 15.0 };					weapons.push_back( weaponState );
	
	std::string filename = "savegames\\saveslot" + std::to_string( static_cast< int >( slot ) ) + ".bin";

	std::ofstream file( filename.c_str(), std::ios::binary );

	file.write( ( const char * )& lvlState, sizeof level_state );
	file.write( ( const char * )& playerState, sizeof player_state );
	for ( auto & it : weapons )
	{
		file.write( ( const char * )& it, sizeof weapon_features );
	}

	file.close();
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
