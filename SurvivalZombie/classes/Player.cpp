#include "Player.h"

Player::Player( b2World * world, b2Vec2 position ) : DynamicBody(world, position)
{
	//base stats
	animSpeed = 0.05;
	hitpoints = 100;
	maxhitpoints = hitpoints;
	speed = 3.f;
	groupID = 1;
	//fixture
	b2CircleShape Shape;
	Shape.m_radius = 24 / SCALE;
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Shape;
	FixtureDef.density = 1;
	body->CreateFixture( &FixtureDef );

	size = 100;

	textureFeetWalkingAnimation.loadFromFile(".\\graphics\\animations\\player\\playerFeetWalkingAnimation.png");
	textureFeetIdleAnimation.loadFromFile(".\\graphics\\animations\\player\\playerFeetIdleAnimation.png");
	textureHandgunWalkingAnimation.loadFromFile(".\\graphics\\animations\\player\\playerHandgunWalkingAnimation.png");
	textureHandgunIdleAnimation.loadFromFile(".\\graphics\\animations\\player\\playerHandgunWalkingAnimation.png");
	textureHandgunAttackingAnimation.loadFromFile(".\\graphics\\animations\\player\\playerHandgunAttackingAnimation.png");
	textureHandgunReloadingAnimation.loadFromFile(".\\graphics\\animations\\player\\playerHandgunReloadingAnimation.png");


	walkingAnimationFeet.setSpriteSheet(textureFeetWalkingAnimation);
	idleAnimationFeet.setSpriteSheet(textureFeetIdleAnimation);
	walkingAnimationHandgun.setSpriteSheet(textureHandgunWalkingAnimation);
	idleAnimationHandgun.setSpriteSheet(textureHandgunIdleAnimation);
	attackingAnimationHandgun.setSpriteSheet(textureHandgunAttackingAnimation);
	reloadingAnimationHandgun.setSpriteSheet(textureHandgunReloadingAnimation);
	//attackingAnimation.setSpriteSheet(textureAttackingAnimation);
	//idleAnimation.setSpriteSheet(textureIdleAnimation);


	for (int i = 0; i <= 19; i++)
	{
		walkingAnimationFeet.addFrame(sf::IntRect(i * size, 0, size, size));
	}
	//
	idleAnimationFeet.addFrame(sf::IntRect(size, 0, size, size));
	//
	for (int i = 0; i <= 19; i++)
	{
		walkingAnimationHandgun.addFrame(sf::IntRect(i * size, 0, size, size));
	}
	//
	for (int i = 0; i <= 19; i++)
	{
		idleAnimationHandgun.addFrame(sf::IntRect(i * size, 0, size, size));
	}
	//
	for (int i = 0; i <= 3; i++)
	{
		attackingAnimationHandgun.addFrame(sf::IntRect(i * size, 0, size, size));
	}
	//
	for (int i = 0; i <= 15; i++)
	{
		reloadingAnimationHandgun.addFrame(sf::IntRect(i * size, 0, size, size));
	}
	//
	for (int i = 0; i <= 8; i++)
	{
		attackingAnimation.addFrame(sf::IntRect(i * size, 0, size, size));
	}
	//
	for (int i = 0; i <= 16; i++)
	{
		idleAnimation.addFrame(sf::IntRect(i * size, 0, size, size));
	}

	
	currentAnimationFeet = &idleAnimationFeet;
	currentAnimation = &idleAnimationHandgun;
	animatedSprite = AnimatedSprite(sf::milliseconds(animSpeed * 2000.f), true, false);
	animatedSpriteFeet = AnimatedSprite(sf::milliseconds(animSpeed * 1000.f), true, false);
	animatedSprite.setOrigin(size / 2.f, size / 2.f);
	animatedSpriteFeet.setOrigin(size / 2.f, size / 2.f);
	animatedSprite.play(*currentAnimation);
}

Player::~Player()
{
}


void Player::StartContact( Entity * )
{
}

void Player::EndContact( Entity * )
{
}

void Player::Presolve( Entity * )
{
}

