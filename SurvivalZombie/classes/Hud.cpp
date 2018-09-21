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

	handgunTex.loadFromFile(".\\graphics\\handgun.png");
	handgunTex.setSmooth(1);
	handgun.setTexture(handgunTex);
	rifleTex.loadFromFile(".\\graphics\\rifle.png");
	rifleTex.setSmooth(1);
	rifle.setTexture(rifleTex);
	shotgunTex.loadFromFile(".\\graphics\\shotgun.png");
	shotgunTex.setSmooth(1);
	shotgun.setTexture(shotgunTex);


	handgunAmmoTex.loadFromFile(".\\graphics\\9mm.png");
	handgunAmmoTex.setSmooth(1);
	handgunAmmo.setTexture(handgunAmmoTex);
	rifleAmmoTex.loadFromFile(".\\graphics\\7.62mm.png");
	rifleAmmoTex.setSmooth(1);
	rifleAmmo.setTexture(rifleAmmoTex);
	shotgunAmmoTex.loadFromFile(".\\graphics\\12gauge.png");
	shotgunAmmoTex.setSmooth(1);
	shotgunAmmo.setTexture(shotgunAmmoTex);

	currentAmmoText.setFont(hitpointsFont);
	currentAmmoText.setCharacterSize(30);
	currentAmmoText.setFillColor(sf::Color::Black);
	currentAmmoText.setStyle(sf::Text::Bold);
	currentAmmoText.setOutlineColor(sf::Color::Black);
	currentAmmoText.setOutlineThickness(1);

	handgunAmmoText.setFont(hitpointsFont);
	handgunAmmoText.setCharacterSize(30);
	handgunAmmoText.setFillColor(sf::Color::Black);
	handgunAmmoText.setStyle(sf::Text::Bold);
	handgunAmmoText.setOutlineColor(sf::Color::Black);
	handgunAmmoText.setOutlineThickness(1);

	rifleAmmoText.setFont(hitpointsFont);
	rifleAmmoText.setCharacterSize(30);
	rifleAmmoText.setFillColor(sf::Color::Black);
	rifleAmmoText.setStyle(sf::Text::Bold);
	rifleAmmoText.setOutlineColor(sf::Color::Black);
	rifleAmmoText.setOutlineThickness(1);

	shotgunAmmoText.setFont(hitpointsFont);
	shotgunAmmoText.setCharacterSize(30);
	shotgunAmmoText.setFillColor(sf::Color::Black);
	shotgunAmmoText.setStyle(sf::Text::Bold);
	shotgunAmmoText.setOutlineColor(sf::Color::Black);
	shotgunAmmoText.setOutlineThickness(1);
	
}


Hud::~Hud()
{
}

void Hud::Render(sf::RenderWindow* window, sf::View* view, Player* player)
{
	hitpoints = player->GetHitpoints()[0];
	maxhitpoints = player->GetHitpoints()[1];

	hitpointsBarBlack.setPosition(view->getCenter().x - 620, view->getCenter().y + 300);

	hitpointsBarRed.setSize(sf::Vector2f(int(320.f * hitpoints / maxhitpoints), 40.f));
	hitpointsBarRed.setPosition(view->getCenter().x - 619, view->getCenter().y + 301);

	hitpointsText.setString("Health: " + std::to_string(hitpoints));
	hitpointsText.setPosition(view->getCenter().x - 540, view->getCenter().y + 302);

	handgun.setPosition(view->getCenter().x + 500, view->getCenter().y + 200);
	rifle.setPosition(view->getCenter().x + 420, view->getCenter().y + 150);
	shotgun.setPosition(view->getCenter().x + 420, view->getCenter().y + 150);

	handgunAmmo.setPosition(view->getCenter().x + 580, view->getCenter().y + 100);
	rifleAmmo.setPosition(view->getCenter().x + 580, view->getCenter().y + 50);
	shotgunAmmo.setPosition(view->getCenter().x + 580, view->getCenter().y + 0);
	handgunAmmoText.setPosition(view->getCenter().x + 515, view->getCenter().y + 98);
	rifleAmmoText.setPosition(view->getCenter().x + 515, view->getCenter().y + 48);
	shotgunAmmoText.setPosition(view->getCenter().x + 515, view->getCenter().y - 2);

	std::string tmp;
	//tutaj powinnismy sprawdzac jaka bron jest w danej chwili uzywana
	weapon_features current_weapon = player->GetCurrentWeapon();
	currentWeaponType = current_weapon.type;
	if (currentWeaponType == WeaponType::PISTOL)
	{
		window->draw(handgun);
		currentAmmo.setTexture(handgunAmmoTex);
	}
	else if ( currentWeaponType == WeaponType::RIFLE )
	{
		window->draw(rifle);
		currentAmmo.setTexture(rifleAmmoTex);
	}
	else if ( currentWeaponType == WeaponType::SHOTGUN )
	{
		window->draw(shotgun);
		currentAmmo.setTexture(shotgunAmmoTex);
	}
	tmp = std::to_string( current_weapon.magazineAmmo ) + " / " + std::to_string( current_weapon.maxMagazineAmmo );
	currentAmmo.setPosition(view->getCenter().x + 570, view->getCenter().y + 290);
	currentAmmoText.setPosition(view->getCenter().x + 450, view->getCenter().y + 288);
	currentAmmoText.setString(tmp);

	std::vector<weapon_features> weapon_list = player->GetWeaponList();
	handgunAmmoText.setString( "   -" );
	rifleAmmoText.setString( "   -" );
	shotgunAmmoText.setString( "   -" );
	for ( auto & it : weapon_list )
	{
		if( it.type == WeaponType::PISTOL )
			handgunAmmoText.setString( std::to_string(it.carriedAmmo) );
		if ( it.type == WeaponType::RIFLE )
			rifleAmmoText.setString( std::to_string( it.carriedAmmo ) );
		if ( it.type == WeaponType::SHOTGUN )
			shotgunAmmoText.setString( std::to_string( it.carriedAmmo ) );
	}


	window->draw(currentAmmo);
	window->draw(currentAmmoText);
	window->draw(handgunAmmo);
	window->draw(handgunAmmoText);
	window->draw(rifleAmmo);
	window->draw(rifleAmmoText);
	window->draw(shotgunAmmo);
	window->draw(shotgunAmmoText);
	window->draw(hitpointsBarBlack);
	window->draw(hitpointsBarRed);
	window->draw(hitpointsText);
}