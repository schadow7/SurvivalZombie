#pragma once
#include<vector>
#include<memory>
#include"Zombie.h"

class StaticBody;
class Player;
class ZombieManager
{
	std::vector<Zombie*>& zombieList;
	//std::vector<StaticBody*>& obstacleList;
	//Player& player;
public:
	ZombieManager(std::vector<Zombie*> &zombieList);
	~ZombieManager();
	void AIStep();
	void Spawn();
};

