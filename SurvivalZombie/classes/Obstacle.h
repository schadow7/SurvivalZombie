#pragma once
#include "StaticBody.h"
class Obstacle :
	public StaticBody
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Obstacle"/> class.
	/// </summary>
	/// <param name="world">The b2World.</param>
	/// <param name="position">The position in b2World.</param>
	/// <param name="size">The size in px.</param>
	/// <param name="ntexture">The new texture.</param>
	Obstacle(b2World* world, b2Vec2 position, sf::Vector2i size = sf::Vector2i(50, 50), sf::Texture * ntexture = AssetManager::GetTexture("grad2"));
	~Obstacle();	
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

protected:
	sf::Sprite sprite;
	sf::RectangleShape hitpointsBarRed;
	sf::RectangleShape hitpointsBarBlack;
	float32					damage;
private:

};


