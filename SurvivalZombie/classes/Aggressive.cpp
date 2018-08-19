#include "Aggressive.h"



Aggressive::Aggressive()
{
}


Aggressive::~Aggressive()
{
}

b2Vec2 Aggressive::Move(b2Vec2 position, b2Vec2 player_position)
{
	b2Vec2 temp = player_position - position;
	temp.x = temp.x / temp.Length();
	temp.y = temp.y / temp.Length();
	return temp;
}