#include "Updates.h"
#include "Round.h"

Updates::Updates()
{
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
	closedClicked = false;
}

void Updates::draw(RenderWindow* window)
{
	window->draw(*update1);
	window->draw(*update2);
	window->draw(*close);
}

int Updates::isClicked(RenderWindow* window, float price1, float price2)
{
	if (Mouse::Button(Mouse::Button::Left)) //Ob die linke Maustaste gedrückt wurde
	{
		Vector2i mouse = Mouse::getPosition(*window);
		Vector2f pos, pos2;

		pos = Service::getInstance()->getObjectPosition(update1->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(update1->getPosition() + Vector2f(150, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			if (Round::getInstance()->getMoney() >= price1)
			{
				index1++;
				return 1;
			}

		}
		else
		{
			pos = Service::getInstance()->getObjectPosition(update2->getPosition()); //Holt sich die Position des Turmes i
			pos2 = Service::getInstance()->getObjectPosition(update2->getPosition() + Vector2f(150, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
			{
				if (Round::getInstance()->getMoney() >= price2)
				{
					index2++;
					return 2;
				}
			}
		}
	}


	return -1;
}

bool Updates::IsCloses(RenderWindow* window)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		closedClicked = true;
	}
	else if (closedClicked && !Mouse::isButtonPressed(Mouse::Left)) // verhindert das Plazieren eines Turmes beim Clicken
	{
		closedClicked = false;
		Vector2i mouse = Mouse::getPosition(*window);
		Vector2f	pos = Service::getInstance()->getObjectPosition(close->getPosition()); //Holt sich die Position des Turmes i
		Vector2f	pos2 = Service::getInstance()->getObjectPosition(close->getPosition() + Vector2f(50, 50)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			return true;
		}
	}
	return false;

}
int Updates::getIndex1()
{
	return index1;
}

int Updates::getIndex2()
{
	return index2;
}
