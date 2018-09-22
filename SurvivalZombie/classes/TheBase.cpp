#include "TheBase.h"

TheBase::TheBase(b2World * world, b2Vec2 position, sf::Texture * ntexture) :
	StaticBody(world, position),
	sizey(50),
	sizex(50)
{
	//base stats 
	groupID = 10;
	damage = -1;
	hitpoints = 100;
	maxhitpoints = 100;
	attack_cooldown = sf::milliseconds(2000);
	attack_timer = sf::milliseconds(520);

	//fixture
	b2PolygonShape obstacleShape;
	obstacleShape.SetAsBox(sizex / SCALE / 2, sizey / SCALE / 2);
	b2FixtureDef obstacleFixtureDef;
	obstacleFixtureDef.shape = &obstacleShape;
	obstacleFixtureDef.density = 1;
	obstacleFixtureDef.restitution = (0.f);
	b2Fixture* fixture = body->CreateFixture(&obstacleFixtureDef);

	hitpointsBarRed.setFillColor(sf::Color(255, 0, 0));
	hitpointsBarBlack.setFillColor(sf::Color(0, 0, 0));

	texture = ntexture;
	sprite.setTexture(*texture);
	sprite.setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
	float scaleX = static_cast<float>(sizex) / texture->getSize().x;
	float scaleY = static_cast<float>(sizey) / texture->getSize().y;
	sprite.setScale(scaleX, scaleY);
	sprite.setColor(sf::Color::White);

	textureDead = AssetManager::GetTexture("grad2");
	textureDead->setSmooth(1);

	sprite.setPosition(SCALE * position.x, SCALE * position.y);
	sprite.setRotation(180 / b2_pi * this->body->GetAngle());
}

TheBase::~TheBase()
{
}

void TheBase::TakeDamage(float32 damage)
{
	hitpoints -= damage;
	if (hitpoints <= 0)
	{
		active = 0;
		notify(this);
	}
}

void TheBase::Attack(Entity * entity)
{
	if (attack_cooldown < attack_timer)
	{
		entity->TakeDamage(damage);
		attack_timer = sf::milliseconds(0);
	}
}

void TheBase::SetDamage(float32 ndamage)
{
	if (damage)damage = ndamage;
}

void TheBase::SetAngle(float32 angle)
{
	body->SetTransform(body->GetPosition(), angle* DEGTORAD);
	sprite.setRotation(angle);
}

b2Vec2 TheBase::GetPxSize()
{
	return b2Vec2(sizex, sizey);
}

void TheBase::Repair(int nHP)
{
	if (nHP)
	{
		hitpoints += nHP;
		if (hitpoints > maxhitpoints) hitpoints = maxhitpoints;
	}
}

void TheBase::SetMaxHP(int nMax)
{
	if (nMax)
	{
		if (hitpoints < nMax)  hitpoints = nMax;
		maxhitpoints = nMax;
	}
}

void TheBase::SetDamage(int ndmg)
{
	damage = -ndmg;
}

void TheBase::MakeActive()
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

void TheBase::StartContact(Entity* entity)
{
	if (entity->GroupID() != 1)
		attack_timer = sf::microseconds(0);
}
void TheBase::EndContact(Entity*)
{
	;
}
void TheBase::Presolve(Entity * entity)
{

		if (entity->GroupID() == 1)
			Attack(entity);
}
void TheBase::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void TheBase::RenderInactive(sf::RenderWindow * window)
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

void TheBase::Update(sf::Time difference_time)
{
	attack_timer += difference_time;
}