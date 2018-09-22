#pragma once
#pragma once
#include "Entity.h"
class StaticBody :
	public Entity
{
public:
	StaticBody(b2World * world, b2Vec2 position);
	StaticBody(b2World * world, b2BodyDef bodyDef, b2FixtureDef fixtureDef);
	virtual				~StaticBody();
	sf::Vector2f		GetPosition();
	float32				GetAngle();

protected:
	b2Vec2				velocity;
	const float			DEGTORAD = b2_pi / 180;



};

