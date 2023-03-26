#include "Sidebar.h"
#include "Round.h"
#include "Game.h"
#include <iostream>

Sidebar* Sidebar::instance = nullptr;

#pragma region Konstruktor
Sidebar::Sidebar()
{
	res = Ressources::getInstance();

	buttonTextFont.loadFromFile("fonts/arial.ttf");

	for (int i = 0; i < Ressources::getInstance()->getTowerCount(); i++)
	{
		price[i] = Ressources::getInstance()->getTowerPrice(i);

		buttonSpr[i] = new Button(Vector2f(1762, 105 * i + 15), res->getTowerPreviewTexture(i));

		buttonText[i].setString(Ressources::getInstance()->getTowerName(i) + "\n" + std::to_string(int(price[i])) + " $");
		buttonText[i].setFont(buttonTextFont);
		buttonText[i].setCharacterSize(20);
		buttonText[i].setFillColor(Color::White);
		buttonText[i].setOutlineColor(Color::Black);
		buttonText[i].setOutlineThickness(2);
	}

	buttonText[0].setPosition(Vector2f(1757, 65)); //Position des Button-Textes
	buttonText[1].setPosition(Vector2f(1757, 170));
	buttonText[2].setPosition(Vector2f(1757, 275));
	buttonText[3].setPosition(Vector2f(1757, 380));
	buttonText[4].setPosition(Vector2f(1757, 485));
	buttonText[5].setPosition(Vector2f(1757, 590));
	buttonText[6].setPosition(Vector2f(1757, 695));


	//buttonSpr[0].setPosition(Vector2f(1762, 15)); //Position der Buttons
	//buttonSpr[1].setPosition(Vector2f(1762, 120));
	//buttonSpr[2].setPosition(Vector2f(1762, 225));
	//buttonSpr[3].setPosition(Vector2f(1762, 330));
	//buttonSpr[4].setPosition(Vector2f(1762, 435));
	//buttonSpr[5].setPosition(Vector2f(1762, 540));
	//buttonSpr[6].setPosition(Vector2f(1762, 645));

	doubleSpeed = new Button(Vector2f(1757, 800), res->getButtonSpeedTexture());
}

#pragma endregion

#pragma region Funktionen
void Sidebar::checkHover(RenderWindow* window)
{
	Vector2i mouse = Mouse::getPosition(*window);

	doubleSpeed->checkHover(mouse);
	for (int i = 0; i < towerCount; i++)
	{
		buttonSpr[i]->checkHover(mouse);
	}
}
bool Sidebar::isChangeSpeed(RenderWindow* window)
{
	Vector2i mouse = Mouse::getPosition(*window);

	if (doubleSpeed->checkHover(mouse))
	{
		return true;
	}
	return false;
}
int Sidebar::isClicked(sf::RenderWindow* window)
{
	if (!window->hasFocus())
		return 0;

	Vector2i mouse = Mouse::getPosition(*window);

	for (int i = 0; i < towerCount; i++) //Geht alle Türme durch
	{
		if (buttonSpr[i]->checkHover(mouse))
		{
			if (Round::getInstance()->submoney(price[i])
				&& ((HomeMenu::getInstance()->getDaily()->getIsDaily() && HomeMenu::getInstance()->getDaily()->getIsTowerAllowed(i)) || !HomeMenu::getInstance()->getDaily()->getIsDaily()))
				//Wenn genug Geld vorhanden ist, wird es vom Geldstand abgezogen
			{
				return i;
			}
		}
	}

	return -1;
}
void Sidebar::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < towerCount; i++)
	{
		if (Round::getInstance()->getMoney() >= Ressources::getInstance()->getTowerPrice(i) &&
			((HomeMenu::getInstance()->getDaily()->getIsDaily() && HomeMenu::getInstance()->getDaily()->getIsTowerAllowed(i)) || !HomeMenu::getInstance()->getDaily()->getIsDaily()))
		{

			buttonSpr[i]->setTexture(res->getTowerPreviewTexture(i));
		}
		else
		{
			buttonSpr[i]->setTexture(res->getTowerNoBuyTexture(i));

		}
		window->draw(*buttonSpr[i]);
		window->draw(buttonText[i]);
	}
	window->draw(*doubleSpeed);

}
void Sidebar::setSpeedButton(bool speed)
{
	if (speed)
	{
		doubleSpeed->setTexture(Ressources::getInstance()->getButtonSpeedTexturePressed());
	}
	else
	{
		doubleSpeed->setTexture(Ressources::getInstance()->getButtonSpeedTexture());
	}
}
#pragma endregion
#pragma region getter
Sidebar* Sidebar::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Sidebar();
	}
	return instance;
}
#pragma endregion

#pragma region setter

#pragma endregion


#pragma region Desturktor
Sidebar::~Sidebar()
{
	instance = nullptr;
}
#pragma endregion