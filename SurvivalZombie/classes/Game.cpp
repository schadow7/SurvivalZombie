#include "Game.h"
Game::Game() :
	mapsizex(1),
	mapsizey(1)
{
	gamePhase = GamePhase::GAME;
	world = new b2World(b2Vec2(0.f, 0.f));
	world->SetAllowSleeping( true );
	world->SetAutoClearForces( true );
	world->SetWarmStarting( true );

	entity_manager = new EntityManager(world);
	view = new sf::View(sf::FloatRect(0, 0, 1280, 720));
	hud = new Hud;
	loadTextures();
	initializeGame();
}

Game::Game( level_state lvlState, player_state playerState, std::vector<weapon_features> weaponState )
{
	gamePhase = GamePhase::GAME;
	world = new b2World( b2Vec2( 0.f, 0.f ) );
	world->SetAllowSleeping( true );
	world->SetAutoClearForces( true );
	world->SetWarmStarting( true );

	entity_manager = new EntityManager( world );

	view = new sf::View( sf::FloatRect( 0, 0, 1280, 720 ) );
	hud = new Hud;
	loadTextures();
	initializeGame( lvlState, playerState, weaponState );
}

Game::~Game()
{
	delete entity_manager;
	delete hud;
	delete view;

}

void Game::loadTextures()
{
	posX = 80;
	posY = 80;
	spacing = 100;
	spacingy = 88;
	width = 304;
	height1 = 84;
	shadow = 3;
	int up = 70;

	backgroundShop.setTexture(*AssetManager::GetTexture("backgroundMenu"));
	backgroundShop.setPosition(sf::Vector2f(0, 0));

	fontType.loadFromFile("cambria.ttc");

	//SHOP
	formatText(text[0], 75);
	text[0].setPosition(sf::Vector2f(545, -13));
	text[0].setString("SHOP");

	//MONEY
	formatText(text[1], 30);
	text[1].setFillColor(sf::Color::Green);
	text[1].setPosition(sf::Vector2f(950, 40));

	///////////////////////////////////////////////////////////////////////
	//PISTOL
	button[0].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[0].setPosition(sf::Vector2f(posX, posY + spacingy));
	weapon[0].setTexture(*AssetManager::GetTexture("handgun"));
	weapon[0].setPosition(sf::Vector2f(posX + 100, posY + spacingy));

	//RIFLE
	button[1].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[1].setPosition(sf::Vector2f(posX, posY + spacingy * 2));
	weapon[1].setTexture(*AssetManager::GetTexture("rifle"));
	weapon[1].setPosition(sf::Vector2f(posX + 50, posY + spacingy * 2 - 60));

	//SHOTGUN
	button[2].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[2].setPosition(sf::Vector2f(posX, posY + spacingy * 3));
	weapon[2].setTexture(*AssetManager::GetTexture("shotgun"));
	weapon[2].setPosition(sf::Vector2f(posX + 50, posY + spacingy * 3 - 50));
	///////////////////////////////////////////////////////////////////////
	//BASE
	button[3].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[3].setPosition(sf::Vector2f(posX, posY));
	formatText(text[2], 30);
	text[2].setPosition(sf::Vector2f(posX + 25, posY + 7));
	formatText(text[3], 30);
	text[3].setPosition(sf::Vector2f(posX + 25, posY + 42));
	//UPGRADE BASE
	button[4].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[4].setPosition(sf::Vector2f(posX + spacing * 4, posY));
	formatText(text[4], 30);
	text[4].setPosition(sf::Vector2f(posX + spacing * 4 + 27, posY + 7));
	formatText(text[5], 25);
	text[5].setFillColor(sf::Color::Green);
	text[5].setPosition(sf::Vector2f(posX + spacing * 4 + 90, posY + 45));
	///////////////////////////////////////////////////////////////////////
	//BUY/SELECT PISTOL
	button[5].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[5].setPosition(sf::Vector2f(posX + spacing * 4, posY + spacingy));
	formatText(text[6], 30);
	text[6].setPosition(sf::Vector2f(posX + spacing * 4 + 30, posY + spacingy + 7));
	formatText(text[7], 25);
	text[7].setFillColor(sf::Color::Green);
	text[7].setPosition(sf::Vector2f(posX + spacing * 4 + 90, posY + spacingy + 45));

	//BUY/SELECT RIFLE
	button[6].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[6].setPosition(sf::Vector2f(posX + spacing * 4, posY + spacingy * 2));
	formatText(text[8], 30);
	text[8].setPosition(sf::Vector2f(posX + spacing * 4 + 30, posY + spacingy * 2 + 7));
	formatText(text[9], 25);
	text[9].setFillColor(sf::Color::Green);
	text[9].setPosition(sf::Vector2f(posX + spacing * 4 + 90, posY + spacingy * 2 + 45));

	//BUY/SELECT SHOTGUN
	button[7].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[7].setPosition(sf::Vector2f(posX + spacing * 4, posY + spacingy * 3));
	formatText(text[10], 30);
	text[10].setPosition(sf::Vector2f(posX + spacing * 4 + 30, posY + spacingy * 3 + 7));
	formatText(text[11], 25);
	text[11].setFillColor(sf::Color::Green);
	text[11].setPosition(sf::Vector2f(posX + spacing * 4 + 90, posY + spacingy * 3 + 45));
	///////////////////////////////////////////////////////////////////////
	//BUY PISTOL AMMO
	button[8].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[8].setPosition(sf::Vector2f(posX + spacing * 8, posY + spacingy));
	formatText(text[12], 30);
	text[12].setPosition(sf::Vector2f(posX + spacing * 8 + 25, posY + spacingy + 7));
	formatText(text[13], 25);
	text[13].setFillColor(sf::Color::Green);
	text[13].setPosition(sf::Vector2f(posX + spacing * 8 + 90, posY + spacingy + 45));

	//BUY RIFLE AMMO
	button[9].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[9].setPosition(sf::Vector2f(posX + spacing * 8, posY + spacingy * 2));
	formatText(text[14], 30);
	text[14].setPosition(sf::Vector2f(posX + spacing * 8 + 30, posY + spacingy * 2 + 7));
	formatText(text[15], 25);
	text[15].setFillColor(sf::Color::Green);
	text[15].setPosition(sf::Vector2f(posX + spacing * 8 + 90, posY + spacingy * 2 + 45));

	//BUY SHOTGUN AMMO
	button[10].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[10].setPosition(sf::Vector2f(posX + spacing * 8, posY + spacingy * 3));
	formatText(text[16], 30);
	text[16].setPosition(sf::Vector2f(posX + spacing * 8 + 7, posY + spacingy * 3 + 7));
	formatText(text[17], 25);
	text[17].setFillColor(sf::Color::Green);
	text[17].setPosition(sf::Vector2f(posX + spacing * 8 + 90, posY + spacingy * 3 + 45));
	///////////////////////////////////////////////////////////////////////
	//UPGRADE DMG
	button[11].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[11].setPosition(sf::Vector2f(posX, posY + spacingy * 4 + up));
	formatText(text[18], 30);
	text[18].setPosition(sf::Vector2f(posX + 60, posY + spacingy * 4 + 7 + up));
	formatText(text[19], 25);
	text[19].setFillColor(sf::Color::Green);
	text[19].setPosition(sf::Vector2f(posX + 90, posY + spacingy * 4 + 45 + up));

	//UPGRADE RECOIL TIME
	button[12].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[12].setPosition(sf::Vector2f(posX + spacing * 4, posY + spacingy * 4 + up));
	formatText(text[20], 30);
	text[20].setPosition(sf::Vector2f(posX + spacing * 4 + 25, posY + spacingy * 4 + 7 + up));
	formatText(text[21], 25);
	text[21].setFillColor(sf::Color::Green);
	text[21].setPosition(sf::Vector2f(posX + spacing * 4 + 90, posY + spacingy * 4 + 45 + up));

	//UPGRADE RELOAD TIME
	button[13].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[13].setPosition(sf::Vector2f(posX + spacing * 8, posY + spacingy * 4 + up));
	formatText(text[22], 30);
	text[22].setPosition(sf::Vector2f(posX + spacing * 8 + 20, posY + spacingy * 4 + 7 + up));
	formatText(text[23], 25);
	text[23].setFillColor(sf::Color::Green);
	text[23].setPosition(sf::Vector2f(posX + spacing * 8 + 90, posY + spacingy * 4 + 45 + up));

	//UPGRADE MAG. CAP.
	button[14].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[14].setPosition(sf::Vector2f(posX, posY + spacingy * 5 + up));
	formatText(text[24], 30);
	text[24].setPosition(sf::Vector2f(posX + 35, posY + spacingy * 5 + 7 + up));
	formatText(text[25], 25);
	text[25].setFillColor(sf::Color::Green);
	text[25].setPosition(sf::Vector2f(posX + 90, posY + spacingy * 5 + 45 + up));

	//UPGRADE AMMO CAP.
	button[15].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[15].setPosition(sf::Vector2f(posX + spacing * 4, posY + spacingy * 5 + up));
	formatText(text[26], 30);
	text[26].setPosition(sf::Vector2f(posX + spacing * 4 + 27, posY + spacingy * 5 + 7 + up));
	formatText(text[27], 25);
	text[27].setFillColor(sf::Color::Green);
	text[27].setPosition(sf::Vector2f(posX + spacing * 4 + 90, posY + spacingy * 5 + 45 + up));

	//CLOSE SHOP
	button[16].setTexture(*AssetManager::GetTexture("buttonSmallOff"));
	button[16].setPosition(sf::Vector2f(posX + spacing * 8, posY + spacingy * 5 + up));
	formatText(text[28], 50);
	text[28].setPosition(sf::Vector2f(posX + spacing * 8 + 17, posY + spacingy * 5 + 13 + up));
}

