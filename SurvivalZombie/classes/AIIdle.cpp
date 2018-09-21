#include "AIIdle.h"



AIIdle::AIIdle(b2World* nworld)
{
	this->world = nworld;
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	engine = new std::default_random_engine(seed);
}


AIIdle::~AIIdle()
{
	delete engine;
}

b2Vec2 AIIdle::Move(b2Vec2 position, b2Vec2 player_position, float32 current_angle)
{
	float turn_gain = .20f;
	b2Vec2 direction = old_dir;

	if (delay == 0)
	{
		float angle = dis(*engine) * DEGTORAD;
		direction.x += turn_gain * cos(angle);
		direction.y += turn_gain * sin(angle);
		printf("%f\n", angle);
	}

	direction.Normalize();
	old_dir = direction;
	delay = ++delay % 20;
	return direction;
}