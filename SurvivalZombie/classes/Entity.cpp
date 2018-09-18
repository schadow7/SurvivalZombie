#include "Entity.h"



Entity::Entity()
{
	this->groupID = 0;
	this->active = 1;
}


int Entity::Active() const
{
	return this->active;
}

int Entity::GroupID() const
{
	return this->groupID;
}

void Entity::TakeDamage( int damage )
{
	hitpoints -= damage;
	if (hitpoints < 0 && active == 1)
	{
		active = 0;
		notify(this);
	}
}

b2Vec2 Entity::GetPosition() const
{
	return body->GetPosition();
}

int Entity::GetID()
{
	return groupID;
}

Entity::~Entity()
{
	delete fixture;
	//delete body;
}


