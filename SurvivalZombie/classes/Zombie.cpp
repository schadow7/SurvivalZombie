#include "Zombie.h"
#include"Aggressive.h"
Zombie::Zombie(b2World world, b2Vec2 position) :
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
	//TEMP
	sf::Sprite sprite;
	sf::CircleShape tempShape;
	tempShape.setRadius(5);
	tempShape.setFillColor(sf::Color(255, 0, 0));
	window->draw(tempShape);
}
void Zombie::Update(sf::RenderWindow* window)
{
	;
}