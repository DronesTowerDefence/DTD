#include "Sidebar.h"
#include "Round.h"
#include <iostream>

Sidebar* Sidebar::instance = nullptr;

Sidebar::Sidebar()
{
	buttonTexture[0].loadFromFile("img/tower0/tower0_preview.png");
	buttonTexture[1].loadFromFile("img/tower1/tower1_preview.png");
	buttonTexture[2].loadFromFile("img/tower2/tower2_preview.png");
	buttonTexture[3].loadFromFile("img/tower3/tower3_preview.png");
	buttonTexture[4].loadFromFile("img/tower4/tower4_preview.png");

	buttonTextFont.loadFromFile("fonts/arial.ttf");

	for (int i = 0; i < Ressources::getInstance()->getTowerCount(); i++)
	{
		price[i] = Ressources::getInstance()->getTowerPrice(i);
		buttonText[i].setString(Ressources::getInstance()->getTowerName(i) + "\n" + std::to_string(int(price[i])) + " $");

		buttonSpr[i].setTexture(buttonTexture[i]);
		buttonText[i].setFont(buttonTextFont);
		buttonText[i].setCharacterSize(20);
		buttonText[i].setFillColor(Color::White);
		buttonText[i].setOutlineColor(Color::Black);
		buttonText[i].setOutlineThickness(2);
	}

	buttonText[0].setPosition(Vector2f(1757, 65)); //Position des Button-Textes
	buttonText[1].setPosition(Vector2f(1832, 65));
	buttonText[2].setPosition(Vector2f(1757, 170));
	buttonText[3].setPosition(Vector2f(1832, 170));
	buttonText[4].setPosition(Vector2f(1757, 275));

	buttonSpr[0].setPosition(Vector2f(1762, 15)); //Position der Buttons
	buttonSpr[1].setPosition(Vector2f(1837, 15));
	buttonSpr[2].setPosition(Vector2f(1762, 120));
	buttonSpr[3].setPosition(Vector2f(1837, 120));
	buttonSpr[4].setPosition(Vector2f(1762, 225));

}

Sidebar* Sidebar::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Sidebar();
	}
	return instance;
}

int Sidebar::isClicked(sf::RenderWindow* window)
{
	Vector2i mouse = Mouse::getPosition(*window);
	Vector2f pos, pos2;


	for (int i = 0; i < 5; i++) //Geht alle Türme durch
	{
		pos = Service::getInstance()->getObjectPosition(buttonSpr[i].getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(buttonSpr[i].getPosition() + Vector2f(50, 50)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			if (Round::getInstance()->submoney(price[i])) //Wenn genug Geld vorhanden ist, wird es vom Geldstand abgezogen
			{
				return i;
			}
		}
	}

	return -1;
}

void Sidebar::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < 5; i++)
	{
		window->draw(buttonSpr[i]);
		window->draw(buttonText[i]);
	}
}

Texture Sidebar::getTowerTexture(int i)
{
	return buttonTexture[i];
}