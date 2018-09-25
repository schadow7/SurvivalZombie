#include "AIAggressive.h"



AIAggressive::AIAggressive(b2World* world)
{
	this->world = world;
}


AIAggressive::~AIAggressive()
{
}

b2Vec2 AIAggressive::Move(b2Vec2 position, b2Vec2 player_position, float32 current_angle)
{
	RayCastCallback callbackRight, callbackLeft;
	doRayCast(callbackRight, position, current_angle);
	volatile float32 angleRight = current_angle;
	float32 angleLeft = current_angle;
	float turn_gain = .20f;
	b2Vec2 direction = old_dir;
	if (!callbackRight.obstructed)
	{
		if (obstructed == 0)
			direction += .08f*(player_position - position);
		else
			obstructed--;
	}
	else
	{
		while (angleRight <= current_angle + b2_pi)
		{
			callbackLeft.obstructed = 0;
			angleLeft -= 25 * DEGTORAD;
			doRayCast(callbackLeft, position, angleLeft);
			if (!callbackRight.obstructed)
			{
				direction.x += turn_gain * cos(angleLeft);
				direction.y += turn_gain * sin(angleLeft);
				obstructed = 15;
				break;
			}

			callbackRight.obstructed = 0;
			angleRight += 25 * DEGTORAD;
			doRayCast(callbackRight, position, angleRight);
			if (!callbackRight.obstructed)
			{
				direction.x += turn_gain * cos(angleRight);
				direction.y += turn_gain * sin(angleRight);
				obstructed = 15;
				break;
			}
		}
	}
	
	direction.Normalize();
	old_dir = direction;
	//printf("%d \n", obstructed);
	//printf("ster:%f \n", atan2(direction.y, direction.x) * 180 / b2_pi);
	return direction;
}

