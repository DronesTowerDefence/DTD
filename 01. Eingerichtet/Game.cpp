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
	}
}
Game::Game()
{
	base = Base::getInstance();
	sidebar = Sidebar::getInstance();
	map = new Map();
	newTower = nullptr;
}
void Game::draw()
{
	if (newTower != nullptr)
	{
		newTower->draw(window);
		for (Tower* t : base->getAllTowers())
		{
			window->draw(t->getTowerSpr());
		}
		for (Drone* d : base->getAllDrones())
		{
			window->draw(d->getDroneSprite());
		}
	}
}

void Game::startGame()
{

	while (window->isOpen())
	{
		moveDrohnes();
		checkTowerAlias();

	}
}
