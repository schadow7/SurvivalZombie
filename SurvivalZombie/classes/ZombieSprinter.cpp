#include "ZombieSprinter.h"



ZombieSprinter::ZombieSprinter(b2World* world, b2Vec2 position) :
	Zombie(world, position)
{
	float spec_factor = .4f;
	hitpoints -= spec_factor * hitpoints;
	speed += spec_factor * speed;
	size = 40;
	body->GetFixtureList()->GetShape()->m_radius = size / 2 / SCALE;
	// + inny rozmiar i tekstury
	//temp
	sprite.setColor(sf::Color::Yellow);
	float scaleX = static_cast<float>(size) / texture->getSize().x;
	float scaleY = static_cast<float>(size) / texture->getSize().y;
	sprite.setScale(scaleX, scaleY);
}


ZombieSprinter::~ZombieSprinter()
{
}
