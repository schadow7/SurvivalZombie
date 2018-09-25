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
	
	/// <summary>
	/// Sprawdza, czy nastąpił koniec gry.
	/// </summary>
	/// <returns>
	///   <c>true</c> jeśli nastąpił koniec gry, w przeciwnym wypadku <c>false</c>.
	/// </returns>
	bool									isGameOver();
	/// <summary>
	/// Główna pętla działającej gry.
	/// </summary>
	/// <param name="window">Okno w ktorym rysowane sa obiekty 2D.</param>
	void									runGame(sf::RenderWindow * window);	
	/// <summary>
	/// Aktualizuje stan postaci - obserwatora
	/// </summary>
	/// <param name="">Pojedyncza postać</param>
	void									updateObserver(Entity*) override;	
	/// <summary>
	/// Restartuje zegar
	/// </summary>
	void									RestartClock() { clock.restart(); }	
	/// <summary>
	/// Zwraca stan poziomu.
	/// </summary>
	/// <returns>Stan poziomu (level, punkty, poziom bazy)</returns>
	level_state								GetLevelState();	
	/// <summary>
	/// Zwraca stan gracza.
	/// </summary>
	/// <returns>Stan gracza (max hp, armor, speed)</returns>
	player_state							GetPlayerState();	
	/// <summary>
	/// Zwraca wektor posiadanych broni.
	/// </summary>
	/// <returns>Wektor posiadanych broni, struktura weapon_features zawiera wszystkie parametry broni.</returns>
	std::vector<weapon_features>			GetWeaponState();	
	/// <summary>
	/// Odtwarza muzykę.
	/// </summary>
	void									PlayMusic();	
	/// <summary>
	/// Zatrzymuje muzykę.
	/// </summary>
	void									StopMusic();	
	/// <summary>
	/// Odtwarza sklep.
	/// </summary>
	/// <param name="window">Okno w ktorym rysowane sa obiekty 2D.</param>
	/// <returns>Zwraca stan gry - sygnalizuje koniec lub kontynuację zakupów.</returns>
	GameState								runShop(sf::Window * window);	
	/// <summary>
	/// Odtwarza sklep po naciśnięciu LPM.
	/// </summary>
	/// <param name="window">Okno w ktorym rysowane sa obiekty 2D.</param>
	/// <returns>Zwraca stan gry - sygnalizuje koniec lub kontynuację zakupów.</returns>
	GameState								runShopClicked(sf::Window * window);	
	/// <summary>
	/// Ustawia odpowiednie stringi do zmiennych tekstowych.
	/// </summary>
	void									setText();	
	/// <summary>
	/// Rysuje w oknie interfejs sklepu.
	/// </summary>
	/// <param name="window">Okno w ktorym rysowane sa obiekty 2D.</param>
	void									drawShop(sf::RenderWindow * window);	
	bool									clicked;
