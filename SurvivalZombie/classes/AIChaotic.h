#pragma once
#include "AIType.h"
#include <random>
class AIChaotic :
	public AIType
{
public:
	AIChaotic();
	AIChaotic(b2World* nworld);
	~AIChaotic();
	b2Vec2 Move(b2Vec2 position, b2Vec2 player_position, float32 current_angle) override;
private:
	b2Vec2 old_dir;
	int obstructed = 0;
	std::default_random_engine engine;
	std::uniform_int_distribution<int> dis{ -1, 1 };
};

