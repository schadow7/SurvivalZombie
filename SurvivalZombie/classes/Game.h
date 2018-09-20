#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "EntityManager.h"
#include <vector>
#include <map>
#include "Zombie.h"
#include "AssetManager.h"
#include "ZombieTank.h"
#include "ZombieSprinter.h"
#include "Player.h"
#include "Menu.h"
#include "Brick.h"
#include "observer.h"
#include "Weapon.h"
#include "Hud.h"
#include <random>


class Game:
	public Observer
{
public:
	Game();
	~Game();

	void									initializeGame();
	void									runGame(sf::RenderWindow * window);
	void									loadTextures();
	void									Controls(sf::RenderWindow * window);
	void									update(Entity*) override;
	void									RestartClock() { clock.restart(); }

private:
	void									Render( sf::RenderWindow * window );


private:
	const float								SCALE = 100.f;
	sf::View *								view;
	EntityManager *							entity_manager;
	std::map<std::string, sf::Texture *>	textures;
	sf::Sprite								background, background2;
	std::vector<Zombie*>					zombieList;
	b2World *								world;
	Zombie *								zombieTester;
	Player *								player;
	Hud *									hud;
	int										undeadCount;
	void									spawnHorde(int next_level);
	int										currentLevel;
	bool									noKeyWasPressed;
	sf::Clock								clock;
	std::default_random_engine				engine;
	std::uniform_int_distribution<int>		angleDistribution{ 1, 360 };
	const float								DEGTORAD = b2_pi / 180;
	b2Vec2									mapCenter;
	std::vector<int>						newLevel(int levelNr, std::vector<int>& zombieQuantity);
	std::uniform_int_distribution<int>		zombieDistribution{ -1, 1 };
};