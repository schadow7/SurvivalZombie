#include "Game.h"
Game::Game()
{
	world = new b2World(b2Vec2(0.f, 0.f));
	entity_manager = new EntityManager(world);
	/*
	sf::Texture * tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\background.png");
	textures.insert(std::pair<std::string, sf::Texture*>("background", tmp));
	tmp->setRepeated(true);
	*/
	sf::Texture * tmp;
	tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\animations\\bullet9mm.png");
	textures.insert(std::pair<std::string, sf::Texture*>("bullet9mm", tmp));
	background.setTexture( *AssetManager::GetTexture( "background" ) );
	background.setTextureRect(sf::IntRect(0, 0, 20000, 20000));
	view = new sf::View(sf::FloatRect(0, 0, 1280, 720));
	hud = new Hud;
	undeadCount = 0;
	currentLevel = 0;
//	noKeyWasPressed = true;
	mapCenter = b2Vec2( 4000 / SCALE, 4000 / SCALE );
	previous_angle = 0.f;
	shoot_timer = sf::seconds( 1 );
}

Game::~Game()
{

}

void Game::runGame(sf::RenderWindow * window)
{
	window->clear();
	view->setCenter(player->GetPosition());
	window->setView(*view);

	//Sterowanie graczem i nie tylko
	Controls(window);

	window->draw( background );
	entity_manager->Update( clock.restart() );
	entity_manager->Render( window );
	hud->Render( window, view, player );
	/*
	sf::Vertex line[] =
	{
	sf::Vertex( player->GetWeaponPosition() ),
	sf::Vertex( window->mapPixelToCoords( sf::Mouse::getPosition( *window ) ) )
	};
	window->draw( line, 2, sf::Lines );
	*/

}


void Game::initializeGame()
{
	engine.seed(time(0));
	arrangeObstacles(100);
	//Player
	player = new Player(world, textures.at("survivor"), positionPixToWorld(sf::Vector2f(4000, 4000)));
	entity_manager->AddEntity(player);
	Weapon * pistol = new Pistol(entity_manager, textures.at("survivor"), textures.at("bullet9mm"));
	player->AddWeapon(pistol);
}

void Game::loadTextures()
{
	sf::Texture * tmp;
	tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\animations\\bullet9mm.png");
	textures.insert(std::pair<std::string, sf::Texture*>("bullet9mm", tmp));
	//background.setTexture(*textures.at("background"));
	background.setTextureRect(sf::IntRect(0, 0, 8000, 8000));
	tmp->loadFromFile(".\\graphics\\survivor.png");
	textures.insert(std::pair<std::string, sf::Texture*>("survivor", tmp));
}

void Game::Controls(sf::RenderWindow * window)
{
	//Przygotowanie wektorów
	b2Vec2 velocity = b2Vec2_zero;
	b2Vec2 normalize_direction = b2Vec2_zero;
	//Odczytanie pozycji kursora
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
	//Wyznaczenie znormalizowanego wektora wyznaczającego kierunek od gracza do pozycycji myszki
	normalize_direction = positionPixToWorld(cordPos) - positionPixToWorld(player->GetWeaponPosition());
	normalize_direction.Normalize();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{

		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
		Zombie* zombieTester = new Zombie(world, positionPixToWorld(cordPos));
		zombieTester->SetTarget(player);
		zombieTester->SetAI(Zombie::Chaotic);
		entity_manager->AddEntity(zombieTester);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{

		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
		Zombie* zombieTester = new ZombieTank(world, positionPixToWorld(cordPos));
		zombieTester->SetTarget(player);
		zombieTester->SetAI(Zombie::Chaotic);
		entity_manager->AddEntity(zombieTester);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{

		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
		Zombie* zombieTester = new ZombieSprinter(world, positionPixToWorld(cordPos));
		zombieTester->SetTarget(player);
		zombieTester->SetAI(Zombie::Chaotic);
		entity_manager->AddEntity(zombieTester);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{

		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
		spawnHorde(0);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{

		entity_manager->KillEverybody();

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{

		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
		Entity* ob = new BasicEntanglements(world, positionPixToWorld(cordPos));
		entity_manager->AddEntity(ob);

	}
	if (undeadCount <= 0)
	{
		currentLevel++;
		spawnHorde(currentLevel);
		printf("level:%d undeadCount:%d\n", currentLevel, undeadCount);

	}
	shoot_timer += clock.getElapsedTime();
	if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
	{
		player->Shoot( normalize_direction, shoot_timer );
		shoot_timer = sf::seconds( 0 );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::R ) )
	{
		player->Reload();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//velocity += b2Vec2(normalize_direction);
		velocity += b2Vec2(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//velocity += b2Vec2(-normalize_direction);
		velocity += b2Vec2(0, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//velocity += b2Vec2(normalize_direction.y, -normalize_direction.x);
		velocity += b2Vec2(-1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//velocity += b2Vec2(-normalize_direction.y, normalize_direction.x);
		velocity += b2Vec2(1, 0);
	}
	player->SetVelocity( velocity );
	if ( 100.f * b2Distance( positionPixToWorld( cordPos ), positionPixToWorld( player->GetPosition() ) ) > 50.f )
		previous_angle = atan2f( normalize_direction.y, normalize_direction.x );
	player->SetAngle( previous_angle );
}

void Game::update(Entity * ptr)
{
	if (ptr->GetID() == 2)
		undeadCount--;
}


void Game::Render(sf::RenderWindow * window)
{
}

void Game::spawnHorde(int next_level)
{
	float spawnRadius = 3500 / SCALE;
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
			angle = angleDistribution(engine)*DEGTORAD;
			spawnPoint.x = mapCenter.x + spawnRadius * cos(angle);
			spawnPoint.y = mapCenter.y + spawnRadius * sin(angle);
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
		std::uniform_int_distribution<int>	obstacleRadiusDistribution{ 500, 4000 };
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

