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
	gameState = GameState::MENU;

	//Przygotowanie menu
	selectedButton = 0;
	mouseX = 0;
	mouseY = 0;
	shadow = 0;
	clicked = false;
	menuType = MenuType::DEFAULT;
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
		if ( gameState == GameState::MENU)
		{
			cursor->loadFromSystem( sf::Cursor::Arrow );
			window->setMouseCursor( *cursor );
			gameState = runMenu( event );
		}
		else if ( gameState == GameState::RUNNING)
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

	delete game;
	game = new Game( lvlState, playerState, weapons );
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
	height1 = 84;
	shadow = 3;


	//////MENU
	AssetManager::AddTexture( "backgroundMenu", ".\\graphics\\menu\\backgroundMenu.png" );
	backgroundMenu.setTexture( *AssetManager::GetTexture( "backgroundMenu" ) );

	AssetManager::AddTexture( "button[0]", ".\\graphics\\menu\\buttonContinueOff.png" );
	button[0].setTexture( *AssetManager::GetTexture( "button[0]" ) );
	button[0].setPosition( sf::Vector2f( posX, posY ) );
	AssetManager::AddTexture( "button[1]", ".\\graphics\\menu\\buttonContinueOn.png" );
	button[1].setTexture( *AssetManager::GetTexture( "button[1]" ) );
	button[1].setPosition( sf::Vector2f( posX, posY ) );

	AssetManager::AddTexture("button[2]", ".\\graphics\\menu\\buttonNewGameOff.png");
	button[2].setTexture( *AssetManager::GetTexture( "button[2]") );
	button[2].setPosition( sf::Vector2f( posX, posY + spacing ) );
	AssetManager::AddTexture("button[3]", ".\\graphics\\menu\\buttonNewGameOn.png");
	button[3].setTexture( *AssetManager::GetTexture( "button[3]" ) );
	button[3].setPosition( sf::Vector2f( posX, posY + spacing ) );

	AssetManager::AddTexture("button[4]", ".\\graphics\\menu\\buttonLoadGameOff.png");
	button[4].setTexture(*AssetManager::GetTexture("button[4]"));
	button[4].setPosition(sf::Vector2f(posX, posY + spacing * 2));
	AssetManager::AddTexture("button[5]", ".\\graphics\\menu\\buttonLoadGameOn.png");
	button[5].setTexture(*AssetManager::GetTexture("button[5]"));
	button[5].setPosition(sf::Vector2f(posX, posY + spacing * 2));

	AssetManager::AddTexture("button[6]", ".\\graphics\\menu\\buttonExitOff.png");
	button[6].setTexture(*AssetManager::GetTexture("button[6]"));
	button[6].setPosition(sf::Vector2f(posX, posY + spacing * 3));
	AssetManager::AddTexture("button[7]", ".\\graphics\\menu\\buttonExitOn.png");
	button[7].setTexture(*AssetManager::GetTexture("button[7]"));
	button[7].setPosition(sf::Vector2f(posX, posY + spacing * 3));

	height2 = 134;
	dposY = -100;
	dspacing = 1.5;
	AssetManager::AddTexture("button[8]", ".\\graphics\\menu\\buttonSlot1Off.png");
	button[8].setTexture(*AssetManager::GetTexture("button[8]"));
	button[8].setPosition(sf::Vector2f(posX, posY + dposY));
	AssetManager::AddTexture("button[9]", ".\\graphics\\menu\\buttonSlot1On.png");
	button[9].setTexture(*AssetManager::GetTexture("button[9]"));
	button[9].setPosition(sf::Vector2f(posX, posY + dposY));

	AssetManager::AddTexture("button[10]", ".\\graphics\\menu\\buttonSlot2Off.png");
	button[10].setTexture(*AssetManager::GetTexture("button[10]"));
	button[10].setPosition(sf::Vector2f(posX, posY + dposY + spacing * dspacing));
	AssetManager::AddTexture("button[11]", ".\\graphics\\menu\\buttonSlot2On.png");
	button[11].setTexture(*AssetManager::GetTexture("button[11]"));
	button[11].setPosition(sf::Vector2f(posX, posY + dposY + spacing * dspacing));

	AssetManager::AddTexture("button[12]", ".\\graphics\\menu\\buttonSlot3Off.png");
	button[12].setTexture(*AssetManager::GetTexture("button[12]"));
	button[12].setPosition(sf::Vector2f(posX, posY + dposY + spacing * dspacing * 2));
	AssetManager::AddTexture("button[13]", ".\\graphics\\menu\\buttonSlot3On.png");
	button[13].setTexture(*AssetManager::GetTexture("button[13]"));
	button[13].setPosition(sf::Vector2f(posX, posY + dposY + spacing * dspacing * 2));

	AssetManager::AddTexture("button[14]", ".\\graphics\\menu\\buttonReturnOff.png");
	button[14].setTexture(*AssetManager::GetTexture("button[14]"));
	button[14].setPosition(sf::Vector2f(posX, posY + dposY + spacing * dspacing * 3));
	AssetManager::AddTexture("button[15]", ".\\graphics\\menu\\buttonReturnOn.png");
	button[15].setTexture(*AssetManager::GetTexture("button[15]"));
	button[15].setPosition(sf::Vector2f(posX, posY + dposY + spacing * dspacing * 3));

	//£adowanie tekstur Asset Managerem
	//Podstawowe
	sf::Texture * tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\background.png");
	tmp->setRepeated(true);
	tmp->setSmooth(true);
	AssetManager::AddTexture("background", tmp);
	AssetManager::AddTexture("grad2", ".\\graphics\\grad2.png");

	//Hud
	AssetManager::AddTexture("handgun", ".\\graphics\\hud\\handgun.png");
	AssetManager::AddTexture("rifle", ".\\graphics\\hud\\rifle.png");
	AssetManager::AddTexture("shotgun", ".\\graphics\\hud\\shotgun.png");
	AssetManager::AddTexture("9mm", ".\\graphics\\hud\\9mm.png");
	AssetManager::AddTexture("7.62mm", ".\\graphics\\hud\\7.62mm.png");
	AssetManager::AddTexture("12gauge", ".\\graphics\\hud\\12gauge.png");

	//Animacje gracza
	AssetManager::AddTexture("bullet9mm", ".\\graphics\\animations\\bullet9mm.png");

	AssetManager::AddTexture("playerFeetWalkingAnimation", ".\\graphics\\animations\\player\\playerFeetWalkingAnimation.png");
	AssetManager::AddTexture("playerFeetIdleAnimation", ".\\graphics\\animations\\player\\playerFeetIdleAnimation.png");

	AssetManager::AddTexture("playerHandgunWalkingAnimation", ".\\graphics\\animations\\player\\playerHandgunWalkingAnimation.png");
	AssetManager::AddTexture("playerHandgunIdleAnimation", ".\\graphics\\animations\\player\\playerHandgunIdleAnimation.png");
	AssetManager::AddTexture("playerHandgunAttackingAnimation", ".\\graphics\\animations\\player\\playerHandgunAttackingAnimation.png");
	AssetManager::AddTexture("playerHandgunReloadingAnimation", ".\\graphics\\animations\\player\\playerHandgunReloadingAnimation.png");

	AssetManager::AddTexture("playerRifleWalkingAnimation", ".\\graphics\\animations\\player\\playerRifleWalkingAnimation.png");
	AssetManager::AddTexture("playerRifleIdleAnimation", ".\\graphics\\animations\\player\\playerRifleIdleAnimation.png");
	AssetManager::AddTexture("playerRifleAttackingAnimation", ".\\graphics\\animations\\player\\playerRifleAttackingAnimation.png");
	AssetManager::AddTexture("playerRifleReloadingAnimation", ".\\graphics\\animations\\player\\playerRifleReloadingAnimation.png");

	AssetManager::AddTexture("playerShotgunWalkingAnimation", ".\\graphics\\animations\\player\\playerShotgunWalkingAnimation.png");
	AssetManager::AddTexture("playerShotgunIdleAnimation", ".\\graphics\\animations\\player\\playerShotgunIdleAnimation.png");
	AssetManager::AddTexture("playerShotgunAttackingAnimation", ".\\graphics\\animations\\player\\playerShotgunAttackingAnimation.png");
	AssetManager::AddTexture("playerShotgunReloadingAnimation", ".\\graphics\\animations\\player\\playerShotgunReloadingAnimation.png");

	//Animacje zombie
	AssetManager::AddTexture("zombie40WalkingAnimation", ".\\graphics\\animations\\zombie40\\zombie40WalkingAnimation.png");
	AssetManager::AddTexture("zombie40AttackingAnimation", ".\\graphics\\animations\\zombie40\\zombie40AttackingAnimation.png");
	AssetManager::AddTexture("zombie40IdleAnimation", ".\\graphics\\animations\\zombie40\\zombie40IdleAnimation.png");
	AssetManager::AddTexture("zombie40Dead", ".\\graphics\\animations\\zombie40\\zombie40Dead.png");


	AssetManager::AddTexture("zombie50WalkingAnimation", ".\\graphics\\animations\\zombie50\\zombie50WalkingAnimation.png");
	AssetManager::AddTexture("zombie50AttackingAnimation", ".\\graphics\\animations\\zombie50\\zombie50AttackingAnimation.png");
	AssetManager::AddTexture("zombie50IdleAnimation", ".\\graphics\\animations\\zombie50\\zombie50IdleAnimation.png");
	AssetManager::AddTexture("zombie50Dead", ".\\graphics\\animations\\zombie50\\zombie50Dead.png");

	AssetManager::AddTexture("zombie60WalkingAnimation", ".\\graphics\\animations\\zombie60\\zombie60WalkingAnimation.png");
	AssetManager::AddTexture("zombie60AttackingAnimation", ".\\graphics\\animations\\zombie60\\zombie60AttackingAnimation.png");
	AssetManager::AddTexture("zombie60IdleAnimation", ".\\graphics\\animations\\zombie60\\zombie60IdleAnimation.png");
	AssetManager::AddTexture("zombie60Dead", ".\\graphics\\animations\\zombie60\\zombie60Dead.png");
}


