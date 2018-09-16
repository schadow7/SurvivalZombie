#include "Aggressive.h"



Aggressive::Aggressive(b2World* world)
{
	this->world = world;
}


Aggressive::~Aggressive()
{
}

b2Vec2 Aggressive::Move(b2Vec2 position, b2Vec2 player_position, float32 current_angle)
{
	RayCastCallback callbackInfo;
	doRayCast(callbackInfo, position, current_angle);
	float32 angle = current_angle;
	int obstructed = 0;
	while (!callbackInfo.obstacleList.empty() || angle >= current_angle + 2 * b2_pi)
	{
		obstructed++;
		callbackInfo.obstacleList.clear();
		angle += 15 * DEGTORAD;
		doRayCast(callbackInfo, position, angle);
	}

	b2Vec2 direction = old_dir;
	if (obstructed)
	{
		direction.x += .15f * cos(angle);
		direction.y += .15f * sin(angle);
	}
	else
	{
		direction += .11f*(player_position - position);
	}
	direction.Normalize();
	old_dir = direction;
	printf("ster:%f \n", atan2(direction.y, direction.x) * 180 / b2_pi);
	return direction;
}

