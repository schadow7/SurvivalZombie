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
	void						Render( sf::RenderWindow * window );


private:
	b2World *					world;
	sf::Clock					clock;
	const float					SCALE = 100.f;
	std::vector <Entity*>		entities;
	ContactListener *			listener;
};