#include "Player.h"

Player::Player( b2World * world, b2Vec2 position ) : DynamicBody(world, position)
{
	//base stats
	animSpeed = 0.05;
	hitpoints = 100;
	armor = 10;
	maxhitpoints = hitpoints;
	speed = 3.f;
	groupID = 1;
	score = 0;
	//fixture
	b2CircleShape Shape;
	Shape.m_radius = 24 / SCALE;
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Shape;
	FixtureDef.density = 1;
	body->CreateFixture( &FixtureDef );

	size1 = 100;
	size2 = 133;

	direction1 = b2Vec2_zero;
	direction2 = b2Vec2_zero;

	setSpriteSheets();

	addFramesToAnimations();

	walkingAnimation = &walkingAnimationHandgun;
	idleAnimation = &idleAnimationHandgun;
	attackingAnimation = &attackingAnimationHandgun;
	reloadingAnimation = &reloadingAnimationHandgun;

	currentAnimationFeet = &idleAnimationFeet;
	currentAnimation = idleAnimation;
	animatedSprite = AnimatedSprite(sf::milliseconds(animSpeed * 2000.f), true, false);
	animatedSpriteFeet = AnimatedSprite(sf::milliseconds(animSpeed * 1000.f), true, false);
	animatedSprite.setOrigin(size1 / 2.f, size1 / 2.f);
	animatedSpriteFeet.setOrigin(size1 / 2.f, size1 / 2.f);
	animatedSprite.play(*currentAnimation);
	soundShoot.setBuffer( *AssetManager::GetSound( "pistol_shot" ) );
	soundClick.setBuffer( *AssetManager::GetSound( "pistol_click1" ) );
	soundReload.setBuffer( *AssetManager::GetSound( "pistol_reload" ) );
}

Player::Player( b2World * world, b2Vec2 position, player_state playerState ) : DynamicBody( world, position )
{
	//base stats
	animSpeed = 0.05;
	maxhitpoints = playerState.max_hitpoints;
	armor = playerState.armor;
	hitpoints = maxhitpoints;
	speed = playerState.speed;
	groupID = 1;
	score = 0;
	//fixture
	b2CircleShape Shape;
	Shape.m_radius = 24 / SCALE;
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Shape;
	FixtureDef.density = 1;
	body->CreateFixture( &FixtureDef );

	size1 = 100;
	size2 = 133;

	direction1 = b2Vec2_zero;
	direction2 = b2Vec2_zero;

	setSpriteSheets();

	addFramesToAnimations();

	walkingAnimation = &walkingAnimationHandgun;
	idleAnimation = &idleAnimationHandgun;
	attackingAnimation = &attackingAnimationHandgun;
	reloadingAnimation = &reloadingAnimationHandgun;

	currentAnimationFeet = &idleAnimationFeet;
	currentAnimation = idleAnimation;
	animatedSprite = AnimatedSprite( sf::milliseconds( animSpeed * 2000.f ), true, false );
	animatedSpriteFeet = AnimatedSprite( sf::milliseconds( animSpeed * 1000.f ), true, false );
	animatedSprite.setOrigin( size1 / 2.f, size1 / 2.f );
	animatedSpriteFeet.setOrigin( size1 / 2.f, size1 / 2.f );
	animatedSprite.play( *currentAnimation );

	soundShoot.setBuffer( *AssetManager::GetSound( "pistol_shoot" ) );
	soundClick.setBuffer( *AssetManager::GetSound( "pistol_click1" ) );
	soundReload.setBuffer( *AssetManager::GetSound( "pistol_reload" ) );
}

Player::~Player()
{
}

void Player::StartContact( Entity * )
{
}

void Player::EndContact( Entity * )
{
}

void Player::Presolve( Entity * )
{
}

