#pragma once
#include "DynamicBody.h"
class Player :
	public DynamicBody
{
public:
	Player( b2World* world, sf::Texture * texture, b2Vec2 position );
	~Player();
	void StartContact( Entity* );
	void EndContact( Entity* );
	void Render( sf::RenderWindow* window );
	void Update();
	//virtual void Action( b2Vec2 player_positon );
private:
	double speed;
	sf::CircleShape shape;

};