#include "ZombieTank.h"



ZombieTank::ZombieTank(b2World* world, b2Vec2 position):
	Zombie(world,position)
{
	float spec_factor = .2f;
	hitpoints += spec_factor * hitpoints;
	maxhitpoints = hitpoints;
	speed -= spec_factor * speed;
	sizey = 60;
	sizex1 = 56;
	sizex2 = 65;
	body->GetFixtureList()->GetShape()->m_radius = sizey / 2 / SCALE;

	textureWalkingAnimation.loadFromFile(".\\graphics\\animations\\zombie60WalkingAnimation.png");
	textureAttackingAnimation.loadFromFile(".\\graphics\\animations\\zombie60AttackingAnimation.png");
	textureIdleAnimation.loadFromFile(".\\graphics\\animations\\zombie60IdleAnimation.png");

	walkingAnimation.setSpriteSheet(textureWalkingAnimation);
	attackingAnimation.setSpriteSheet(textureAttackingAnimation);
	idleAnimation.setSpriteSheet(textureIdleAnimation);
	for (int i = 0; i <= 16; i++)
	{
		walkingAnimation.addFrame(sf::IntRect(i * sizex1, 0, sizex1, sizey));
	}
	for (int i = 0; i <= 8; i++)
	{
		attackingAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
	}
	for (int i = 0; i <= 16; i++)
	{
		idleAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
	}

	currentAnimation = &walkingAnimation;
	animatedSprite = AnimatedSprite(sf::seconds(animSpeed/spec_factor/3), true, false);
	animatedSprite.setOrigin(sizex1/2, sizey/2);
	animatedSprite.setColor(sf::Color::Red);
}


ZombieTank::~ZombieTank()
{
}