void Player::Render( sf::RenderWindow * window )
{
	//Wyznaczenie znormalizowanego wektora wyznaczaj¹cego kierunek poruszania sie gracza
	direction1 = body->GetLinearVelocity();
	isMoving();
	direction1.Normalize();

	setAnimationsForCurrentWeapontype();

	if (isMoving()) animatedSpriteFeet.setRotation(atan2(direction1.y, direction1.x) * 180 / b2_pi);
	else if (isIdle())
	{
		currentAnimation = idleAnimation;
		animatedSprite.play(*currentAnimation);
	}
	
	frameTime = frameClock.restart();
	
	if (currentAnimation == walkingAnimation || currentAnimation == idleAnimation)
		animatedSprite.setFrameTime(sf::milliseconds(animSpeed * 2000.f));

	animatedSprite.update(frameTime);
	animatedSprite.setPosition(this->GetPosition());

	animatedSpriteFeet.play(*currentAnimationFeet);
	animatedSpriteFeet.update(frameTime);
	animatedSpriteFeet.setPosition(this->GetPosition());

	//Wyznaczenie znormalizowanego wektora wyznaczaj¹cego kierunek od gracza do pozycycji myszki
	mousePos = sf::Mouse::getPosition( *window );
	cordPos = window->mapPixelToCoords( mousePos );

	direction2 = positionPixToWorld(cordPos) - positionPixToWorld(this->GetWeaponPosition());
	direction2.Normalize();
	animatedSprite.setRotation(atan2(direction2.y, direction2.x) * 180 / b2_pi);



	if ((currentAnimation == &attackingAnimationRifle || currentAnimation == &attackingAnimationShotgun)) animatedSprite.setOrigin(size2 / 2.f, size2 / 2.f);
	else animatedSprite.setOrigin(size1 / 2.f, size1 / 2.f);

	window->draw(animatedSpriteFeet);
	window->draw(animatedSprite);
}

void Player::Update(sf::Time)
{
	this->body->SetLinearVelocity( static_cast<float32>(speed) * velocity );
}

void Player::SetAngle( float32 angle )
{
	this->body->SetTransform( this->body->GetPosition(), angle );
}

sf::Vector2f Player::GetWeaponPosition()
{
	if ( current_weapon == nullptr )
	{
		return GetPosition();
	}
	else
	{
		float32 playerAngle = body->GetAngle();
		b2Vec2 position = current_weapon->GetPosition();
		b2Vec2 rotatedPosition = b2Vec2( ( position.x*cosf( playerAngle ) - position.y*sinf( playerAngle ) ), ( position.x*sinf( playerAngle ) + position.y*cosf( playerAngle ) ) );
		b2Vec2 positionWeapon = body->GetPosition() + rotatedPosition;
		return positionWorldToPix( positionWeapon );
	}
}

void Player::AddWeapon(Weapon * weapon)
{
	if ( weapons.size() < 1 )
		current_weapon = weapon;
	weapons.push_back( weapon );
}

void Player::Reload()
{
	if ( current_weapon && this->canReload() )
	{
		current_weapon->Reload();
		currentAnimation = reloadingAnimation;
		reloadTime = current_weapon->ReloadTime();
		if ((current_weapon->GetWeaponFeatures()).type == WeaponType::PISTOL) currentWeaponReloadingFrames = handgunReloadingFrames;
		else if ((current_weapon->GetWeaponFeatures()).type == WeaponType::RIFLE) currentWeaponReloadingFrames = rifleReloadingFrames;
		else if ((current_weapon->GetWeaponFeatures()).type == WeaponType::SHOTGUN) currentWeaponReloadingFrames = shotgunReloadingFrames;
		animatedSprite.setFrameTime(reloadTime / sf::Int64(currentWeaponReloadingFrames));
		animatedSprite.play(*currentAnimation);
		soundReload.setPlayingOffset( sf::milliseconds( 1000 ) );
		soundReload.setVolume( 40 );
		soundReload.play();
	}
}

void Player::Shoot( b2Vec2 direction, sf::Time difference_time )
{
	if ( current_weapon && this->canShoot() )
	{
		current_weapon->Shoot(body->GetPosition(), body->GetAngle(), direction, difference_time);
		currentAnimation = attackingAnimation;
		recoilTime = current_weapon->RecoilTime();
		if ((current_weapon->GetWeaponFeatures()).type == WeaponType::PISTOL) currentWeaponAttackingFrames = handgunAttackingFrames;
		else if ((current_weapon->GetWeaponFeatures()).type == WeaponType::RIFLE) currentWeaponAttackingFrames = rifleAttackingFrames;
		else if ((current_weapon->GetWeaponFeatures()).type == WeaponType::SHOTGUN) currentWeaponAttackingFrames = shotgunAttackingFrames;
		animatedSprite.setFrameTime(recoilTime / sf::Int64(currentWeaponAttackingFrames));
		animatedSprite.play(*currentAnimation);
		soundShoot.setVolume( 40 );
		soundShoot.play();
	}
	if ( current_weapon->MagazineAmmo() == 0 )
	{
		soundClick.play();
	}
}

