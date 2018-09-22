#pragma once
#include "DynamicBody.h"
#include "Weapon.h"
#include "AnimatedSprite.h"
#include <SFML/Graphics.hpp>

struct player_state 
{
	long int max_hitpoints;
	short int armor;
	double speed;
};

class Player :
	public DynamicBody
{
public:
	Player( b2World* world, b2Vec2 position );
	Player( b2World* world, b2Vec2 position, player_state playerState );
	~Player();
	void								StartContact( Entity* );
	void								EndContact( Entity* );
	void								Presolve( Entity* );
	void								Render( sf::RenderWindow* window );
	void								Update(sf::Time);
	void								SetAngle( float32 angle );
	sf::Vector2f						GetWeaponPosition();
	void								AddWeapon( Weapon * weapon );
	void								Reload();
	void								Shoot( b2Vec2 direction, sf::Time difference_time );
	void								TakeDamage( float32 damage );
	player_state						GetPlayerState() const;

	std::vector<long int>				GetHitpoints();
	std::vector<weapon_features>		GetWeaponList();
	weapon_features						GetCurrentWeapon();

private:
	void								setSpriteSheets();
	void								addFramesToAnimations();
	bool								isMoving();
	bool								isIdle();
	bool								isShooting();
	bool								isReloading();
	bool								canShoot();
	bool								canReload();
	void								setAnimationsForCurrentWeapontype();

	int									size1;
	int									size2;
	double								speed;
	short int							armor;
	double								animSpeed;
	sf::CircleShape						shape;
	std::list<Weapon *>					weapons;
	Weapon *							current_weapon = nullptr;

	b2Vec2								direction1;
	b2Vec2								direction2;
	sf::Vector2i						mousePos;
	sf::Vector2f						cordPos;
	sf::Clock							frameClock;
	sf::Time							frameTime;
	AnimatedSprite						animatedSprite;
	AnimatedSprite						animatedSpriteFeet;
	Animation*							currentAnimation;
	Animation*							currentAnimationFeet;
	Animation							walkingAnimationFeet;
	Animation							idleAnimationFeet;
	Animation							walkingAnimationHandgun;
	Animation							idleAnimationHandgun;
	Animation							attackingAnimationHandgun;
	Animation							reloadingAnimationHandgun;
	Animation							walkingAnimationRifle;
	Animation							idleAnimationRifle;
	Animation							attackingAnimationRifle;
	Animation							reloadingAnimationRifle;
	Animation							walkingAnimationShotgun;
	Animation							idleAnimationShotgun;
	Animation							attackingAnimationShotgun;
	Animation							reloadingAnimationShotgun;
	Animation*							walkingAnimation;
	Animation*							idleAnimation;
	Animation*							attackingAnimation;
	Animation*							reloadingAnimation;
};