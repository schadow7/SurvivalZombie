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
enum class WeaponType { NOGUN, PISTOL, SHOTGUN, RIFLE };

struct weapon_features {
	WeaponType type = WeaponType::NOGUN;
	int maxMagazineAmmo, magazineAmmo, carriedAmmo;
	sf::Time cooldown, reload_cooldown;
	float32 damage, bullet_speed;

};

class Weapon
{
public:
	Weapon( EntityManager * EntMng, sf::Texture * TxtrProjectile ) : entityManager( EntMng ), textureProjectile( TxtrProjectile ) { ; }
	~Weapon() { }
	b2Vec2					GetPosition() const { return position; }
	int						MaxAmmo() const { return maxMagazineAmmo; }
	int						CarriedtAmmo() const { return carriedAmmo; }
	int						MagazineAmmo() const { return magazineAmmo; }
	virtual void			Reload()
	{
		int tmp = maxMagazineAmmo - magazineAmmo;
		if ( carriedAmmo > maxMagazineAmmo )
		{
			magazineAmmo = maxMagazineAmmo;	carriedAmmo -= tmp;
		}
		else
		{

			if ( tmp >= carriedAmmo )
			{
				magazineAmmo += carriedAmmo; carriedAmmo = 0;
			}
			else
			{
				magazineAmmo = maxMagazineAmmo; carriedAmmo -= tmp;
			}
		}
		reload_timer = reload_cooldown;
	}
	virtual void			AddMagazine() { carriedAmmo += maxMagazineAmmo; }
	virtual void			SetWeaponFeatures( weapon_features weaponFeat ) 
	{ 
		magazineAmmo = weaponFeat.magazineAmmo;		maxMagazineAmmo = weaponFeat.maxMagazineAmmo;
		carriedAmmo = weaponFeat.carriedAmmo;		damage = weaponFeat.damage;
		cooldown = weaponFeat.cooldown;				reload_cooldown = weaponFeat.reload_cooldown;
		type = weaponFeat.type;						bullet_speed = weaponFeat.bullet_speed;
	}
	virtual void			Shoot( b2Vec2 playerPosition, float32 playerAngle, b2Vec2 direction, sf::Time difference_time ) = 0;
	weapon_features			GetWeaponFeatures() { weapon_features feat = { type, maxMagazineAmmo, magazineAmmo, carriedAmmo, cooldown, reload_cooldown, damage, bullet_speed }; return feat; }
	bool					CanReload() { if ( magazineAmmo < maxMagazineAmmo && carriedAmmo > 0 ) { return true; } else { return false; } }
	sf::Time				ReloadTime() const { return reload_cooldown; }
	sf::Time				RecoilTime() const { return cooldown;  }

protected:
	EntityManager *			entityManager;
	sf::Texture *			textureProjectile;
	b2Vec2					position;						//Pozycja broni(�r�d�o wystrza�u) wzgl�dem �rodka cia�a 
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
			this->active = -1;
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
	Pistol( EntityManager * EntMng, sf::Texture * TxtrProjectile ) : Weapon( EntMng, TxtrProjectile ) 
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

	Pistol( EntityManager * EntMng,  sf::Texture * TxtrProjectile, weapon_features wpnFeat ) : Weapon( EntMng, TxtrProjectile )
	{
		position = positionPixToWorld( sf::Vector2f( 30, 14 ) );
		cooldown = wpnFeat.cooldown;		reload_cooldown = wpnFeat.reload_cooldown;
		timer = sf::milliseconds( 0 );
		damage = wpnFeat.damage;	bullet_speed = wpnFeat.bullet_speed;
		maxMagazineAmmo = wpnFeat.maxMagazineAmmo;
		carriedAmmo = wpnFeat.carriedAmmo;
		reload_timer = sf::microseconds( 0 );
		magazineAmmo = wpnFeat.magazineAmmo;
		type = WeaponType::PISTOL;
	}
	void	Reload() { magazineAmmo = maxMagazineAmmo; reload_timer = reload_cooldown; }

	void	Shoot( b2Vec2 playerPositon, float32 playerAngle, b2Vec2 direction, sf::Time difference_time )
	{
		timer += difference_time;
		reload_timer -= difference_time; //cooldown < timer &&  reload_timer < sf::milliseconds(0) &&
		if (  magazineAmmo > 0 )
		{
			timer = sf::milliseconds(0);
			--magazineAmmo;
			CreateBullet( playerPositon, playerAngle, direction );
		}
	}

