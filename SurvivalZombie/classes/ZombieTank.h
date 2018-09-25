#pragma once
#include "Zombie.h"
class ZombieTank :
	public Zombie
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ZombieTank"/> class.
	/// </summary>
	/// <param name="world">The b2World.</param>
	/// <param name="position">The position in px on the map.</param>
	ZombieTank(b2World* world, b2Vec2 position);
	~ZombieTank();

private:	
	/// <summary>
	/// Sets the sprite sheets.
	/// </summary>
	void					setSpriteSheets();	
	/// <summary>
	/// Adds the frames to animations.
	/// </summary>
	void					addFramesToAnimations();
	Animation				walkingAnimation;
	Animation				attackingAnimation;
	Animation				idleAnimation;
	Animation				deadAnimation;
};

