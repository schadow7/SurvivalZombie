#pragma once
#include <Box2D/Common/b2Math.h>
#include <vector>
class Level
{
public:
	Level(int nr, std::vector<int>& quantity, b2Vec2 pos= b2Vec2_zero);
	~Level();
	int levelNumber;
	b2Vec2 spawnPosition;
	std::vector<int> zombieQuantity;
};

