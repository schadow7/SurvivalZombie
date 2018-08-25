#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "EntityManager.h"
#include <vector>
#include <map>
#include "Zombie.h"
#include "ZombieManager.h"
#include "Player.h"
#include "Menu.h"

class Game
{
public:
	Game();
	~Game();

	void									initializeGame();
	void									runGame(sf::RenderWindow * window);
	void									loadTextures();

private:
	void									Render( sf::RenderWindow * window );


private:
	const float								SCALE = 100.f;
	sf::View *								view;
	EntityManager *							entity_manager;
	ZombieManager *							zombie_manager;
	std::map<std::string, sf::Texture *>	textures;
	sf::Sprite								background, background2;
	std::vector<Zombie*>					zombieList;
	b2World *								world;
	Zombie *								zombieTester;
	Player *								player;
	Menu *									menu;
	int										gameState;
};