#pragma once
#include "StaticBody.h"
class Obstacle :
	public StaticBody
{
public:
	Obstacle(b2World* world, b2Vec2 position);
	~Obstacle();
	void StartContact(Entity*);
	void EndContact(Entity*);
	void Presolve(Entity*);
	void Render(sf::RenderWindow* window);
	void RenderInactive(sf::RenderWindow* window);
	void Update(sf::Time);
	void TakeDamage(float32 damage) override;

protected:
	int sizey; //rozmiar Obstacle w pikselach
	int sizex1;
	int sizex2;
	sf::Sprite sprite;
	sf::RectangleShape hitpointsBarRed;
	sf::RectangleShape hitpointsBarBlack;
	float32					damage;
private:

};

