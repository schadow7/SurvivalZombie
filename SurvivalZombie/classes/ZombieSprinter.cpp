#include "ZombieSprinter.h"



ZombieSprinter::ZombieSprinter(b2World* world, b2Vec2 position) :
	Zombie(world, position)
{
	float spec_factor = .4f;
	hitpoints -= spec_factor * hitpoints;
	maxhitpoints = hitpoints;
	speed += spec_factor * speed;
	sizey = 40;
	sizex1 = 37;
	sizex2 = 43;
	body->GetFixtureList()->GetShape()->m_radius = sizey / 2 / SCALE;

	textureWalkingAnimation.loadFromFile(".\\graphics\\animations\\zombie40WalkingAnimation.png");
	textureWalkingAnimation.setSmooth(1);
	textureAttackingAnimation.loadFromFile(".\\graphics\\animations\\zombie40AttackingAnimation.png");
	textureAttackingAnimation.setSmooth(1);
	textureIdleAnimation.loadFromFile(".\\graphics\\animations\\zombie40IdleAnimation.png");
	textureIdleAnimation.setSmooth(1);

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
	animatedSprite = AnimatedSprite(sf::seconds(animSpeed*spec_factor), true, false);
	animatedSprite.setOrigin(sizex1/2, sizey/2);
	animatedSprite.setColor(sf::Color::Yellow);
	sprite.setColor(sf::Color::Yellow);
}


ZombieSprinter::~ZombieSprinter()
{
}
