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
private:
	AIType* AIType;
	double speed;
	sf::CircleShape shape; 
	sf::Texture texture;

};

