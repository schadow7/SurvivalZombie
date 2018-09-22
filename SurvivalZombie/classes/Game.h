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
#include "observer.h"
#include "Weapon.h"
#include "Hud.h"
#include <random>
#include "Obstacle.h"
#include "Trap.h"
#include "TheBase.h"

struct level_state
{
	int level;
	long int points;
	short int base_level;
};


class Game:
	public Observer
{
public:
	Game();
	Game( level_state lvlState, player_state playerState, std::vector<weapon_features> weaponState );
	~Game();

	
	void									runGame(sf::RenderWindow * window);
	void									update(Entity*) override;
	void									RestartClock() { clock.restart(); }
	level_state								GetLevelState();
	player_state							GetPlayerState();
	std::vector<weapon_features>			GetWeaponState();
private:
	void									Render( sf::RenderWindow * window );
	void									loadTextures();
	void									Controls(sf::RenderWindow * window);
	void									initializeGame();
	void									initializeGame( level_state lvlState, player_state playerState, std::vector<weapon_features> weaponState );
	const float								SCALE = 100.f;
	EntityManager *							entity_manager;
	sf::View *								view;
	sf::Sprite								background;
	std::vector<Zombie*>					zombieList;
	b2World *								world;
	Zombie *								zombieTester;
	Player *								player;
	Hud *									hud;
	int										undeadCount;
	void									spawnHorde(int next_level);
	int										currentLevel;
	int										baseLevel;
	long int								points = 0;
	sf::Clock								clock;
	sf::Time								delay;
	float32									previous_angle;
	std::default_random_engine				engine;
	std::uniform_int_distribution<int>		angleDistribution{ 1, 360 };
	const float								DEGTORAD = b2_pi / 180;
	b2Vec2									mapCenter;
	std::vector<int>						newLevel(int levelNr, std::vector<int>& zombieQuantity);
	std::uniform_int_distribution<int>		zombieDistribution{ -1, 1 };
	sf::Time								shoot_timer;
	void									arrangeObstacles(int quantity);
	void									makeBase();
	std::vector<BasicEntanglements*>		base;
	BasicEntanglements*						spawnWall(int i, int boxSize, sf::Vector2f& position);
	void									setBaseLevel(int level);
};

