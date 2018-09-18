#include "Level.h"

Level::Level(int nr, std::vector<int>& quantity, b2Vec2 pos):
	levelNumber(nr),
	zombieQuantity(quantity),
	spawnPosition(pos)
{
}

Level::Level(int nr):
	levelNumber(nr)
{
	engine.seed(time(0));
	spawnPosition = possibleSpawnPoints[positionDistribution(engine)];
	unsigned int number_of_zombie_types = 3;
	for (unsigned int i=0; i < number_of_zombie_types; i++)
	{
		int random_part = levelNumber * zombieDistribution(engine);
		if (abs(random_part) > 3) random_part = 6;
		zombieQuantity.push_back(levelNumber*(number_of_zombie_types - i) + random_part);
	}
}


Level::~Level()
{
}
