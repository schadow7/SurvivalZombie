#pragma once
#include "AIType.h"
#include <random>
#include <chrono>
class AIIdle :
	public AIType
{
public:
	AIIdle(b2World* nworld);
	~AIIdle();
	b2Vec2 Move(b2Vec2 position, b2Vec2 player_position, float32 current_angle) override;
private:
	b2Vec2 old_dir;
	int delay = 0;
	std::default_random_engine* engine;
	std::uniform_int_distribution<int> dis{ 0, 360 };
};

