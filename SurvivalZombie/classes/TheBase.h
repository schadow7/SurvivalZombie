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
	void StartContact(Entity*);
	void EndContact(Entity*);
	void Presolve(Entity*);
	void Render(sf::RenderWindow* window);
	void RenderInactive(sf::RenderWindow* window);
	void Update(sf::Time);
	void TakeDamage(float32 damage) override;
	virtual void Attack(Entity * entity);
	void SetDamage(float32);
	void SetAngle(float32);
	b2Vec2 GetPxSize();
	void Repair(int);
	void SetMaxHP(int);
	int GetMaxHP();
	void SetDamage(int);
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
