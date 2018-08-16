#include "Entity.h"
#include <Box2D/Box2D.h>


class ContactListener : public b2ContactListener
{
public:
	ContactListener( b2World * world )
	{
		world->SetContactListener( this );
	}

	~ContactListener() { };

	void BeginContact( b2Contact* contact ) {

		void * entityA = contact->GetFixtureA()->GetBody()->GetUserData();
		void * entityB = contact->GetFixtureB()->GetBody()->GetUserData();
		if ( entityA && entityB )
		{
			static_cast< Entity* >( entityA )->StartContact( static_cast< Entity* > ( entityB ) );
			static_cast< Entity* >( entityB )->StartContact( static_cast< Entity* > ( entityA ) );
		}
	}

	void EndContact( b2Contact* contact ) {

		void * entityA = contact->GetFixtureA()->GetBody()->GetUserData();
		void * entityB = contact->GetFixtureB()->GetBody()->GetUserData();
		if ( entityA && entityB )
		{
			static_cast< Entity* >( entityA )->EndContact( static_cast< Entity* > ( entityB ) );
			static_cast< Entity* >( entityB )->EndContact( static_cast< Entity* > ( entityA ) );
		}

	}
};