GameState MainWindow::runMenu( sf::Event event )
{
	if ( !clicked && sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
	{
		mouseX = sf::Mouse::getPosition( *window ).x;
		mouseY = sf::Mouse::getPosition( *window ).y;

		if(menuType == MenuType::DEFAULT) runDefaultMenu();
		else if (menuType == MenuType::NEWGAME) runNewGameMenu();
		else if (menuType == MenuType::LOADGAME) runLoadGameMenu();
	}

	gameState = GameState::MENU;
	if ( clicked && event.type == sf::Event::MouseButtonReleased )
	{
		if ( event.mouseButton.button == sf::Mouse::Left )
		{
			mouseX = sf::Mouse::getPosition( *window ).x;
			mouseY = sf::Mouse::getPosition( *window ).y;
			clicked = false;

			if (menuType == MenuType::DEFAULT) gameState = runDefaultMenuClicked();
			else if (menuType == MenuType::NEWGAME) gameState = runNewGameMenuClicked();
			else if (menuType == MenuType::LOADGAME) gameState = runLoadGameMenuClicked();
		}
	}

	this->draw();

	return gameState;
}

void MainWindow::runDefaultMenu()
{
	if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY && mouseY <= shadow + posY + height1))
	{
		selectedButton = 1;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacing && mouseY <= shadow + posY + spacing + height1))
	{
		selectedButton = 3;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacing * 2 && mouseY <= shadow + posY + spacing * 2 + height1))
	{
		selectedButton = 5;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacing * 3 && mouseY <= shadow + posY + spacing * 3 + height1))
	{
		selectedButton = 7;
		clicked = true;
	}
}

