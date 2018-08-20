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
	this->velocity = velocity;
}
void DynamicBody::ApplyForce(b2Vec2 force)
{
	body->ApplyForceToCenter(force,1);
}

sf::Vector2f DynamicBody::GetPosition()
{
	return sf::Vector2f( positionWorldToPix( body->GetPosition() ) );
}

float32 DynamicBody::GetAngle()
{
	return 180 / b2_pi * this->body->GetAngle();
}
