#include "ZombieSprinter.h"



ZombieSprinter::ZombieSprinter(b2World* world, b2Vec2 position) :
	Zombie(world, position)
{
	float spec_factor = .4f;
	hitpoints -= spec_factor * hitpoints;
	maxhitpoints = hitpoints;
	speed += spec_factor * speed;
	animSpeed -= spec_factor * animSpeed;

	sizey = 40;
	sizex1 = 37;
	sizex2 = 43;

	body->GetFixtureList()->GetShape()->m_radius = sizey / 2 / SCALE;

	setSpriteSheets();
	addFramesToAnimations();

	currentAnimation = &idleAnimation;
	animatedSprite = AnimatedSprite(sf::seconds(animSpeed), true, false);
	animatedSprite.setOrigin(sizex1/2, sizey/2);
	animatedSprite.setColor(sf::Color::Yellow);
	sprite.setColor(sf::Color::Yellow);
	animatedSprite.play(*currentAnimation);
}


ZombieSprinter::~ZombieSprinter()
{
}

void ZombieSprinter::setSpriteSheets()
{
	walkingAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie40WalkingAnimation"));
	idleAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie40AttackingAnimation"));
	attackingAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie40IdleAnimation"));
	textureDead = *AssetManager::GetTexture("zombie40Dead");
}

void ZombieSprinter::addFramesToAnimations()
{
	for (int i = 0; i < 17; i++) walkingAnimation.addFrame(sf::IntRect(i * sizex1, 0, sizex1, sizey));
	for (int i = 0; i < 17; i++) idleAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
	for (int i = 0; i < 9; i++) attackingAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
}
