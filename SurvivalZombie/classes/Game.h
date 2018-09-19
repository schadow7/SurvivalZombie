#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "EntityManager.h"
#include <vector>
#include <map>
#include "Zombie.h"
#include "AssetManager.h"
#include "ZombieTank.h"
#include "ZombieSprinter.h"
#include "Player.h"
#include "Menu.h"
#include "Brick.h"
#include "observer.h"
#include "Level.h"
#include "Weapon.h"
class Game:
	public Observer
{
public:
	Game();
	~Game();

	void									initializeGame();
	void									runGame(sf::RenderWindow * window);
	void									loadTextures();
	void									Controls(sf::RenderWindow * window);
	void									update(Entity*) override;

private:
	void									Render( sf::RenderWindow * window );


private:
	const float								SCALE = 100.f;
	sf::View *								view;
	EntityManager *							entity_manager;
	std::map<std::string, sf::Texture *>	textures;
	sf::Sprite								background, background2;
	std::vector<Zombie*>					zombieList;
	b2World *								world;
	Zombie *								zombieTester;
	Player *								player;
	Menu *									menu;
	int										gameState;
	sf::Cursor *							cursor;
	int										undeadCount;
	void									spawnHorde(Level & next_level);
	int										currentLevel;
};