#pragma once
#include "StaticBody.h"

/// <summary>
/// Œrodek bazy.
/// </summary>
/// <seealso cref="StaticBody" />
class TheBase :
	public StaticBody
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="TheBase"/> class.
	/// </summary>
	/// <param name="world">The b2World.</param>
	/// <param name="position">The position in b2World.</param>
	/// <param name="size">The size in px.</param>
	/// <param name="ntexture">The new texture.</param>
	TheBase(b2World* world, b2Vec2 position, sf::Vector2i nsize = sf::Vector2i(50, 50), sf::Texture* ntexture = AssetManager::GetTexture("grad2"));
	~TheBase();	
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
	/// Attacks the specified entity.
	/// </summary>
	/// <param name="entity">The entity.</param>
	virtual void Attack(Entity * entity);
	/// <summary>
	/// Sets the damage.
	/// </summary>
	/// <param name="">The .</param>
	void SetDamage(float32);
	/// <summary>
	/// Sets the angle.
	/// </summary>
	/// <param name="">The .</param>
	void SetAngle(float32);
	/// <summary>
	/// Gets the size of the px.
	/// </summary>
	/// <returns></returns>
	b2Vec2 GetPxSize();
	/// <summary>
	/// Repairs the specified .
	/// </summary>
	/// <param name="">The .</param>
	void Repair(int);
	/// <summary>
	/// Sets the maximum hp.
	/// </summary>
	/// <param name="">The .</param>
	void SetMaxHP(int);
	/// <summary>
	/// Gets the maximum hp.
	/// </summary>
	/// <returns></returns>
	int GetMaxHP();
	/// <summary>
	/// Sets the damage.
	/// </summary>
	/// <param name="">The .</param>
	void SetDamage(int);
	/// <summary>
	/// Makes the active.
	/// </summary>
	void MakeActive();
protected:
	sf::Sprite sprite;
	sf::RectangleShape hitpointsBarRed;
	sf::RectangleShape hitpointsBarBlack;
	float32					damage;
	sf::Time				attack_timer;
	sf::Time				attack_cooldown;
private:
	sf::Texture* textureDead;
};
