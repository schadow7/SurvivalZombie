#include "Zombie.h"
#include"Aggressive.h"
#include <iostream>
#include <math.h>
Zombie::Zombie(b2World *world, b2Vec2 position) :
	DynamicBody(world, position),
	speed(1),
	size(50),
	world(world)
{
	//base stats 
	groupID = 2;
	hitpoints = 100;
	AIType = new Aggressive(world);
	//fixture
	b2CircleShape zombieShape;
	zombieShape.m_radius = size/2/SCALE;
	b2FixtureDef zombieFixtureDef;
	zombieFixtureDef.shape = &zombieShape;
	zombieFixtureDef.density = 1;
	zombieFixtureDef.restitution = (0.f); 
	b2Fixture* fixture=body->CreateFixture(&zombieFixtureDef);
	
	////SFML
	texture = AssetManager::GetTexture(".\\graphics\\skeleton.png");
	sprite.setTexture(*texture);
	sprite.setOrigin(texture->getSize().x/2.f, texture->getSize().y / 2.f);
	float scaleX= static_cast<float>(size) / texture->getSize().x;
	float scaleY = static_cast<float>(size) / texture->getSize().y;
	sprite.setScale(scaleX, scaleY);

	////Do zobaczenia czy wyœwietlanie jest prawid³owe
	//shape.setOrigin( sf::Vector2f( 24.f, 24.f ) );
	//shape.setOutlineThickness( 1 );
	//shape.setOutlineColor( sf::Color::Black );
}

Zombie::~Zombie()
{
	delete AIType;
}

void Zombie::Action(b2Vec2 player_position)  //deprecated
{
	;
}
void Zombie::SetTarget(const Entity* new_terget)
{
	target = new_terget;
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
	sprite.setPosition( SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y );
	//shape.setPosition(SCALE * 2, SCALE * 2);
	sprite.setRotation( 180 / b2_pi * this->body->GetAngle() );
	window->draw( sprite );
}
void Zombie::Update(sf::Time)
{
	if (target)
	{
		//RayCastCallback callbackInfo;
		//doRayCast(callbackInfo);
		b2Vec2 player_position = target->GetPosition();
		/*b2Vec2 dir = AIType->Move(body->GetPosition(), player_position, callbackInfo.obstacleList);*/
		b2Vec2 dir = AIType->Move(body->GetPosition(), player_position,body->GetAngle());
		float32 new_angle = atan2(dir.y, dir.x);
		body->SetTransform(body->GetPosition(), new_angle);
		body->SetLinearVelocity(b2Vec2(dir.x*speed, dir.y*speed));
	}
	else {
		//stoi w miejscu
		body->SetLinearVelocity(b2Vec2(0,0));
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
