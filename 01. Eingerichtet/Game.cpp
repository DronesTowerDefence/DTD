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

Game::~Game()
{
	if (!round->getAllTowers().empty())
	{
		for (auto i : round->getAllTowers())
		{
			delete i;
		}
	}
	if (!round->getAllDrones().empty())
	{
		for (auto i : round->getAllDrones())
		{
			delete i;
		}
	}
	if (!round->getAllProjectiles().empty())
	{
		for (auto i : round->getAllProjectiles())
		{
			delete i;
		}
	}
	delete newTower;
	delete sidebar;
	delete p_map;
	delete round;
	instance = nullptr;
}

Game::Game()
{

	p_ressources = Ressources::getInstance();
	stdFont.loadFromFile("fonts/arial.ttf");
	eco.setFont(stdFont);
	p_map = new Map(HomeMenu::getInstance()->getChoseIndex());
	round = Round::getInstance();
	sidebar = Sidebar::getInstance();
	newTower = nullptr;
	round->setAllCoverablePoints();

	droneCount = 0;
	chooseMusic = 0;

	lost = false;
	eco.setCharacterSize(30);
	eco.setPosition(20, 20);
	tower = nullptr;
	toolbar = RectangleShape();
	toolbar.setFillColor(Color::Blue);
	toolbar.setPosition(1720, 0);
	toolbar.setSize(Vector2f(200, 991));
	isMouseClicked = false;

	musicBuffer[0].loadFromFile("music/1-0.wav");
	musicBuffer[1].loadFromFile("music/1-1.wav");
	musicBuffer[2].loadFromFile("music/2-0.wav");
	musicBuffer[3].loadFromFile("music/3-0.wav");
	music[0].setBuffer(musicBuffer[0]);
	music[1].setBuffer(musicBuffer[1]);
	music[2].setBuffer(musicBuffer[2]);
	music[3].setBuffer(musicBuffer[3]);
	music[0].setVolume(50);
	music[1].setVolume(50);
	music[2].setVolume(50);
	music[3].setVolume(50);

	loadGame();
}

void Game::draw()
{
	window->clear();

	window->draw(*p_map->getBackround()); //Karte wird gedrawt
	window->draw(toolbar);

	if (tower != nullptr)
	{
		tower->getUpdates()->draw(window);
	}
	else
	{
		sidebar->draw(window); //Sidebar wird gedrawt
	}

	if (newTower != nullptr) //TowerAlias wird gedrawt
	{
		window->draw((*newTower->getSpr()));
		window->draw((*newTower->getRangeShape()));
	}
	if (tower != nullptr)
	{
		window->draw(*tower->getRangeShape());
	}

	for (auto* t : round->getAllMoneyTower()) //Geldgenerations Tower werden gedrawt
	{
		window->draw(*(t->getDrawSprite()));
	}

	for (auto* t : round->getAllAttackTower()) //Tower werden gedrawt
	{
		window->draw(*(t->getDrawSprite()));
	}


	for (auto* t : round->getAllProjectiles()) //Projectiles werden gedrawt
	{
		if (t->getcollided() == 0)
			window->draw(*(t->getProjectileSprite()));

	}

	for (auto* d : round->getAllDrones()) //Drones werden gedrawt
	{
		window->draw(*d->getDrawSprite());
	}

	for (auto* q : round->getAllSpawns()) 
	{
		window->draw(q->getSpawnSprite());
	}


	if (round->getDroneTimer().getElapsedTime().asSeconds() > round->getDroneSpawnTime() && droneCount < round->getDroneCountInRound()) {

		droneCount++;
		round->addDrone(new Drone(0, p_map->getStart(), p_map->getStartMove().x, p_map->getStartMove().y));
		round->restartDroneTimer();
	}
	if (droneCount == round->getDroneCountInRound() && round->getAllDrones().empty())
	{
		newRound();
	}

	if (lost)
	{
		window->draw(gameOverBackround);
		window->draw(gameOverHomeButton);
		window->draw(gameOverRestartButton);
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
				//saveGame();
				window->close();
			}


			PauseMenu::getInstance()->checkPause(event);
		}

		getNewEco();
		checkLoseGame();
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
	datei += ".sav"; //Dateiendung. Kann mit Text-Editor geöffnet werden

	system("md saves >nul 2>&1");
	//Erstellt den Ordner, wo die Spielstände gespeichert werden,
	//wenn der Ordner bereits existiert, wird eine Fehlermeldung zurückgegeben, diese wird aber mit ">nul 2>&1" unterdrückt

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

