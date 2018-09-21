#include "StaticBody.h"



StaticBody::StaticBody(b2World* world, b2Vec2 position)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position = position;
	myBodyDef.angle = 0;
	body = world->CreateBody(&myBodyDef);
	this->body->SetUserData(dynamic_cast<Entity *> (this));
}

StaticBody::StaticBody(b2World * world, b2BodyDef bodyDef, b2FixtureDef fixtureDef)
{
	body = world->CreateBody(&bodyDef);
	this->body->SetUserData(dynamic_cast<Entity *> (this));
	body->CreateFixture(&fixtureDef);
}



StaticBody::~StaticBody()
{
}

sf::Vector2f StaticBody::GetPosition()
{
	return sf::Vector2f(positionWorldToPix(body->GetPosition()));
}

float32 StaticBody::GetAngle()
{
	return 180 / b2_pi * this->body->GetAngle();
}
