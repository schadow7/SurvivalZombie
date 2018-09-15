#include "AIType.h"
#include "Entity.h"

AIType::AIType()
{
}


AIType::~AIType()
{
}
void AIType::doRayCast(RayCastCallback & callback, b2Vec2 ray_orgin, float currentRayAngle)
{
	float rayLength = 1.33f;
	float DEGTORAD = 0.017453292519f;
	int RayNum = 1;

	for (int i = 0; i < RayNum; i++)
	{
		currentRayAngle += 360 / RayNum * DEGTORAD;
		//calculate points of ray
		b2Vec2 p2 = ray_orgin + rayLength * b2Vec2(sinf(currentRayAngle), cosf(currentRayAngle));
		world->RayCast(&callback, ray_orgin, p2);
	}
}

float32 AIType::RayCastCallback::ReportFixture(b2Fixture * fixture, const b2Vec2 & point, const b2Vec2 & normal, float32 fraction)
{
	b2Body* bod = fixture->GetBody();
	Entity* temp = (Entity*)bod->GetUserData();
	//Entity* temp = static_cast<Entity*>(fixture->GetBody()->GetUserData());
	b2Vec2 vek = temp->GetPosition();
	int id = temp->getID();
	//if (!id == 1)
	{
		obstacleList.push_back(point);
	}
	return float32(1);
}