void MainWindow::runNewGameMenu()
{
	if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY && mouseY <= shadow + posY + dposY + height2))
	{
		selectedButton = 9;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing && mouseY <= shadow + posY + dposY + spacing * dspacing + height2))
	{
		selectedButton = 11;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing * 2 && mouseY <= shadow + posY + dposY + spacing * dspacing * 2 + height2))
	{
		selectedButton = 13;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing * 3 && mouseY <= shadow + posY + dposY + spacing * dspacing * 3 + height1))
	{
		selectedButton = 15;
		clicked = true;
	}
}

void MainWindow::runLoadGameMenu()
{
	if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY && mouseY <= shadow + posY + dposY + height2))
	{
		selectedButton = 9;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing && mouseY <= shadow + posY + dposY + spacing * dspacing + height2))
	{
		selectedButton = 11;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing * 2 && mouseY <= shadow + posY + dposY + spacing * dspacing * 2 + height2))
	{
		selectedButton = 13;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing * 3 && mouseY <= shadow + posY + dposY + spacing * dspacing * 3 + height1))
	{
		selectedButton = 15;
		clicked = true;
	}
}

GameState MainWindow::runDefaultMenuClicked()
{
	if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY && mouseY <= shadow + posY + height1))
	{
		return GameState::RUNNING;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacing && mouseY <= shadow + posY + spacing + height1))
	{
		menuType = MenuType::NEWGAME;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacing * 2 && mouseY <= shadow + posY + spacing * 2 + height1))
	{
		menuType = MenuType::LOADGAME;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacing * 3 && mouseY <= shadow + posY + spacing * 3 + height1))
	{
		window->close();
	}

	return GameState::MENU;
}

