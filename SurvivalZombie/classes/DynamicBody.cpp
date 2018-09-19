#include "DynamicBody.h"



DynamicBody::DynamicBody(b2World* world, b2Vec2 position)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position = position;
	myBodyDef.angle = 0;
	body = world->CreateBody(&myBodyDef);
	body->SetLinearVelocity(b2Vec2_zero);
	this->body->SetUserData(dynamic_cast<Entity *> (this));
}

DynamicBody::DynamicBody( b2World * world, b2BodyDef bodyDef, b2FixtureDef fixtureDef )
{
	body = world->CreateBody( &bodyDef );
	body->SetLinearVelocity( b2Vec2_zero );
	this->body->SetUserData( dynamic_cast<Entity *> ( this ) );
	body->CreateFixture( &fixtureDef );
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
