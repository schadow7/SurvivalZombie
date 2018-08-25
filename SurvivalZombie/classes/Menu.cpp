#include "Menu.h"


Menu::Menu()
{
	selectedButton = 0;
	clicked = false;
	loadTextures();
}


Menu::~Menu()
{
}


void Menu::loadTextures()
{
	posX = 100;
	posY = 200;
	spacing = 100;
	width = 304;
	height = 79;


	sf::Texture * tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\backgroundMenu.png");
	textures.insert(std::pair<std::string, sf::Texture*>("backgroundMenu", tmp));
	backgroundMenu.setTexture(*textures.at("backgroundMenu"));


	tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\buttonPlayOff.png");
	textures.insert(std::pair<std::string, sf::Texture*>("button[0]", tmp));
	button[0].setTexture(*textures.at("button[0]"));
	button[0].setPosition(sf::Vector2f(posX, posY));

	tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\buttonPlayOn.png");
	textures.insert(std::pair<std::string, sf::Texture*>("button[1]", tmp));
	button[1].setTexture(*textures.at("button[1]"));
	button[1].setPosition(sf::Vector2f(posX, posY));


	tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\buttonOptionsOff.png");
	textures.insert(std::pair<std::string, sf::Texture*>("button[2]", tmp));
	button[2].setTexture(*textures.at("button[2]"));
	button[2].setPosition(sf::Vector2f(posX, posY + spacing));

	tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\buttonOptionsOn.png");
	textures.insert(std::pair<std::string, sf::Texture*>("button[3]", tmp));
	button[3].setTexture(*textures.at("button[3]"));
	button[3].setPosition(sf::Vector2f(posX, posY + spacing));


	tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\buttonExitOff.png");
	textures.insert(std::pair<std::string, sf::Texture*>("button[4]", tmp));
	button[4].setTexture(*textures.at("button[4]"));
	button[4].setPosition(sf::Vector2f(posX, posY + spacing*2));

	tmp = new sf::Texture;
	tmp->loadFromFile(".\\graphics\\buttonExitOn.png");
	textures.insert(std::pair<std::string, sf::Texture*>("button[5]", tmp));
	button[5].setTexture(*textures.at("button[5]"));
	button[5].setPosition(sf::Vector2f(posX, posY + spacing*2));
}


int Menu::runMenu(sf::RenderWindow * window, sf::Event event)
{
	if (!clicked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		int mouseX = sf::Mouse::getPosition(*window).x;
		int mouseY = sf::Mouse::getPosition(*window).y;

		if ((mouseX >= posX   &&   mouseX <= posX + width) &&
			(mouseY >= posY   &&   mouseY <= posY + height))
		{
			selectedButton = 1;
			clicked = true;
		}
		else if ((mouseX >= posX   &&   mouseX <= posX + width) &&
			     (mouseY >= posY + spacing   &&   mouseY <= posY + spacing + height))
		{
			selectedButton = 3;
			clicked = true;
		}
		else if ((mouseX >= posX   &&   mouseX <= posX + width) &&
			     (mouseY >= posY + spacing * 2   &&   mouseY <= posY + spacing * 2 + height))
		{
			selectedButton = 5;
			clicked = true;
		}
	}

	if (clicked && event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			int mouseX = sf::Mouse::getPosition(*window).x;
			int mouseY = sf::Mouse::getPosition(*window).y;
			clicked = false;

			if ((mouseX >= posX && mouseX <= posX + width) &&
				(mouseY >= posY && mouseY <= posY + height))
			{
				return 1;
			}
			else if ((mouseX >= posX && mouseX <= posX + width) &&
				(mouseY >= posY + spacing && mouseY <= posY + spacing + height))
			{
				selectedButton = 3;
			}
			else if ((mouseX >= posX && mouseX <= posX + width) &&
				(mouseY >= posY + spacing * 2 && mouseY <= posY + spacing * 2 + height))
			{
				window->close();
			}
		}
	}

	this->draw(window);

	return 0;
}




void Menu::draw(sf::RenderWindow* window)
{
	window->draw(backgroundMenu);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window->draw(button[i*2]);
	}
	if(clicked) window->draw(button[selectedButton]);
}
