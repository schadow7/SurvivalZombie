#include "Game.h"
Game::Game()
{
	loadTextures();
	world = new b2World(b2Vec2(0.f, 0.f));
	entity_manager = new EntityManager(world);

	view = new sf::View(sf::FloatRect(0, 0, 1280, 720));
	hud = new Hud;
	undeadCount = 0;
	currentLevel = 0;
	mapCenter = b2Vec2(4000 / SCALE, 4000 / SCALE);
	previous_angle = 0.f;
	shoot_timer = sf::seconds(1);
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
	entity_manager->Update(clock.restart());
	entity_manager->Render(window);
	hud->Render(window, view, player);
}

void Game::initializeGame()
{
	//T³o
	background.setTexture(*AssetManager::GetTexture("background"));
	background.setTextureRect(sf::IntRect(0, 0, 8000, 8000));

	engine.seed(time(0));
	arrangeObstacles(100);
	makeBase();
	//Player
	player = new Player(world, positionPixToWorld(sf::Vector2f(4000, 4000)));
	entity_manager->AddEntity(player);
	//Bazowa broñ
	Weapon * pistol = new Pistol(entity_manager, AssetManager::GetTexture("bullet9mm"));
	player->AddWeapon(pistol);
}

void Game::loadTextures()
{
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

	//Animacje
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

	//konkretne klawisze
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
		Entity* ob = new BasicEntanglements(world, positionPixToWorld(cordPos));
		entity_manager->AddEntity(ob);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
		BasicEntanglements* ob = new BasicEntanglements(world, positionPixToWorld(cordPos));
		entity_manager->AddEntity(ob);
		ob->SetAngle(90);

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

void Game::makeBase()
{

	int sizex = 50;
	int boxSize = 10;
	sf::Vector2f position(4000 - 5 * sizex, 4000 - 5 * sizex);
	BasicEntanglements* ob;
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
		ob=spawnWall(i, boxSize, position);
		entity_manager->AddEntity(ob);
		position.y += sizex;
	}
	position.y -= sizex / 4;
	position.x -= sizex / 4;
	for (int i = 0; i < boxSize; i++)
	{
		ob=spawnWall(i, boxSize, position);
		entity_manager->AddEntity(ob);
		ob->SetAngle(90);
		position.x -= sizex;
	}
	position.x += sizex / 4;
	position.y -= sizex / 4;
	for (int i = 0; i < boxSize; i++)
	{
		ob=spawnWall(i, boxSize, position);
		entity_manager->AddEntity(ob);
		position.y -= sizex;
	}
}

BasicEntanglements* Game::spawnWall(int i, int boxSize, sf::Vector2f& position)
{
	if (i != floor(boxSize / 2))
		return new Door(world, positionPixToWorld(position));
	else
		return new Door(world, positionPixToWorld(position));
}
