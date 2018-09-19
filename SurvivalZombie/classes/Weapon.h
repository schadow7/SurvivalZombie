#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "DynamicBody.h"

struct projectile_features {
	int speed;
	int damage;
	sf::Time lifetime;
	b2Vec2 direction;
};

class Weapon
{
public:
	Weapon( EntityManager * EntMng, sf::Texture * TxtrPlayer, sf::Texture * TxtrProjectile ) : entityManager( EntMng ), texturePlayer( TxtrPlayer ), textureProjectile( TxtrProjectile ) { ; }
	~Weapon() { }
	b2Vec2					GetPosition() const { return position; }
	int						MaxAmmo() const { return maxMagazineAmmo; }
	int						CarriedtAmmo() const { return carriedAmmo; }
	int						MagazineAmmo() const { return magazineAmmo; }
	void					Reload() { magazineAmmo = ( carriedAmmo > maxMagazineAmmo ) ? maxMagazineAmmo : carriedAmmo; carriedAmmo -= magazineAmmo; }
	virtual void			Shoot( b2Vec2 playerPosition, float32 playerAngle, b2Vec2 direction ) = 0;

protected:
	EntityManager *			entityManager;
	sf::Texture *			texturePlayer;
	sf::Texture *			textureProjectile;
	b2Vec2					position;						//Pozycja broni(Ÿród³o wystrza³u) wzglêdem œrodka cia³a 
	int						maxMagazineAmmo;
	int						magazineAmmo;
	int						carriedAmmo;
	const float				SCALE = 100.f;
	sf::Clock				clock;
	sf::Time				cooldown;

};

class Projectile : public DynamicBody
{
public:
	explicit Projectile( b2World* world, sf::Shape * shape, b2BodyDef bodyDef, b2FixtureDef fixtureDef, projectile_features projFeat ) : DynamicBody( world, bodyDef, fixtureDef )
	{
		groupID = 3;	speed = projFeat.speed;		damage = projFeat.damage;	
		lifetime = projFeat.lifetime;	velocity = projFeat.direction;
		this->shape = shape;
	}
	~Projectile() { delete shape; }
	void StartContact( Entity * ) { ; }
	void EndContact( Entity * ) { ; }
	void Presolve( Entity* ) { ; }
	void Update(sf::Time difference_time) {  this->body->SetLinearVelocity( speed * velocity ); }
	void Render( sf::RenderWindow * window ) 
	{
		shape->setPosition( this->GetPosition() );
		shape->setRotation( this->GetAngle() );
		window->draw( *shape );
	}

private: 
	int speed;
	int damage;
	sf::Time lifetime;
	sf::Shape * shape;
};

class Pistol : public Weapon
{
public:
	Pistol( EntityManager * EntMng, sf::Texture * TxtrPlayer, sf::Texture * TxtrProjectile ) : Weapon( EntMng, TxtrPlayer, TxtrProjectile ) 
	{ 
		position = positionPixToWorld( sf::Vector2f( 30, 14 ) );
		cooldown = sf::milliseconds( 600 );
	}
	void	Shoot( b2Vec2 playerPositon, float32 playerAngle, b2Vec2 direction )
	{

		if ( cooldown < clock.getElapsedTime() )
		{
			clock.restart();
			CreateBullet( playerPositon, playerAngle, direction );
		}
	}

	void CreateBullet( b2Vec2 playerPositon, float32 playerAngle, b2Vec2 direction )
	{
		//Wyznaczenie pozycji w œwiecie, w której ma siê pojawiæ pocisk
		b2Vec2 rotatedPosition = rotateVector( position, playerAngle );
		b2Vec2 positionProjectile = playerPositon + rotatedPosition;
		//Wype³nienie struktury z w³aœciwoœciami obiektu (tj. szybkoœæ, zadawane obra¿enia, czas po którym pocisk znika
		projectile_features projFeat = { 10, 20, sf::seconds( 2 ), direction };
		//Stworzenie definicji cia³a
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;
		myBodyDef.position = positionProjectile;
		myBodyDef.angle = playerAngle;
		myBodyDef.bullet = 1;
		//Stworzenie definicj fikstury
		b2PolygonShape polyShape;
		polyShape.SetAsBox( 6 / SCALE, 2 / SCALE );
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polyShape;
		FixtureDef.density = 1;
		//Stworzenie kszta³tu do renderowania (SFML)
		sf::RectangleShape * shape = new sf::RectangleShape;
		shape->setSize( sf::Vector2f( 6, 2 ) );
		shape->setTexture( textureProjectile );
		shape->setOrigin( 3.f, 1.f );
		shape->setFillColor( sf::Color( 0, 0, 0 ) );
		//Stworzenie pocisku i dodanie go do menad¿era obiektów
		Projectile * bullet = new Projectile( entityManager->World(), shape, myBodyDef, FixtureDef, projFeat );
		entityManager->AddEntity( bullet );

	}


};