	void CreateBullet( b2Vec2 playerPositon, float32 playerAngle, b2Vec2 direction )
	{
		//Wyznaczenie pozycji w �wiecie, w kt�rej ma si� pojawi� pocisk
		b2Vec2 rotatedPosition = rotateVector( position, playerAngle );
		b2Vec2 positionProjectile = playerPositon + rotatedPosition;
		//Wype�nienie struktury z w�a�ciwo�ciami obiektu (tj. szybko��, zadawane obra�enia, czas po kt�rym pocisk znika
		projectile_features projFeat = { bullet_speed, damage, sf::seconds( 2 ), direction };
		//Stworzenie definicji cia�a
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;
		myBodyDef.position = positionProjectile;
		myBodyDef.angle = atan2( direction.y, direction.x );
		myBodyDef.bullet = 1;
		//Stworzenie definicj fikstury
		b2PolygonShape polyShape;
		polyShape.SetAsBox( 7 / SCALE, 3 / SCALE );
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polyShape;
		FixtureDef.density = 1;
		//Stworzenie kszta�tu do renderowania (SFML)
		sf::RectangleShape * shape = new sf::RectangleShape;
		shape->setSize( sf::Vector2f( 8, 4 ) );
		textureProjectile->setSmooth(1);
		shape->setTexture( textureProjectile );
		shape->setOrigin( -5.0f, 4.0f );
		//Stworzenie pocisku i dodanie go do menad�era obiekt�w
		Projectile * bullet = new Projectile( entityManager->World(), shape, myBodyDef, FixtureDef, projFeat );
		entityManager->AddEntity( bullet );

	}


};

class Rifle : public Weapon
{
public:
	Rifle( EntityManager * EntMng, sf::Texture * TxtrProjectile ) : Weapon( EntMng, TxtrProjectile )
	{
		position = positionPixToWorld( sf::Vector2f( 40, 18 ) );
		cooldown = sf::milliseconds( 150 );		reload_cooldown = sf::milliseconds( 1500 );
		timer = sf::milliseconds( 0 );
		damage = 50;	bullet_speed = 15;
		maxMagazineAmmo = 30;
		carriedAmmo = 100;
		reload_timer = sf::microseconds( 0 );
		magazineAmmo = maxMagazineAmmo;
		type = WeaponType::RIFLE;
	}

	Rifle( EntityManager * EntMng, sf::Texture * TxtrProjectile, weapon_features wpnFeat ) : Weapon( EntMng, TxtrProjectile )
	{
		position = positionPixToWorld( sf::Vector2f( 40, 18 ) );
		cooldown = wpnFeat.cooldown;		reload_cooldown = wpnFeat.reload_cooldown;
		timer = sf::milliseconds( 0 );
		damage = wpnFeat.damage;	bullet_speed = wpnFeat.bullet_speed;
		maxMagazineAmmo = wpnFeat.maxMagazineAmmo;
		carriedAmmo = wpnFeat.carriedAmmo;
		reload_timer = sf::microseconds( 0 );
		magazineAmmo = wpnFeat.magazineAmmo;
		type = WeaponType::RIFLE;
	}

	void	Shoot( b2Vec2 playerPositon, float32 playerAngle, b2Vec2 direction, sf::Time difference_time )
	{
		timer += difference_time;
		reload_timer -= difference_time; //cooldown < timer &&  reload_timer < sf::milliseconds(0) &&
		if ( magazineAmmo > 0 )
		{
			timer = sf::milliseconds( 0 );
			--magazineAmmo;
			CreateBullet( playerPositon, playerAngle, direction );
		}
	}

	void CreateBullet( b2Vec2 playerPositon, float32 playerAngle, b2Vec2 direction )
	{
		//Wyznaczenie pozycji w �wiecie, w kt�rej ma si� pojawi� pocisk
		b2Vec2 rotatedPosition = rotateVector( position, playerAngle );
		b2Vec2 positionProjectile = playerPositon + rotatedPosition;
		//Wype�nienie struktury z w�a�ciwo�ciami obiektu (tj. szybko��, zadawane obra�enia, czas po kt�rym pocisk znika
		projectile_features projFeat = { bullet_speed, damage, sf::seconds( 2 ), direction };
		//Stworzenie definicji cia�a
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;
		myBodyDef.position = positionProjectile;
		myBodyDef.angle = atan2( direction.y, direction.x );
		myBodyDef.bullet = 1;
		//Stworzenie definicj fikstury
		b2PolygonShape polyShape;
		polyShape.SetAsBox( 7 / SCALE, 3 / SCALE );
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polyShape;
		FixtureDef.density = 1;
		//Stworzenie kszta�tu do renderowania (SFML)
		sf::RectangleShape * shape = new sf::RectangleShape;
		shape->setSize( sf::Vector2f( 8, 4 ) );
		textureProjectile->setSmooth( 1 );
		shape->setTexture( textureProjectile );
		shape->setOrigin( -5.0f, 4.0f );
		//Stworzenie pocisku i dodanie go do menad�era obiekt�w
		Projectile * bullet = new Projectile( entityManager->World(), shape, myBodyDef, FixtureDef, projFeat );
		entityManager->AddEntity( bullet );

	}


};

