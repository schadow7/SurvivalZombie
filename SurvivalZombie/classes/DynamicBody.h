#pragma once
#include "Entity.h"
class DynamicBody :
	public Entity
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="DynamicBody"/> class.
	/// </summary>
	/// <param name="world">The b2World.</param>
	/// <param name="position">The position.</param>
	DynamicBody(b2World * world, b2Vec2 position);
	/// <summary>
	/// Initializes a new instance of the <see cref="DynamicBody"/> class.
	/// </summary>
	/// <param name="world">The b2World.</param>
	/// <param name="bodyDef">The body definition.</param>
	/// <param name="fixtureDef">The fixture definition.</param>
	DynamicBody(b2World * world, b2BodyDef bodyDef, b2FixtureDef fixtureDef);
	virtual				~DynamicBody();
	void				SetVelocity(b2Vec2 velocity);
	/// <summary>
	/// Wywiera si³ê bezpoœednio na cia³o.
	/// </summary>
	/// <param name="force">The force.</param>
	void				ApplyForce(b2Vec2 force);
	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns></returns>
	sf::Vector2f		GetPosition();
	/// <summary>
	/// Gets the angle.
	/// </summary>
	/// <returns></returns>
	float32				GetAngle();

protected:
	b2Vec2				velocity;
	float32				speed;


};