void Player::TakeDamage( float32 damage )
{
	int tmp = (int)damage - armor;
	if ( tmp <= 0 )
		tmp = 1;
	hitpoints -= tmp;
	if ( hitpoints <= 0 && active == 1 )
	{
		active = 0;
	}
}

player_state Player::GetPlayerState() const
{
	player_state myState = { maxhitpoints, armor, speed };
	return myState;
}

std::vector<long int> Player::GetHitpoints()
{
	std::vector<long int> hp (2);
	hp[0] = hitpoints;
	hp[1] = maxhitpoints;

	return hp;
}

std::vector<weapon_features> Player::GetWeaponList()
{
	std::vector<weapon_features> weapon_list;

	for ( auto & it : weapons )
	{
		weapon_list.push_back( it->GetWeaponFeatures() );
	}
	return weapon_list;
}

weapon_features Player::GetCurrentWeapon()
{
	if ( current_weapon )
		return current_weapon->GetWeaponFeatures();
	else
		return weapon_features();
}

void Player::ChangeWeaponRight()
{
	if ( weapons.size() > 1 )
	{
		for ( std::list<Weapon*>::iterator it = weapons.begin() ; it != weapons.end() ; ++it )
		{
			if ( (*it) == current_weapon )
			{
				if ( it == --weapons.end() )
					current_weapon = *weapons.begin();
				else
					current_weapon = *( ++it );
			}
		}
		setAnimationsForCurrentWeapontype();
		currentAnimation = idleAnimation;
	}
}

void Player::setSpriteSheets()
{
	walkingAnimationFeet.setSpriteSheet( *AssetManager::GetTexture("playerFeetWalkingAnimation") );
	idleAnimationFeet.setSpriteSheet( *AssetManager::GetTexture("playerFeetIdleAnimation") );

	walkingAnimationHandgun.setSpriteSheet( *AssetManager::GetTexture("playerHandgunWalkingAnimation") );
	idleAnimationHandgun.setSpriteSheet( *AssetManager::GetTexture("playerHandgunIdleAnimation") );
	attackingAnimationHandgun.setSpriteSheet( *AssetManager::GetTexture("playerHandgunAttackingAnimation") );
	reloadingAnimationHandgun.setSpriteSheet( *AssetManager::GetTexture("playerHandgunReloadingAnimation") );

	walkingAnimationRifle.setSpriteSheet( *AssetManager::GetTexture("playerRifleWalkingAnimation") );
	idleAnimationRifle.setSpriteSheet( *AssetManager::GetTexture("playerRifleIdleAnimation") );
	attackingAnimationRifle.setSpriteSheet( *AssetManager::GetTexture("playerRifleAttackingAnimation") );
	reloadingAnimationRifle.setSpriteSheet( *AssetManager::GetTexture("playerRifleReloadingAnimation") );

	walkingAnimationShotgun.setSpriteSheet( *AssetManager::GetTexture("playerShotgunWalkingAnimation") );
	idleAnimationShotgun.setSpriteSheet( *AssetManager::GetTexture("playerShotgunIdleAnimation") );
	attackingAnimationShotgun.setSpriteSheet( *AssetManager::GetTexture("playerShotgunAttackingAnimation") );
	reloadingAnimationShotgun.setSpriteSheet( *AssetManager::GetTexture("playerShotgunReloadingAnimation") );
}

