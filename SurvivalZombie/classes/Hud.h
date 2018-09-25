#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"

class Hud
{
public:
	Hud();
	~Hud();
	
	/// <summary>
	/// Renders the specified window.
	/// </summary>
	/// <param name="window">The window.</param>
	/// <param name="view">The view.</param>
	/// <param name="player">The player.</param>
	void					Render(sf::RenderWindow* window, sf::View* view, Player* player);
private:	
	/// <summary>
	/// Formats the text.
	/// </summary>
	/// <param name="text">The text.</param>
	void					FormatText(sf::Text & text);	
	/// <summary>
	/// Positions the hud elements.
	/// </summary>
	/// <param name="view">The view.</param>
	/// <param name="player">The player.</param>
	/// <param name="current_weapon">The current weapon.</param>
	void					positioningHudElements(sf::View* view, Player* player, weapon_features current_weapon);
	/// <summary>
	/// Specifies and renders weapon.
	/// </summary>
	/// <param name="window">The window.</param>
	/// <param name="current_weapon">The current weapon.</param>
	void					specifyAndRenderWeapon(sf::RenderWindow* window, weapon_features current_weapon);

	sf::RectangleShape		hitpointsBarRed;
	sf::RectangleShape		hitpointsBarBlack;
	sf::Font				hitpointsFont, fontType;
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
	std::string             ammoHudString;
	sf::Text				scoreText;
	sf::Sprite				gameOverSprite;
	sf::Text				gameOverText;
};