private:	
	/// <summary>
	/// Determines whether this instance is wave.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is wave; otherwise, <c>false</c>.
	/// </returns>
	bool									isWave();	
	/// <summary>
	/// Wczytuje tekstury.
	/// </summary>
	void									loadTextures();	
	/// <summary>
	/// Metoda obsługująca sterowanie.
	/// </summary>
	/// <param name="window">Okno w ktorym rysowane sa obiekty 2D..</param>
	void									Controls(sf::RenderWindow * window);	
	/// <summary>
	/// Inicjalizacja nowej gry.
	/// </summary>
	void									initializeGame();	
	/// <summary>
	/// Inicjalizacja wczytanej gry.
	/// </summary>
	/// <param name="lvlState">State of the level.</param>
	/// <param name="playerState">State of the player.</param>
	/// <param name="weaponState">State of the weapon.</param>
	void									initializeGame(level_state lvlState, player_state playerState, std::vector<weapon_features> weaponState);	
	/// <summary>
	/// Ustawianie cen w sklepie.
	/// </summary>
	void									setPrices();	
	/// <summary>
	/// Metoda wykonywana, gdy próbujemy dokonać zakupu z niewystarczającą ilością funduszy.
	/// </summary>
	void									insufficientFunds();	
	/// <summary>
	/// Formatowanie tekstu
	/// </summary>
	/// <param name="text">Tekst.</param>
	/// <param name="size">Rozmiar.</param>
	void									formatText(sf::Text & text, int size);	
	/// <summary>
	/// Czy gracz posiada pistolet?
	/// </summary>
	/// <returns>True - posiada, false - nie posiada.</returns>
	bool									pistolOwned();	
	/// <summary>
	/// Czy gracz posiada karabin?
	/// </summary>
	/// <returns>True - posiada, false - nie posiada.</returns>
	bool									rifleOwned();	
	/// <summary>
	/// Czy gracz posiada strzelbę?
	/// </summary>
	/// <returns>True - posiada, false - nie posiada.</returns>
	bool									shotgunOwned();	
	/// <summary>
	/// Metoda odpowiedzalna za spawnowanie zombie.
	/// </summary>
	/// <param name="next_level">Następny poziom</param>
	void									spawnHorde(int next_level);	
	/// <summary>
	/// Oblicza parametry nowego poziomu.
	/// </summary>
	/// <param name="levelNr">Numer poziomu.</param>
	/// <param name="zombieQuantity">Liczebność zombie.</param>
	/// <returns>Nowa liczebność zombie</returns>
	std::vector<int>						newLevel(int levelNr, std::vector<int>& zombieQuantity);	
	/// <summary>
	/// Ustawianie przeszkód na mapie.
	/// </summary>
	/// <param name="quantity">Ilość przeszkód.</param>
	void									arrangeObstacles(int quantity);	
	/// <summary>
	/// Tworzy bazę
	/// </summary>
	void									makeBase();	
	/// <summary>
	/// Tworzy barykadę.
	/// </summary>
	/// <param name="i">The i.</param>
	/// <param name="boxSize">Rozmiar sciany.</param>
	/// <param name="position">Pozycja.</param>
	/// <returns></returns>
	BasicEntanglements*						spawnWall(int i, int boxSize, sf::Vector2f& position);	
	/// <summary>
	/// Ustawia poziom bazy.
	/// </summary>
	/// <param name="level">Poziom bazy.</param>
	void									setBaseLevel(int level);	
	/// <summary>
	/// Zwraca życie bazy.
	/// </summary>
	/// <returns>Życie bazy.</returns>
	int										getBaseHP();
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
	int										currentLevel;
	int										baseLevel;
	long int								points = 0;
	sf::Clock								clock;
	sf::Time								delay,delay2;
	sf::Time								levelDelay;
	float32									previous_angle;
	std::default_random_engine				engine;
	std::uniform_int_distribution<int>		angleDistribution{ 1, 360 };
	const float								DEGTORAD = b2_pi / 180;
	b2Vec2									mapCenter;
	std::uniform_int_distribution<int>		zombieDistribution{ -1, 1 };
	std::uniform_int_distribution<int>		noiseDistribution{ 0,23 };
	sf::Time								shoot_timer;
	std::vector<BasicEntanglements*>		base;
	int										mapsizex, mapsizey;
	sf::Vector2f							previousMousePos;
	sf::Music								music;
	sf::Sound								startLevelSound;
	std::vector<sf::Sound>					zombieNoises;
	GamePhase								gamePhase;
	int										up, shadow, posX, posY, spacing, spacingy, dposY, width, height1, height2, mouseX, mouseY, selectedButton;
	sf::Sprite								backgroundShop, button[40], weapon[3];
	sf::Text								text[50];
	sf::Font								fontType;
	SelectedWeapon							selectedWeapon;
	bool									isWeaponSelected;
	int										priceBaseUpgrade, pricePistol, priceRifle, priceShotgun;
	int										pricePistolAmmo, priceRifleAmmo, priceShotgunAmmo;
	int										priceRifleFactor, priceShotgunFactor;
	int										priceDMG, priceRecoil, priceReload, priceMagCap, priceAmmoCap;
	int										factor, factorShotgun = 4, factorRifle = 6;
	bool									next_level;
};

