#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "DynamicBody.h"

struct projectile_features {
	float32 speed;
	float32 damage;
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
	virtual void			Reload() { magazineAmmo = ( carriedAmmo > maxMagazineAmmo ) ? maxMagazineAmmo : carriedAmmo; carriedAmmo -= magazineAmmo; reload_timer = reload_cooldown; }
	virtual void			Shoot( b2Vec2 playerPosition, float32 playerAngle, b2Vec2 direction, sf::Time difference_time ) = 0;

protected:
	EntityManager *			entityManager;
	sf::Texture *			texturePlayer;
	sf::Texture *			textureProjectile;
	b2Vec2					position;						//Pozycja broni(Ÿród³o wystrza³u) wzglêdem œrodka cia³a 
	int						maxMagazineAmmo;
	int						magazineAmmo;
	int						carriedAmmo;
	const float				SCALE = 100.f;
	sf::Time				timer, cooldown, reload_cooldown, reload_timer;
	float32					damage;

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
	float32 speed;
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
		cooldown = sf::milliseconds( 600 );		reload_cooldown = sf::milliseconds( 2000 );
		timer = sf::milliseconds( 0 );
		damage = 20;
		maxMagazineAmmo = 8;
		carriedAmmo = 100;
		magazineAmmo = maxMagazineAmmo;
	}

	void			Reload() { magazineAmmo = maxMagazineAmmo; reload_timer = reload_cooldown; }

	void	Shoot( b2Vec2 playerPositon, float32 playerAngle, b2Vec2 direction, sf::Time difference_time )
	{
		timer += difference_time;
		reload_timer -= difference_time;
		if ( cooldown < timer && reload_timer < sf::milliseconds(0) && magazineAmmo > 0 )
		{
			timer = sf::milliseconds(0);
			--magazineAmmo;
			CreateBullet( playerPositon, playerAngle, direction );
		}
	}

	void CreateBullet( b2Vec2 playerPositon, float32 playerAngle, b2Vec2 direction )
	{
		//Wyznaczenie pozycji w œwiecie, w której ma siê pojawiæ pocisk
		b2Vec2 rotatedPosition = rotateVector( position, playerAngle );
		b2Vec2 positionProjectile = playerPositon + rotatedPosition;
		//Wype³nienie struktury z w³aœciwoœciami obiektu (tj. szybkoœæ, zadawane obra¿enia, czas po którym pocisk znika
		projectile_features projFeat = { 5, damage, sf::seconds( 2 ), direction };
		//Stworzenie definicji cia³a
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;
		myBodyDef.position = positionProjectile;
		myBodyDef.angle = playerAngle;
		myBodyDef.bullet = 1;
		//Stworzenie definicj fikstury
		b2PolygonShape polyShape;
		polyShape.SetAsBox( 10 / SCALE, 4 / SCALE );
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polyShape;
		FixtureDef.density = 1;
		//Stworzenie kszta³tu do renderowania (SFML)
		sf::RectangleShape * shape = new sf::RectangleShape;
		shape->setSize( sf::Vector2f( 10, 4 ) );
		shape->setTexture( textureProjectile );
		shape->setOrigin( 5.f, 2.f );
		shape->setFillColor( sf::Color( 0, 0, 0 ) );
		//Stworzenie pocisku i dodanie go do menad¿era obiektów
		Projectile * bullet = new Projectile( entityManager->World(), shape, myBodyDef, FixtureDef, projFeat );
		entityManager->AddEntity( bullet );

	}


};