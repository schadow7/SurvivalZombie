#include "BasicEntanglements.h"

BasicEntanglements::BasicEntanglements(b2World* world, b2Vec2 position, sf::Vector2i nsize, sf::Texture* ntexture) :
	StaticBody(world, position)
{
	//base stats 
	groupID = 6;
	damage = 0;
	hitpoints = 100;
	maxhitpoints = 100;
	attack_cooldown = sf::milliseconds(500);
	attack_timer = sf::milliseconds(520);
	size = nsize;

	//fixture
	b2PolygonShape obstacleShape;
	obstacleShape.SetAsBox(size.x / SCALE / 2, size.y / SCALE / 2);
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
	float scaleX = static_cast<float>(size.x) / texture->getSize().x;
	float scaleY = static_cast<float>(size.y) / texture->getSize().y;
	sprite.setScale(scaleX, scaleY);
	//sprite.setColor(sf::Color::Red);

	textureDead = AssetManager::GetTexture("wall_broken");

	sprite.setPosition(SCALE * position.x, SCALE * position.y);
	sprite.setRotation(180 / b2_pi * this->body->GetAngle());
	//sounds
	soundsCount = 4;
	for (int i = 1; i <= soundsCount; i++)
	{
		sf::Sound temp;
		temp.setBuffer(*AssetManager::GetSound("fort"+std::to_string(i)));
		temp.setVolume(40);
		hitSounds.push_back(temp);
	}
}

BasicEntanglements::~BasicEntanglements()
{
}


void BasicEntanglements::TakeDamage(float32 damage)
{
	hitpoints -= damage;
	int i = soundDistribution(engine);
	if( i<= (soundsCount-1) && i >=0)
	hitSounds[i].play();
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
	return b2Vec2(size.x, size.y);
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
	float scaleX = static_cast<float>(size.x) / textureDead->getSize().x;
	float scaleY = static_cast<float>(size.y) / textureDead->getSize().y;
	sprite.setScale(scaleX, scaleY);
	//sprite.setColor(sf::Color::Red);
	active = 1;
	SetBodyActive();
}

int BasicEntanglements::getHitpoints()
{
	return hitpoints;
}

int BasicEntanglements::getMaxHitpoints()
{
	return maxhitpoints;
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
	float scaleX = static_cast<float>(size.x) / textureDead->getSize().x;
	float scaleY = static_cast<float>(size.y) / textureDead->getSize().y;
	sprite.setScale(scaleX, scaleY);
	//sprite.setColor(sf::Color::Green);
	window->draw(sprite);
}

void BasicEntanglements::Update(sf::Time difference_time)
{
	attack_timer += difference_time;
}

Door::Door(b2World * world, b2Vec2 position, sf::Vector2i size, sf::Texture * ntexture) :
	BasicEntanglements(world, position,size, ntexture)
{
	sprite.setColor(sf::Color::Yellow);
	damage = 0;
	groupID = 9;
	textureDead = AssetManager::GetTexture( "wall_broken" );
}

Door::~Door()
{
}

Bounds::Bounds( b2World * world, b2Vec2 position, sf::Vector2i size, sf::Texture * ntexture ) :
	BasicEntanglements( world, position, size, ntexture )
{
	damage = 0;
	groupID = 20;
}

Bounds::~Bounds()
{
}
