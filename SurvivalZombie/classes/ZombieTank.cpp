#include "ZombieTank.h"



ZombieTank::ZombieTank(b2World* world, b2Vec2 position):
	Zombie(world,position)
{
	float spec_factor=.2f;
	hitpoints += spec_factor * hitpoints;
	speed -= spec_factor * speed;
	size = 60;
	body->GetFixtureList()->GetShape()->m_radius = size / 2 / SCALE;
	// + inny rozmiar i tekstury
	//temp
	sprite.setColor(sf::Color::Red);
	float scaleX = static_cast<float>(size) / texture->getSize().x;
	float scaleY = static_cast<float>(size) / texture->getSize().y;
	sprite.setScale(scaleX, scaleY);
}


ZombieTank::~ZombieTank()
{
}
