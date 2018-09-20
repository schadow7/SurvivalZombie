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
	//Symulacja �wiata
	world->Step( 1 / 60.f, 8, 3 );
	//Aktualizacja statusu obiektu (tu si� wykonuje logika gry)
	for ( auto & it : entities )
	{
		it->Update( difference_time );

	}
	//Czyszczenie i przerzucanie obiekt�w do listy nieaktywnych obiekt�w
	for ( std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); )
	{
		if ( ( *it )->Active() == -1 )
		{
			delete ( *it );
			it = entities.erase( it );

		}
		else if ( ( *it )->Active() == 0 )
		{
			( *it )->SetBodyInactive();
			inactive_entities.push_back( ( *it ) );
			it = entities.erase( it );
		}
		else
		{
			it++;
		}
	}
}

void EntityManager::Render( sf::RenderWindow * window )
{
	//Rysowanie obiekt�w nieaktywnych
	for ( auto & it : inactive_entities )
	{
		it->RenderInactive( window );
	}
	
	//Rysowanie obiekt�w symulowanych przez Box2D
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
