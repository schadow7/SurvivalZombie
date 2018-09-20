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

void Entity::TakeDamage( float32 damage )
{
	hitpoints -= damage;
	if (hitpoints < 0 && active == 1)
	{
		active = 0;
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
	this->body->SetUserData( nullptr );
	this->body->GetWorld()->DestroyBody( body );
	for ( auto & it : effects )
	{
		delete it;
	}
}


