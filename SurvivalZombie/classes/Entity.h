#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>
#include <list>
#include "AssetManager.h"
#include "subject.h"
//Zdefiniowana poni�ej
class Effect;


class Entity:
	public Subject
{
public:
	const float SCALE = 100.f;  //	MetersToPixelsFactor 
	Entity();
	virtual void			Update(sf::Time ) = 0;
	virtual void			Render( sf::RenderWindow * window ) = 0;
	virtual void			StartContact( Entity * entity ) = 0;
	virtual void			EndContact( Entity * entity ) = 0;
	virtual void			Presolve( Entity * entitity ) = 0;
	int						Active() const;
	int						GroupID() const;
	void					TakeDamage( int damage );
	b2Vec2					GetPosition()const;
	int						GetID();
	~Entity();

protected:
	int						groupID;  //1-PLayer 2-Zombie 3-Projectile
	int						active;
	b2Body *				body;
	b2Fixture *				fixture;
	std::string				name;
	/*sf::RenderTexture*		texture;*/
	long int				hitpoints;
	std::list<Effect *>		effects;
	std::shared_ptr<sf::Texture> texture;
};


inline b2Vec2 positionPixToWorld( sf::Vector2f vec )
{
	return b2Vec2( vec.x / 100.f, vec.y / 100.f );
}

inline float sizesPixToWorld( float size )
{
	return size / 200.f;
}

inline sf::Vector2f positionWorldToPix( b2Vec2 vec )
{
	sf::Vector2f tmp = sf::Vector2f( vec.x * 100.f, vec.y * 100.f );
	return tmp;
}

inline sf::Vector2f rotateVector( sf::Vector2f vector, float32 angle )
{
	return sf::Vector2f( ( vector.x*cosf( angle ) - vector.y*sinf( angle ) ), ( vector.x*sinf( angle ) + vector.y*cosf( angle ) ) );
}

inline b2Vec2 rotateVector( b2Vec2 vector, float32 angle )
{
	return b2Vec2( ( vector.x*cosf( angle ) - vector.y*sinf( angle ) ), ( vector.x*sinf( angle ) + vector.y*cosf( angle ) ) );
}

class Effect
{
public:
	Effect( Entity * Origin, sf::Time Cooldown, sf::Time Duration ) : origin( Origin ), cooldown( Cooldown ), duration( Duration ) { };
	~Effect() { };
	virtual bool				ApplyEffect( Entity * entity, sf::Time time_difference ) { return false; };
	bool						IsActive() { return ( duration > sf::seconds( 0 ) ) ? false : true; };
	Entity *					GetOrigin() { return origin; }
protected:
	Entity * origin;
	sf::Time					counter;
	sf::Time					cooldown;
	sf::Time					duration;
};


class EffectDamage : public Effect
{
public:
	EffectDamage( Entity * Origin, sf::Time Cooldown, sf::Time Duration, int Damage ) : Effect( Origin, Cooldown, Duration ), damage( Damage ) {};
	~EffectDamage() {};
	bool						ApplyEffect( Entity * entity, sf::Time time_difference )
	{
		if ( ( duration = duration - time_difference ) <= sf::seconds( 0 ) )
			return false;
		if ( ( counter = counter + time_difference ) > cooldown )
		{
			counter = sf::seconds( 0 );
			entity->TakeDamage( damage );
		}
		return true;
	};
private:
	unsigned int				damage;
};