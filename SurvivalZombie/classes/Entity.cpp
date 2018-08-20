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

Entity::~Entity()
{
	delete fixture;
	//delete body;
}


