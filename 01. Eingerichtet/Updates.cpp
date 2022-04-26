#include "Updates.h"
#include "Round.h"

Updates::Updates(int towerIndex)
{
	this->towerIndex = towerIndex;
	index1 = 0;
	index2 = 0;
	close = new Sprite();
	update1 = new Sprite();
	update2 = new Sprite();
	textureUpdate1 = new Texture();
	textureUpdate2 = new Texture();
	textureclose = new Texture();
	textureUpdate1->loadFromFile("img/update.png");
	textureUpdate2->loadFromFile("img/update.png");
	textureclose->loadFromFile("img/close.png");
	update1->setPosition(Vector2f(1745, 100));
	update2->setPosition(Vector2f(1745, 250));
	close->setPosition(Vector2f(1850, 25));
	update1->setTexture(*textureUpdate1);
	update2->setTexture(*textureUpdate2);
	close->setTexture(*textureclose);
	for (int i = 0, x = 1745; i < 4; i++, x += 15)
	{
		shoowUpdate1[i] = new RectangleShape(Vector2f(10, 10));
		shoowUpdate2[i] = new RectangleShape(Vector2f(10, 10));

		shoowUpdate1[i]->setPosition(x, 80);
		shoowUpdate2[i]->setPosition(x, 230);
		shoowUpdate1[i]->setFillColor(Color::Green);
		shoowUpdate2[i]->setFillColor(Color::Green);
	}
	arial.loadFromFile("fonts/arial.ttf");
	text1 = new Text();
	text2 = new Text();
	text1->setString(std::to_string(Ressources::getInstance()->getTowerUpgradesPrice1(towerIndex, index1))); //TODO updatepeis
	text2->setString(std::to_string(Ressources::getInstance()->getTowerUpgradesPrice2(towerIndex, index2))); //TODO updatepeis

	text1->setPosition(1745, 100);
	text2->setPosition(1745, 250);

	text1->setFont(arial);
	text2->setFont(arial);

	text1->setCharacterSize(20);
	text2->setCharacterSize(20);

}

void Updates::draw(RenderWindow* window)
{
	window->draw(*update1);
	window->draw(*update2);
	window->draw(*close);
	window->draw(*text1);
	window->draw(*text2);
	for (int i = 0; i < 4; i++)
	{
		if (index1 > i)
			window->draw(*shoowUpdate1[i]);
		if (index2 > i)
			window->draw(*shoowUpdate2[i]);
	}

}

int Updates::isClicked(RenderWindow* window, float price1, float price2)
{
	Vector2i mouse = Mouse::getPosition(*window);
	Vector2f pos, pos2;

	pos = Service::getInstance()->getObjectPosition(update1->getPosition()); //Holt sich die Position des Turmes i
	pos2 = Service::getInstance()->getObjectPosition(update1->getPosition() + Vector2f(150, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

	if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
	{
		if (Round::getInstance()->submoney(price1))
		{
			index1++;
			text1->setString(std::to_string(Ressources::getInstance()->getTowerUpgradesPrice1(towerIndex, index1))); //TODO updatepeis

			return 1;
		}

	}
	else
	{
		pos = Service::getInstance()->getObjectPosition(update2->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(update2->getPosition() + Vector2f(150, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			if (Round::getInstance()->submoney(price2))
			{
				index2++;
				text2->setString(std::to_string(Ressources::getInstance()->getTowerUpgradesPrice2(towerIndex, index2))); //TODO updatepeis
				return 2;
			}
		}
	}

	return -1;
}

bool Updates::IsCloses(RenderWindow* window)
{

	Vector2i mouse = Mouse::getPosition(*window);
	Vector2f	pos = Service::getInstance()->getObjectPosition(close->getPosition()); //Holt sich die Position des Turmes i
	Vector2f	pos2 = Service::getInstance()->getObjectPosition(close->getPosition() + Vector2f(50, 50)); //Holt sich die Position des Turmes i + 50 wegen der Größe

	if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
	{
		return true;
	}
	else
	{
		return false;
	}

}
int Updates::getIndex1()
{
	return index1;
}

int Updates::getIndex2()
{
	return index2;
}
