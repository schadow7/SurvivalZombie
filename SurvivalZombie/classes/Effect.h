#include "Entity.h"



class Effect
{
public:
	Effect( Entity * Origin, sf::Time Cooldown, sf::Time Duration ) : origin( Origin ), cooldown( Cooldown ), duration( Duration ) { };
	~Effect() { };
	virtual bool				ApplyEffect( Entity * entity, sf::Time time_difference ) { return false; };
	bool						IsActive() { return ( duration > sf::seconds( 0 ) ) ? false : true; };
	Entity *					GetOrigin() { return origin; }
protected:
	Entity *					origin;
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
			counter = sf::seconds(0);
			entity->TakeDamage( damage );
		}
		return true;
	};
private:
	unsigned int				damage;
};