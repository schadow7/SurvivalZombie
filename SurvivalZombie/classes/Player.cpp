#include "Player.h"

Player::Player( b2World * world, sf::Texture * texture, b2Vec2 position ) : DynamicBody(world)
{
	//base stats 
	hitpoints = 100;
	speed = 5;
	angle = 0;
	body->SetTransform( position, body->GetAngle() );
	//fixture
	b2CircleShape Shape;
	Shape.m_radius = 24 / SCALE;
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Shape;
	FixtureDef.density = 1;
	body->CreateFixture( &FixtureDef );
	////SFML
	texture->loadFromFile( ".\\graphics\\survivor.png" );
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

void Player::Render( sf::RenderWindow * window )
{
	shape.setPosition( this->GetPosition() );
	window->draw( shape );
}

void Player::Update()
{
	this->body->SetLinearVelocity( speed * velocity );
}

void Player::SetAngle( float32 angle )
{
	this->angle = angle;
}