void Game::formatText(sf::Text & text, int size)
{
	text.setFont(fontType);
	text.setCharacterSize(size);
	text.setFillColor(sf::Color::White);
	//text.setStyle( sf::Text::Bold );
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1);
}

void Game::runGame(sf::RenderWindow * window)
{
	window->clear();

	view->setCenter(player->GetPosition());
	window->setView(*view);

	//Sterowanie graczem i nie tylko
	Controls(window);

	window->draw(background);
	entity_manager->Update(clock.restart());
	entity_manager->Render(window);
	hud->Render(window, view, player);

}

GameState Game::runShop( sf::Window * window )
{
	mouseX = sf::Mouse::getPosition( *window ).x;
	mouseY = sf::Mouse::getPosition( *window ).y;

	if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY && mouseY <= shadow + posY + height1))
	{	
		selectedButton = 1;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacingy && mouseY <= shadow + posY + spacingy + height1))
	{
		selectedButton = 3;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacingy * 2 && mouseY <= shadow + posY + spacingy * 2 + height1))
	{
		selectedButton = 5;
		clicked = true;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacingy * 3 && mouseY <= shadow + posY + spacingy * 3 + height1))
	{
		selectedButton = 7;
		clicked = true;
	}

	return GameState::SHOP;
}

GameState Game::runShopClicked(sf::Window * window)
{
	mouseX = sf::Mouse::getPosition( *window ).x;
	mouseY = sf::Mouse::getPosition( *window ).y;
	clicked = false;

	if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY && mouseY <= shadow + posY + height1))
	{
		return GameState::RUNNING;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacingy && mouseY <= shadow + posY + spacingy + height1))
	{
		return GameState::RUNNING;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacingy * 2 && mouseY <= shadow + posY + spacingy * 2 + height1))
	{
		return GameState::SHOP;
	}
	else if ((mouseX >= shadow + posX && mouseX <= shadow + posX + width) &&
		(mouseY >= shadow + posY + spacingy * 3 && mouseY <= shadow + posY + spacingy * 3 + height1))
	{
		return GameState::SHOP;
	}

	return GameState::SHOP;
}

