#pragma once
#include "AIType.h"
class AIAggressive :
	public AIType
{
public:
	AIAggressive(b2World*);
	~AIAggressive();
	/// <summary>
	/// Wyznacza kierunek ruchu Zombie.
	/// </summary>
	/// <param name="position">Bierz�ca pozycja Zombie</param>
	/// <param name="player_position">Bierz�ca pozycja gracza</param>
	/// <param name="current_angle">Bierz�cy k�t Zombie</param>
	/// <returns>
	/// Kierunek w postaci wektora
	/// </returns>
	b2Vec2 Move(b2Vec2 position, b2Vec2 player_position, float32 current_angle) override;
private:
	b2Vec2 old_dir;
	int obstructed=0;
};

