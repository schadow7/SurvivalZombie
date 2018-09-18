#pragma once
#include "Zombie.h"
class ZombieSprinter :
	public Zombie
{
public:
	ZombieSprinter(b2World* world, b2Vec2 position);
	~ZombieSprinter();
};

