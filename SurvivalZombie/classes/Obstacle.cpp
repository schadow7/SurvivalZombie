#include "Obstacle.h"

Obstacle::Obstacle(b2World* world, b2Vec2 position,sf::Vector2i nsize, sf::Texture* ntexture) :
	StaticBody(world, position)
{
	//base stats 
	groupID = 5;
	size = nsize;
	//fixture
	b2CircleShape obstacleShape;
	obstacleShape.m_radius = size.y / 2 / SCALE;
	b2FixtureDef obstacleFixtureDef;
	obstacleFixtureDef.shape = &obstacleShape;
	obstacleFixtureDef.density = 1;
	obstacleFixtureDef.restitution = (0.f);
	b2Fixture* fixture = body->CreateFixture(&obstacleFixtureDef);

	texture = ntexture;
	sprite.setTexture(*texture);
	sprite.setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
	float scaleX = static_cast<float>(size.y) / texture->getSize().x;
	float scaleY = static_cast<float>(size.y) / texture->getSize().y;
	sprite.setScale(scaleX, scaleY);

	sprite.setPosition(SCALE * position.x, SCALE * position.y);
	sprite.setRotation(180 / b2_pi * this->body->GetAngle());
}

Obstacle::~Obstacle()
{
}


void Obstacle::TakeDamage(float32 damage)
{
	hitpoints -= damage;
	if (hitpoints <= 0)
	{
		active = 0;
		notify(this);
	}
}

void Obstacle::StartContact(Entity* entity)
{

}
void Obstacle::EndContact(Entity*)
{
	;
}
void Obstacle::Presolve(Entity * entity)
{

}
void Obstacle::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Obstacle::RenderInactive(sf::RenderWindow * window)
{
	window->draw(sprite);
}

void Obstacle::Update(sf::Time difference_time)
{
	
}
