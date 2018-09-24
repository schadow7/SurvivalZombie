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
#include "observer.h"
#include "Weapon.h"
#include "Hud.h"
#include <random>
#include "Obstacle.h"
#include "BasicEntanglements.h"
#include "TheBase.h"

#define N_OF_BUTTONS 8
enum class SaveSlot { SLOT_1 = 1, SLOT_2 = 2, SLOT_3 = 3 };
enum class GameState { MENU, RUNNING, SHOP };
enum class MenuType { DEFAULT, NEWGAME, LOADGAME };

struct level_state
{
	int level;
	long int points;
	short int base_level;
};

enum class GamePhase { GAME, SHOP };
enum class SelectedWeapon { PISTOL, RIFLE, SHOTGUN };

class Game:
	public Observer
{
public:
	Game();
	Game( level_state lvlState, player_state playerState, std::vector<weapon_features> weaponState );
	~Game();

	
	void									runGame(sf::RenderWindow * window);
	void									updateObserver(Entity*) override;
	void									RestartClock() { clock.restart(); }
	level_state								GetLevelState();
	player_state							GetPlayerState();
	std::vector<weapon_features>			GetWeaponState();
	void									PlayMusic();
	void									StopMusic();
	GameState								runShop( sf::Window * window );
	GameState								runShopClicked( sf::Window * window);
	void									setText();
	void									drawShop( sf::RenderWindow * window );
private:
	bool									isWave();
	void									Render( sf::RenderWindow * window );
	void									loadTextures();
	void									Controls(sf::RenderWindow * window);
	void									initializeGame();
	void									initializeGame( level_state lvlState, player_state playerState, std::vector<weapon_features> weaponState );
	
	
	
	void									formatText(sf::Text & text, int size);
	
	bool									pistolOwned();
	bool									rifleOwned();
	bool									shotgunOwned();
	bool									isWeaponSelected();
	const float								SCALE = 100.f;
	EntityManager *							entity_manager;
	sf::View *								view;
	sf::Sprite								background;
	std::vector<Zombie*>					zombieList;
	b2World *								world;
	Zombie *								zombieTester;
	Player *								player;
	Hud *									hud;
	int										undeadCount;
	void									spawnHorde(int next_level);
	int										currentLevel;
	int										baseLevel;
	long int								points = 0;
	sf::Clock								clock;
	sf::Time								delay,delay2;
	float32									previous_angle;
	std::default_random_engine				engine;
	std::uniform_int_distribution<int>		angleDistribution{ 1, 360 };
	const float								DEGTORAD = b2_pi / 180;
	b2Vec2									mapCenter;
	std::vector<int>						newLevel(int levelNr, std::vector<int>& zombieQuantity);
	std::uniform_int_distribution<int>		zombieDistribution{ -1, 1 };
	std::uniform_int_distribution<int>		noiseDistribution{ 0,23 };
	sf::Time								shoot_timer;
	void									arrangeObstacles(int quantity);
	void									makeBase();
	std::vector<BasicEntanglements*>		base;
	BasicEntanglements*						spawnWall(int i, int boxSize, sf::Vector2f& position);
	void									setBaseLevel(int level);
	int										mapsizex, mapsizey;
	sf::Vector2f							previousMousePos;
	sf::Music								music;
	sf::Sound								startLevelSound;
	std::vector<sf::Sound>					zombieNoises;
	GamePhase								gamePhase;
	bool									clicked;
	int										shadow, posX, posY, spacing, spacingy, dposY, width, height1, height2, mouseX, mouseY, selectedButton;
	sf::Sprite								backgroundShop, button[17], weapon[3];
	sf::Text								text[50];
	sf::Font								fontType;
	SelectedWeapon							selectedWeapon;

};

