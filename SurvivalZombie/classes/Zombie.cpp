#include "Zombie.h"
#include"Aggressive.h"
#include <iostream>
#include <math.h>
Zombie::Zombie(b2World *world, b2Vec2 position) :
	DynamicBody(world),
	speed(1)
{
	//base stats 
	hitpoints = 100;
	AIType = new Aggressive();
	body->SetTransform(position, body->GetAngle());
	//fixture
	b2CircleShape zombieShape;
	zombieShape.m_radius = 24 / SCALE;
	b2FixtureDef zombieFixtureDef;
	zombieFixtureDef.shape = &zombieShape;
	zombieFixtureDef.density = 1;
	body->CreateFixture(&zombieFixtureDef);
	////SFML
	texture.loadFromFile(".\\graphics\\skeleton.png");
	shape.setTexture(&texture);
	shape.setRadius(25);

	//Do zobaczenia czy wyœwietlanie jest prawid³owe
	shape.setOrigin( sf::Vector2f( 24.f, 24.f ) );
	shape.setOutlineThickness( 1 );
	shape.setOutlineColor( sf::Color::Black );
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
	//std::cout << "BoX: " << this->body->GetPosition().x << " " << this->body->GetPosition().x << " SFML: " << shape.getPosition().x << " " << shape.getPosition().y << std::endl;
	shape.setPosition( SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y );
	//shape.setPosition(SCALE * 2, SCALE * 2);
	shape.setRotation( 180 / b2_pi * this->body->GetAngle() );
	window->draw( shape );
}
void Zombie::Update()
{

	;
}