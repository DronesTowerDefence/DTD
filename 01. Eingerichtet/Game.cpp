#include "Game.h"

void Game::newRound()
{

}

void Game::moveDrohnes()
{
	for (Drone* p : round->getAllDrones())
	{
		map->checkChangeDirection(p);
		p->move();
	}


}

void Game::checkButtonClick()
{
	int index = sidebar->isCklickes(window);
	if (index > -1)
	{
		newTower = new TowerAlias(index, map);
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
	round = Round::getInstance();
	sidebar = Sidebar::getInstance();
	map = new Map();
	newTower = nullptr;
	this->window = window;
	texture = new Texture();
	texture->loadFromFile("img/Map1.png");
	background = new RectangleShape(Vector2f(1920, 991));
	background->setTexture(texture);
	stdFont.loadFromFile("fonts/arial.ttf");
	eco.setFont(stdFont);
	eco.setCharacterSize(30);
	eco.setPosition(20, 20);
}
void Game::draw()
{
	window->clear();
	window->draw(*background);
	sidebar->draw(window);
	if (newTower != nullptr)
	{
		window->draw((*newTower->getSprite()));
	}
	for (Tower* t : round->getAllTowers())
	{
		window->draw(t->getTowerSpr());
	}
	for (Drone* d : round->getAllDrones())
	{
		window->draw(d->getDroneSprite());
		if (d->getPosition().y > 991){

			round->subhealth(1);

		}
	}
	
	eco.setString("Lives: " + std::to_string(round->getHealth()) + "\nMoney: " + std::to_string(round->getMoney()));
	window->draw(eco);

	if (round->getDroneTimer().getElapsedTime().asSeconds() > 3.0) {

		round->addDrone(new Drone(1, map->getStart(), 0, -1));
		round->restartDroneTimer();
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