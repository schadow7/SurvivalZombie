#pragma once
#include "DynamicBody.h"
#include "Weapon.h"
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
	std::vector<long int>	GetHitpoints();
	//virtual void Action( b2Vec2 player_positon );
private:
	double					speed;
	sf::CircleShape			shape;
	std::list<Weapon *>		weapons;
	Weapon *				current_weapon = nullptr;

};