void Game::setText()
{
	int PLACEHOLDER = 1;
	selectedWeapon = SelectedWeapon::PISTOL;

	text[1].setString("Money: " + std::to_string(GetLevelState().points) + "$");

	text[2].setString("Base level: " + std::to_string(PLACEHOLDER));
	text[3].setString("Wall Hitpoints: " + std::to_string(PLACEHOLDER));
	text[4].setString("Upgrade base level");
	text[5].setString("Price: " + std::to_string(PLACEHOLDER) + "$");

	text[12].setString("Buy Pistol Magazine");
	text[13].setString("Price: " + std::to_string(PLACEHOLDER) + "$");
	text[14].setString("Buy Rifle Magazine");
	text[15].setString("Price: " + std::to_string(PLACEHOLDER) + "$");
	text[16].setString("Buy Shotgun Magazine");
	text[17].setString("Price: " + std::to_string(PLACEHOLDER) + "$");

	text[18].setString("Upgrade DMG");
	text[19].setString("Price: " + std::to_string(PLACEHOLDER) + "$");
	text[20].setString("Upgrade recoil time");
	text[21].setString("Price: " + std::to_string(PLACEHOLDER) + "$");
	text[22].setString("Upgrade reload time");
	text[23].setString("Price: " + std::to_string(PLACEHOLDER) + "$");
	text[24].setString("Upgrade mag. cap.");
	text[25].setString("Price: " + std::to_string(PLACEHOLDER) + "$");
	text[26].setString("Upgrade ammo cap.");
	text[27].setString("Price: " + std::to_string(PLACEHOLDER) + "$");

	text[28].setString("CLOSE SHOP");

	if (!isWeaponSelected())
	{
		for (int i = 9; i < 14; i++)
		{
			text[i * 2].setFillColor(sf::Color(50, 50, 50));
			text[i * 2 + 1].setFillColor(sf::Color(25, 50, 25));
			button[i + 2].setColor(sf::Color(50, 50, 50));
		}
	}
	else
	{
		for (int i = 9; i < 14; i++)
		{
			text[i * 2].setFillColor(sf::Color::White);
			text[i * 2 + 1].setFillColor(sf::Color::Green);
			button[i + 2].setColor(sf::Color(255, 255, 255));
		}
	}

	if (!pistolOwned())
	{
		button[0].setColor(sf::Color(50, 50, 50));
		text[6].setPosition(sf::Vector2f(posX + spacing * 4 + 80, posY + spacingy + 7));
		text[6].setString("Buy Pistol");
		text[7].setFillColor(sf::Color::Green);
		text[7].setString("Price: " + std::to_string(PLACEHOLDER) + "$");
		text[12].setFillColor(sf::Color(50, 50, 50));
		text[13].setFillColor(sf::Color(25, 50, 25));
		button[8].setColor(sf::Color(50, 50, 50));
	}
	else
	{
		button[0].setColor(sf::Color(255, 255, 255));
		text[6].setPosition(sf::Vector2f(posX + spacing * 4 + 70, posY + spacingy + 7));
		text[6].setString("Select Pistol");
		text[7].setFillColor(sf::Color::White);
		text[7].setString("Ammo: " + std::to_string(PLACEHOLDER));
		text[12].setFillColor(sf::Color::White);
		text[13].setFillColor(sf::Color::Green);
		button[8].setColor(sf::Color(255, 255, 255));
	}


	if (!rifleOwned())
	{
		button[1].setColor(sf::Color(50, 50, 50));
		text[8].setPosition(sf::Vector2f(posX + spacing * 4 + 90, posY + spacingy * 2 + 7));
		text[8].setString("Buy Rifle");
		text[9].setFillColor(sf::Color::Green);
		text[9].setString("Price: " + std::to_string(PLACEHOLDER) + "$");
		text[14].setFillColor(sf::Color(50, 50, 50));
		text[15].setFillColor(sf::Color(25, 50, 25));
		button[9].setColor(sf::Color(50, 50, 50));
	}
	else
	{
		button[1].setColor(sf::Color(255, 255, 255));
		text[8].setPosition(sf::Vector2f(posX + spacing * 4 + 77, posY + spacingy * 2 + 7));
		text[8].setString("Select Rifle");
		text[9].setFillColor(sf::Color::White);
		text[9].setString("Ammo: " + std::to_string(PLACEHOLDER));
		text[14].setFillColor(sf::Color::White);
		text[15].setFillColor(sf::Color::Green);
		button[9].setColor(sf::Color(255, 255, 255));
	}


	if (!shotgunOwned())
	{
		button[2].setColor(sf::Color(50, 50, 50));
		text[10].setPosition(sf::Vector2f(posX + spacing * 4 + 70, posY + spacingy * 3 + 7));
		text[10].setString("Buy Shotgun");
		text[11].setFillColor(sf::Color::Green);
		text[11].setString("Price: " + std::to_string(PLACEHOLDER) + "$");
		text[16].setFillColor(sf::Color(50, 50, 50));
		text[17].setFillColor(sf::Color(25, 50, 25));
		button[10].setColor(sf::Color(50, 50, 50));
	}
	else
	{
		button[2].setColor(sf::Color(255, 255, 255));
		text[10].setPosition(sf::Vector2f(posX + spacing * 4 + 57, posY + spacingy * 3 + 7));
		text[10].setString("Select Shotgun");
		text[11].setFillColor(sf::Color::White);
		text[11].setString("Ammo: " + std::to_string(PLACEHOLDER));
		text[16].setFillColor(sf::Color::White);
		text[17].setFillColor(sf::Color::Green);
		button[10].setColor(sf::Color(255, 255, 255));
	}
}

