#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>
#include <list>
#include "AssetManager.h"
#include "subject.h"
#include "observer.h"
//Zdefiniowana poni¿ej
class Effect;


/// <summary>
/// Klasa abstrakcyjnego obiektu w grze.
/// </summary>
/// <seealso cref="Observer" />
/// <seealso cref="Subject" />
class Entity :
	public Subject,
	public Observer
{
public:
	/// <summary>
	/// MetersToPixelsFactor 
	/// </summary>
	const float SCALE = 100.f;
	Entity();
	/// <summary>
	/// Uaktualnia stan obiektu w kroku symulacji 
	/// </summary>
	/// <param name="">Bierzący czas</param>
	virtual void			Update(sf::Time) = 0;
	/// <summary>
	/// Rysuje obiekt w oknie gry
	/// </summary>
	/// <param name="window">Okno gry.</param>
	virtual void			Render(sf::RenderWindow * window) = 0;
	/// <summary>
	/// Rysuje wersję nieaktywną obiektu (zwłoki) w oknie gry.
	/// </summary>
	/// <param name="window">Okno gry.</param>
	virtual void			RenderInactive(sf::RenderWindow * window) { ; }
	/// <summary>
	/// Wywoływania na początku kolicji obiektów
	/// </summary>
	/// <param name="entity">Drugi uczestnik kolizji.</param>
	virtual void			StartContact(Entity * entity) = 0;
	/// <summary>
	/// Wywołana prze przerwaniu kolicji.
	/// </summary>
	/// <param name="entity">Drugi uczestnik kolizji.</param>
	virtual void			EndContact(Entity * entity) = 0;
	/// <summary>
	/// Wywoływana przed spodziewanym zajściem kolicji. Np. działania zapobiegające kolizji.
	/// </summary>
	/// <param name="entitity">Drugi uczestnik kolizji</param>
	virtual void			Presolve(Entity * entitity) = 0;
	/// <summary>
	/// 
	/// </summary>
	/// <returns>Zwraca status obiektu</returns>
	int						Active() const;
	/// <summary>
	/// 
	/// </summary>
	/// <returns>Zwraca ID obiektu</returns>
	int						GroupID() const;
	/// <summary>
	/// Wywoływanie przez atakujący obiekt w celu zadania obrażeń
	/// </summary>
	/// <param name="damage">Ilość obrażeń.</param>
	virtual void			TakeDamage(float32 damage);
	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns>Pozycja obiektu w b2World</returns>
	b2Vec2					GetPosition() const;
	/// <summary>
	/// Gets the identifier.
	/// </summary>
	/// <returns>ID</returns>
	int						GetID();
	/// <summary>
	/// Dezaktywuje obiekt.
	/// </summary>
	void					SetBodyInactive() { body->SetActive(false); }
	/// <summary>
	/// Ustala maksymalny poziom punktów życia.
	/// </summary>
	/// <param name="max_hitpoints">The maximum hitpoints.</param>
	void					SetMaxHitpoints(unsigned long int max_hitpoints) { this->maxhitpoints = max_hitpoints; }
	/// <summary>
	/// Aktywuje obiekt.
	/// </summary>
	void					SetBodyActive() { body->SetActive(true); }
	/// <summary>
	/// Updates the observer.
	/// </summary>
	/// <param name="">The .</param>
	void					updateObserver(Entity*) override;
	/// <summary>
	/// Gets the score.
	/// </summary>
	/// <returns></returns>
	long int				getScore();
	/// <summary>
	/// Sets the score.
	/// </summary>
	/// <param name="">The .</param>
	void					setScore(long int);
	~Entity();

protected:
	int						groupID;  //1-PLayer 2-Zombie 3-Projectile 6-BasicEntanglements 9-Door 20 - niewidzialne ściany
	int						active;	  //-1 - do usunięcia; 0 - nieaktywny, ale wyświetlany; 1 - aktywny (brany pod uwagę przy symulacji, kolizjach...)	
	b2Body *				body;
	std::string				name;
	/*sf::RenderTexture*		texture;*/
	long int				hitpoints;
	long int				maxhitpoints;
	std::list<Effect *>		effects;
	sf::Texture*			texture;
	long int				score;
	sf::Vector2i			size;
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

 inline b2Vec2 rotateVectorAroundPoint( b2Vec2 point, b2Vec2 vector, float32 angle )
 {
	 return b2Vec2( ( (vector.x - point.x)*cosf( angle ) - (vector.y - point.y)*sinf( angle ) ) + point.x, ( (vector.x - point.x)*sinf( angle ) + (vector.y - point.y)*cosf( angle ) ) + point.y );
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
	EffectDamage( Entity * Origin, sf::Time Cooldown, sf::Time Duration, float32 Damage ) : Effect( Origin, Cooldown, Duration ), damage( Damage ) {};
	~EffectDamage() {};
	bool						ApplyEffect( Entity * entity, sf::Time time_difference )
	{
		if ( ( duration -= time_difference ) <= sf::seconds( 0 ) )
			return false;
		if ( ( counter = counter + time_difference ) > cooldown )
		{
			counter = sf::seconds( 0 );
			entity->TakeDamage( damage );
		}
		return true;
	};
private:
	float32				damage;
};
