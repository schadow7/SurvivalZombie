#include "Obstacle.h"

Obstacle::Obstacle(b2World *world, b2Vec2 position) :
	StaticBody(world, position),
	sizey(50)
{
	//base stats 
	groupID = 5;
	hitpoints = 100;
	maxhitpoints = 100;
	damage = 5;

	//fixture
	b2CircleShape obstacleShape;
	obstacleShape.m_radius = sizey / 2 / SCALE;
	b2FixtureDef obstacleFixtureDef;
	obstacleFixtureDef.shape = &obstacleShape;
	obstacleFixtureDef.density = 1;
	obstacleFixtureDef.restitution = (0.f);
	b2Fixture* fixture = body->CreateFixture(&obstacleFixtureDef);

	//hitpointsBarRed.setFillColor(sf::Color(255, 0, 0));
	//hitpointsBarBlack.setFillColor(sf::Color(0, 0, 0));

	int sizex1 = 46;
	int sizex2 = 54;
	int sizey = 50;

}

Obstacle::~Obstacle()
{
}


void Obstacle::TakeDamage(float32 damage)
{
	hitpoints -= damage;
	if (hitpoints <= 0)
	{
		active = 0;
		notify(this);
	}
}

void Obstacle::StartContact(Entity* entity)
{
	if (entity->GroupID() == 1)
		attack_timer = sf::microseconds(0);
}
void Obstacle::EndContact(Entity*)
{
	;
}
void Obstacle::Presolve(Entity * entity)
{
	if (entity->GroupID() == 1)
		Attack(entity);
}
void Obstacle::Render(sf::RenderWindow* window)
{
	//std::cout << "BoX: " << this->body->GetPosition().x << " " << this->body->GetPosition().x << " SFML: " << shape.getPosition().x << " " << shape.getPosition().y << std::endl;
	//sprite.setPosition( SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y );
	//shape.setPosition(SCALE * 2, SCALE * 2);
	//sprite.setRotation( 180 / b2_pi * this->body->GetAngle() );



	hitpointsBarRed.setSize(sf::Vector2f(int(70 * hitpoints / maxhitpoints), 5));
	hitpointsBarBlack.setSize(sf::Vector2f(int(72 * hitpoints / maxhitpoints), 7));
	hitpointsBarRed.setPosition(SCALE * this->body->GetPosition().x - int(35 * hitpoints / maxhitpoints), SCALE * this->body->GetPosition().y - 25);
	hitpointsBarBlack.setPosition(SCALE * this->body->GetPosition().x - int(36 * hitpoints / maxhitpoints), SCALE * this->body->GetPosition().y - 26);


	window->draw(animatedSprite);
	window->draw(hitpointsBarBlack);
	window->draw(hitpointsBarRed);
}

void Obstacle::RenderInactive(sf::RenderWindow * window)
{
	sprite.setTexture(textureDead);
	sprite.setPosition(SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y);
	sprite.setRotation(180 / b2_pi * this->body->GetAngle());
	float scaleX = static_cast<float>(sizey) / textureDead.getSize().x;
	float scaleY = static_cast<float>(sizey) / textureDead.getSize().y;
	sprite.setScale(scaleX, scaleY);
	window->draw(sprite);
}

void Obstacle::Update(sf::Time difference_time)
{
	
}