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
	void					FormatText( sf::Text & text );
	sf::RectangleShape		hitpointsBarRed;
	sf::RectangleShape		hitpointsBarBlack;
	sf::Font				hitpointsFont;
	sf::Text				hitpointsText;
	long int				hitpoints;
	long int				maxhitpoints;
	WeaponType				currentWeaponType;

	sf::Sprite				handgun;
	sf::Sprite				rifle;
	sf::Sprite				shotgun;

	sf::Sprite				handgunAmmo;
	sf::Text				handgunAmmoText;
	sf::Sprite				rifleAmmo;
	sf::Text				rifleAmmoText;
	sf::Sprite				shotgunAmmo;
	sf::Text				shotgunAmmoText;

	sf::Sprite				currentAmmo;
	sf::Text				currentAmmoText;
};
