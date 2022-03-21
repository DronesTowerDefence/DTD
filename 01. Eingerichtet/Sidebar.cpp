#include "Sidebar.h"

Sidebar* Sidebar::instance = nullptr;
Sidebar* Sidebar::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Sidebar();
	}
	return instance;
}
int Sidebar::isCklickes(sf::RenderWindow* window)
{
	Vector2i mouse;

	mouse = Mouse::getPosition(*window);
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		for (int i = 0; i < 4; i++)
		{
			if (Base::getInstance()->getMoney()>=towers[i]->getPrice() && towers[i]->isClicked(mouse))
			{
				return i;
				Base::getInstance()->submoney(towers[i]->getPrice());
			}
		}
	}
	return -1;
}

void Sidebar::draw(sf::RenderWindow* window)
{
	window->draw(backround);
	for (int i = 0; i < 4; i++)
	{
		window->draw(towers[i]->getSprite());
	}
}

Sidebar::Sidebar()
{
	towers[0] = new BuyTower(100 , Vector2f(50, 50), Vector2f(1775, 15), "img/drone0_40x40.png");
	towers[1] = new BuyTower(200,Vector2f(50, 50), Vector2f(1850, 15), "img/drone0_40x40.png");
	towers[2] = new BuyTower(300,Vector2f(50, 50), Vector2f(1775, 100), "img/drone0_40x40.png");
	towers[3] = new BuyTower(400,Vector2f(50, 50), Vector2f(1850, 100), "img/drone0_40x40.png");

	backround = RectangleShape();
	backround.setFillColor(Color::Yellow);
	backround.setPosition(1750, 0);
	backround.setSize(Vector2f(200, 991));
}