bool Game::pistolOwned()
{
	return false;
}

bool Game::rifleOwned()
{
	return true;
}

bool Game::shotgunOwned()
{
	return true;
}

bool Game::isWeaponSelected()
{
	return false;
}

void Game::drawShop(sf::RenderWindow * window)
{
	window->draw(backgroundShop);
	
	for (int i = 0; i < 3; i++)
	{
		window->draw(button[i]);
		window->draw(weapon[i]);
	}

	for (int i = 3; i < 17; i++)
	{
		window->draw(button[i]);
	}

	for (int i = 0; i < 50; i++)
	{
		window->draw(text[i]);
	}
}

void Game::initializeGame()
{
	undeadCount = 0;
	currentLevel = 0;
	baseLevel = 0;
	mapsizex = (*AssetManager::GetTexture("map")).getSize().x;
	mapsizey = (*AssetManager::GetTexture("map")).getSize().y;
	delay = sf::milliseconds( 0 );
	delay2 = sf::milliseconds(0);
	loadTextures();
	mapCenter = b2Vec2(mapsizex/2.0f / SCALE, mapsizey/2.0f / SCALE );
	previous_angle = 0.f;
	shoot_timer = sf::seconds( 1 );
	//T³o
	background.setTexture(*AssetManager::GetTexture("map"));
	background.setTextureRect(sf::IntRect(0, 0, mapsizex, mapsizey));
	previousMousePos = sf::Vector2f( 0, 0 );
	engine.seed(time(0));
	arrangeObstacles(25);
	makeBase();
	//Player
	player = new Player(world, positionPixToWorld(sf::Vector2f(mapsizex / 2.0f, mapsizey / 2.0f + 96)));
	entity_manager->AddEntity(player);
	//Bazowa broñ
	Weapon * pistol = new Pistol(entity_manager, AssetManager::GetTexture("bullet9mm"));
	player->AddWeapon(pistol);
	Weapon * rifle = new Rifle( entity_manager, AssetManager::GetTexture( "bullet9mm" ) );
	player->AddWeapon( rifle );
	Weapon * shotgun = new Shotgun( entity_manager, AssetManager::GetTexture( "bullet9mm" ) );
	player->AddWeapon( shotgun );
	startLevelSound.setBuffer(*AssetManager::GetSound("brains"));
	for (int i = 1; i < 25; i++)
	{
		sf::Sound temp;
		temp.setBuffer(*AssetManager::GetSound("zombie" + std::to_string(i)));
		temp.setVolume(20);
		zombieNoises.push_back(temp);
	}
}

