#pragma once
#include <Box2D/Common/b2Math.h>
#include <vector>
#include <random>
#include <chrono>
#include <ctime>
class Level
{
public:
	Level(int nr, std::vector<int>& quantity, b2Vec2 pos= b2Vec2_zero);
	Level(int nr);
	~Level();
	int levelNumber;
	b2Vec2 spawnPosition;
	std::vector<int> zombieQuantity;
private:
	std::default_random_engine engine;
	std::uniform_int_distribution<int> zombieDistribution{ -1, 1 };
	//trzeba bêdzie uzupe³niæ jak ju¿ bêd¹ ustalonw spawn pointy
	std::uniform_int_distribution<int> positionDistribution{ 0, 1 };
	std::vector< b2Vec2> possibleSpawnPoints = { b2Vec2(1,1), b2Vec2(12,12) };
};

