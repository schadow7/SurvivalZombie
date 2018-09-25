#include "AIChaotic.h"



AIChaotic::AIChaotic()
{
}

AIChaotic::AIChaotic(b2World* nworld)
{
	this->world = nworld;
}


AIChaotic::~AIChaotic()
{
}

b2Vec2 AIChaotic::Move(b2Vec2 position, b2Vec2 player_position, float32 current_angle)
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
			int roll = dis(engine);
			callbackLeft.obstructed = 0;
			angleLeft -= 25 * DEGTORAD;
			doRayCast(callbackLeft, position, angleLeft);
			if (!callbackLeft.obstructed)
			{
				direction.x += turn_gain * cos(roll*angleLeft);
				direction.y += turn_gain * sin(roll*angleLeft);
				obstructed = 15;
				break;
			}
			
			callbackRight.obstructed = 0;
			angleRight += 25 * DEGTORAD;
			doRayCast(callbackRight, position, angleRight);
			if (!callbackRight.obstructed)
			{
				direction.x += turn_gain * cos(roll*angleRight);
				direction.y += turn_gain * sin(roll*angleRight);
				obstructed = 15;
				break;
			}
		}
	}
	direction.Normalize();
	old_dir = direction;
	return direction;
}
