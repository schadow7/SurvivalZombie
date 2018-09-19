#include "Player.h"

Player::Player( b2World * world, sf::Texture * texture, b2Vec2 position ) : DynamicBody(world, position)
{
	//base stats 
	hitpoints = 100;
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
	shape.setOrigin( sf::Vector2f( 24.f, 24.f ) );
	shape.setTexture( texture );
	shape.setRadius( 25 );
	shape.setOutlineThickness( 1 );
	shape.setOutlineColor( sf::Color::Black );
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
	shape.setPosition( this->GetPosition() );
	shape.setRotation( this->GetAngle() );
	window->draw( shape );
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

void Player::Shoot( b2Vec2 direction )
{
	if ( current_weapon )
		current_weapon->Shoot( body->GetPosition(), body->GetAngle(), direction );
}