class Shotgun : public Weapon
{
public:
	Shotgun( EntityManager * EntMng, sf::Texture * TxtrProjectile ) : Weapon( EntMng, TxtrProjectile )
	{
		position = positionPixToWorld( sf::Vector2f( 40, 18 ) );
		cooldown = sf::milliseconds( 500 );		reload_cooldown = sf::milliseconds( 1500 );
		timer = sf::milliseconds( 0 );
		damage = 30;	bullet_speed = 8;
		maxMagazineAmmo = 6;
		carriedAmmo = 32;
		reload_timer = sf::microseconds( 0 );
		magazineAmmo = maxMagazineAmmo;
		type = WeaponType::SHOTGUN;
	}

	Shotgun( EntityManager * EntMng, sf::Texture * TxtrProjectile, weapon_features wpnFeat ) : Weapon( EntMng, TxtrProjectile )
	{
		position = positionPixToWorld( sf::Vector2f( 40, 18 ) );
		cooldown = wpnFeat.cooldown;		reload_cooldown = wpnFeat.reload_cooldown;
		timer = sf::milliseconds( 0 );
		damage = wpnFeat.damage;	bullet_speed = wpnFeat.bullet_speed;
		maxMagazineAmmo = wpnFeat.maxMagazineAmmo;
		carriedAmmo = wpnFeat.carriedAmmo;
		reload_timer = sf::microseconds( 0 );
		magazineAmmo = wpnFeat.magazineAmmo;
		type = WeaponType::SHOTGUN;
	}

	void	Shoot( b2Vec2 playerPositon, float32 playerAngle, b2Vec2 direction, sf::Time difference_time )
	{
		timer += difference_time;
		reload_timer -= difference_time; //cooldown < timer &&  reload_timer < sf::milliseconds(0) &&
		if ( magazineAmmo > 0 )
		{
			timer = sf::milliseconds( 0 );
			--magazineAmmo;
			CreateBullet( playerPositon, playerAngle, direction );
			CreateBullet( playerPositon, playerAngle, rotateVector( direction, (  b2_pi / 32 ) ) ); //rotateVectorAroundPoint( playerPositon, direction, ( 30 / 180 * b2_pi ) ) );
			CreateBullet( playerPositon, playerAngle, rotateVector( direction, (  -b2_pi / 32 ) ) );//rotateVectorAroundPoint( playerPositon, direction, ( -30 / 180 * b2_pi ) ) );
			CreateBullet( playerPositon, playerAngle, rotateVector( direction, ( -b2_pi / 32 ) ) );
			CreateBullet( playerPositon + b2Vec2( direction.x / 5.f, direction.y / 5.f ), playerAngle + ( b2_pi / 32 ), rotateVector( direction, ( b2_pi / 64 ) ) );
			CreateBullet( playerPositon + b2Vec2( direction.x / 5.f, direction.y / 5.f ), playerAngle + ( -b2_pi / 32 ), rotateVector( direction, ( -b2_pi / 64 ) ) );
		}
	}

	void CreateBullet( b2Vec2 playerPositon, float32 playerAngle, b2Vec2 direction )
	{
		//Wyznaczenie pozycji w �wiecie, w kt�rej ma si� pojawi� pocisk
		b2Vec2 rotatedPosition = rotateVector( position, playerAngle );
		b2Vec2 positionProjectile = playerPositon + rotatedPosition;
		//Wype�nienie struktury z w�a�ciwo�ciami obiektu (tj. szybko��, zadawane obra�enia, czas po kt�rym pocisk znika
		projectile_features projFeat = { bullet_speed, damage, sf::seconds( 2 ), direction };
		//Stworzenie definicji cia�a
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;
		myBodyDef.position = positionProjectile;
		myBodyDef.angle = atan2( direction.y, direction.x );
		myBodyDef.bullet = 1;
		//Stworzenie definicj fikstury
		b2PolygonShape polyShape;
		polyShape.SetAsBox( 7 / SCALE, 3 / SCALE );
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polyShape;
		FixtureDef.density = 1;
		//Stworzenie kszta�tu do renderowania (SFML)
		sf::RectangleShape * shape = new sf::RectangleShape;
		shape->setSize( sf::Vector2f( 8, 4 ) );
		textureProjectile->setSmooth( 1 );
		shape->setTexture( textureProjectile );
		shape->setOrigin( -5.0f, 4.0f );
		//Stworzenie pocisku i dodanie go do menad�era obiekt�w
		Projectile * bullet = new Projectile( entityManager->World(), shape, myBodyDef, FixtureDef, projFeat );
		entityManager->AddEntity( bullet );

	}


};