void Game::initializeGame( level_state lvlState, player_state playerState, std::vector<weapon_features> weaponState )
{
	undeadCount = 0;
	currentLevel = lvlState.level;
	baseLevel = lvlState.base_level;
	points = lvlState.points;
	loadTextures();
	mapsizex = (*AssetManager::GetTexture("map")).getSize().x;
	mapsizey = (*AssetManager::GetTexture("map")).getSize().y;
	delay = sf::milliseconds( 0 );
	delay2 = sf::milliseconds(0);
	mapCenter = b2Vec2( mapsizex / 2.0f / SCALE, mapsizey / 2.0f / SCALE );
	previous_angle = 0.f;
	shoot_timer = sf::seconds( 1 );
	//T³o
	background.setTexture( *AssetManager::GetTexture( "map" ) );
	background.setTextureRect( sf::IntRect( 0, 0, mapsizex, mapsizey ) );
	previousMousePos = sf::Vector2f( 0, 0 );
	engine.seed( time( 0 ) );
	arrangeObstacles( 25 );
	makeBase();
	//Player
	player = new Player( world, positionPixToWorld( sf::Vector2f( mapsizex / 2.0f, mapsizey / 2.0f + 96 ) ) , playerState );
	entity_manager->AddEntity( player );
	//Dodawanie broni
	Weapon * tmp;
	for ( auto & it : weaponState )
	{
		if ( it.type == WeaponType::PISTOL )
		{
			tmp = new Pistol( entity_manager, AssetManager::GetTexture( "bullet9mm" ), it );
			player->AddWeapon( tmp );
		}
		if ( it.type == WeaponType::RIFLE )
		{
			tmp = new Rifle( entity_manager, AssetManager::GetTexture( "bullet9mm" ), it );
			player->AddWeapon( tmp );
		}
		if ( it.type == WeaponType::SHOTGUN )
		{
			tmp = new Shotgun( entity_manager, AssetManager::GetTexture( "bullet9mm" ), it );
			player->AddWeapon( tmp );
		}

	}
	startLevelSound.setBuffer(*AssetManager::GetSound("brains"));
	for (int i = 1; i < 25; i++)
	{
		sf::Sound temp;
		temp.setBuffer(*AssetManager::GetSound("zombie" + std::to_string(i)));
		temp.setVolume(20);
		zombieNoises.push_back(temp);
	}
}

