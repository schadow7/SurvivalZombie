#pragma once
#include "DynamicBody.h"
#include "Weapon.h"
#include "AnimatedSprite.h"
#include <SFML/Graphics.hpp>
class Player :
	public DynamicBody
{
public:
	Player( b2World* world, b2Vec2 position );
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
	bool								canShoot();
	bool								canReload();
	bool								isShooting();
	bool								isReloading();
	std::vector<long int>				GetHitpoints();
	std::vector<weapon_features>		GetWeaponList();
	weapon_features						GetCurrentWeapon();
	//virtual void Action( b2Vec2 player_positon );
private:
	int									size;
	double								speed;
	double								animSpeed;
	sf::CircleShape						shape;
	std::list<Weapon *>					weapons;
	Weapon *							current_weapon = nullptr;
	AnimatedSprite						animatedSprite;
	AnimatedSprite						animatedSpriteFeet;
	Animation*							currentAnimation;
	Animation*							currentAnimationFeet;
	sf::Texture							textureFeetWalkingAnimation;
	sf::Texture							textureFeetIdleAnimation;
	sf::Texture							textureHandgunWalkingAnimation;
	sf::Texture							textureHandgunIdleAnimation;
	sf::Texture							textureHandgunAttackingAnimation;
	sf::Texture							textureHandgunReloadingAnimation;
	sf::Texture							textureRifleWalkingAnimation;
	sf::Texture							textureShotgunWalkingAnimation;
	sf::Texture							textureAttackingAnimation;
	sf::Texture							textureIdleAnimation;
	sf::Clock							frameClock;
	sf::Time							frameTime;
	Animation							walkingAnimationFeet;
	Animation							idleAnimationFeet;
	Animation							walkingAnimationHandgun;
	Animation							idleAnimationHandgun;
	Animation							attackingAnimationHandgun;
	Animation							reloadingAnimationHandgun;
	Animation							walkingAnimationRifle;
	Animation							walkingAnimationShotgun;
	Animation							attackingAnimation;
	Animation							idleAnimation;
};