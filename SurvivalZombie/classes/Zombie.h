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
	b2World* world;  //do raycast. shared pointer?
	//////
	class RayCastCallback :public b2RayCastCallback
	{
	public:
		std::vector<b2Vec2> obstacleList;
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
	};
	void doRayCast(RayCastCallback& callback);
};

