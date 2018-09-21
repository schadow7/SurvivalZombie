#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"

class Hud
{
public:
	Hud();
	~Hud();

	void					Render(sf::RenderWindow* window, sf::View* view, Player* player);

private:
	sf::RectangleShape		hitpointsBarRed;
	sf::RectangleShape		hitpointsBarBlack;
	sf::Font				hitpointsFont;
	sf::Text				hitpointsText;
	long int				hitpoints;
	long int				maxhitpoints;
	WeaponType				currentWeaponType;

	sf::Sprite				handgun;
	sf::Texture				handgunTex;
	sf::Sprite				rifle;
	sf::Texture				rifleTex;
	sf::Sprite				shotgun;
	sf::Texture				shotgunTex;

	sf::Sprite				handgunAmmo;
	sf::Texture				handgunAmmoTex;
	sf::Text				handgunAmmoText;
	sf::Sprite				rifleAmmo;
	sf::Texture				rifleAmmoTex;
	sf::Text				rifleAmmoText;
	sf::Sprite				shotgunAmmo;
	sf::Texture				shotgunAmmoTex;
	sf::Text				shotgunAmmoText;

	sf::Sprite				currentAmmo;
	sf::Text				currentAmmoText;
};
