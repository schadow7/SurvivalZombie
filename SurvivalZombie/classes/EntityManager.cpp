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

void EntityManager::Render( sf::RenderWindow * window )
{
	//Symulacja œwiata
	world->Step( 1 / 60.f, 8, 3 );

	//Rysowanie obiektów symulowanych przez Box2D
		for (auto & it : entities)
		{
			it->Update(window);
			//Przy okazji krok AI
			if (it->GroupID() == 1)
			{
				static_cast<Zombie*>(it)->Action(b2Vec2(3.f, 3.f));
			}
		}
}
