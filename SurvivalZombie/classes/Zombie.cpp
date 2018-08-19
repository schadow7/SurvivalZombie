#include "Zombie.h"
#include"Aggressive.h"
#include <iostream>
Zombie::Zombie(b2World *world, b2Vec2 position) :
	DynamicBody(world),
	speed(1)
{
	AIType = new Aggressive();
	body->SetTransform(position, body->GetAngle());
	//fixture
	b2CircleShape zombieShape;
	zombieShape.m_radius = 1;
	b2FixtureDef zombieFixtureDef;
	zombieFixtureDef.shape = &zombieShape;
	zombieFixtureDef.density = 1;
	body->CreateFixture(&zombieFixtureDef);
	//SFML
	shape.setRadius(5);
	shape.setFillColor(sf::Color(255, 0, 0));
}

Zombie::~Zombie()
{
	delete AIType;
}

void Zombie::Action()
{
	;
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
	shape.setPosition(SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y);
	//shape.setPosition(SCALE * 2, SCALE * 2);
	shape.setRotation(180 / b2_pi * this->body->GetAngle());
	window->draw(shape);
	
}