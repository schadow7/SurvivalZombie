#include "Hud.h"

Hud::Hud()
{
	hitpointsBarRed.setFillColor(sf::Color(255, 0, 0));
	hitpointsBarBlack.setFillColor(sf::Color(0, 0, 0));
	hitpointsFont.loadFromFile("arial.ttf");
	FormatText( hitpointsText );
	hitpointsText.setFillColor(sf::Color::White);
	hitpointsText.setOutlineThickness(2);
	hitpointsBarBlack.setSize(sf::Vector2f(322, 42));

	//Wczytywanie tekstur
	handgun.setTexture( *AssetManager::GetTexture( "handgun" ) );
	rifle.setTexture( *AssetManager::GetTexture( "rifle" ) );
	shotgun.setTexture( *AssetManager::GetTexture( "shotgun" ) );
	handgunAmmo.setTexture( *AssetManager::GetTexture( "9mm" ) );
	rifleAmmo.setTexture( *AssetManager::GetTexture( "7.62mm" ) );
	shotgunAmmo.setTexture( *AssetManager::GetTexture( "12gauge" ) );

	//Formatowanie tekstu
	FormatText( currentAmmoText );
	FormatText( handgunAmmoText );
	FormatText( rifleAmmoText );
	FormatText( shotgunAmmoText );

	ammoHudString = "";
}

Hud::~Hud()
{
}

void Hud::Render(sf::RenderWindow* window, sf::View* view, Player* player)
{
	//sprawdzamy jaka bron jest obecnie uzywana
	weapon_features current_weapon = player->GetCurrentWeapon();

	//okreslamy pozycje elementow Hud'u
	positioningHudElements(view, player, current_weapon);

	//rysujemy odpowiednia ikone broni
	specifyAndRenderWeapon(window, current_weapon);

	//TODO
	std::vector<weapon_features> weapon_list = player->GetWeaponList();
	handgunAmmoText.setString( "   -" );
	rifleAmmoText.setString( "   -" );
	shotgunAmmoText.setString( "   -" );
	for ( auto & it : weapon_list )
	{
		if ( it.type == WeaponType::PISTOL )
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

void Hud::positioningHudElements(sf::View* view, Player* player, weapon_features current_weapon)
{
	hitpoints = player->GetHitpoints()[0];
	maxhitpoints = player->GetHitpoints()[1];

	//ustalanie miejsca healthbara
	hitpointsBarBlack.setPosition(view->getCenter().x - 620, view->getCenter().y + 300);
	hitpointsBarRed.setSize(sf::Vector2f(static_cast<int>(320.f * hitpoints / maxhitpoints), 40.f));
	hitpointsBarRed.setPosition(view->getCenter().x - 619, view->getCenter().y + 301);
	//ustalanie miejsca tekstu na healthbarze
	hitpointsText.setString("Health: " + std::to_string(hitpoints));
	hitpointsText.setPosition(view->getCenter().x - 540, view->getCenter().y + 302);
	//ustalanie miejsca ikon broni
	handgun.setPosition(view->getCenter().x + 500, view->getCenter().y + 200);
	rifle.setPosition(view->getCenter().x + 420, view->getCenter().y + 150);
	shotgun.setPosition(view->getCenter().x + 420, view->getCenter().y + 150);
	//ustalanie miejsca ikon amunicji
	handgunAmmo.setPosition(view->getCenter().x + 580, view->getCenter().y + 100);
	rifleAmmo.setPosition(view->getCenter().x + 580, view->getCenter().y + 50);
	shotgunAmmo.setPosition(view->getCenter().x + 580, view->getCenter().y + 0);
	//ustalanie miejsca tekstu mowiacego o ilosci niesionej amunicji
	handgunAmmoText.setPosition(view->getCenter().x + 515, view->getCenter().y + 98);
	rifleAmmoText.setPosition(view->getCenter().x + 515, view->getCenter().y + 48);
	shotgunAmmoText.setPosition(view->getCenter().x + 515, view->getCenter().y - 2);
	//ustalanie miejsca tekstu mowiacego o ilosci zaladowanej amunicji
	currentAmmo.setPosition(view->getCenter().x + 570, view->getCenter().y + 290);
	currentAmmoText.setPosition(view->getCenter().x + 450, view->getCenter().y + 288);
	ammoHudString = std::to_string(current_weapon.magazineAmmo) + " / " + std::to_string(current_weapon.maxMagazineAmmo);
	currentAmmoText.setString(ammoHudString);
}

void Hud::specifyAndRenderWeapon(sf::RenderWindow* window, weapon_features current_weapon)
{
	currentWeaponType = current_weapon.type;
	if (currentWeaponType == WeaponType::PISTOL)
	{
		window->draw(handgun);
		currentAmmo.setTexture(*AssetManager::GetTexture("9mm"));
	}
	else if (currentWeaponType == WeaponType::RIFLE)
	{
		window->draw(rifle);
		currentAmmo.setTexture(*AssetManager::GetTexture("7.62mm"));
	}
	else if (currentWeaponType == WeaponType::SHOTGUN)
	{
		window->draw(shotgun);
		currentAmmo.setTexture(*AssetManager::GetTexture("12gauge"));
	}
}

void Hud::FormatText( sf::Text & text )
{
	text.setFont( hitpointsFont );
	text.setCharacterSize( 30 );
	text.setFillColor( sf::Color::Black );
	text.setStyle( sf::Text::Bold );
	text.setOutlineColor( sf::Color::Black );
	text.setOutlineThickness( 1 );
}