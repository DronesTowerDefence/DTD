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

Game::Game()
{
	stdFont.loadFromFile("fonts/arial.ttf");
	eco.setFont(stdFont);
	map = new Map();
	round = Round::getInstance();
	sidebar = Sidebar::getInstance(/*map*/);
	newTower = nullptr;
	texture = new Texture();
	texture->loadFromFile("img/Map1.png");
	background = new RectangleShape(Vector2f(1920, 991));
	background->setTexture(texture);
	round->setAllCoverablePoints();

	droneCount = 0;

	lost = false;
	eco.setCharacterSize(30);
	eco.setPosition(20, 20);
}

void Game::draw()
{
	window->clear();

	window->draw(*background); //Karte wird gedrawt

	sidebar->draw(window); //Sidebar wird gedrawt

	if (newTower != nullptr) //TowerAlias wird gedrawt
	{
		window->draw((*newTower->getSpr()));
		window->draw((*newTower->getRangeShape()));
	}

	window->draw(collisionShape);

	for (auto* t : round->getAllMoneyTower()) //Geldgenerations Tower werden gedrawt
	{
		window->draw(t->getTowerSpr());
	}

	for (auto* t : round->getAllAttackTower()) //Tower werden gedrawt
	{
		window->draw(t->getTowerSpr());
	}

	for (auto* t : round->getAllAttackTower()) //Tower Range wird gedrawt
	{
		window->draw(*(t->getRangeShape()));
	}

	for (auto* t : round->getAllProjectiles()) //Projectiles werden gedrawt
	{
		if(t->getcollided() == 0)
			window->draw(*(t->getProjectileSprite()));
		
	}

	for (auto* d : round->getAllDrones()) //Drones werden gedrawt
	{
		if (d->getAlive() == false) {
			continue;
		}
		window->draw(d->getDroneSprite());
	}

	if (round->getDroneTimer().getElapsedTime().asSeconds() > 2.0 && droneCount < round->getDroneCountInRound(round->getRound())) {

		droneCount++;
		round->addDrone(new Drone(1, map->getStart(), 0, -1));
		round->restartDroneTimer();
	}
	if (droneCount == round->getDroneCountInRound(round->getRound()) && round->getAllDrones().empty())
	{
		newRound();
	}

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
		loseGame();
		checkShoot();
		moveDrohnes();
		checkTowerAlias();
		generateMoneyTowers();
		draw();
	}
}

void Game::newRound()
{
	droneCount = 0;
	round->addRound();
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
		i->colission();
	}

}

void Game::checkButtonClick()
{
	int index = sidebar->isClicked(window);
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
			newTower->setPositionMouse(Mouse::getPosition(*window)); //Bewegt den TowerAlias an die Position der Maus
		}
		else if (towerAliasForbiddenPosition())
		{
			newTower->CreateNewTower(); //TowerAlias erstellt einen neuen Tower an der eigenen Position
			delete newTower;
			newTower = nullptr;
		}
	}
}

void Game::generateMoneyTowers()
{
	for (auto i : Round::getInstance()->getAllMoneyTower())
	{
		i->generateMoney();
	}
}

void Game::loseGame()
{
	if (round->getDroneSubHealthTimer().getElapsedTime().asSeconds() > 1)
	{
		for (auto i : round->getAllDrones())
		{
			if (i->getPosition().y > 991 && i->getNextPoint() >= 9) {
				if (i->getAlive() == true) {
					round->subhealth(i->getLives());
					i->setAlive(false);
				}
			}
		}
		round->restartDroneSubHealthTimer();
	}

	if (round->getLost())
	{
		eco.setFillColor(Color::Red);
		eco.setOutlineColor(Color::Black);
		eco.setOutlineThickness(5);
		eco.setPosition(350, 340);
		eco.setCharacterSize(240);
		eco.setString("YOU LOSE");
		lost = true;
	}
	else
	{
		eco.setString("Lives: " + std::to_string(round->getHealth()) +
			"\nMoney: " + std::to_string(round->getMoney()) +
			"\nRound: " + std::to_string(round->getRound() + 1));
	}
}

bool Game::towerAliasForbiddenPosition()
{
	if (newTower->getPos().x < 1700 && Mouse::getPosition(*window).x < 1700)
	{
		collisionShape.setFillColor(Color::Transparent);
		collisionShape.setRadius(20);
		for (auto i : round->getAllCoverablePoints())
		{
			collisionShape.setPosition(i);
			if (newTower->getSpr()->getGlobalBounds().intersects(collisionShape.getGlobalBounds()))
				return 0;
		}
	}
	else return 0;

	return 1;
}

void Game::checkShoot()
{
	for (auto t : round->getAllAttackTower())
	{
		for (auto d : round->getAllDrones())
		{
			if (t->getRangeShape()->getGlobalBounds().intersects(d->getDroneSprite().getGlobalBounds()))
			{
				t->shoot(d);
			}
		}
	}
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