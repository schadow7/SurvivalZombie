#pragma once
#include "DynamicBody.h"
#include "AIType.h"
class Zombie :
	public DynamicBody
{
public:
	Zombie(b2World* world,b2Vec2 position);
	~Zombie();
	void StartContact(Entity*);
	void EndContact(Entity*);
	void Render(sf::RenderWindow* window);
	void Update();
	virtual void Action(b2Vec2 player_positon) ;
	void SetTarget(const Entity* new_target);
private:
	AIType* AIType;
	float32 speed;
	sf::Sprite sprite;
	int size; //rozmair zombie w pikselach
	const Entity* target;
};

