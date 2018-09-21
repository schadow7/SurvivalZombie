#pragma once
#include <Box2D/Box2D.h>
#include <vector>
class AIType
{
public:
	AIType();
	virtual ~AIType();
	virtual b2Vec2 Move(b2Vec2 position, b2Vec2 player_position, float32 current_angle) = 0;
protected:
	b2World* world;
	class RayCastCallback :public b2RayCastCallback
	{
	public:
		std::vector<b2Vec2> obstacleList;
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
	};
	virtual void doRayCast(RayCastCallback& callback, b2Vec2 ray_orgin, float currentRayAngle = 0);
	const float DEGTORAD = b2_pi/180;
};

