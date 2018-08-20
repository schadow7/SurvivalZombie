#include "DynamicBody.h"



DynamicBody::DynamicBody(b2World* world, b2Vec2 position)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position = position;
	myBodyDef.angle = 0;
	body = world->CreateBody(&myBodyDef);
	body->SetLinearVelocity(b2Vec2_zero);
}


DynamicBody::~DynamicBody()
{
}

void DynamicBody::SetVelocity(b2Vec2 velocity)
{
	body->SetLinearVelocity(velocity);
}
void DynamicBody::ApplyForce(b2Vec2 force)
{
	body->ApplyForceToCenter(force,1);
}
