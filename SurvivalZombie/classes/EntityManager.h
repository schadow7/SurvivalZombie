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
		Entity* temp = static_cast<Entity*>(fixtureA->GetBody()->GetUserData());
		int id1 = temp->GetID();
		temp = static_cast<Entity*>(fixtureB->GetBody()->GetUserData());
		int id2 = temp->GetID();
		if (id1 == 9 && id2 == 1)
			return false;
		else
			return true;
	}

};