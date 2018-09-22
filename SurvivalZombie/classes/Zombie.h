#pragma once
#pragma once
#include "DynamicBody.h"
#include "AIType.h"
#include "AnimatedSprite.h"
class Zombie :
	public DynamicBody
{
public:
	Zombie(b2World* world, b2Vec2 position);
	~Zombie();
	void StartContact(Entity*);
	void EndContact(Entity*);
	void Presolve(Entity*);
	void Render(sf::RenderWindow* window);
	void RenderInactive(sf::RenderWindow* window);
	void Update(sf::Time);
	virtual void Action(b2Vec2 player_positon);
	void TakeDamage(float32 damage) override;
	void SetTarget(const Entity* new_target);
	enum AI_enum { Aggrssive, Chaotic, Idle };
	void SetAI(AI_enum);
	void SetAI(AIType*);
	virtual void Attack(Entity * entity);
protected:
	float32 speed;
	double animSpeed;
	int sizey; //rozmiar zombie w pikselach
	int sizex1;
	int sizex2;
	sf::Sprite sprite;
	sf::RectangleShape hitpointsBarRed;
	sf::RectangleShape hitpointsBarBlack;
	AnimatedSprite			animatedSprite;
	Animation*				currentAnimation;
	sf::Texture				textureDead;
	sf::Clock				frameClock;
	sf::Time				frameTime;
	sf::Time				attack_timer;
	sf::Time				attack_cooldown;
	float32					damage;
	void					setupHealthbar();
	bool					isMoving();
	bool					isAttacking();
	bool					isIdle();
	b2Vec2					direction;
	AIType* AI;
	const Entity* target;
	b2World* world;
private:
	void					setSpriteSheets();
	void					addFramesToAnimations();
	Animation				walkingAnimation;
	Animation				attackingAnimation;
	Animation				idleAnimation;
	Animation				deadAnimation;
	////// //do raycast. shared pointer?

	class RayCastCallback :public b2RayCastCallback
	{
	public:
		std::vector<b2Vec2> obstacleList;
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
	};
	void doRayCast(RayCastCallback& callback);
};

