#include "Player.h"

Player::Player( b2World * world, sf::Texture * texture, b2Vec2 position ) : DynamicBody(world, position)
{
	//base stats
	animSpeed = 0.05;
	hitpoints = 100;
	maxhitpoints = hitpoints;
	speed = 5;
	groupID = 1;
	//fixture
	b2CircleShape Shape;
	Shape.m_radius = 24 / SCALE;
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Shape;
	FixtureDef.density = 1;
	body->CreateFixture( &FixtureDef );
	////SFML
	/*shape.setOrigin( sf::Vector2f( 24.f, 24.f ) );
	shape.setTexture( texture );
	shape.setRadius( 25 );
	shape.setOutlineThickness( 1 );
	shape.setOutlineColor( sf::Color::Black );*/
	int sizex1 = 75;
	int sizex2 = 54;
	int sizey = 50;

	textureWalkingAnimation.loadFromFile(".\\graphics\\playerWalkingAnimation.png");
	textureAttackingAnimation.loadFromFile(".\\graphics\\zombie50AttackingAnimation.png");
	textureIdleAnimation.loadFromFile(".\\graphics\\zombie50IdleAnimation.png");

	walkingAnimation.setSpriteSheet(textureWalkingAnimation);
	attackingAnimation.setSpriteSheet(textureAttackingAnimation);
	idleAnimation.setSpriteSheet(textureIdleAnimation);
	for (int i = 0; i <= 3; i++)
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
	animatedSprite = AnimatedSprite(sf::seconds(animSpeed*3), true, false);
	animatedSprite.setOrigin(sizex1 / 2, sizey / 2);

}

Player::~Player()
{
}

void Player::StopAnimation()
{
	animatedSprite.stop();
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
	animatedSprite.play(*currentAnimation);
	animatedSprite.update(frameTime);
	animatedSprite.setPosition(this->GetPosition());
	animatedSprite.setRotation(this->GetAngle());

	window->draw(animatedSprite);
}

void Player::Update(sf::Time)
{
	this->body->SetLinearVelocity( speed * velocity );
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
	if ( current_weapon )
	{
		current_weapon->Reload();
	}
}

void Player::Shoot( b2Vec2 direction, sf::Time difference_time )
{
	if (current_weapon)
	{
		current_weapon->Shoot(body->GetPosition(), body->GetAngle(), direction, difference_time);
		currentAnimation = &attackingAnimation;
	}
}


std::vector<long int> Player::GetHitpoints()
{
	std::vector<long int> hp (2);
	hp[0] = hitpoints;
	hp[1] = maxhitpoints;

	return hp;
}