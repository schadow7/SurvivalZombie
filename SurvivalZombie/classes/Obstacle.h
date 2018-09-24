#pragma once
#include "StaticBody.h"
class Obstacle :
	public StaticBody
{
public:
	Obstacle(b2World* world, b2Vec2 position,sf::Vector2i size = sf::Vector2i(50,50), sf::Texture * ntexture = AssetManager::GetTexture("grad2"));
	~Obstacle();
	void StartContact(Entity*);
	void EndContact(Entity*);
	void Presolve(Entity*);
	void Render(sf::RenderWindow* window);
	void RenderInactive(sf::RenderWindow* window);
	void Update(sf::Time);
	void TakeDamage(float32 damage) override;

protected:
	sf::Sprite sprite;
	sf::RectangleShape hitpointsBarRed;
	sf::RectangleShape hitpointsBarBlack;
	float32					damage;
private:

};


