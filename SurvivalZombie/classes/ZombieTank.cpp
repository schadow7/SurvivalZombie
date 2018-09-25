#include "ZombieTank.h"



ZombieTank::ZombieTank(b2World* world, b2Vec2 position) :
	Zombie(world, position)
{
	float spec_factor = .2f;
	hitpoints += spec_factor * hitpoints;
	maxhitpoints = hitpoints;
	speed -= spec_factor * speed;
	animSpeed += spec_factor * animSpeed;
	score += spec_factor * score;
	damage = 15;
	sizex1 = 56;
	sizex2 = 65;
	sizey = 60;

	body->GetFixtureList()->GetShape()->m_radius = sizey / 2 / SCALE;

	setSpriteSheets();
	addFramesToAnimations();

	currentAnimation = &idleAnimation;
	animatedSprite = AnimatedSprite(sf::seconds(animSpeed), true, false);
	animatedSprite.setOrigin(sizex1 / 2, sizey / 2);
	animatedSprite.setColor(sf::Color::Red);
	sprite.setColor(sf::Color::Red);
	animatedSprite.play(*currentAnimation);
}


ZombieTank::~ZombieTank()
{
}

void ZombieTank::setSpriteSheets()
{
	walkingAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie60WalkingAnimation"));
	idleAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie60IdleAnimation"));
	attackingAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie60AttackingAnimation"));
	deadAnimation.setSpriteSheet(*AssetManager::GetTexture("zombie60Dead"));
}

void ZombieTank::addFramesToAnimations()
{
	for (int i = 0; i < 17; i++) walkingAnimation.addFrame(sf::IntRect(i * sizex1, 0, sizex1, sizey));
	for (int i = 0; i < 17; i++) idleAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
	for (int i = 0; i < 9; i++) attackingAnimation.addFrame(sf::IntRect(i * sizex2, 0, sizex2, sizey));
	for (int i = 0; i < 1; i++) deadAnimation.addFrame(sf::IntRect(0, 0, sizex1, sizey));
}
