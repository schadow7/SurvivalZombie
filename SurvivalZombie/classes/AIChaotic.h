#pragma once
#include "AIType.h"
#include <random>
class AIChaotic :
	public AIType
{
public:
	AIChaotic(b2World* nworld);
	~AIChaotic();
	/// <summary>
	/// Wyznacza kierunek ruchu Zombie.
	/// </summary>
	/// <param name="position">Bierz¹ca pozycja Zombie</param>
	/// <param name="player_position">Bierz¹ca pozycja gracza</param>
	/// <param name="current_angle">Bierz¹cy k¹t Zombie</param>
	/// <returns>
	/// Kierunek w postaci wektora
	/// </returns>
	b2Vec2 Move(b2Vec2 position, b2Vec2 player_position, float32 current_angle) override;
private:
	b2Vec2 old_dir;
	int obstructed = 0;
	std::default_random_engine engine;
	std::uniform_int_distribution<int> dis{ -1, 1 };
};

