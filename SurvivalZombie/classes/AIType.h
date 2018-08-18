#pragma once
#include <Box2D/Box2D.h>

class AIType
{
public:
	AIType();
	virtual ~AIType();
	virtual b2Vec2 Move()=0;
};

