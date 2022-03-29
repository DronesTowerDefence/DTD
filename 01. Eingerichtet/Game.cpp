#include "Game.h"

Game* Game::instance = nullptr;

Game* Game::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Game;
	}
	return instance;
}

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

	for (Projectile* i : round->getAllProjectiles())
	{
		i->moveProjectile();
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
Game::Game()
{	
	stdFont.loadFromFile("fonts/arial.ttf");
	eco.setFont(stdFont);
	round = Round::getInstance();
	sidebar = Sidebar::getInstance();
	map = new Map();
	newTower = nullptr;
	texture = new Texture();
	texture->loadFromFile("img/Map1.png");
	background = new RectangleShape(Vector2f(1920, 991));
	background->setTexture(texture);
	
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
	for (auto* t : round->getAllTowers())
	{
		window->draw(t->getTowerSpr());
	}
	for (auto* t : round->getAllTowers())
	{
		window->draw(*(t->getRangeShape()));
	}
	for (auto* t : round->getAllProjectiles())
	{
		window->draw(*(t->getProjectileSprite()));
	}
	for (auto* d : round->getAllDrones())
	{
		window->draw(d->getDroneSprite());
		if (d->getPosition().y > 991 && d->getNextPoint() >= 9){

			round->subhealth(d->getLives());

		}
	}
	
	

	if (round->getDroneTimer().getElapsedTime().asSeconds() > 3.0) {

		round->addDrone(new Drone(1, map->getStart(), 0, -1));
		round->restartDroneTimer();
	}

	if (round->getLost() == true) {
		eco.setFillColor(Color::Red);
		eco.setPosition(500, 340);
		eco.setCharacterSize(240);
		eco.setString("YOU LOSE");
		window->draw(eco);
		window->display();
		return;

	}

	eco.setString("Lives: " + std::to_string(round->getHealth()) + "\nMoney: " + std::to_string(round->getMoney()));
	window->draw(eco);	
	
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
		checkShoot();
		checkTowerAlias();
		moveDrohnes();
		draw();
	}

	//}
}

Font Game::getFont()
{
	return stdFont;
}

RenderWindow* Game::getWindow()
{
	return window;
}

void Game::setWindow(RenderWindow* _window)
{
	window = _window;
}

void Game::checkShoot()
{
	for (auto t : Round::getInstance()->getAllTowers())
	{
		for (auto d : Round::getInstance()->getAllDrones())
		{
			if (t->getRangeShape()->getGlobalBounds().intersects(d->getDroneSprite().getGlobalBounds()))
			{
				t->shoot(d);
			}
		}
	}
}