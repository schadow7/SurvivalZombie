#pragma once
#include "DynamicBody.h"
#include "AIType.h"
class Zombie :
	public DynamicBody
{
public:
	Zombie(b2World world,b2Vec2 position);
	~Zombie();
	void Action();
	void StartContact(Entity*);
	void EndContact(Entity*);
	void Render(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window);
private:
AIType* AIType;
double speed;

};

