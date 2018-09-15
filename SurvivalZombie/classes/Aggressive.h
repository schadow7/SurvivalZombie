#pragma once
#include "AIType.h"
class Aggressive :
	public AIType
{
public:
	Aggressive(b2World* world);
	~Aggressive();
	b2Vec2 Move(b2Vec2 position, b2Vec2 player_position) override;
private:
	b2Vec2 old_dir;
	int obstructed=0;
};

