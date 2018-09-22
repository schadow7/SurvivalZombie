#pragma once
#include "Zombie.h"
class ZombieTank :
	public Zombie
{
public:
	ZombieTank(b2World* world, b2Vec2 position);
	~ZombieTank();

private:
	void					setSpriteSheets();
	void					addFramesToAnimations();
	Animation				walkingAnimation;
	Animation				attackingAnimation;
	Animation				idleAnimation;
};

