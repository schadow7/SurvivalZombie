#include "ZombieManager.h"



ZombieManager::ZombieManager(std::vector<Zombie*> &zombieList):
zombieList(zombieList)
{
}


ZombieManager::~ZombieManager()
{
}

void ZombieManager::AIStep()
{
	for (auto & it : zombieList)
	{
		it->Action(b2Vec2(5.f,5.f));
	}

}
