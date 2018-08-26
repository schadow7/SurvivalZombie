#include "EntityManager.h"
#include "Zombie.h"

EntityManager::EntityManager(b2World * world)
{
	this->world = world;
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

void EntityManager::Update()
{
	//Symulacja �wiata
	world->Step( 1 / 60.f, 8, 3 );

	//Aktualizacja statusu obiektu (tu si� wykonuje logika gry)
	for ( auto & it : entities )
	{
		it->Update();
	}
}

void EntityManager::Render( sf::RenderWindow * window )
{
	//Rysowanie obiekt�w symulowanych przez Box2D
		for (auto & it : entities)
		{
			it->Render( window );
		}
}
