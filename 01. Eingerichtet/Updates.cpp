#include "Ressources.h"
#include "Updates.h"
#include "Game.h"

#pragma region Konstruktor
Updates::Updates(Tower* tower)
{

	res = Ressources::getInstance();
	this->tower = tower;
	index1 = 0;
	index2 = 0;
	isClosed1 = false;
	isClosed2 = false;
	close = new Sprite();
	update1 = new Sprite();
	update2 = new Sprite();
	sell = new Sprite();
	information1 = new Sprite();
	information2 = new Sprite();
	informationTexture = new Texture();
	background = new Sprite();
	backgroundTexture = new Texture();
	textureUpdate1 = new Texture();
	textureUpdate2 = new Texture();
	textureclose = new Texture();
	textureSell = new Texture();
	if (tower->getIndex() == 6) {
		rArrow = new Sprite();
		lArrow = new Sprite();
		texRArrow = new Texture();
		texLArrow = new Texture();
		texRArrow->loadFromFile("img/tower6/R.png");
		texLArrow->loadFromFile("img/tower6/L.png");
		rArrow->setTexture(*texRArrow);
		lArrow->setTexture(*texLArrow);
		rArrow->setPosition(Vector2f(1745, 600));
		lArrow->setPosition(Vector2f(1745, 720));
	}

	textureUpdate1NoBuy = new Texture();
	textureUpdate2NoBuy = new Texture();
	backgroundTexture->loadFromFile("img/sendMoneyBackground.png");
	informationTexture->loadFromFile("img/buttons/infoButton.png");

	if (tower->getIndex() == 4)
	{
		textureUpdate1 = res->getUpdateTexture(0);
		textureUpdate2 = res->getUpdateTexture(1);
		textureUpdate1NoBuy = res->getUpdateNoBuyTexture(0);
		textureUpdate2NoBuy = res->getUpdateNoBuyTexture(1);
	}
	else if (tower->getIndex() == 3)
	{
		textureUpdate1 = res->getUpdateTexture(4);
		textureUpdate2 = res->getUpdateTexture(3);
		textureUpdate1NoBuy = res->getUpdateNoBuyTexture(4);
		textureUpdate2NoBuy = res->getUpdateNoBuyTexture(3);
	}
	else
	{
		textureUpdate1 = res->getUpdateTexture(2);
		textureUpdate2 = res->getUpdateTexture(3);
		textureUpdate1NoBuy = res->getUpdateNoBuyTexture(2);
		textureUpdate2NoBuy = res->getUpdateNoBuyTexture(3);
	}

	textureclose = res->getButtonCloseTexture();
	textureSell = res->getButtonSellTexture();

	if (Account::getAccName() != tower->getOwnerName())
	{
		textureUpdate1->loadFromImage(textureUpdate1NoBuy->copyToImage());
		textureUpdate2->loadFromImage(textureUpdate2NoBuy->copyToImage());
	}

	update1->setTexture(*textureUpdate1);
	update2->setTexture(*textureUpdate2);

	close->setTexture(*textureclose);
	sell->setTexture(*textureSell);
	information1->setTexture(*informationTexture);
	information2->setTexture(*informationTexture);
	background->setTexture(*backgroundTexture);

	update1->setPosition(Vector2f(1745, 300));
	update2->setPosition(Vector2f(1745, 450));
	close->setPosition(Vector2f(1850, 25));
	sell->setPosition(Vector2f(1745, 25));
	information1->setPosition(Vector2f(1850, 300));
	information2->setPosition(Vector2f(1850, 450));
	background->setPosition(Vector2f(1395, 250));

	close->setScale(Vector2f(0.5, 0.5));


	for (int i = 0, x = 1745; i < 4; i++, x += 15)
	{
		shoowUpdate1[i] = new RectangleShape(Vector2f(10, 10));
		shoowUpdate2[i] = new RectangleShape(Vector2f(10, 10));

		shoowUpdate1[i]->setPosition(x, 280);
		shoowUpdate2[i]->setPosition(x, 430);
		shoowUpdate1[i]->setFillColor(Color::Green);
		shoowUpdate2[i]->setFillColor(Color::Green);
	}
	arial.loadFromFile("fonts/arial.ttf");
	text1 = new Text();
	text2 = new Text();
	price = new Text();
	TowerDamageCount = new Text();
	informationtext = new Text();
	if (index1 == 4)
	{
		text1->setString("CLOSE");
	}
	else
	{
		text1->setString(std::to_string(Ressources::getInstance()->getTowerUpgradesPrice1(tower->getIndex(), index1)) + " $");
	}

	if (index2 == 4)
	{
		text2->setString("CLOSE");
	}
	else
	{
		text2->setString(std::to_string(Ressources::getInstance()->getTowerUpgradesPrice2(tower->getIndex(), index2)) + " $");
	}
	price->setString(std::to_string((int)(tower->getValue() * 0.75f)) + " $");

	towerOwnerText = new Text();
	towerOwnerText->setFont(arial);
	towerOwnerText->setCharacterSize(25);
	towerOwnerText->setFillColor(Color::White);
	towerOwnerText->setOutlineColor(Color::Black);
	towerOwnerText->setOutlineThickness(2);
	towerOwnerText->setString("Besitzer:\n" + tower->getOwnerName());
	towerOwnerText->setPosition(1745, 180);

	text1->setPosition(1745, 400);
	text2->setPosition(1745, 550);
	price->setPosition(1745, 100);
	informationtext->setPosition(Vector2f(1435, 300));

	informationtext->setFont(arial);
	text1->setFont(arial);
	text2->setFont(arial);
	price->setFont(arial);

	TowerDamageCount->setPosition(1745, 150);
	TowerDamageCount->setFont(arial);
	TowerDamageCount->setCharacterSize(25);
	TowerDamageCount->setFillColor(Color::White);
	TowerDamageCount->setOutlineColor(Color::Black);
	TowerDamageCount->setOutlineThickness(2);



	informationtext->setCharacterSize(20);
	text1->setCharacterSize(20);
	text2->setCharacterSize(20);
	price->setCharacterSize(20);

	text1->setOutlineThickness(2);
	price->setOutlineThickness(2);
	text2->setOutlineThickness(2);
	informationtext->setOutlineThickness(2);

	text1->setOutlineColor(Color::Black);
	text2->setOutlineColor(Color::Black);
	price->setOutlineColor(Color::Black);
	informationtext->setOutlineColor(Color::Black);

}
#pragma endregion

