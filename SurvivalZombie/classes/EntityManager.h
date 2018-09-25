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

	/// <summary>
	/// Dodaje obiekt do listy aktywych obiektów na mapie.
	/// </summary>
	/// <param name="entity">The entity.</param>
	void						AddEntity(Entity * entity);
	/// <summary>
	/// Usywa wskazany obiekt
	/// </summary>
	/// <param name="entity">The entity.</param>
	void						RemoveEntity(Entity * entity);
	/// <summary>
	/// Aktualizuje wszystkie obekty na mapie.
	/// </summary>
	/// <param name="difference_time">The difference time.</param>
	void						Update(sf::Time difference_time);
	/// <summary>
	/// Rysuje wszystkie obiekty w oknie gry
	/// </summary>
	/// <param name="window">The window.</param>
	void						Render(sf::RenderWindow * window);
	b2World *					World() { return world; }
	/// <summary>
	/// Zabija wszystkie obiekty obiekty. Funkcjia do debugowania
	/// </summary>
	void						KillEverybody();
	/// <summary>
	/// Usuwa niaktywne obiekty z mapy gry.
	/// </summary>
	void						CleanBodies();


private:
	b2World *					world;
	std::list <Entity*>			entities;
	std::list <Entity*>			inactive_entities;
	ContactListener *			listener;
};

/// <summary>
/// Filtr kolizji
/// </summary>
/// <seealso cref="b2ContactFilter" />
class ContactFilter : public b2ContactFilter
{
public:
	ContactFilter(b2World* world)
	{
		world->SetContactFilter(this);
	}
	/// <summary>
	/// Wywo³ywania w przpadku zajœcia kolizji
	/// </summary>
	/// <param name="fixtureA"></param>
	/// <param name="fixtureB"></param>
	/// <returns></returns>
	/// Return true if contact calculations should be performed between these two shapes.
	/// @warning for performance reasons this is only called when the AABBs begin to overlap.
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
		else if ( ( id1 == 3 && id2 == 20 ) || ( id1 == 20 && id2 == 3 ) )
			return false;
		else if ( ( id1 == 2 && id2 == 20 ) || ( id1 == 20 && id2 == 2 ) )
			return false;
		else
			return true;
	}

}; 