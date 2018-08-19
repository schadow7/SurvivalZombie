#pragma once
#include <Box2D/Box2D.h>

class AIType
{
public:
	AIType();
	virtual ~AIType();
	virtual b2Vec2 Move(b2Vec2 position, b2Vec2 player_position)=0;
};

