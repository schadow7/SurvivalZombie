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
enum class WeaponType { PISTOL, SHOTGUN, RIFLE };

struct weapon_features {
	WeaponType type;
	int maxMagazineAmmo, magazineAmmo, carriedAmmo;
	sf::Time cooldown, reload_cooldown;
	float32 damage, bullet_speed;

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
	weapon_features			GetWeaponFeatures() { weapon_features feat = { type, maxMagazineAmmo, magazineAmmo, carriedAmmo, cooldown, reload_cooldown, damage, bullet_speed }; return feat; }

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
	float32					bullet_speed;
	WeaponType				type;

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
	void StartContact( Entity * entity ) 
	{ 
		if ( entity->GroupID() == 2 )
		{
			entity->TakeDamage( damage );
			this->active = -1;
		}
		else if ( entity->GroupID() == 1 )
		{

		}
		else
		{
			this->active = -1;
		}
	}
	void EndContact( Entity * ) { ; }
	void Presolve( Entity* entity ) 
	{
	}
	void Update(sf::Time difference_time) 
	{  
		if ( ( lifetime -= difference_time ) < sf::milliseconds( 0 ) )
		{
			this->active = -1;
			//this->body->SetActive( false );
		}
		else
			this->body->SetLinearVelocity( speed * velocity ); 
	}
	void Render( sf::RenderWindow * window ) 
	{
		shape->setPosition( this->GetPosition() );
		shape->setRotation( this->GetAngle() );
		window->draw( *shape );
	}

private: 
	float32 speed;
	float32 damage;
	sf::Time lifetime;
	sf::Shape * shape;
};

class Pistol : public Weapon
{
public:
	Pistol( EntityManager * EntMng, sf::Texture * TxtrPlayer, sf::Texture * TxtrProjectile ) : Weapon( EntMng, TxtrPlayer, TxtrProjectile ) 
	{ 
		position = positionPixToWorld( sf::Vector2f( 30, 14 ) );
		cooldown = sf::milliseconds( 300 );		reload_cooldown = sf::milliseconds( 1000 );
		timer = sf::milliseconds( 0 );
		damage = 20;	bullet_speed = 10;
		maxMagazineAmmo = 8;
		carriedAmmo = 100;
		reload_timer = sf::microseconds(0);
		magazineAmmo = maxMagazineAmmo;
		type = WeaponType::PISTOL;
	}

	Pistol( EntityManager * EntMng, sf::Texture * TxtrPlayer, sf::Texture * TxtrProjectile, weapon_features wpnFeat ) : Weapon( EntMng, TxtrPlayer, TxtrProjectile )
	{
		position = positionPixToWorld( sf::Vector2f( 30, 14 ) );
		cooldown = wpnFeat.cooldown;		reload_cooldown = wpnFeat.reload_cooldown;
		timer = sf::milliseconds( 0 );
		damage = wpnFeat.damage;	bullet_speed = wpnFeat.bullet_speed;
		maxMagazineAmmo = wpnFeat.maxMagazineAmmo;
		carriedAmmo = wpnFeat.carriedAmmo;
		reload_timer = sf::microseconds( 0 );
		magazineAmmo = wpnFeat.magazineAmmo;
		type = wpnFeat.type;
	}
	void	Reload() { magazineAmmo = maxMagazineAmmo; reload_timer = reload_cooldown; }

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
		projectile_features projFeat = { bullet_speed, damage, sf::seconds( 2 ), direction };
		//Stworzenie definicji cia³a
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;
		myBodyDef.position = positionProjectile;
		myBodyDef.angle = playerAngle;
		myBodyDef.bullet = 1;
		//Stworzenie definicj fikstury
		b2PolygonShape polyShape;
		polyShape.SetAsBox( 7 / SCALE, 3 / SCALE );
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polyShape;
		FixtureDef.density = 1;
		//Stworzenie kszta³tu do renderowania (SFML)
		sf::RectangleShape * shape = new sf::RectangleShape;
		shape->setSize( sf::Vector2f( 7, 3 ) );
		shape->setTexture( textureProjectile );
		shape->setOrigin( 3.5f, 1.5f );
		shape->setFillColor( sf::Color( 0, 0, 0 ) );
		//Stworzenie pocisku i dodanie go do menad¿era obiektów
		Projectile * bullet = new Projectile( entityManager->World(), shape, myBodyDef, FixtureDef, projFeat );
		entityManager->AddEntity( bullet );

	}


};