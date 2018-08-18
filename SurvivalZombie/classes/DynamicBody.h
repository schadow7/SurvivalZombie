#pragma once
#include "Entity.h"
class DynamicBody :
	public Entity
{
public:
						DynamicBody(b2World& world);
						DynamicBody(b2World, sf::Texture, b2BodyDef, b2FixtureDef);
	virtual				~DynamicBody();
	void				SetVelocity(b2Vec2 velocity);
	void				ApplyForce(b2Vec2 force);
	virtual void		Action() = 0;

protected:
	b2Vec2				velocity;


};

