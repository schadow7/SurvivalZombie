#include "AIType.h"
#include "Entity.h"

AIType::AIType(b2World* nworld):
	world(nworld)
{
}


AIType::~AIType()
{
}
void AIType::doRayCast(RayCastCallback & callback, b2Vec2 ray_orgin, float currentRayAngle)
{
	float rayLength = 0.5f;
	int RayNum = 1;
	// RayNum>1 stworz sto¿ek o zadanej iloci promieni
	float cone_opening_angle = 25 * DEGTORAD;
	float angle = currentRayAngle - (RayNum-1)/2 * cone_opening_angle / RayNum;
	for (int i = 0; i < RayNum; i++)
	{
		angle += cone_opening_angle / RayNum ;
		b2Vec2 p2 = ray_orgin + rayLength * b2Vec2(sinf(angle), cosf(angle));
		world->RayCast(&callback, ray_orgin, p2);
	}
}

float32 AIType::RayCastCallback::ReportFixture(b2Fixture * fixture, const b2Vec2 & point, const b2Vec2 & normal, float32 fraction)
{
	Entity* temp = static_cast<Entity*>(fixture->GetBody()->GetUserData());
	int id = temp->GetID();
	if (id != 1)
	{
		obstructed = 1;
	}
	return float32(1);
}
