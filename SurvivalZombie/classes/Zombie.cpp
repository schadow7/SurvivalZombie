#include "Zombie.h"
#include"AIType.h"
#include <iostream>
#include <math.h>
#include "AIChaotic.h"
#include "AIAggressive.h"
#include "AIIdle.h"
Zombie::Zombie(b2World *world, b2Vec2 position) :
	DynamicBody(world, position),
	speed(1),
	sizey(50),
	world(world),
	animSpeed(0.03)
{
	//base stats 
	groupID = 2;
	hitpoints = 100;
	maxhitpoints = 100;
	//AI = new AIAggressive(world);
	//AIType = new AIChaotic(world);
	AI = new AIIdle(world);
	//fixture
	b2CircleShape zombieShape;
	zombieShape.m_radius = sizey/2/SCALE;
	b2FixtureDef zombieFixtureDef;
	zombieFixtureDef.shape = &zombieShape;
	zombieFixtureDef.density = 1;
	zombieFixtureDef.restitution = (0.f); 
	b2Fixture* fixture=body->CreateFixture(&zombieFixtureDef);

	hitpointsBarRed.setFillColor(sf::Color(255, 0, 0));
	hitpointsBarBlack.setFillColor(sf::Color(0, 0, 0));

	int sizex1 = 46;
	int sizex2 = 54;
	int sizey = 50;

	textureWalkingAnimation.loadFromFile(".\\graphics\\zombie50WalkingAnimation.png");
	textureAttackingAnimation.loadFromFile(".\\graphics\\zombie50AttackingAnimation.png");
	textureIdleAnimation.loadFromFile(".\\graphics\\zombie50IdleAnimation.png");

	walkingAnimation.setSpriteSheet(textureWalkingAnimation);
	attackingAnimation.setSpriteSheet(textureAttackingAnimation);
	idleAnimation.setSpriteSheet(textureIdleAnimation);
	for (int i = 0; i <= 16; i++)
	{
		walkingAnimation.addFrame(sf::IntRect(i * sizex1, 0, sizex1, sizey));
	}
	for (int i = 0; i <= 8; i++)
	{
		attackingAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
	}
	for (int i = 0; i <= 16; i++)
	{
		idleAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
	}

	currentAnimation = &walkingAnimation;
	animatedSprite = AnimatedSprite(sf::seconds(animSpeed), true, false);
	animatedSprite.setOrigin(sizex1/2, sizey/2);
}

Zombie::~Zombie()
{
	delete AI;
}

void Zombie::Action(b2Vec2 player_position)  //deprecated
{
	;
}
void Zombie::TakeDamage( float32 damage )
{
	hitpoints -= damage;
	if ( hitpoints < 0 )
	{
		body->SetActive( false );
		active = 0;
		notify( this );
	}
}
void Zombie::SetTarget(const Entity* new_target)
{
	target = new_target;
}
void Zombie::SetAI(AI_enum new_type)
{
	AIType* AI_old = AI;
	switch (new_type) {
	case Aggrssive: AI = new AIAggressive(world);
				if(AI_old) delete AI_old;
				break;
	case Chaotic: AI = new AIChaotic(world);
		if (AI_old) delete AI_old;
				break;
	case Idle: AI = new AIIdle(world);
		if (AI_old) delete AI_old;
			break;
	default: 
		break;
	}
}
void Zombie::SetAI(AIType * new_type)
{
	if (AI) delete (AI);
	AI = new_type;
}
void Zombie::StartContact(Entity*) 
{
	;
}
void Zombie::EndContact(Entity*)
{
	;
}
void Zombie::Presolve( Entity * )
{
}
void Zombie::Render(sf::RenderWindow* window)
{
	//std::cout << "BoX: " << this->body->GetPosition().x << " " << this->body->GetPosition().x << " SFML: " << shape.getPosition().x << " " << shape.getPosition().y << std::endl;
	//sprite.setPosition( SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y );
	//shape.setPosition(SCALE * 2, SCALE * 2);
	//sprite.setRotation( 180 / b2_pi * this->body->GetAngle() );



	hitpointsBarRed.setSize(sf::Vector2f(int(70 * hitpoints / maxhitpoints), 5));
	hitpointsBarBlack.setSize(sf::Vector2f(int(72 * hitpoints / maxhitpoints), 7));
	hitpointsBarRed.setPosition(SCALE * this->body->GetPosition().x - int(35*hitpoints/maxhitpoints), SCALE * this->body->GetPosition().y - 25);
	hitpointsBarBlack.setPosition(SCALE * this->body->GetPosition().x - int(36*hitpoints/maxhitpoints), SCALE * this->body->GetPosition().y - 26);

	frameTime = frameClock.restart();
	animatedSprite.play(*currentAnimation);
	animatedSprite.update(frameTime);
	animatedSprite.setPosition(SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y);
	animatedSprite.setRotation(180 / b2_pi * this->body->GetAngle());


	window->draw(animatedSprite);
	window->draw(hitpointsBarBlack);
	window->draw(hitpointsBarRed);
}
void Zombie::Update(sf::Time)
{
	if (target && active)
	{
		//RayCastCallback callbackInfo;
		//doRayCast(callbackInfo);
		b2Vec2 player_position = target->GetPosition();
		/*b2Vec2 dir = AIType->Move(body->GetPosition(), player_position, callbackInfo.obstacleList);*/
		b2Vec2 dir = AI->Move(body->GetPosition(), player_position,body->GetAngle());
		float32 new_angle = atan2(dir.y, dir.x);
		body->SetTransform(body->GetPosition(), new_angle);
		body->SetLinearVelocity(b2Vec2(dir.x*speed, dir.y*speed));
	}
	else if ( active == 0 )
	{

	}
	else {
		//stoi w miejscu
		body->SetLinearVelocity(b2Vec2(0,0));
		body->SetAngularVelocity(0.f);
	}
}
void Zombie::doRayCast(RayCastCallback & callback)
{
	float currentRayAngle = 0;
	float rayLength = .33f;
	float DEGTORAD = 0.017453292519;
	int RayNum = 8;
	//in Step() function
	for (int i=0;i< RayNum;i++)
	{
		currentRayAngle += 360 / RayNum * DEGTORAD;
		//calculate points of ray
		b2Vec2 p1=body->GetPosition();
		b2Vec2 p2 = p1 + rayLength * b2Vec2(sinf(currentRayAngle), cosf(currentRayAngle));
		world->RayCast(&callback, p1, p2);
	}
}

float32 Zombie::RayCastCallback::ReportFixture(b2Fixture * fixture, const b2Vec2 & point, const b2Vec2 & normal, float32 fraction)
{
	obstacleList.push_back(point);
	return float32(1);
}
