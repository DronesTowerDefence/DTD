#include "Game.h"

void Game::newRound()
{
	
}

void Game::moveDrohnes()
{
	for (Drone*   p :  drones)
	{
		map->chekChangeDirection(p);
		p->move();
	}
}

void Game::checkButtonClick()
{
}

Game::Game()
{
	base = Base::getInstance();
	sidebar = Sidebar::getInstance();
	map = new Map();
}

void Game::startGame()
{

	while (window->isOpen())
	{
		moveDrohnes();

	}
}