bool Game::loadGame()
{
	std::string datei; //Dateipfad
	datei = "saves/savegame" + std::to_string(p_map->getIndex());
	datei += ".sav";

	std::ifstream FileTest(datei); //Überprüft ob die Datei existiert, wenn nicht, wird false zurückgegeben
	if (!FileTest)
		return false;

	std::ifstream rdatei;
	rdatei.open(datei);

	bool defaultCounter = 0;
	char buffer[50], bufferValue1[30], bufferValue2[30];
	int counter = 0, first = 0, second = 0, third = 0, length1 = 0, length2 = 0, towerIndex = 0;


	while (!rdatei.eof())
	{
		for (int i = 0; i < 49; i++, buffer[i] = '\0'); //Löscht den Inhalt des Buffers
		for (int i = 0; i < 19; i++, bufferValue1[i] = '\0', bufferValue2[i] = '\0');

		for (int i = 0; i < 49; i++)
		{
			rdatei.get(buffer[i]);

			if (buffer[i] == '\n') //Ende der Zeile
			{
				break;
			}
		}

		if (buffer[1] == '\0') //Ende der Datei
		{
			goto end;
		}

		first = std::string(buffer).find("\"");
		second = std::string(buffer).find("\"", first + 1);
		length1 = second - first - 1;
		std::string(buffer).copy(bufferValue1, length1, first + 1);

		switch (counter)
		{
		case 0:
			break;
		case 1:
			round->setIndex(std::stoi(bufferValue1));
			break;

		case 2:
			round->setMoney(std::stoi(bufferValue1));
			break;

		case 3:
			round->setHealth(std::stoi(bufferValue1));
			break;

		default:
			if (!defaultCounter)
			{
				towerIndex = std::stoi(bufferValue1);
				defaultCounter = 1;
			}
			else if (defaultCounter)
			{
				first = std::string(buffer).find("\"");
				second = std::string(buffer).find(",", first + 1);
				third = std::string(buffer).find("\"", second + 1);
				length1 = second - first - 1;
				length2 = third - second - 1;
				std::string(buffer).copy(bufferValue1, length1, first + 1);
				std::string(buffer).copy(bufferValue2, length2, second + 1);

				defaultCounter = 0;
				new Tower(towerIndex, Vector2f(std::stof(bufferValue1), std::stof(bufferValue2)), p_map);
			}
			break;
		}
		counter++;
	}

end:
	rdatei.close();
	return true;
}



void Game::changeBackgroundMusic()
{
	if (music[chooseMusic].getStatus() != music[chooseMusic].Playing)
	{
		if (chooseMusic == 3)
		{
			chooseMusic = 0;
		}
		else
		{
			chooseMusic++;
		}
		music[chooseMusic].play();
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
	}
	for (Projectile* i : round->getAllProjectiles())
	{
		i->collission();
	}
}

