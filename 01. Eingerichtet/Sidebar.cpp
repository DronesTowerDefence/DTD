#include "Sidebar.h"
#include "Round.h"
#include <iostream>

Sidebar* Sidebar::instance = nullptr;

Sidebar::Sidebar()
{
	price[0] = 100;
	price[1] = 200;
	price[2] = 300;
	price[3] = 400;
	price[4] = 1000;

	buttonTexture[0].loadFromFile("img/tower0_50x50.png");
	buttonTexture[1].loadFromFile("img/tower1_50x50.png");
	buttonTexture[2].loadFromFile("img/tower2_50x50.png");
	buttonTexture[3].loadFromFile("img/tower3_50x50.png");
	buttonTexture[4].loadFromFile("img/moneyTower0_50x50.png");


	buttonSpr[0].setTexture(buttonTexture[0]);
	buttonSpr[1].setTexture(buttonTexture[1]);
	buttonSpr[2].setTexture(buttonTexture[2]);
	buttonSpr[3].setTexture(buttonTexture[3]);
	buttonSpr[4].setTexture(buttonTexture[4]);

	buttonSpr[0].setPosition(Vector2f(1775, 15)); //Position der Buttons
	buttonSpr[1].setPosition(Vector2f(1850, 15));
	buttonSpr[2].setPosition(Vector2f(1775, 100));
	buttonSpr[3].setPosition(Vector2f(1850, 100));
	buttonSpr[4].setPosition(Vector2f(1775, 185));

	backround = RectangleShape();
	backround.setFillColor(Color::Blue);
	backround.setPosition(1750, 0);
	backround.setSize(Vector2f(200, 991));
}

Sidebar* Sidebar::getInstance(Map* _map)
{
	if (instance == nullptr)
	{
		instance = new Sidebar();
		instance->p_map = _map;
	}
	return instance;
}

int Sidebar::isClicked(sf::RenderWindow* window)
{
	if (Mouse::isButtonPressed(Mouse::Button::Left)) //Ob die linke Maustaste gedrückt wurde
	{
		Vector2i mouse = Mouse::getPosition(*window);
		Vector2f pos,pos2;

		for (int i = 0; i < 5; i++) //Geht alle Türme durch
		{
			pos = Service::getInstance()->getObjectPosition(Vector2f(1920, 991), buttonSpr[i].getPosition()); //Holt sich die Position des Turmes i
			pos2 = Service::getInstance()->getObjectPosition(Vector2f(1920, 991), buttonSpr[i].getPosition() + Vector2f(50,50)); //Holt sich die Position des Turmes i + 50 wegen der Größe

			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
			{
				if (Round::getInstance()->submoney(price[i])) //Wenn genug Geld vorhanden ist, wird es vom Geldstand abgezogen
				{
					return i;
				}
			}
		}
	}

	return -1;
}

void Sidebar::draw(sf::RenderWindow* window)
{
	window->draw(backround);
	for (int i = 0; i < 5; i++)
	{
		window->draw(buttonSpr[i]);
	}
}