void Game::Controls(sf::RenderWindow * window)
{
	delay -= clock.getElapsedTime();
	delay2 -= clock.getElapsedTime();
	//Przygotowanie wektorów
	b2Vec2 velocity = b2Vec2_zero;
	b2Vec2 normalize_direction = b2Vec2_zero;
	//Odczytanie pozycji kursora
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
	normalize_direction = positionPixToWorld( cordPos ) - positionPixToWorld( player->GetWeaponPosition() );
	normalize_direction.Normalize();
	if ( 100.f * b2Distance( positionPixToWorld( player->GetPosition() ), positionPixToWorld( cordPos ) ) < 85.f )
	{
		normalize_direction = positionPixToWorld( cordPos ) - positionPixToWorld( player->GetWeaponPosition() );
		normalize_direction.Normalize();
		previousMousePos = player->GetPosition() + positionWorldToPix( 0.95f * normalize_direction );
		sf::Mouse::setPosition( window->mapCoordsToPixel( previousMousePos ), *window );
		cordPos = previousMousePos;
	}

	//Wyznaczenie znormalizowanego wektora wyznaczaj¹cego kierunek od gracza do pozycycji myszki
	normalize_direction = positionPixToWorld(cordPos) - positionPixToWorld(player->GetWeaponPosition());
	normalize_direction.Normalize();

	//konkretne klawisze
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Num5 ) && delay <= sf::milliseconds( 0 ) )
	{
		Zombie* zombieTester = new Zombie(world, positionPixToWorld(cordPos));
		zombieTester->SetTarget(player);
		zombieTester->SetAI(Zombie::Chaotic);
		entity_manager->AddEntity(zombieTester);
		undeadCount++;
		delay = sf::milliseconds( 500 );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && delay <= sf::milliseconds( 0 ) )
	{
		Zombie* zombieTester = new ZombieTank(world, positionPixToWorld(cordPos));
		zombieTester->SetTarget(player);
		zombieTester->SetAI(Zombie::Chaotic);
		entity_manager->AddEntity(zombieTester);
		delay = sf::milliseconds( 500 );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) && delay <= sf::milliseconds( 0 ) )
	{
		Zombie* zombieTester = new ZombieSprinter(world, positionPixToWorld(cordPos));
		zombieTester->SetTarget(player);
		zombieTester->SetAI(Zombie::Chaotic);
		entity_manager->AddEntity(zombieTester);
		delay = sf::milliseconds( 500 );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && delay <= sf::milliseconds( 0 ) )
	{
		spawnHorde(1);
		delay = sf::milliseconds( 500 );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && delay <= sf::milliseconds( 0 ) )
	{
			currentLevel++;
			spawnHorde(currentLevel);
			printf("level:%d undeadCount:%d\n", currentLevel, undeadCount);
			delay = sf::milliseconds( 500 );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && delay <= sf::milliseconds( 0 ) )
	{
		StaticBody* ob = new TheBase(world, positionPixToWorld(cordPos), sf::Vector2i(10, 5) );
		entity_manager->AddEntity(ob);
		delay = sf::milliseconds( 500 );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && delay <= sf::milliseconds( 0 ) )
	{
		setBaseLevel(++baseLevel);
		delay = sf::milliseconds( 500 );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::E ) && delay <= sf::milliseconds( 0 ) )
	{
		player->ChangeWeaponRight();
		delay = sf::milliseconds( 500 );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) entity_manager->KillEverybody();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) player->Reload();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) velocity += b2Vec2(0, -1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) velocity += b2Vec2(0, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity += b2Vec2(-1, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity += b2Vec2(1, 0);

	if (undeadCount <= 0)
	{
		currentLevel++;
		startLevelSound.play();
		spawnHorde(currentLevel);
		printf("level:%d undeadCount:%d\n", currentLevel, undeadCount);
	}
	if (undeadCount > 0 && delay2 <= sf::milliseconds(0))
	{
		zombieNoises[noiseDistribution(engine)].play();
		delay2 = sf::milliseconds(30 * angleDistribution(engine));

	}

	shoot_timer += clock.getElapsedTime();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		player->Shoot(normalize_direction, shoot_timer);
		shoot_timer = sf::seconds(0);
	}


	player->SetVelocity(velocity);
	previous_angle = atan2f(normalize_direction.y, normalize_direction.x); player->SetAngle(previous_angle);
}

void Game::updateObserver(Entity * ptr)
{
	if (ptr->GetID() == 2) undeadCount--;
}

level_state Game::GetLevelState()
{
	level_state tmp = { currentLevel, points, baseLevel };
	return tmp;
}

