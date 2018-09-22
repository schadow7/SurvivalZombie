#include "Trap.h"

BasicEntanglements::BasicEntanglements(b2World* world, b2Vec2 position, sf::Texture* ntexture) :
	StaticBody(world, position),
	sizey(50),
	sizex(25)
{
	//base stats 
	groupID = 6;
	damage = 0;
	hitpoints = 100;
	maxhitpoints = 100;
	attack_cooldown = sf::milliseconds(500);
	attack_timer = sf::milliseconds(520);

	//fixture
	b2PolygonShape obstacleShape;
	obstacleShape.SetAsBox(sizex / SCALE / 2, sizey / SCALE / 2);
	b2FixtureDef obstacleFixtureDef;
	obstacleFixtureDef.shape = &obstacleShape;
	obstacleFixtureDef.density = 1;
	obstacleFixtureDef.restitution = (0.f);
	//obstacleFixtureDef.filter.maskBits = 0x0000;
	b2Fixture* fixture = body->CreateFixture(&obstacleFixtureDef);

	hitpointsBarRed.setFillColor(sf::Color(255, 0, 0));
	hitpointsBarBlack.setFillColor(sf::Color(0, 0, 0));

	texture = ntexture;
	sprite.setTexture(*texture);
	sprite.setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
	float scaleX = static_cast<float>(sizex) / texture->getSize().x;
	float scaleY = static_cast<float>(sizey) / texture->getSize().y;
	sprite.setScale(scaleX, scaleY);
	sprite.setColor(sf::Color::Red);

	textureDead = AssetManager::GetTexture("grad2");
	textureDead->setSmooth(1);

	sprite.setPosition(SCALE * position.x, SCALE * position.y);
	sprite.setRotation(180 / b2_pi * this->body->GetAngle());
}

BasicEntanglements::~BasicEntanglements()
{
}


void BasicEntanglements::TakeDamage(float32 damage)
{
	hitpoints -= damage;
	if (hitpoints <= 0)
	{
		active = 0;
		notify(this);
	}
}

void BasicEntanglements::Attack(Entity * entity)
{
	if (attack_cooldown < attack_timer)
	{
		entity->TakeDamage(damage);
		attack_timer = sf::milliseconds(0);
	}
}

void BasicEntanglements::SetDamage(float32 ndamage)
{
	if (damage)damage = ndamage;
}

void BasicEntanglements::SetAngle(float32 angle)
{
	body->SetTransform(body->GetPosition(), angle* DEGTORAD);
	sprite.setRotation(angle);
}

b2Vec2 BasicEntanglements::GetPxSize()
{
	return b2Vec2(sizex, sizey);
}

void BasicEntanglements::Repair(int nHP)
{
	if (nHP)
	{
		hitpoints += nHP;
		if (hitpoints > maxhitpoints) hitpoints = maxhitpoints;
	}
}

void BasicEntanglements::SetMaxHP(int nMax)
{
	if (nMax)
	{
		if (hitpoints < nMax)  hitpoints = nMax;
		maxhitpoints = nMax;
	}
}

void BasicEntanglements::SetDamage(int ndmg)
{
	damage = ndmg;
}

void BasicEntanglements::MakeActive()
{
	sprite.setTexture(*texture);
	sprite.setPosition(SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y);
	sprite.setRotation(180 / b2_pi * this->body->GetAngle());
	float scaleX = static_cast<float>(sizex) / textureDead->getSize().x;
	float scaleY = static_cast<float>(sizey) / textureDead->getSize().y;
	sprite.setScale(scaleX, scaleY);
	sprite.setColor(sf::Color::Red);
	active = 1;
	SetBodyActive();
}

void BasicEntanglements::StartContact(Entity* entity)
{
	if (entity->GroupID() != 1)
		attack_timer = sf::microseconds(0);
}
void BasicEntanglements::EndContact(Entity*)
{
	;
}
void BasicEntanglements::Presolve(Entity * entity)
{
	if (damage)
	{
		if (entity->GroupID() != 1)
			Attack(entity);
	}
}
void BasicEntanglements::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void BasicEntanglements::RenderInactive(sf::RenderWindow * window)
{
	sprite.setTexture(*textureDead);
	sprite.setPosition(SCALE * this->body->GetPosition().x, SCALE * this->body->GetPosition().y);
	sprite.setRotation(180 / b2_pi * this->body->GetAngle());
	float scaleX = static_cast<float>(sizex) / textureDead->getSize().x;
	float scaleY = static_cast<float>(sizey) / textureDead->getSize().y;
	sprite.setScale(scaleX, scaleY);
	sprite.setColor(sf::Color::Green);
	window->draw(sprite);
}

void BasicEntanglements::Update(sf::Time difference_time)
{
	attack_timer += difference_time;
}

Door::Door(b2World * world, b2Vec2 position, sf::Texture * ntexture) :
	BasicEntanglements(world, position, ntexture)
{
	sprite.setColor(sf::Color::Yellow);
	damage = 0;
	groupID = 9;
}

Door::~Door()
{
}
