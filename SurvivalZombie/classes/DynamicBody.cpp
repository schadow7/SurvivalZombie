#include "DynamicBody.h"



DynamicBody::DynamicBody(b2World& world)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(0, 0);
	myBodyDef.angle = 0;
	body = world.CreateBody(&myBodyDef);
}


DynamicBody::~DynamicBody()
{
}

void DynamicBody::SetVelocity(b2Vec2 velocity)
{
	body->SetLinearVelocity(velocity);
}
