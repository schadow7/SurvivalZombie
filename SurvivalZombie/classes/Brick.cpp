#include "Brick.h"

unsigned int Brick::counter = 0;
Brick::Brick( b2World * world, sf::Texture * texture, int x, int y )
{
	
	this->active = 2;
	this->groupID = 3;
	b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2( x / SCALE, y / SCALE );
	this->body = world->CreateBody( &bodyDef );
	this->body->SetUserData( dynamic_cast<Entity *> (this) );

	b2PolygonShape shapeb;
	b2FixtureDef fixtureDef;
	shapeb.SetAsBox( ( 50.f / 2 ) / SCALE, ( 26 / 2 ) / SCALE );
	fixtureDef.density = 2.f;
	fixtureDef.friction = 0.7f;
	fixtureDef.shape = &shapeb;
	this->body->CreateFixture( &fixtureDef );

	shape.setSize( sf::Vector2f( 47, 23 ) );
	shape.setTexture( texture );
	shape.setOrigin( 24.f, 12.f );
	shape.setFillColor( sf::Color( 0, 255, 0 ) );
	shape.setOutlineThickness( 1 );
	shape.setOutlineColor( sf::Color( 0, 0, 0 ) );
	contacts = 0;
	name = "brick_" + std::to_string( Brick::counter );
	Brick::counter++;
}

void Brick::Update()
{
	this->shape.setPosition( SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y );
	this->shape.setRotation( 180 / b2_pi * this->body->GetAngle() );
	if(contacts > 0 )
		this->shape.setFillColor( sf::Color::Red );
	else
		this->shape.setFillColor( sf::Color::Green );
}

void Brick::StartContact( Entity * entity )
{
	if(entity->GroupID() == 1 )
		contacts++;
}

void Brick::EndContact( Entity * entity )
{
	if ( entity->GroupID() == 1 )
		contacts--;
}

void Brick::Render(sf::RenderWindow * window)
{
	window->draw(shape);
}

Brick::~Brick()
{
}
