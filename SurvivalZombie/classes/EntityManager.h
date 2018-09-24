#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Entity.h"
#include "ContactListener.h"
#include <vector>

class EntityManager
{
public:
	EntityManager(b2World * world);
	~EntityManager();

	void						AddEntity( Entity * entity );
	void						RemoveEntity( Entity * entity );
	void						Update(sf::Time difference_time);
	void						Render( sf::RenderWindow * window );
	b2World *					World() { return world; }
	void						KillEverybody();
	void						CleanBodies();

private:
	b2World *					world;
	std::list <Entity*>			entities;
	std::list <Entity*>			inactive_entities;
	ContactListener *			listener;
};

class ContactFilter : public b2ContactFilter
{
public:
	ContactFilter(b2World* world)
	{
		world->SetContactFilter(this);
	}
	bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override
	{
		int id1 = static_cast<Entity*>(fixtureA->GetBody()->GetUserData())->GetID();
		int id2 = static_cast<Entity*>(fixtureB->GetBody()->GetUserData())->GetID();
		// przechodzenie Player przez drzwi
		if (id1 == 9 && id2 == 1)
			return false;
		// przelatywanie pocisków nad murem
		else if ((id1 == 3 && id2 == 6) || (id1 == 6 && id2 == 3))
			return false;
		// przelatywanie pocisków nad drzwiami
		else if ((id1 == 3 && id2 == 9) || (id1 == 9 && id2 == 3))
			return false;
		else if ( ( id1 == 3 && id2 == 3 ) || ( id1 == 3 && id2 == 3 ) )
			return false;
		else if ( ( id1 == 3 && id2 == 1 ) || ( id1 == 1 && id2 == 3 ) )
			return false;
		//wlatywanie pocisków w zombie
		//else if ((id1 = 3 && id2 == 2) || (id1 = 2 && id2 == 3))
		//	return true;
		else
			return true;
	}

}; 