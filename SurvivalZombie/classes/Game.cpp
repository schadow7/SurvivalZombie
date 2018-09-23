#include "Game.h"
Game::Game() :
	mapsizex(1),
	mapsizey(1)
{
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
	view->setCenter(player->GetPosition());
	window->setView(*view);

	//Sterowanie graczem i nie tylko
	Controls(window);

	window->draw(background);
	entity_manager->Update(clock.restart());
	entity_manager->Render(window);
	hud->Render(window, view, player);
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
	//T�o
	background.setTexture(*AssetManager::GetTexture("map"));
	background.setTextureRect(sf::IntRect(0, 0, mapsizex, mapsizey));

	engine.seed(time(0));
	arrangeObstacles(25);
	makeBase();
	//Player
	player = new Player(world, positionPixToWorld(sf::Vector2f(mapsizex / 2.0f, mapsizey / 2.0f + 96)));
	entity_manager->AddEntity(player);
	//Bazowa bro�
	Weapon * pistol = new Pistol(entity_manager, AssetManager::GetTexture("bullet9mm"));
	player->AddWeapon(pistol);
	Weapon * rifle = new Rifle( entity_manager, AssetManager::GetTexture( "bullet9mm" ) );
	player->AddWeapon( rifle );
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
	//T�o
	background.setTexture( *AssetManager::GetTexture( "map" ) );
	background.setTextureRect( sf::IntRect( 0, 0, mapsizex, mapsizey ) );

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
			//tmp = new Pistol( entity_manager, AssetManager::GetTexture( "bullet9mm" ), it );
			//player->AddWeapon( tmp );
		}

	}

}

void Game::loadTextures()
{
	
}

void Game::Controls(sf::RenderWindow * window)
{
	delay -= clock.getElapsedTime();
	//Przygotowanie wektor�w
	b2Vec2 velocity = b2Vec2_zero;
	b2Vec2 normalize_direction = b2Vec2_zero;
	//Odczytanie pozycji kursora
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
	//Wyznaczenie znormalizowanego wektora wyznaczaj�cego kierunek od gracza do pozycycji myszki
	normalize_direction = positionPixToWorld(cordPos) - positionPixToWorld(player->GetWeaponPosition());
	normalize_direction.Normalize();

	//konkretne klawisze
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Num1 ) && delay <= sf::milliseconds( 0 ) )
	{
		Zombie* zombieTester = new Zombie(world, positionPixToWorld(cordPos));
		zombieTester->SetTarget(player);
		zombieTester->SetAI(Zombie::Chaotic);
		entity_manager->AddEntity(zombieTester);
		undeadCount++;
		delay = sf::milliseconds( 500 );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && delay <= sf::milliseconds( 0 ) )
	{
		Zombie* zombieTester = new ZombieTank(world, positionPixToWorld(cordPos));
		zombieTester->SetTarget(player);
		zombieTester->SetAI(Zombie::Idle);
		entity_manager->AddEntity(zombieTester);
		delay = sf::milliseconds( 500 );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && delay <= sf::milliseconds( 0 ) )
	{
		Zombie* zombieTester = new ZombieSprinter(world, positionPixToWorld(cordPos));
		zombieTester->SetTarget(player);
		zombieTester->SetAI(Zombie::Chaotic);
		entity_manager->AddEntity(zombieTester);
		delay = sf::milliseconds( 500 );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && delay <= sf::milliseconds( 0 ) )
	{
		spawnHorde(0);
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
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
		StaticBody* ob = new TheBase(world, positionPixToWorld(cordPos));
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

	//if (undeadCount <= 0)
	//{
	//	currentLevel++;
	//	spawnHorde(currentLevel);
	//	printf("level:%d undeadCount:%d\n", currentLevel, undeadCount);
	//}

	shoot_timer += clock.getElapsedTime();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		player->Shoot(normalize_direction, shoot_timer);
		shoot_timer = sf::seconds(0);
	}


	player->SetVelocity(velocity);
	if (100.f * b2Distance(positionPixToWorld(cordPos), positionPixToWorld(player->GetPosition())) > 50.f)
		previous_angle = atan2f(normalize_direction.y, normalize_direction.x); player->SetAngle(previous_angle);
}

void Game::update(Entity * ptr)
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
			entity_manager->AddEntity(temp);
		}
	}
}

void Game::makeBase()
{
	int sizex = 50;
	int boxSize = 10;
	sf::Vector2f position(mapsizex/2 - 5 * sizex, mapsizey/2 - 5 * sizex);
	BasicEntanglements* ob;
	TheBase* Base = new TheBase(world, mapCenter);
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
	if (i != floor(boxSize / 2))
		ob = new BasicEntanglements(world, positionPixToWorld(position));
	else
		ob = new Door(world, positionPixToWorld(position));
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
