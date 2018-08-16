#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>
#include "Entity.h"



class Brick : public Entity
{
public:
	const float SCALE = 100.f;
	static unsigned int			counter;
								Brick( b2World * world, sf::Texture * texture, int x, int y );
	virtual void				Update( sf::RenderWindow * window ) override;
	virtual void				StartContact( Entity * entity ) override;
	virtual void				EndContact( Entity * entity ) override;
								~Brick();
private:
	sf::RectangleShape			shape;
	unsigned int				contacts;
};