void Player::Render( sf::RenderWindow * window )
{
	frameTime = frameClock.restart();
	b2Vec2 direction;
	direction = body->GetLinearVelocity();

	if (sqrt(direction.x*direction.x + direction.y*direction.y) > speed/10.0f && !this->isShooting() && !this->isReloading())
	{
		currentAnimationFeet = &walkingAnimationFeet;
		currentAnimation = &walkingAnimationHandgun;
		animatedSprite.play(*currentAnimation);
	}
	else if (sqrt(direction.x*direction.x + direction.y*direction.y) > speed/10.0f)
	{
		currentAnimationFeet = &walkingAnimationFeet;
	}
	else
	{
		currentAnimationFeet = &idleAnimationFeet;
	}

	


	direction.Normalize();
	animatedSprite.update(frameTime);
	animatedSprite.setPosition(this->GetPosition());

	animatedSpriteFeet.play(*currentAnimationFeet);
	animatedSpriteFeet.update(frameTime);
	animatedSpriteFeet.setPosition(this->GetPosition());

	b2Vec2 normalize_direction = b2Vec2_zero;
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	sf::Vector2f cordPos = window->mapPixelToCoords(mousePos);
	//Wyznaczenie znormalizowanego wektora wyznaczaj¹cego kierunek od gracza do pozycycji myszki
	normalize_direction = positionPixToWorld(cordPos) - positionPixToWorld(this->GetWeaponPosition());
	normalize_direction.Normalize();

	animatedSprite.setRotation(atan2(normalize_direction.y, normalize_direction.x) * 180 / b2_pi);
	animatedSpriteFeet.setRotation(atan2(direction.y, direction.x) * 180 / b2_pi);

	window->draw(animatedSpriteFeet);
	window->draw(animatedSprite);
}

void Player::Update(sf::Time)
{
	this->body->SetLinearVelocity( static_cast<float32>(speed) * velocity );
}

void Player::SetAngle( float32 angle )
{
	this->body->SetTransform( this->body->GetPosition(), angle );
}

sf::Vector2f Player::GetWeaponPosition()
{
	if ( current_weapon == nullptr )
	{
		return GetPosition();
	}
	else
	{
		float32 playerAngle = body->GetAngle();
		b2Vec2 position = current_weapon->GetPosition();
		b2Vec2 rotatedPosition = b2Vec2( ( position.x*cosf( playerAngle ) - position.y*sinf( playerAngle ) ), ( position.x*sinf( playerAngle ) + position.y*cosf( playerAngle ) ) );
		b2Vec2 positionWeapon = body->GetPosition() + rotatedPosition;
		return positionWorldToPix( positionWeapon );
	}

}

void Player::AddWeapon(Weapon * weapon)
{
	if ( weapons.size() < 1 )
		current_weapon = weapon;
	weapons.push_back( weapon );
}

void Player::Reload()
{
	if ( current_weapon && this->canReload() )
	{
		current_weapon->Reload();
		currentAnimation = &reloadingAnimationHandgun;
		animatedSprite.play(*currentAnimation);
	}
}

void Player::Shoot( b2Vec2 direction, sf::Time difference_time )
{
	if (current_weapon && this->canShoot())
	{
		current_weapon->Shoot(body->GetPosition(), body->GetAngle(), direction, difference_time);
		currentAnimation = &attackingAnimationHandgun;
		animatedSprite.play(*currentAnimation);
	}
}


std::vector<long int> Player::GetHitpoints()
{
	std::vector<long int> hp (2);
	hp[0] = hitpoints;
	hp[1] = maxhitpoints;

	return hp;
}

std::vector<weapon_features> Player::GetWeaponList()
{
	std::vector<weapon_features> weapon_list;

	for ( auto & it : weapons )
	{
		weapon_list.push_back( it->GetWeaponFeatures() );
	}
	return weapon_list;
}

weapon_features Player::GetCurrentWeapon()
{
	if ( current_weapon )
		return current_weapon->GetWeaponFeatures();
	else
		return weapon_features();
}

bool Player::canShoot()
{
	if (current_weapon->MagazineAmmo() <= 0) return false;
	if (currentAnimation == &walkingAnimationHandgun || currentAnimation == &idleAnimationHandgun) return true;
	else if (!this->isShooting() && !this->isReloading()) return true;
	else return false;
}

bool Player::canReload()
{
	if ( ( currentAnimation == &walkingAnimationHandgun || currentAnimation == &idleAnimationHandgun ) && current_weapon->CanReload() ) return true;
	else if ( !this->isShooting() && !this->isReloading() && current_weapon->CanReload() ) return true;
	else return false;
}

bool Player::isShooting()
{
	if (currentAnimation == &attackingAnimationHandgun && animatedSprite.isPlaying()) return true;
	else return false;
}

bool Player::isReloading()
{
	if (currentAnimation == &reloadingAnimationHandgun && animatedSprite.isPlaying()) return true;
	else return false;
}