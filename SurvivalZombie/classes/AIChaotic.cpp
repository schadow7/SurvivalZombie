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
	if (callbackRight.obstacleList.empty())
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
			callbackLeft.obstacleList.clear();
			angleLeft -= 25 * DEGTORAD;
			doRayCast(callbackLeft, position, angleLeft);
			if (callbackLeft.obstacleList.empty())
			{
				direction.x += turn_gain * cos(dis(engine)*angleLeft);
				direction.y += turn_gain * sin(dis(engine)*angleLeft);
				//printf("L %f\n", angleLeft * 180 / b2_pi);
				obstructed = 15;
				break;
			}
			
			callbackRight.obstacleList.clear();
			angleRight += 25 * DEGTORAD;
			doRayCast(callbackRight, position, angleRight);
			if (callbackRight.obstacleList.empty())
			{
				direction.x += turn_gain * cos(dis(engine)*angleRight);
				direction.y += turn_gain * sin(dis(engine)*angleRight);
				//printf("R %f\n", angleRight*180/b2_pi);
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
