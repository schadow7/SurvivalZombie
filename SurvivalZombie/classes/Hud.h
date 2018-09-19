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
};
