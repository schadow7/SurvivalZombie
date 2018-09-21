#pragma once
#include "Entity.h"
class DynamicBody :
	public Entity
{
public:
						DynamicBody(b2World * world, b2Vec2 position);
						DynamicBody(b2World * world, b2BodyDef bodyDef, b2FixtureDef fixtureDef);
	virtual				~DynamicBody();
	void				SetVelocity(b2Vec2 velocity);
	void				ApplyForce(b2Vec2 force);
	sf::Vector2f		GetPosition();
	float32				GetAngle();

protected:
	b2Vec2				velocity;


};

