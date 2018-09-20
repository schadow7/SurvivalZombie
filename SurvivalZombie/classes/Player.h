#pragma once
#include "DynamicBody.h"
#include "Weapon.h"
#include "AnimatedSprite.h"
#include <SFML/Graphics.hpp>
class Player :
	public DynamicBody
{
public:
	Player( b2World* world, sf::Texture * texture, b2Vec2 position );
	~Player();
	void					StartContact( Entity* );
	void					EndContact( Entity* );
	void					Presolve( Entity* );
	void					Render( sf::RenderWindow* window );
	void					Update(sf::Time);
	void					SetAngle( float32 angle );
	sf::Vector2f			GetWeaponPosition();
	void					AddWeapon( Weapon * weapon );
	void					Shoot( b2Vec2 direction );
	void					StopAnimation();
	std::vector<long int>	GetHitpoints();
	//virtual void Action( b2Vec2 player_positon );
private:
	double					speed;
	double					animSpeed;
	sf::CircleShape			shape;
	std::list<Weapon *>		weapons;
	Weapon *				current_weapon = nullptr;
	AnimatedSprite			animatedSprite;
	Animation*				currentAnimation;
	sf::Texture				textureWalkingAnimation;
	sf::Texture				textureAttackingAnimation;
	sf::Texture				textureIdleAnimation;
	sf::Clock				frameClock;
	sf::Time				frameTime;
	Animation				walkingAnimation;
	Animation				attackingAnimation;
	Animation				idleAnimation;
};