void Player::addFramesToAnimations()
{
	for (int i = 0; i < 20; i++) walkingAnimationFeet.addFrame(sf::IntRect(i * size1, 0, size1, size1));
	for (int i = 0; i < 20; i++) idleAnimationFeet.addFrame(sf::IntRect(0, 0, size1, size1));

	for (int i = 0; i < 20; i++) walkingAnimationHandgun.addFrame(sf::IntRect(i * size1, 0, size1, size1));
	for (int i = 0; i < 20; i++) idleAnimationHandgun.addFrame(sf::IntRect(i * size1, 0, size1, size1));
	for (int i = 0; i < 4; i++) attackingAnimationHandgun.addFrame(sf::IntRect(i * size1, 0, size1, size1));
	handgunAttackingFrames = 4;
	for (int i = 0; i < 16; i++) reloadingAnimationHandgun.addFrame(sf::IntRect(i * size1, 0, size1, size1));
	handgunReloadingFrames = 16;

	for (int i = 0; i < 20; i++) walkingAnimationRifle.addFrame(sf::IntRect(i * size1, 0, size1, size1));
	for (int i = 0; i < 20; i++) idleAnimationRifle.addFrame(sf::IntRect(i * size1, 0, size1, size1));
	for (int i = 0; i < 4; i++) attackingAnimationRifle.addFrame(sf::IntRect(i * size2, 0, size2, size2));
	rifleAttackingFrames = 4;
	for (int i = 0; i < 21; i++) reloadingAnimationRifle.addFrame(sf::IntRect(i * size1, 0, size1, size1));
	rifleReloadingFrames = 21;

	for (int i = 0; i < 20; i++) walkingAnimationShotgun.addFrame(sf::IntRect(i * size1, 0, size1, size1));
	for (int i = 0; i < 20; i++) idleAnimationShotgun.addFrame(sf::IntRect(i * size1, 0, size1, size1));
	for (int i = 0; i < 4; i++) attackingAnimationShotgun.addFrame(sf::IntRect(i * size2, 0, size2, size2));
	shotgunAttackingFrames = 4;
	for (int i = 0; i < 21; i++) reloadingAnimationShotgun.addFrame(sf::IntRect(i * size1, 0, size1, size1));
	shotgunReloadingFrames = 21;
}

bool Player::isMoving()
{
	if (sqrt(direction1.x*direction1.x + direction1.y*direction1.y) > speed / 10.0f && !this->isShooting() && !this->isReloading())
	{
		currentAnimationFeet = &walkingAnimationFeet;
		currentAnimation = walkingAnimation;
		animatedSprite.play(*currentAnimation);
		return true;
	}
	else if (sqrt(direction1.x*direction1.x + direction1.y*direction1.y) > speed / 10.0f)
	{
		currentAnimationFeet = &walkingAnimationFeet;
		return true;
	}
	else
	{
		currentAnimationFeet = &idleAnimationFeet;
		return false;
	}
}

bool Player::canShoot()
{
	if (current_weapon->MagazineAmmo() <= 0) return false;
	if (currentAnimation == walkingAnimation || currentAnimation == idleAnimation) return true;
	else if (!this->isShooting() && !this->isReloading()) return true;
	else return false;
}

bool Player::canReload()
{
	if ( ( currentAnimation == walkingAnimation || currentAnimation == idleAnimation ) && current_weapon->CanReload() ) return true;
	else if ( !this->isShooting() && !this->isReloading() && current_weapon->CanReload() ) return true;
	else return false;
}

void Player::setAnimationsForCurrentWeapontype()
{
	if ((current_weapon->GetWeaponFeatures()).type == WeaponType::PISTOL)
	{
		walkingAnimation = &walkingAnimationHandgun;
		idleAnimation = &idleAnimationHandgun;
		attackingAnimation = &attackingAnimationHandgun;
		reloadingAnimation = &reloadingAnimationHandgun;
	}
	else if ((current_weapon->GetWeaponFeatures()).type == WeaponType::RIFLE)
	{
		walkingAnimation = &walkingAnimationRifle;
		idleAnimation = &idleAnimationRifle;
		attackingAnimation = &attackingAnimationRifle;
		reloadingAnimation = &reloadingAnimationRifle;
	}
	else if ((current_weapon->GetWeaponFeatures()).type == WeaponType::SHOTGUN)
	{
		walkingAnimation = &walkingAnimationShotgun;
		idleAnimation = &idleAnimationShotgun;
		attackingAnimation = &attackingAnimationShotgun;
		reloadingAnimation = &reloadingAnimationShotgun;
	}
}

void Player::updateObserver(Entity * ptr)
{
	if (ptr->GetID() == 2)
		score += ptr->getScore();
}

bool Player::isShooting()
{
	if (currentAnimation == attackingAnimation && animatedSprite.isPlaying()) return true;
	else return false;
}

bool Player::isReloading()
{
	if (currentAnimation == reloadingAnimation && animatedSprite.isPlaying()) return true;
	else return false;
}

bool Player::isIdle()
{
	if (currentAnimation == &idleAnimationHandgun || currentAnimation == &idleAnimationRifle || currentAnimation == &idleAnimationShotgun || !animatedSprite.isPlaying()) return true;
	else return false;
}