void Game::checkButtonClick()
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		int index = -1;
		if (tower == nullptr) // wenn die Toolbar nicht die Updates anzeigt
		{
			index = sidebar->isClicked(window);
			if (index > -1)
			{
				newTower = new TowerAlias(index, p_map);
			}
			//else clicked = true;
		}
		if (newTower == nullptr || index == -1)
		{
			isMouseClicked = true;
		}
	}

	if (isMouseClicked && !Mouse::isButtonPressed(Mouse::Button::Left))
	{
		isMouseClicked = false;

		for (auto* t : round->getAllTowers())
		{
			if (t->isClicked(window))
				tower = t;
		}
		if (tower != nullptr)
		{

			tower->manageUpdate(window);
			if (tower->getUpdates()->IsClosed(window))
			{
				tower = nullptr;
			}
			else if (tower->getUpdates()->isSell(window))
			{
				Round::getInstance()->sellTower(tower);
				tower = nullptr;
			}
		}

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
		else if (newTower->getSpr()->getPosition().x > 1700)
		{
			round->addMoney(Ressources::getInstance()->getTowerPrice(newTower->getIndex()));
			delete newTower;
			newTower = nullptr;
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

void Game::checkLoseGame()
{
	if (round->getDroneSubHealthTimer().getElapsedTime().asSeconds() > 1)
	{
		Vector2f pos_drohne = Vector2f(0, 0);
		Vector2f pos_waypoint = Vector2f(0, 0);
		for (auto i : round->getAllDrones())
		{
			pos_drohne = i->getPosition();
			pos_waypoint = p_map->getWaypoint(p_map->getWayPointCount() - 1)->getKooadinaten();

			if (i->getNextPoint() >= p_map->getWayPointCount() - 1)
			{
				switch (p_map->getWaypoint(p_map->getWayPointCount() - 1)->getCondition())
				{
				case 1:
					if (pos_drohne.y == pos_waypoint.y && pos_drohne.x >= pos_waypoint.x)
					{
						round->subhealth(i->getLives());
						i->~Drone();
						return;
					}
					break;

				case 2:
					if (pos_drohne.y == pos_waypoint.y && pos_drohne.x <= pos_waypoint.x)
					{
						round->subhealth(i->getLives());
						i->~Drone();
						return;
					}
					break;
				case 3:
					if (pos_drohne.y >= pos_waypoint.y && pos_drohne.x == pos_waypoint.x)
					{
						round->subhealth(i->getLives());
						i->~Drone();
						return;
					}
					break;
				case 4:
					if (pos_drohne.y <= pos_waypoint.y && pos_drohne.x == pos_waypoint.x)
					{
						round->subhealth(i->getLives());
						i->~Drone();
						return;
					}
					break;
				default:
					break;
				}
			}

		}
		round->restartDroneSubHealthTimer();
	}

	if (round->getLost())
	{
		round->setHealth(0);

		gameOverBackgroundTexture.loadFromFile("img/gameOverBackround.png");
		gameOverBackround.setTexture(gameOverBackgroundTexture);
		gameOverBackround.setPosition(Vector2f(500, 300));

		gameOverHomeButtonTexture.loadFromFile("img/buttons/homeButton.png");
		gameOverHomeButton.setTexture(gameOverHomeButtonTexture);
		gameOverHomeButton.setPosition(Vector2f(600, 500));

		gameOverRestartButtonTexture.loadFromFile("img/buttons/restartButton.png");
		gameOverRestartButton.setTexture(gameOverRestartButtonTexture);
		gameOverRestartButton.setPosition(Vector2f(700, 500));

		lost = true;

		Vector2i mousePos = Vector2i(0, 0);
		bool homeMenu = false;

		while (lost)
		{
			window->draw(gameOverBackround);
			window->draw(gameOverHomeButton);
			window->draw(gameOverRestartButton);
			window->display();

			mousePos = Mouse::getPosition();

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (((mousePos.x >= gameOverHomeButton.getPosition().x) && (mousePos.x <= gameOverHomeButton.getPosition().x + 100)) &&
					((mousePos.y >= gameOverHomeButton.getPosition().y) && (mousePos.y <= gameOverHomeButton.getPosition().y + 100)))
				{
					homeMenu = true;
				}
				else if (((mousePos.x >= gameOverRestartButton.getPosition().x) && (mousePos.x <= gameOverRestartButton.getPosition().x + 100)) &&
					((mousePos.y >= gameOverRestartButton.getPosition().y) && (mousePos.y <= gameOverRestartButton.getPosition().y + 100)))
				{
					delete Round::getInstance();
					Round::getInstance();
				}
				if (homeMenu)
				{
					lost = false;
					//Neue Funktion in Round zum resetten
					HomeMenu::getInstance()->HomeMenuStart();
				}
			}

		}
	}

}


bool Game::towerAliasForbiddenPosition()
{
	if (newTower->getPos().x < 1700 && Mouse::getPosition(*window).x < 1700) //Überprüfung ob auf der Sidebar
	{
		CircleShape* collisionShape = new CircleShape();
		collisionShape->setFillColor(Color::Transparent);
		collisionShape->setRadius(25);
		for (auto i : round->getAllCoverablePoints()) //Überprüfung ob auf der Strecke
		{

			collisionShape->setPosition(i);
			if (newTower->getSpr()->getGlobalBounds().intersects(collisionShape->getGlobalBounds()))
				return 0;
		}

		for (auto i : round->getAllTowers()) //Überprüfung ob auf anderem Turm
		{
			if (newTower->getSpr()->getGlobalBounds().intersects(i->getTowerSpr().getGlobalBounds()))
				return 0;
		}
		delete collisionShape;
	}
	else return 0;

	return 1;
}

void Game::checkShoot()
{
	CircleShape* tmp = new CircleShape;
	for (auto t : round->getAllAttackTower())
	{
		for (auto iter : t->getCoverableArea())
		{
			tmp->setFillColor(Color::Transparent);
			tmp->setRadius(15);
			tmp->setPosition(Vector2f(iter.x, iter.y));

			for (auto d : round->getAllDrones())
			{
				if (tmp->getGlobalBounds().intersects(d->getDroneSprite().getGlobalBounds()))
				{
					t->shoot(d);
				}
			}
		}
	}
	delete tmp;
}

Font Game::getFont()
{
	return stdFont;
}

RenderWindow* Game::getWindow()
{
	return window;
}



void Game::setWindow(RenderWindow* _window) {
	window = _window;
}

Sound Game::getMusic()
{
	return music[0];
}

void Game::setMusicVolume(float v)
{
	for (int i = 0; i < 4; i++) {

		music[i].setVolume(v);

	}
}

void Game::getNewEco()
{
	eco.setString("Lives: " + std::to_string(round->getHealth()) +
		"\nMoney: " + std::to_string(round->getMoney()) + " $"
		"\nRound: " + std::to_string(round->getIndex() + 1)
		/* + "\nx: " + std::to_string(Mouse::getPosition(*window).x) +
		"\ny: " + std::to_string(Mouse::getPosition(*window).y)*/);
}