GameState MainWindow::runNewGameMenuClicked()
{
	if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY && mouseY <= shadow + posY + dposY + height2))
	{
		return GameState::RUNNING;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing && mouseY <= shadow + posY + dposY + spacing * dspacing + height2))
	{
		return GameState::RUNNING;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing * 2 && mouseY <= shadow + posY + dposY + spacing * dspacing * 2 + height2))
	{
		return GameState::RUNNING;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing * 3 && mouseY <= shadow + posY + dposY + spacing * dspacing * 3 + height1))
	{
		menuType = MenuType::DEFAULT;
	}

	return GameState::MENU;
}

GameState MainWindow::runLoadGameMenuClicked()
{
	if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY && mouseY <= shadow + posY + dposY + height2))
	{
		return GameState::RUNNING;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing && mouseY <= shadow + posY + dposY + spacing * dspacing + height2))
	{
		return GameState::RUNNING;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing * 2 && mouseY <= shadow + posY + dposY + spacing * dspacing * 2 + height2))
	{
		return GameState::RUNNING;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + dposY + spacing * dspacing * 3 && mouseY <= shadow + posY + dposY + spacing * dspacing * 3 + height1))
	{
		menuType = MenuType::DEFAULT;
	}

	return GameState::MENU;
}

void MainWindow::draw()
{
	window->draw( backgroundMenu );

	if (menuType == MenuType::DEFAULT)
		for (int i = 0; i < 4; i++)
		{
			window->draw(button[i * 2]);
		}
	else if (menuType == MenuType::NEWGAME)
		for (int i = 4; i < 8; i++)
		{
			window->draw(button[i * 2]);
		}
	else if (menuType == MenuType::LOADGAME)
		for (int i = 4; i < 8; i++)
		{
			window->draw(button[i * 2]);
		}

	if ( clicked ) window->draw( button[selectedButton] );
}
