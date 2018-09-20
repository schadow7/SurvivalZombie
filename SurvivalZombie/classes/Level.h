#pragma once
#include <Box2D/Common/b2Math.h>
#include <vector>
#include <random>
#include <ctime>
#include "EntityManager.h"
#include "ZombieTank.h"
#include "ZombieSprinter.h"
#include "Game.h"
class Level
{
public:
	Level(Game*,b2World* ,Entity* ,EntityManager* );
	~Level();
private:
	b2World* world;
	Entity*  target;
	EntityManager* entity_manager;
	Game* game;
	const float								SCALE = 100.f;
	void									spawnHorde(int next_level);
	std::default_random_engine				engine;
	std::uniform_int_distribution<int>		angleDistribution{ 1, 360 };
	const float								DEGTORAD = b2_pi / 180;
	b2Vec2									mapCenter;
	std::vector<int>						newLevel(int levelNr, std::vector<int>& zombieQuantity);
	std::uniform_int_distribution<int>		zombieDistribution{ -1, 1 };
};

