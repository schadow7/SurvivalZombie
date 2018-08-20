#include "Zombie.h"
#include"Aggressive.h"
#include <iostream>
#include <math.h>
Zombie::Zombie(b2World *world, b2Vec2 position) :
	DynamicBody(world, position),
	speed(1),
	size(50)
{
	//base stats 
	hitpoints = 100;
	AIType = new Aggressive();
	//fixture
	b2CircleShape zombieShape;
	zombieShape.m_radius = size/2/SCALE;
	b2FixtureDef zombieFixtureDef;
	zombieFixtureDef.shape = &zombieShape;
	zombieFixtureDef.density = 1;
	zombieFixtureDef.restitution = (0.f); 
	body->CreateFixture(&zombieFixtureDef);
	////SFML
	texture.loadFromFile(".\\graphics\\skeleton.png");
	sprite.setTexture(texture);
	float32 tmp= static_cast<float32>(size) / texture.getSize().x;
	sprite.setScale(tmp, tmp);

}

Zombie::~Zombie()
{
	delete AIType;
}

void Zombie::Action(b2Vec2 player_position)
{
	b2Vec2 dir = AIType->Move(body->GetPosition(),player_position);
	float32 angle =atan2(dir.y , dir.x);
	body->SetTransform(body->GetPosition(), angle);
	body->SetLinearVelocity(b2Vec2(dir.x*speed,dir.y*speed));
}
void Zombie::StartContact(Entity*) 
{
	;
}
void Zombie::EndContact(Entity*)
{
	;
}
void Zombie::Render(sf::RenderWindow* window)
{
	;
}
void Zombie::Update(sf::RenderWindow* window)
{
	//std::cout << "BoX: " << this->body->GetPosition().x << " " << this->body->GetPosition().x << " SFML: " << shape.getPosition().x << " " << shape.getPosition().y << std::endl;
	sprite.setPosition(SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y);
	sprite.setRotation(180 / b2_pi * this->body->GetAngle());
	window->draw(sprite);
	
}