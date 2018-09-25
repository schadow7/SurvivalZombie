#pragma once
#include "DynamicBody.h"
#include "Weapon.h"
#include "AnimatedSprite.h"
#include <SFML/Graphics.hpp>


struct player_state 
{
	long int max_hitpoints;
	short int armor;
	double speed;
};

class Player :
	public DynamicBody
{
public:
	Player( b2World* world, b2Vec2 position );
	Player( b2World* world, b2Vec2 position, player_state playerState );
	~Player();	
	/// <summary>
	/// Starts the contact.
	/// </summary>
	/// <param name="">The .</param>
	void								StartContact(Entity*);	
	/// <summary>
	/// Ends the contact.
	/// </summary>
	/// <param name="">The .</param>
	void								EndContact(Entity*);
	/// <summary>
	/// Presolves the specified .
	/// </summary>
	/// <param name="">The .</param>
	void								Presolve(Entity*);
	/// <summary>
	/// Renders the specified window.
	/// </summary>
	/// <param name="window">The window.</param>
	void								Render(sf::RenderWindow* window);
	/// <summary>
	/// Updates the specified .
	/// </summary>
	/// <param name="">The .</param>
	void								Update(sf::Time);
	/// <summary>
	/// Sets the angle.
	/// </summary>
	/// <param name="angle">The angle.</param>
	void								SetAngle(float32 angle);
	/// <summary>
	/// Gets the weapon position.
	/// </summary>
	/// <returns></returns>
	sf::Vector2f						GetWeaponPosition();
	/// <summary>
	/// Adds the weapon.
	/// </summary>
	/// <param name="weapon">The weapon.</param>
	void								AddWeapon(Weapon * weapon);
	/// <summary>
	/// Reloads this instance.
	/// </summary>
	void								Reload();
	/// <summary>
	/// Shoots the specified direction.
	/// </summary>
	/// <param name="direction">The direction.</param>
	/// <param name="difference_time">The difference time.</param>
	void								Shoot(b2Vec2 direction, sf::Time difference_time);
	/// <summary>
	/// Takes the damage.
	/// </summary>
	/// <param name="damage">The damage.</param>
	void								TakeDamage(float32 damage);
	/// <summary>
	/// Gets the state of the player.
	/// </summary>
	/// <returns></returns>
	player_state						GetPlayerState() const;
	/// <summary>
	/// Gets the speed.
	/// </summary>
	/// <returns></returns>
	float32								GetSpeed();


	std::vector<long int>				GetHitpoints();	
	/// <summary>
	/// Gets the weapon list.
	/// </summary>
	/// <returns></returns>
	std::vector<weapon_features>		GetWeaponList();
	/// <summary>
	/// Gets the current weapon.
	/// </summary>
	/// <returns></returns>
	weapon_features						GetCurrentWeapon();
	/// <summary>
	/// Gets the weapon.
	/// </summary>
	/// <param name="type">The type.</param>
	/// <returns></returns>
	weapon_features						GetWeapon(WeaponType type);
	/// <summary>
	/// Changes the weapon right.
	/// </summary>
	void								ChangeWeaponRight();
	/// <summary>
	/// Determines whether the specified type is weapon.
	/// </summary>
	/// <param name="type">The type.</param>
	/// <returns>
	///   <c>true</c> if the specified type is weapon; otherwise, <c>false</c>.
	/// </returns>
	bool								isWeapon(WeaponType type);
	/// <summary>
	/// Changes the weapon.
	/// </summary>
	/// <param name="type">The type.</param>
	/// <returns></returns>
	bool								ChangeWeapon(WeaponType type);
	/// <summary>
	/// Adds the magazine.
	/// </summary>
	/// <param name="type">The type.</param>
	void								AddMagazine(WeaponType type);
	/// <summary>
	/// Sets the weapon features.
	/// </summary>
	/// <param name="weaponFeat">The weapon feat.</param>
	void								SetWeaponFeatures(weapon_features weaponFeat);
	/// <summary>
	/// Heals up.
	/// </summary>
	void								HealUp();
	/// <summary>
	/// Sets the state of the player.
	/// </summary>
	/// <param name="playerState">State of the player.</param>
	void								SetPlayerState(player_state playerState);
private:	
	/// <summary>
	/// Sets the sprite sheets.
	/// </summary>
	void								setSpriteSheets();
	/// <summary>
	/// Adds the frames to animations.
	/// </summary>
	void								addFramesToAnimations();
	/// <summary>
	/// Determines whether this instance is moving.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is moving; otherwise, <c>false</c>.
	/// </returns>
	bool								isMoving();
	/// <summary>
	/// Determines whether this instance is idle.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is idle; otherwise, <c>false</c>.
	/// </returns>
	bool								isIdle();
	/// <summary>
	/// Determines whether this instance is shooting.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is shooting; otherwise, <c>false</c>.
	/// </returns>
	bool								isShooting();
	/// <summary>
	/// Determines whether this instance is reloading.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is reloading; otherwise, <c>false</c>.
	/// </returns>
	bool								isReloading();
	/// <summary>
	/// Determines whether this instance can shoot.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance can shoot; otherwise, <c>false</c>.
	/// </returns>
	bool								canShoot();
	/// <summary>
	/// Determines whether this instance can reload.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance can reload; otherwise, <c>false</c>.
	/// </returns>
	bool								canReload();
	/// <summary>
	/// Sets the animations for current weapontype.
	/// </summary>
	void								setAnimationsForCurrentWeapontype();
	/// <summary>
	/// Updates the observer.
	/// </summary>
	/// <param name="">The .</param>
	void								updateObserver(Entity*) override;

	int									size1;
	int									size2;
	int									handgunAttackingFrames, handgunReloadingFrames, rifleAttackingFrames, rifleReloadingFrames, shotgunAttackingFrames, shotgunReloadingFrames;
	int									currentWeaponAttackingFrames, currentWeaponReloadingFrames;
	double								speed;
	short int							armor;
	double								animSpeed;
	sf::CircleShape						shape;
	std::list<Weapon *>					weapons;
	Weapon *							current_weapon = nullptr;
	sf::Vector2f						previousMousePos = sf::Vector2f( 0, 0 );
	b2Vec2								direction1;
	b2Vec2								direction2;
	sf::Vector2i						mousePos;
	sf::Vector2f						cordPos;
	sf::Clock							frameClock;
	sf::Time							frameTime, recoilTime, reloadTime;
	AnimatedSprite						animatedSprite;
	AnimatedSprite						animatedSpriteFeet;
	Animation*							currentAnimation;
	Animation*							currentAnimationFeet;
	Animation							walkingAnimationFeet;
	Animation							idleAnimationFeet;
	Animation							walkingAnimationHandgun;
	Animation							idleAnimationHandgun;
	Animation							attackingAnimationHandgun;
	Animation							reloadingAnimationHandgun;
	Animation							walkingAnimationRifle;
	Animation							idleAnimationRifle;
	Animation							attackingAnimationRifle;
	Animation							reloadingAnimationRifle;
	Animation							walkingAnimationShotgun;
	Animation							idleAnimationShotgun;
	Animation							attackingAnimationShotgun;
	Animation							reloadingAnimationShotgun;
	Animation*							walkingAnimation;
	Animation*							idleAnimation;
	Animation*							attackingAnimation;
	Animation*							reloadingAnimation;
	sf::Sound							soundShoot;
	sf::Sound							soundReload;
	sf::Sound							soundClick;
};