player_state Game::GetPlayerState()
{
	return player->GetPlayerState();
}

std::vector<weapon_features> Game::GetWeaponState()
{
	return player->GetWeaponList();
}

void Game::PlayMusic()
{
	if ( isWave() && ( music.getStatus() == sf::SoundSource::Status::Paused || music.getStatus() == sf::SoundSource::Status::Stopped ) )
	{
		music.openFromFile( ".\\music\\theme2.ogg" );
		music.setVolume( 2 );
		music.setLoop( true );
	}
	else if ( !isWave() && ( music.getStatus() == sf::SoundSource::Status::Paused || music.getStatus() == sf::SoundSource::Status::Stopped ) )
	{
		music.openFromFile( ".\\music\\theme2.ogg" );
		music.setVolume( 2 );
		music.setPlayingOffset( sf::seconds( 40 ) );
		music.setLoop( true );
	}
	if(   music.getStatus() == sf::SoundSource::Status::Paused || music.getStatus() == sf::SoundSource::Status::Stopped  )
		music.play();
}

void Game::StopMusic()
{
	music.pause();
}

bool Game::isWave()
{
	return false;
}

void Game::Render(sf::RenderWindow * window)
{
}

void Game::spawnHorde(int next_level)
{
	float spawnRadius = (mapsizex/2-500) / SCALE;
	float angle = 0;
	b2Vec2 spawnPoint = b2Vec2_zero;
	int type = 0;
	Zombie* zombieTmp;
	std::vector<int> zombieQuantity;
	newLevel(next_level, zombieQuantity);
	for (auto & it : zombieQuantity)
	{
		type++;
		for (int i = 0; i < it; i++)
		{
			float radius = spawnRadius + angleDistribution(engine)/ SCALE;
			angle = angleDistribution(engine)*DEGTORAD;
			spawnPoint.x = mapCenter.x + radius * cos(angle);
			spawnPoint.y = mapCenter.y + radius * sin(angle);
			if (type == 2) zombieTmp = new ZombieTank(world, spawnPoint);
			else if (type == 3) zombieTmp = new ZombieSprinter(world, spawnPoint);
			else zombieTmp = new Zombie(world, spawnPoint);
			zombieTmp->SetTarget(player);
			zombieTmp->SetAI(Zombie::Chaotic);
			entity_manager->AddEntity(zombieTmp);
			zombieTmp->registerObserver(this);
			zombieTmp->registerObserver(player);
			undeadCount++;
		}
	}
}

std::vector<int> Game::newLevel(int levelNr, std::vector<int>& zombieQuantity)
{
	unsigned int number_of_zombie_types = 3;
	if (levelNr)
	{
		for (unsigned int i = 0; i < number_of_zombie_types; i++)
		{
			int random_part = levelNr * zombieDistribution(engine);
			if (abs(random_part) > 3) random_part = 6;
			zombieQuantity.push_back(levelNr*(number_of_zombie_types - i) + random_part);
		}
	}
	return zombieQuantity;
}

