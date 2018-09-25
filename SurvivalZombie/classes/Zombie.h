#pragma once
#pragma once
#include "DynamicBody.h"
#include "AIType.h"
#include "AnimatedSprite.h"
#include <random>
class Zombie :
	public DynamicBody
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Zombie"/> class.
	/// </summary>
	/// <param name="world">The b2World.</param>
	/// <param name="position">The position in px on the map.</param>
	Zombie(b2World* world, b2Vec2 position);
	~Zombie();	
	/// <summary>
	/// Starts the contact.
	/// </summary>
	/// <param name="">The .</param>
	void StartContact(Entity*);
	/// <summary>
	/// Ends the contact.
	/// </summary>
	/// <param name="">The .</param>
	void EndContact(Entity*);
	/// <summary>
	/// Presolves the specified .
	/// </summary>
	/// <param name="">The .</param>
	void Presolve(Entity*);	
	/// <summary>
	/// Renders the specified window.
	/// </summary>
	/// <param name="window">The window.</param>
	void Render(sf::RenderWindow* window);
	/// <summary>
	/// Renders the inactive.
	/// </summary>
	/// <param name="window">The window.</param>
	void RenderInactive(sf::RenderWindow* window);
	/// <summary>
	/// Updates the specified .
	/// </summary>
	/// <param name="">The .</param>
	void Update(sf::Time);
	/// <summary>
	/// Takes the damage.
	/// </summary>
	/// <param name="damage">The damage.</param>
	void TakeDamage(float32 damage) override;
	/// <summary>
	/// Ustawia Entity za którym Zombie maj¹ pod¹¿aæ.
	/// </summary>
	/// <param name="new_target">The new target.</param>
	void SetTarget(const Entity* new_target);
	enum AI_enum { Aggrssive, Chaotic, Idle };
	/// <summary>
	/// Wybór algorytmu steruj¹cego przeciwnikiem
	/// </summary>
	/// <param name="">The .</param>
	void SetAI(AI_enum);
	/// <summary>
	/// Wybór algorytmu steruj¹cego przeciwnikiem
	/// </summary>
	/// <param name="">The .</param>
	void SetAI(AIType*);
	/// <summary>
	/// Attacks the specified entity.
	/// </summary>
	/// <param name="entity">The entity.</param>
	virtual void Attack(Entity * entity);

protected:	
	/// <summary>
	/// Determines whether this instance is idle.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is idle; otherwise, <c>false</c>.
	/// </returns>
	bool					isIdle();	
	/// <summary>
	/// Setups the healthbar.
	/// </summary>
	void					setupHealthbar();	
	/// <summary>
	/// Determines whether this instance is moving.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is moving; otherwise, <c>false</c>.
	/// </returns>
	bool					isMoving();	
	/// <summary>
	/// Determines whether this instance is attacking.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is attacking; otherwise, <c>false</c>.
	/// </returns>
	bool					isAttacking();
	double animSpeed;
	int sizey; //rozmiar zombie w pikselach
	int sizex1;
	int sizex2;
	sf::Sprite sprite;
	sf::RectangleShape hitpointsBarRed;
	AnimatedSprite			animatedSprite;
	Animation*				currentAnimation;
	sf::Texture				textureDead;
	sf::Clock				frameClock;
	sf::Time				frameTime;
	sf::Time				attack_timer;
	sf::Time				attack_cooldown;
	float32					damage;
	bool					attack = false;

	b2Vec2					direction;
	AIType*					AI;
	const Entity*			target;
	b2World*				world;

private:	
	/// <summary>
	/// Sets the sprite sheets.
	/// </summary>
	void					setSpriteSheets();	
	/// <summary>
	/// Adds the frames to animations.
	/// </summary>
	void					addFramesToAnimations();
	Animation				walkingAnimation;
	Animation				attackingAnimation;
	Animation				idleAnimation;
	Animation				deadAnimation;


};