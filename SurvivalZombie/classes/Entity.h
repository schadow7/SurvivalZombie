#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>





class Entity
{
public:
	Entity();
	virtual void			Update(sf::RenderWindow * window) = 0;
	virtual void			Render( sf::RenderWindow * window ) = 0;
	virtual void			StartContact( Entity * entity ) = 0;
	virtual void			EndContact( Entity * entity ) = 0;
	int						Active() const;
	int						GroupID() const;
	~Entity();

protected:
	int						groupID;
	int						active;
	b2Body *				body;
	b2Fixture *				fixture;
	std::string				name;
	//static b2World&			world;
	sf::RenderTexture*		texture;
};


inline b2Vec2 positionPixToWorld( float x, float y )
{
	return b2Vec2( x / 100.f, y / 100.f );
}

inline float sizesPixToWorld( float size )
{
	return size / 200.f;
}

inline sf::Vector2f positionPixToWorld( b2Vec2 vec )
{
	sf::Vector2f tmp = sf::Vector2f( vec.x * 100.f, vec.y * 100.f );
	return tmp;
}