void Game::arrangeObstacles(int quantity)
{
	if (quantity)
	{
		struct obstacleInfo { b2Vec2 spawnPoint; sf::Vector2i size; sf::Texture * tex; };
		Obstacle* temp;
		quantity = 14;
		obstacleInfo obstacle[14];

		obstacle[0] = { mapCenter + b2Vec2( -5, 1 ),	 sf::Vector2i( 52, 32 ),	AssetManager::GetTexture( "stone4" ) };
		obstacle[1] = { mapCenter + b2Vec2( -3, 5 ),	 sf::Vector2i( 52, 32 ),	AssetManager::GetTexture( "stone2" ) };
		obstacle[2] = { mapCenter + b2Vec2( -8, 3 ),	 sf::Vector2i( 125, 149 ),  AssetManager::GetTexture( "tree7" ) };
		obstacle[3] = { mapCenter + b2Vec2( -10, -8 ),	 sf::Vector2i( 52, 32 ),	AssetManager::GetTexture( "stone4" ) };
		obstacle[4] = { mapCenter + b2Vec2( -3, -4 ),  	 sf::Vector2i( 52, 32 ),	AssetManager::GetTexture( "stone4" ) };
		obstacle[5] = { mapCenter + b2Vec2( 10, 3 ),	 sf::Vector2i( 52, 32 ),	AssetManager::GetTexture( "stone2" ) };
		obstacle[6] = { mapCenter + b2Vec2( 8, 2 ),		 sf::Vector2i( 125, 149 ),  AssetManager::GetTexture( "tree7" ) };
		obstacle[7] = { mapCenter + b2Vec2( 4, -8 ),		 sf::Vector2i( 52, 32 ),	AssetManager::GetTexture( "stone4" ) };
		obstacle[8] = { mapCenter + b2Vec2( 6, 5 ),		 sf::Vector2i( 52, 32 ),	AssetManager::GetTexture( "stone2" ) };
		obstacle[9] = { mapCenter + b2Vec2( 1, 11 ),	 sf::Vector2i( 52, 32 ),	AssetManager::GetTexture( "stone4" ) };
		obstacle[10] = { mapCenter + b2Vec2( 0.5f, -6 ),	 sf::Vector2i( 125, 149 ),	AssetManager::GetTexture( "tree7" ) };
		obstacle[11] = { mapCenter + b2Vec2( 4, -8 ),	 sf::Vector2i( 52, 32 ),	AssetManager::GetTexture( "stone4" ) };
		obstacle[12] = { mapCenter + b2Vec2( 2, -4 ),	 sf::Vector2i( 52, 32 ),	AssetManager::GetTexture( "stone2" ) };
		obstacle[13] = { mapCenter + b2Vec2( 4, 4 ),	 sf::Vector2i( 52, 32 ),	AssetManager::GetTexture( "stone2" ) };

		for ( int i = 0; i < quantity; i++ )
		{
			temp = new Obstacle( world, obstacle[i].spawnPoint, obstacle[i].size, obstacle[i].tex );
			entity_manager->AddEntity( temp );
		}
		/*
		float angle = 0;
		b2Vec2 spawnPoint = b2Vec2_zero;
		int spawnRadius;
		Obstacle* temp;
		std::uniform_int_distribution<int>	obstacleRadiusDistribution{ 500, mapsizex/2 };
		for (int i = 0; i < quantity; i++)
		{
			angle = angleDistribution(engine)*DEGTORAD;
			spawnRadius = obstacleRadiusDistribution(engine) / SCALE;
			spawnPoint.x = mapCenter.x + spawnRadius * cos(angle);
			spawnPoint.y = mapCenter.y + spawnRadius * sin(angle);
			temp = new Obstacle(world, spawnPoint);
			entity_manager->AddEntity( temp );
		}

		*/
	}
}

void Game::makeBase()
{
	int sizex = 50;
	int boxSize = 8;
	sf::Vector2f position(mapsizex/2 - boxSize/2 * sizex, mapsizey/2 - boxSize / 2 * sizex);
	BasicEntanglements* ob;
	TheBase* Base = new TheBase( world, mapCenter, sf::Vector2i( 80, 82 ), AssetManager::GetTexture( "box22" ) );
	entity_manager->AddEntity(Base);
	for (int i = 0; i < boxSize; i++)
	{
		ob=spawnWall(i, boxSize, position);
		entity_manager->AddEntity(ob);
		ob->SetAngle(90);
		position.x += sizex;
	}
	position.x -= sizex / 4;
	position.y += sizex / 4;
	for (int i = 0; i < boxSize; i++)
	{
		ob = spawnWall(i, boxSize, position);
		entity_manager->AddEntity(ob);
		position.y += sizex;
	}
	position.y -= sizex / 4;
	position.x -= sizex / 4;
	for (int i = 0; i < boxSize; i++)
	{
		ob = spawnWall(i, boxSize, position);
		entity_manager->AddEntity(ob);
		ob->SetAngle(90);
		position.x -= sizex;
	}
	position.x += sizex / 4;
	position.y -= sizex / 4;
	for (int i = 0; i < boxSize; i++)
	{
		ob = spawnWall(i, boxSize, position);
		entity_manager->AddEntity(ob);
		position.y -= sizex;
	}
}

BasicEntanglements* Game::spawnWall(int i, int boxSize, sf::Vector2f& position)
{
	BasicEntanglements* ob;
	if ( i != floor( boxSize / 2 ) )
		ob = new BasicEntanglements( world, positionPixToWorld( position ), sf::Vector2i( 25, 50 ), AssetManager::GetTexture( "wall" ) );
	else
		ob = new Door(world, positionPixToWorld(position), sf::Vector2i( 25, 50 ), AssetManager::GetTexture( "wall" ) );
	base.push_back(ob);
	return ob;
}

void Game::setBaseLevel(int level)
{
	for (auto & it : base)
	{
		it->SetDamage(level);
		it->SetMaxHP(50 * level);
		it->Repair(50 * level);
		it->MakeActive();
	}
}
