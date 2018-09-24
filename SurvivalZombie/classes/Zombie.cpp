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
	score = 100;
	
	AI = new AIIdle(world);

	sizex1 = 46;
	sizex2 = 54;
	sizey = 50;

	//fixture
	b2CircleShape zombieShape;
	zombieShape.m_radius = sizey / 2 / SCALE;
	b2FixtureDef zombieFixtureDef;
	zombieFixtureDef.shape = &zombieShape;
	zombieFixtureDef.density = 1;
	zombieFixtureDef.restitution = (0.f);
	b2Fixture* fixture = body->CreateFixture(&zombieFixtureDef);

	hitpointsBarRed.setFillColor(sf::Color(255, 0, 0));
	hitpointsBarRed.setOutlineThickness( 1 );
	hitpointsBarRed.setOutlineColor( sf::Color( 0, 0, 0 ) );


	this->setSpriteSheets();

	this->addFramesToAnimations();

	currentAnimation = &idleAnimation;
	animatedSprite = AnimatedSprite(sf::seconds(animSpeed), true, false);
	animatedSprite.setOrigin(sizex2/2.0f, sizey/2.0f);
	animatedSprite.play(*currentAnimation);
	//dzwiêki
	hitSound.setBuffer(*AssetManager::GetSound("zombie2"));
	hitSound.setVolume(40);
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
	if (hitpoints <= 0)
	{
		active = 0;
		notify(this);
	}
	 if (hitSound.getStatus()!=sf::Sound::Playing)
		hitSound.play();
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
		if (AI_old) delete AI_old;
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
	if (attack_cooldown < attack_timer)
	{
		entity->TakeDamage( damage );
		attack_timer = sf::milliseconds( 0 );
		currentAnimation = &attackingAnimation;
		animatedSprite.setFrameTime(sf::seconds(animSpeed*3));
		animatedSprite.play(*currentAnimation);
//		int i = soundDistribution(engine);
		//if (i <= 6 && i >= 0)
			//attackSounds[i].play();
	}
}

void Zombie::StartContact(Entity* entity) 
{
	if ( entity->GroupID() == 1 )
	{
		attack_timer = sf::microseconds( 0 );
		attack = true;
	}
}

void Zombie::EndContact(Entity* entity)
{
	if ( entity->GroupID() == 1 )
	{
		attack_timer = sf::microseconds( 0 );
		attack = false;
	}
}

void Zombie::Presolve( Entity * entity )
{
	int id = entity->GroupID();
	if (id == 1 || id == 6 || id == 9)
		Attack(entity);
}

void Zombie::Render(sf::RenderWindow* window)
{
	this->setupHealthbar();

	if (isMoving())
	{
		currentAnimation = &walkingAnimation;
		animatedSprite.setFrameTime(sf::seconds(animSpeed));
		animatedSprite.play(*currentAnimation);
	}
	else if (isIdle())
	{
		currentAnimation = &idleAnimation;
		animatedSprite.setFrameTime(sf::seconds(animSpeed));
		animatedSprite.play(*currentAnimation);
	}

	frameTime = frameClock.restart();

	animatedSprite.update(frameTime);
	animatedSprite.setPosition(SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y);
	animatedSprite.setRotation(180 / b2_pi * this->body->GetAngle());

	if ((currentAnimation == &walkingAnimation) && animatedSprite.isPlaying()) animatedSprite.setOrigin(sizex1 / 2.f, sizey / 2.f);
	else animatedSprite.setOrigin(sizex2 / 2.f, sizey / 2.f);


	animatedSprite.setScale(float(sizey)/50.0f, float(sizey)/50.0f);
	window->draw(animatedSprite);
	window->draw(hitpointsBarRed);
}

void Zombie::RenderInactive(sf::RenderWindow * window)
{
	currentAnimation = &deadAnimation;
	animatedSprite.setOrigin(sizex1 / 2.f, sizey / 2.f);
	animatedSprite.setPosition( SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y );
	animatedSprite.setRotation( 180 / b2_pi * this->body->GetAngle() );
	animatedSprite.play(*currentAnimation);
	window->draw(animatedSprite);
}

bool Zombie::isMoving()
{
	direction = body->GetLinearVelocity();
	if (sqrt(direction.x*direction.x + direction.y*direction.y) > speed / 10.0f && !isAttacking()) return true;
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
		if ( !attack )
			body->SetLinearVelocity(b2Vec2(dir.x*speed, dir.y*speed));
		else
		{
			body->SetLinearVelocity( b2Vec2( 0, 0 ) );
			body->SetAngularVelocity( 0.f );
		}
	}
	else {
		//stoi w miejscu
		body->SetLinearVelocity(b2Vec2(0, 0));
		body->SetAngularVelocity(0.f);
	}
}

void Zombie::setSpriteSheets()
{
	walkingAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie50WalkingAnimation"));
	idleAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie50IdleAnimation"));
	attackingAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie50AttackingAnimation"));
	deadAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie50Dead"));
}

void Zombie::addFramesToAnimations()
{
	for (int i = 0; i < 17; i++) walkingAnimation.addFrame(sf::IntRect(i * sizex1, 0, sizex1, sizey));
	for (int i = 0; i < 17; i++) idleAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
	for (int i = 0; i < 9; i++) attackingAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
	for (int i = 0; i < 1; i++) deadAnimation.addFrame(sf::IntRect(0, 0, sizex1, sizey));
}


void Zombie::setupHealthbar()
{
	hitpointsBarRed.setSize(sf::Vector2f(int(70 * hitpoints / maxhitpoints), 5));
	hitpointsBarRed.setPosition(SCALE * this->body->GetPosition().x - int(35 * hitpoints / maxhitpoints), SCALE * this->body->GetPosition().y - 25);
}