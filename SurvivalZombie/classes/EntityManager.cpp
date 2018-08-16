#include "EntityManager.h"

EntityManager::EntityManager(b2World * world)
{
	listener = new ContactListener( world );
}

EntityManager::~EntityManager()
{
}

void EntityManager::AddEntity( Entity * entity )
{
	entities.push_back( entity );
}

void EntityManager::RemoveEntity( Entity * entity )
{
}

void EntityManager::Render( sf::RenderWindow * window )
{
	//Symulacja œwiata
	world->Step( 1 / 60.f, 8, 3 );

	//Rysowanie obiektów symulowanych przez Box2D
	for ( auto & it : entities )
	{
		it->Update( window );
	}


}
