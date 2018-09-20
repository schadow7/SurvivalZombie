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
	int sizex = 100;
	int sizey = 100;

	textureFeetWalkingAnimation.loadFromFile(".\\graphics\\animations\\player\\feet\\walking\\playerFeetWalkingAnimation.png");
	textureFeetIdleAnimation.loadFromFile(".\\graphics\\animations\\player\\feet\\idle\\playerFeetIdleAnimation.png");
	textureHandgunWalkingAnimation.loadFromFile(".\\graphics\\animations\\player\\handgun\\walking\\playerHandgunWalkingAnimation.png");
	textureHandgunIdleAnimation.loadFromFile(".\\graphics\\animations\\player\\handgun\\walking\\playerHandgunWalkingAnimation.png");
	textureHandgunAttackingAnimation.loadFromFile(".\\graphics\\animations\\player\\handgun\\attacking\\playerHandgunAttackingAnimation.png");
	//textureRifleWalkingAnimation.loadFromFile(".\\graphics\\animations\\playerHandgunWalkingAnimation00.png");
	//textureShotgunWalkingAnimation.loadFromFile(".\\graphics\\animations\\playerHandgunWalkingAnimation00.png");
	//textureAttackingAnimation.loadFromFile(".\\graphics\\animations\\zombie50AttackingAnimation.png");
	//textureIdleAnimation.loadFromFile(".\\graphics\\animations\\zombie50IdleAnimation.png");


	walkingAnimationFeet.setSpriteSheet(textureFeetWalkingAnimation);
	idleAnimationFeet.setSpriteSheet(textureFeetIdleAnimation);
	walkingAnimationHandgun.setSpriteSheet(textureHandgunWalkingAnimation);
	idleAnimationHandgun.setSpriteSheet(textureHandgunIdleAnimation);
	attackingAnimationHandgun.setSpriteSheet(textureHandgunAttackingAnimation);
	//attackingAnimation.setSpriteSheet(textureAttackingAnimation);
	//idleAnimation.setSpriteSheet(textureIdleAnimation);


	for (int i = 0; i <= 19; i++)
	{
		walkingAnimationFeet.addFrame(sf::IntRect(i * sizex, 0, sizex, sizey));
	}
	//
	idleAnimationFeet.addFrame(sf::IntRect(sizex, 0, sizex, sizey));
	//
	for (int i = 0; i <= 19; i++)
	{
		walkingAnimationHandgun.addFrame(sf::IntRect(i * sizex, 0, sizex, sizey));
	}
	//
	for (int i = 0; i <= 19; i++)
	{
		idleAnimationHandgun.addFrame(sf::IntRect(i * sizex, 0, sizex, sizey));
	}
	//
	for (int i = 0; i <= 3; i++)
	{
		attackingAnimationHandgun.addFrame(sf::IntRect(i * sizex, 0, sizex, sizey));
	}
	//
	for (int i = 0; i <= 8; i++)
	{
		attackingAnimation.addFrame(sf::IntRect(i * sizex, 0, sizex, sizey));
	}
	//
	for (int i = 0; i <= 16; i++)
	{
		idleAnimation.addFrame(sf::IntRect(i * sizex, 0, sizex, sizey));
	}

	
	currentAnimationFeet = &idleAnimationFeet;
	currentAnimation = &idleAnimationHandgun;
	animatedSprite = AnimatedSprite(sf::seconds(animSpeed * 2), true, false);
	animatedSpriteFeet = AnimatedSprite(sf::seconds(animSpeed * 2), true, false);
	animatedSprite.setOrigin(sizex / 2, sizey / 2);
	animatedSpriteFeet.setOrigin(sizex / 2, sizey / 2);

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

	if (shootingFrame < 4)
	{
		currentAnimation = &attackingAnimationHandgun;
		if (sqrt(direction.x*direction.x + direction.y*direction.y) > 5)
		{
			currentAnimationFeet = &walkingAnimationFeet;
		}
		shootingFrame++;
	}
	else if (sqrt(direction.x*direction.x + direction.y*direction.y) < 5)
	{
		currentAnimationFeet = &idleAnimationFeet;
		currentAnimation = &idleAnimationHandgun;
	}
	else
	{
		currentAnimationFeet = &walkingAnimationFeet;
		currentAnimation = &walkingAnimationHandgun;
	}
	direction.Normalize();
	animatedSprite.play(*currentAnimation);
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
		shootingFrame = 0;
	}
}


std::vector<long int> Player::GetHitpoints()
{
	std::vector<long int> hp (2);
	hp[0] = hitpoints;
	hp[1] = maxhitpoints;

	return hp;
}