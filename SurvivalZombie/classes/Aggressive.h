#pragma once
#include "AIType.h"
class Aggressive :
	public AIType
{
public:
	Aggressive();
	~Aggressive();
	b2Vec2 Move(b2Vec2 position,b2Vec2 player_position);
};

