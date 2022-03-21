#include "Game.h"

void Game::newRound()
{

}

void Game::moveDrohnes()
{
	for (Drone* p : base->getAllDrones())
	{
		map->chekChangeDirection(p);
		p->move();
	}


}

void Game::checkButtonClick()
{
	int index = sidebar->isCklickes(window);
	if (index > -1)
	{
		newTower = new TowerAlias(index);
	}
}
void Game::checkTowerAlias()
{
	if (newTower == nullptr)
	{
		checkButtonClick();
	}
	else
	{
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			newTower->setPositionMouse(Mouse::getPosition(*window));
		}
		else
		{
			newTower->CreateNewTower();
			delete newTower;
			newTower = nullptr;
		}
	}
}
Game::Game(RenderWindow* window)
{
	base = Base::getInstance();
	sidebar = Sidebar::getInstance();
	map = new Map();
	newTower = nullptr;
	this->window = window;
	texture = new Texture();
	texture->loadFromFile("img/Map1.png");
	background = new RectangleShape(Vector2f(1920, 991));
	background->setTexture(texture);
}
void Game::draw()
{
	window->clear();
	window->draw(*background);
	sidebar->draw(window);
	if (newTower != nullptr)
	{
		newTower->draw(window);

	}
	for (Tower* t : base->getAllTowers())
	{
		window->draw(t->getTowerSpr());
	}
	for (Drone* d : base->getAllDrones())
	{
		window->draw(d->getDroneSprite());
	}
	window->display();
}

void Game::startGame()
{
	while (window->isOpen())
	{
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

		}
		checkTowerAlias();
		moveDrohnes();
		draw();
	}

	//}
}
