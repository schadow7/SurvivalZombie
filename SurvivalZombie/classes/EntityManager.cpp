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

void EntityManager::Update(sf::Time difference_time)
{
	//Symulacja œwiata
	world->Step( 1 / 60.f, 8, 3 );
	//Aktualizacja statusu obiektu (tu siê wykonuje logika gry)
	for ( auto & it : entities )
	{
		it->Update(difference_time);
	}
}

void EntityManager::Render( sf::RenderWindow * window )
{
	//Rysowanie obiektów symulowanych przez Box2D
		for (auto & it : entities)
		{
			it->Render( window );
		}
}

void EntityManager::KillEverybody()
{
	for (auto & it : entities)
	{
		it->TakeDamage(1000);
	}
}
