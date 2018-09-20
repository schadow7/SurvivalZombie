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
	std::vector <Entity*>		entities;
	ContactListener *			listener;
};