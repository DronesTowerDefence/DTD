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
			if (towers[i]->isClicked(mouse))
			{
				return i;
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
	towers[0] = new Button(Vector2f(50, 50), Vector2f(1775, 15), "img/drone0_40x40.png");
	towers[1] = new Button(Vector2f(50, 50), Vector2f(1850, 15), "img/drone0_40x40.png");
	towers[2] = new Button(Vector2f(50, 50), Vector2f(1775, 100), "img/drone0_40x40.png");
	towers[3] = new Button(Vector2f(50, 50), Vector2f(1850, 100), "img/drone0_40x40.png");

	backround = RectangleShape();
	backround.setFillColor(Color::Yellow);
	backround.setPosition(1750, 0);
	backround.setSize(Vector2f(200, 991));
}
