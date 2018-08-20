#include "DynamicBody.h"



DynamicBody::DynamicBody(b2World* world)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(0.f,0.f);
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
