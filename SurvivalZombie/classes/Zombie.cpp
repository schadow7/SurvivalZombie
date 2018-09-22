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
	world(world),
	animSpeed(0.03)
{
	//base stats 
	groupID = 2;
	hitpoints = 100;
	maxhitpoints = 100;
	damage = 5;
	attack_cooldown = sf::milliseconds( 500 );
	attack_timer = sf::milliseconds( 520 );
	
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

	sizex1 = 46;
	sizex2 = 54;
	sizey = 50;

	setSpriteSheets();

	addFramesToAnimations();

	currentAnimation = &idleAnimation;
	animatedSprite = AnimatedSprite(sf::seconds(animSpeed), true, false);
	animatedSprite.setOrigin(sizex2/2.0f, sizey/2.0f);
	animatedSprite.play(*currentAnimation);
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
	if ( hitpoints <= 0 )
	{
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

void Zombie::Attack( Entity * entity )
{
	if ( attack_cooldown < attack_timer )
	{
		entity->TakeDamage( damage );
		attack_timer = sf::milliseconds( 0 );
		currentAnimation = &attackingAnimation;
		animatedSprite.play(*currentAnimation);
	}
}

void Zombie::StartContact(Entity* entity) 
{
	if ( entity->GroupID() == 1 )
		attack_timer = sf::microseconds( 0 );
}

void Zombie::EndContact(Entity*)
{
	;
}

void Zombie::Presolve( Entity * entity )
{
	if ( entity->GroupID() == 1 || entity->GroupID() == 6)
		Attack( entity );
}

void Zombie::Render(sf::RenderWindow* window)
{
	setupHealthbar();

	isMoving();

	frameTime = frameClock.restart();

	animatedSprite.update(frameTime);
	animatedSprite.setPosition(SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y);
	animatedSprite.setRotation(180 / b2_pi * this->body->GetAngle());

	if ((currentAnimation == &walkingAnimation) && animatedSprite.isPlaying()) animatedSprite.setOrigin(sizex1 / 2.f, sizey / 2.f);
	else animatedSprite.setOrigin(sizex2 / 2.f, sizey / 2.f);

	window->draw(animatedSprite);
	window->draw(hitpointsBarBlack);
	window->draw(hitpointsBarRed);
}

void Zombie::RenderInactive( sf::RenderWindow * window )
{
	sprite.setTexture( textureDead );
	sprite.setPosition( SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y );
	sprite.setRotation( 180 / b2_pi * this->body->GetAngle() );
	window->draw( sprite );
}

bool Zombie::isMoving()
{
	direction = body->GetLinearVelocity();
	if (sqrt(direction.x*direction.x + direction.y*direction.y) > speed / 10.0f && !this->isAttacking())
	{
		currentAnimation = &walkingAnimation;
		animatedSprite.play(*currentAnimation);
		return true;
	}
	else return false;
}

bool Zombie::isAttacking()
{
	if (currentAnimation == &attackingAnimation && animatedSprite.isPlaying()) return true;
	else return false;
}

bool Zombie::isIdle()
{
	if (currentAnimation == &idleAnimation || !animatedSprite.isPlaying()) return true;
	else return false;
}

void Zombie::Update(sf::Time difference_time)
{
	if (target && active)
	{
		attack_timer += difference_time;
		b2Vec2 player_position = target->GetPosition();
		b2Vec2 dir = AI->Move(body->GetPosition(), player_position,body->GetAngle());
		float32 new_angle = atan2(dir.y, dir.x);
		body->SetTransform(body->GetPosition(), new_angle);
		body->SetLinearVelocity(b2Vec2(dir.x*speed, dir.y*speed));
	}
	else {
		//stoi w miejscu
		body->SetLinearVelocity(b2Vec2(0,0));
		body->SetAngularVelocity(0.f);
	}
}

void Zombie::setSpriteSheets()
{
	walkingAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie50WalkingAnimation"));
	idleAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie50AttackingAnimation"));
	attackingAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie50IdleAnimation"));
	textureDead = *AssetManager::GetTexture("zombie50Dead");
}

void Zombie::addFramesToAnimations()
{
	for (int i = 0; i < 17; i++) walkingAnimation.addFrame(sf::IntRect(i * sizex1, 0, sizex1, sizey));
	for (int i = 0; i < 17; i++) idleAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
	for (int i = 0; i < 9; i++) attackingAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
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

void Zombie::setupHealthbar()
{
	hitpointsBarRed.setSize(sf::Vector2f(int(70 * hitpoints / maxhitpoints), 5));
	hitpointsBarBlack.setSize(sf::Vector2f(int(72 * hitpoints / maxhitpoints), 7));
	hitpointsBarRed.setPosition(SCALE * this->body->GetPosition().x - int(35 * hitpoints / maxhitpoints), SCALE * this->body->GetPosition().y - 25);
	hitpointsBarBlack.setPosition(SCALE * this->body->GetPosition().x - int(36 * hitpoints / maxhitpoints), SCALE * this->body->GetPosition().y - 26);
}