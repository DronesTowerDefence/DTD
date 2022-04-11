#include "Game.h"
#include <fstream>

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
	p_map = new Map();
	round = Round::getInstance();
	sidebar = Sidebar::getInstance(/*map*/);
	newTower = nullptr;
	texture = new Texture();
	texture->loadFromFile("img/Map1.png");
	background = new RectangleShape(Vector2f(1920, 991));
	background->setTexture(texture);
	round->setAllCoverablePoints();

	droneCount = 0;
	chooseMusic = 0;

	lost = false;
	eco.setCharacterSize(30);
	eco.setPosition(20, 20);

	setMusicSound();
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
		if (t->getcollided() == 0)
			window->draw(*(t->getProjectileSprite()));

	}

	for (auto* d : round->getAllDrones()) //Drones werden gedrawt
	{
		window->draw(d->getDroneSprite());
	}

	if (round->getDroneTimer().getElapsedTime().asSeconds() > 2.0 && droneCount < round->getDroneCountInRound(round->getIndex())) {

		droneCount++;
		round->addDrone(new Drone(1, p_map->getStart(), 0, -1));
		round->restartDroneTimer();
	}
	if (droneCount == round->getDroneCountInRound(round->getIndex()) && round->getAllDrones().empty())
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
			{
				saveGame();
				window->close();
			}
			if (event.type == Event::LostFocus)
			{
				window->requestFocus();
			}

		}
		loseGame();
		moveDrohnes();
		checkShoot();
		checkTowerAlias();
		generateMoneyTowers();
		changeBackgroundMusic();
		draw();
	}
}

void Game::newRound()
{
	droneCount = 0;
	round->nextRound();
}

void Game::saveGame()
{
	if (round->getIndex() <= 0)
		return;

	std::string datei;
	datei = "saves/savegame" + std::to_string(p_map->getIndex()); //Dateiname
	datei += ".sav"; //Dateiendung. Kann mit Text-Editor ge�ffnet werden

	system("md saves >nul 2>&1");
	//Erstellt den Ordner, wo die Spielst�nde gespeichert werden,
	//wenn der Ordner bereits existiert, wird eine Fehlermeldung zur�ckgegeben, diese wird aber mit ">nul 2>&1" unterdr�ckt

	std::ofstream wdatei;
	wdatei.open(datei);

	wdatei << "Map.Index=\"" << p_map->getIndex() << "\"\n";
	wdatei << "Round.Index=\"" << round->getIndex() << "\"\n";
	wdatei << "Round.Money=\"" << round->getMoney() << "\"\n";
	wdatei << "Round.Health=\"" << round->getHealth() << "\"\n";

	int j = 0;
	for (auto i : round->getAllAttackTower())
	{
		wdatei << "Tower" << j << "_index=\"" << i->getIndex() << "\"\n";
		wdatei << "Tower" << j << "_position=\"" << i->getTowerPos().x << "," << i->getTowerPos().y << "\"\n";
		j++;
	}

	for (auto i : round->getAllMoneyTower())
	{
		wdatei << "Tower" << j << "_index=\"" << i->getIndex() << "\"\n";
		wdatei << "Tower" << j << "_position=\"" << i->getTowerPos().x << "," << i->getTowerPos().y << "\"\n";
		j++;
	}

	wdatei << "\n";
	wdatei.close();
}

bool Game::loadGame(int mapIndex)
{
	std::string datei; //Dateipfad
	datei = "saves/savegame" + std::to_string(mapIndex);
	datei += ".sav";


	std::ifstream FileTest(datei); //�berpr�ft ob die Datei existiert, wenn nicht, wird false zur�ckgegeben
	if (!FileTest)
		return false;

	std::ifstream rdatei;
	rdatei.open(datei);

	char buffer[50];

	while (!rdatei.eof())
	{
		for (int i = 0; i < 50; i++, buffer[i] = '\0'); //L�scht den Inhalt des Buffers

		for (int i = 0; i < 50; i++)
		{
			if (buffer[i] != '\0') //Jeder Buchstabe einer Zeile wird im Array gespeichert
			{
				rdatei.get(buffer[i]);
			}
			else if (i != 0) //Nullterminierung am Ende der Zeile
			{
				buffer[i - 1] = '\0';
			}
			else //Wenn die Zeile leer ist
			{
				buffer[i] = '\0';
			}
		}
	}
	rdatei.close();
	return true;
}

void Game::setMusicSound()
{
	musicBuffer[0].loadFromFile("music/1-0.wav");
	musicBuffer[1].loadFromFile("music/1-1.wav");
	musicBuffer[2].loadFromFile("music/2-0.wav");
	musicBuffer[3].loadFromFile("music/3-0.wav");
	music[0].setBuffer(musicBuffer[0]);
	music[1].setBuffer(musicBuffer[1]);
	music[2].setBuffer(musicBuffer[2]);
	music[3].setBuffer(musicBuffer[3]);

	//Anfangsmusik wird in changeBackgroundMusic nach einer bestimmten Zeit ge�ndert
	music[chooseMusic].play();
	music[chooseMusic].setLoop(true);
}

void Game::changeBackgroundMusic()
{
	if (chooseMusic == 0 && changeMusicTimer.getElapsedTime().asSeconds() >= 30)
	{
		music[chooseMusic].setLoop(false);
		chooseMusic = 1;
		music[chooseMusic].play();
		music[chooseMusic].setLoop(true);
		changeMusicTimer.restart();
	}
	else if (changeMusicTimer.getElapsedTime().asSeconds() >= 30)
	{
		music[chooseMusic].setLoop(false);
		chooseMusic++;
		music[chooseMusic].play();
		music[chooseMusic].setLoop(true);
		changeMusicTimer.restart();
	}
	else if (chooseMusic == 3 && changeMusicTimer.getElapsedTime().asSeconds() >= 30)
	{
		music[chooseMusic].setLoop(false);
		chooseMusic = 0;
		music[chooseMusic].play();
		music[chooseMusic].setLoop(true);
		changeMusicTimer.restart();
	}

}

void Game::moveDrohnes()
{
	for (Drone* p : round->getAllDrones())
	{
		p_map->checkChangeDirection(p);
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
		newTower = new TowerAlias(index, p_map);
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

				round->subhealth(i->getLives());
				i->~Drone();

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
			"\nRound: " + std::to_string(round->getIndex() + 1));
	}
}

bool Game::towerAliasForbiddenPosition()
{
	if (newTower->getPos().x < 1700 && Mouse::getPosition(*window).x < 1700)
	{
		CircleShape collisionShape;
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