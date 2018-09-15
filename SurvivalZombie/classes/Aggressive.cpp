#include "Aggressive.h"



Aggressive::Aggressive(b2World* world)
{
	this->world = world;
}


Aggressive::~Aggressive()
{
}

b2Vec2 Aggressive::Move(b2Vec2 position, b2Vec2 player_position)
{
	RayCastCallback callbackInfo;
	doRayCast(callbackInfo,position);

	b2Vec2 direction = .1f*(player_position - position);
	for (auto& v : callbackInfo.obstacleList)
	{
		auto temp = v - position;
		temp.x = temp.x / temp.Length()/ temp.Length();
		temp.y = temp.y / temp.Length()/ temp.Length();
		direction -= temp;
	}
	//normalizacja
	direction.x = direction.x / direction.Length();
	direction.y = direction.y / direction.Length();
	return direction;
}

//RayCastCallback callbackInfo;
//doRayCast(callbackInfo, position);
////sztuczne pola potncja³u
//b2Vec2 direction = .1f*(player_position - position);
//for (auto& v : obstacles)
//{
//	auto temp = v - position;
//	temp.x = temp.x / temp.Length() / temp.Length();
//	temp.y = temp.y / temp.Length() / temp.Length();
//	direction -= temp;
//}
////normalizacja
//direction.x = direction.x / direction.Length();
//direction.y = direction.y / direction.Length();
//return direction;