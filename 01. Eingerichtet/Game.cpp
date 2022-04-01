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
	round = Round::getInstance();
	sidebar = Sidebar::getInstance(map);
	map = new Map();
	newTower = nullptr;
	texture = new Texture();
	texture->loadFromFile("img/Map1.png");
	background = new RectangleShape(Vector2f(1920, 991));
	background->setTexture(texture);

	droneCount = 0;

	lost = false;
	eco.setCharacterSize(30);
	eco.setPosition(20, 20);
}

void Game::draw()
{
	window->clear();
	window->draw(*background);
	sidebar->draw(window);
	if (newTower != nullptr) //TowerAlias wird gedrawt
	{
		window->draw((*newTower->getSpr()));
		window->draw((*newTower->getRangeShape()));
	}
	for (auto* t : round->getAllMoneyTower()) //Geldgenerations Tower werden gedrawt
	{
		window->draw(t->getTowerSpr());
	}
	for (auto* t : round->getAllTowers()) //Tower werden gedrawt
	{
		window->draw(t->getTowerSpr());
	}
	for (auto* t : round->getAllTowers()) //Tower Range wird gedrawt
	{
		window->draw(*(t->getRangeShape()));
	}
	for (auto* t : round->getAllProjectiles()) //Projectiles werden gedrawt
	{
		window->draw(*(t->getProjectileSprite()));
	}
	for (auto* d : round->getAllDrones()) //Drones werden gedrawt
	{
		window->draw(d->getDroneSprite());
		if (d->getPosition().y > 991 && d->getNextPoint() >= 9) {

			round->subhealth(d->getLives());

		}
	}

	if (round->getDroneTimer().getElapsedTime().asSeconds() > 2.0 && droneCount<round->getDroneCountInRound(round->getRound())) {

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
		else
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
			"\nRound: " + std::to_string(round->getRound()+1));
	}
}

void Game::checkShoot()
{
	for (auto t : round->getAllTowers())
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