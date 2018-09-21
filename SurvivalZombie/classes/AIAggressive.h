#pragma once
#include "AIType.h"
class AIAggressive :
	public AIType
{
public:
	AIAggressive(b2World* world);
	~AIAggressive();
	b2Vec2 Move(b2Vec2 position, b2Vec2 player_position, float32 current_angle) override;
private:
	b2Vec2 old_dir;
	int obstructed=0;
};