#pragma region Funktionen
void Updates::draw(RenderWindow* window)
{
	window->draw(*update1);
	window->draw(*update2);
	window->draw(*close);
	window->draw(*text1);
	window->draw(*text2);
	window->draw(*sell);
	window->draw(*price);
	window->draw(*towerOwnerText);
	TowerDamageCount->setString("Schaden:" + std::to_string(tower->getDamageCount()));
	window->draw(*TowerDamageCount);
	for (int i = 0; i < 4; i++)
	{
		if (index1 > i)
			window->draw(*shoowUpdate1[i]);
		if (index2 > i)
			window->draw(*shoowUpdate2[i]);
	}
	if (showinformation)
	{
		window->draw(*background);
		window->draw(*informationtext);
	}
	window->draw(*information1);
	window->draw(*information2);
	if (tower->getIndex() == 6) {
		window->draw(*rArrow);
		window->draw(*lArrow);
	}

}
void Updates::hover(RenderWindow* window)
{
	Vector2i mouse = Mouse::getPosition(*window);
	Vector2f pos, pos2;

	pos = Service::getInstance()->getObjectPosition(information1->getPosition());
	pos2 = Service::getInstance()->getObjectPosition(information1->getPosition() + Vector2f(100, 100));

	if (index1 < 4 && (mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
	{
		std::string test = Ressources::getInstance()->getUpdateBeschreibungEins(tower->getIndex(), index1);
		informationtext->setString(Ressources::getInstance()->getUpdateBeschreibungEins(tower->getIndex(), index1));
		showinformation = true;
	}

	else
	{

		pos = Service::getInstance()->getObjectPosition(information2->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(information2->getPosition() + Vector2f(100, 100));

		if (index1 < 4 && (mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{

			informationtext->setString(Ressources::getInstance()->getUpdateBeschreibungZwei(tower->getIndex(), index2));
			showinformation = true;
		}
		else
		{
			showinformation = false;
		}
	}
}
int Updates::isClicked(RenderWindow* window, Tower* tow)
{
	if (!window->hasFocus())
		return 0;

	Vector2i mouse = Mouse::getPosition(*window);
	Vector2f pos, pos2;



	if (tower->getOwnerName() == Account::getAcc()->getAccName())
	{
		pos = Service::getInstance()->getObjectPosition(update1->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(update1->getPosition() + Vector2f(100, 100));

		if (index1 < 4 && (mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			tow->Update1();
		}
		else
		{
			pos = Service::getInstance()->getObjectPosition(update2->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(update2->getPosition() + Vector2f(100, 100));

			if (index2 < 4 && (mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				tow->Update2();
			}
		}
		if (tower->getIndex() == 6) {
			pos = Service::getInstance()->getObjectPosition(rArrow->getPosition()); 
			pos2 = Service::getInstance()->getObjectPosition(rArrow->getPosition() + Vector2f(100, 100));
			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) {
				tower->addRotCount();
			}
			else {
				pos = Service::getInstance()->getObjectPosition(lArrow->getPosition());
				pos2 = Service::getInstance()->getObjectPosition(lArrow->getPosition() + Vector2f(100, 100));
				if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) {
					tower->subRotCount();
				}
			}

		}
	}

	return -1;
}
bool Updates::IsClosed(RenderWindow* window)
{

	Vector2i mouse = Mouse::getPosition(*window);
	Vector2f	pos = Service::getInstance()->getObjectPosition(close->getPosition());
	Vector2f	pos2 = Service::getInstance()->getObjectPosition(close->getPosition() + Vector2f(50, 50));

	if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool Updates::isSell(RenderWindow* window)
{
	Vector2i mouse = Mouse::getPosition(*window);
	Vector2f pos = Service::getInstance()->getObjectPosition(sell->getPosition());
	Vector2f pos2 = Service::getInstance()->getObjectPosition(sell->getPosition() + Vector2f(50, 50));

	if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Updates::canBuy()
{
	if (Ressources::getInstance()->getTowerUpgradesPrice1(tower->getIndex(), index1) > Round::getInstance()->getMoney())
	{
		update1->setTexture(*textureUpdate1NoBuy);
	}
	else
	{
		update1->setTexture(*textureUpdate1);
	}
	if (Ressources::getInstance()->getTowerUpgradesPrice2(tower->getIndex(), index2) > Round::getInstance()->getMoney())
	{
		update2->setTexture(*textureUpdate2NoBuy);
	}
	else
	{
		update2->setTexture(*textureUpdate2);
	}
}
void Updates::setStringPrice()
{
	price->setString(std::to_string((int)(tower->getValue() * 0.75f)) + " $");
}
#pragma endregion

#pragma region getter
int Updates::getIndex1()
{
	return index1;
}
int Updates::getIndex2()
{
	return index2;
}
bool Updates::getIsClosed1()
{
	return isClosed1;
}
bool Updates::getIsClosed2()
{
	return isClosed2;
}
#pragma endregion

#pragma region setter
void Updates::setIndex1(int index)
{
	index1 = index;
}
void Updates::setIndex2(int index)
{
	index2 = index;
}
void Updates::setIsClosed1(bool a)
{
	isClosed1 = a;
}
void Updates::setIsClosed2(bool a)
{
	isClosed2 = a;
}
void Updates::setText1(std::string text)
{
	text1->setString(text);
}
void Updates::setText2(std::string text)
{
	text2->setString(text);
}
void Updates::addIndex1()
{
	index1++;
}
void Updates::addIndex2()
{
	index2++;
}
#pragma endregion

#pragma region Desturktor

#pragma endregion