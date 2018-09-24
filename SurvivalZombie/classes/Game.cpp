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

	initializeGame( lvlState, playerState, weaponState );
}

Game::~Game()
{
	delete entity_manager;
	delete hud;
	delete view;

}

void Game::runGame(sf::RenderWindow * window)
{
	window->clear();


	if (gamePhase == GamePhase::GAME)
	{
		view->setCenter(player->GetPosition());
		window->setView(*view);

		//Sterowanie graczem i nie tylko
		Controls(window);

		window->draw(background);
		entity_manager->Update(clock.restart());
		entity_manager->Render(window);
		hud->Render(window, view, player);
	}

	else if (gamePhase == GamePhase::SHOP)
	{
		;
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
}

void Game::initializeGame( level_state lvlState, player_state playerState, std::vector<weapon_features> weaponState )
{
	undeadCount = 0;
	currentLevel = lvlState.level;
	baseLevel = lvlState.base_level;
	points = lvlState.points;
	mapsizex = (*AssetManager::GetTexture("map")).getSize().x;
	mapsizey = (*AssetManager::GetTexture("map")).getSize().y;
	delay = sf::milliseconds( 0 );
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

}

void Game::loadTextures()
{
	
}

void Game::Controls(sf::RenderWindow * window)
{
	delay -= clock.getElapsedTime();
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
