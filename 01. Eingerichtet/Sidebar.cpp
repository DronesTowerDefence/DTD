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

	buttonTexture[0].loadFromFile("img/tower0/tower0_preview.png");
	buttonTexture[1].loadFromFile("img/tower1/tower1_preview.png");
	buttonTexture[2].loadFromFile("img/tower2/tower2_preview.png");
	buttonTexture[3].loadFromFile("img/tower3/tower3_preview.png");
	buttonTexture[4].loadFromFile("img/tower4/tower4_preview.png");


	buttonTextFont.loadFromFile("fonts/arial.ttf");

	for (int i = 0; i < 5; i++)
	{
	buttonSpr[i].setTexture(buttonTexture[i]);
		buttonText[i].setFont(buttonTextFont);
		buttonText[i].setCharacterSize(20);
		buttonText[i].setFillColor(Color::White);
		buttonText[i].setOutlineColor(Color::Black);
		buttonText[i].setOutlineThickness(2);
	}

	buttonText[0].setString("Turm 1\n100G");
	buttonText[1].setString("Turm 2\n200G");
	buttonText[2].setString("Turm 3\n300G");
	buttonText[3].setString("Turm 4\n400G");
	buttonText[4].setString("Ölbohrer\n1000G");

	//std::cout << "Sidebar::Sidebar: \224"; //224

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

Sidebar* Sidebar::getInstance(/*Map* _map*/)
{
	if (instance == nullptr)
	{
		instance = new Sidebar();
		//instance->p_map = _map;
	}
	return instance;
}

int Sidebar::isClicked(sf::RenderWindow* window)
{
	if (Mouse::isButtonPressed(Mouse::Button::Left)) //Ob die linke Maustaste gedrückt wurde
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