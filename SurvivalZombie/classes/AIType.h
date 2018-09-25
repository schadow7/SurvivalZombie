#pragma once
#include <Box2D/Box2D.h>
#include <vector>
/// <summary>
/// Interfejs algorytmów kieruj¹cych Zombie
/// </summary>
class AIType
{
public:
	AIType(b2World*);
	virtual ~AIType();

	/// <summary>
	/// Wyznacza kierunek ruchu Zombie.
	/// </summary>
	/// <param name="position">Bierz¹ca pozycja Zombie</param>
	/// <param name="player_position">Bierz¹ca pozycja gracza</param>
	/// <param name="current_angle">Bierz¹cy k¹t Zombie</param>
	/// <returns>Kierunek w postaci wektora</returns>
	virtual b2Vec2 Move(b2Vec2 position, b2Vec2 player_position, float32 current_angle) = 0;
protected:
	b2World* world;
	/// <summary>
	/// Klasa zawieraj¹ca wynik wykonania raycast.
	/// </summary>
	/// <seealso cref="b2RayCastCallback" />
	class RayCastCallback :public b2RayCastCallback
	{
	public:
		RayCastCallback() :obstructed(0) {};
		bool obstructed;
		/// <summary>
		/// </summary>
		/// <param name="fixture"></param>
		/// <param name="point"></param>
		/// <param name="normal"></param>
		/// <param name="fraction"></param>
		/// <returns></returns>
		/// Called for each fixture found in the query. You control how the ray cast
		/// proceeds by returning a float:
		/// return -1: ignore this fixture and continue
		/// return 0: terminate the ray cast
		/// return fraction: clip the ray to this point
		/// return 1: don't clip the ray and continue
		/// @param fixture the fixture hit by the ray
		/// @param point the point of initial intersection
		/// @param normal the normal vector at the point of intersection
		/// @return -1 to filter, 0 to terminate, fraction to clip the ray for
		/// closest hit, 1 to continue
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
	};
	/// <summary>
	/// Wywyo³uje raycast w zadanym kierunku, i pozycji, o sta³ej d³ugoœci.
	/// </summary>
	/// <param name="callback">Obiekt callback</param>
	/// <param name="ray_orgin">Punkt pocz¹tku promienia</param>
	/// <param name="currentRayAngle">K¹t pocz¹tku promiena</param>
	virtual void doRayCast(RayCastCallback& callback, b2Vec2 ray_orgin, float currentRayAngle = 0);
	const float DEGTORAD = b2_pi / 180;
};

