#include "Level.h"



Level::Level(int nr, std::vector<int>& quantity, b2Vec2 pos):
	levelNumber(nr),
	zombieQuantity(quantity),
	spawnPosition(pos)
{
}


Level::~Level()
{
}
