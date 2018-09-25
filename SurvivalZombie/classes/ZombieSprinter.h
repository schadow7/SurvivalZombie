#pragma once
#include "Zombie.h"
class ZombieSprinter :
	public Zombie
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ZombieSprinter"/> class.
	/// </summary>
	/// <param name="world">The b2World.</param>
	/// <param name="position">The position in px on the map.</param>
	ZombieSprinter(b2World* world, b2Vec2 position);
	~ZombieSprinter();

private:
	void					setSpriteSheets();
	void					addFramesToAnimations();
	Animation				walkingAnimation;
	Animation				attackingAnimation;
	Animation				idleAnimation;
	Animation				deadAnimation;
};

