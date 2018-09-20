#include "Game.h"
Game::Game()
{
	world = new b2World(b2Vec2(0.f, 0.f));
	entity_manager = new EntityManager(world);
	sf::Texture * tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\background.png");
	textures.insert(std::pair<std::string, sf::Texture*>("background", tmp));
	tmp->setRepeated(true);
	tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\grad1.png");
	textures.insert(std::pair<std::string, sf::Texture*>("grad1", tmp));
	background.setTexture(*textures.at("background"));
	background.setTextureRect(sf::IntRect(0, 0, 20000, 20000));
	view = new sf::View(sf::FloatRect(0, 0, 1280, 720));
	hud = new Hud;
	undeadCount = 0;
	currentLevel = 0;
	noKeyWasPressed = true;
	mapCenter= b2Vec2(4000 / SCALE, 4000 / SCALE);
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

	window->draw(background);
	entity_manager->Update();
	entity_manager->Render(window);
	hud->Render(window, view, player);
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
	//Player
	player = new Player(world, textures.at("survivor"), positionPixToWorld(sf::Vector2f(4000, 4000)));
	entity_manager->AddEntity(player);
	Weapon * pistol = new Pistol(entity_manager, textures.at("survivor"), textures.at("grad1"));
	player->AddWeapon(pistol);
	//TEMP undead tester
	//Zombie * zombieTester = new Zombie(world, b2Vec2(1.f, 1.f));
	//entity_manager->AddEntity(zombieTester);
	//zombieTester->SetTarget(player);
	engine.seed(time(0));

}

void Game::loadTextures()
{
	sf::Texture * tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\background.png");
	textures.insert(std::pair<std::string, sf::Texture*>("background", tmp));
	tmp->setRepeated(true);
	tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\grad1.png");
	textures.insert(std::pair<std::string, sf::Texture*>("grad1", tmp));
	background.setTexture(*textures.at("background"));
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
	//Wyznaczenie znormalizowanego wektora wyznaczaj¹cego kierunek od gracza do pozycycji myszki
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
		Brick* obstacle = new Brick(world, textures.at("grad1"), cordPos.x, cordPos.y);
		entity_manager->AddEntity(obstacle);

	}
	if (undeadCount == 0)
	{
		currentLevel++;
		spawnHorde(currentLevel);
		printf("level:%d undeadCount:%d\n", currentLevel, undeadCount);

	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		player->Shoot(normalize_direction);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//velocity += b2Vec2(normalize_direction);
		velocity += b2Vec2(0, -1);
		noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//velocity += b2Vec2(-normalize_direction);
		velocity += b2Vec2(0, 1);
		noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//velocity += b2Vec2(normalize_direction.y, -normalize_direction.x);
		velocity += b2Vec2(-1, 0);
		noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//velocity += b2Vec2(-normalize_direction.y, normalize_direction.x);
		velocity += b2Vec2(1, 0);
		noKeyWasPressed = false;
	}
	if (noKeyWasPressed)
	{
		player->StopAnimation();
	}
	noKeyWasPressed = true;
	player->SetVelocity(velocity);
	player->SetAngle(atan2f(normalize_direction.y, normalize_direction.x));
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

