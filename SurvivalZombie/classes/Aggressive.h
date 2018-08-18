#pragma once
#include "AIType.h"
class Aggressive :
	public AIType
{
public:
	Aggressive();
	~Aggressive();
	b2Vec2 Move();
};

