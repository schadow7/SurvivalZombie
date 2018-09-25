#pragma once
#pragma once
#include "Entity.h"
class StaticBody :
	public Entity
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="StaticBody"/> class.
	/// </summary>
	/// <param name="world">The b2World.</param>
	/// <param name="position">Pozycja w b2World.</param>
	StaticBody(b2World * world, b2Vec2 position);
	/// <summary>
	/// Initializes a new instance of the <see cref="StaticBody"/> class.
	/// </summary>
	/// <param name="world">The b2World.</param>
	/// <param name="bodyDef">The body definition.</param>
	/// <param name="fixtureDef">The fixture definition.</param>
	StaticBody(b2World * world, b2BodyDef bodyDef, b2FixtureDef fixtureDef);
	virtual				~StaticBody();
	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns>Pozycja na mapie gry</returns>
	sf::Vector2f		GetPosition();
	/// <summary>
	/// Gets the angle.
	/// </summary>
	/// <returns></returns>
	float32				GetAngle();

protected:
	b2Vec2				velocity;
	const float			DEGTORAD = b2_pi / 180;



};

