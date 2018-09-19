#include "Hud.h"



Hud::Hud()
{
	hitpointsBarRed.setFillColor(sf::Color(255, 0, 0));
	hitpointsBarBlack.setFillColor(sf::Color(0, 0, 0));
	hitpointsFont.loadFromFile("arial.ttf");
	hitpointsText.setFont(hitpointsFont);
	hitpointsText.setCharacterSize(30);
	hitpointsText.setFillColor(sf::Color::White);
	hitpointsText.setStyle(sf::Text::Bold);
	hitpointsText.setOutlineColor(sf::Color::Black);
	hitpointsText.setOutlineThickness(2);
	hitpointsBarBlack.setSize(sf::Vector2f(322, 42));
}


Hud::~Hud()
{
}

void Hud::Render(sf::RenderWindow* window, sf::View* view, Player* player)
{
	hitpoints = player->GetHitpoints()[0];
	maxhitpoints = player->GetHitpoints()[1];

	hitpointsBarBlack.setPosition(view->getCenter().x - 620, view->getCenter().y + 300);

	hitpointsBarRed.setSize(sf::Vector2f(int(320 * hitpoints / maxhitpoints), 40));
	hitpointsBarRed.setPosition(view->getCenter().x - 619, view->getCenter().y + 301);

	hitpointsText.setString("Health: " + std::to_string(hitpoints));
	hitpointsText.setPosition(view->getCenter().x - 540, view->getCenter().y + 302);

	window->draw(hitpointsBarBlack);
	window->draw(hitpointsBarRed);
	window->draw(hitpointsText);
}