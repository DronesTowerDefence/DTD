#include "Game.h"
#include "Multiplayer.h"
#include "Round.h"

Game* Game::instance = nullptr;

#pragma region Konstruktor
Game::Game()
{
	doubleSpeed = false;
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
}
#pragma endregion

#pragma region Funktionen
bool Game::loadGame()
{
	return 0; //DELETE WHEN DONE : Nur zum testen, im Final-Build entfernen!

	std::ifstream rdatei;

	bool defaultCounter = 0;
	char bufferValue1[30], bufferValue2[30], buffer[50];
	int counter = 0, first = 0, second = 0, third = 0, length1 = 0, length2 = 0, towerIndex = 0;

	std::ifstream FileTestSettings("saves/settings.sav"); //Überprüft ob die Datei existiert, wenn nicht, wird false zurückgegeben
	if (!FileTestSettings)
		return false;

	rdatei.open("saves/settings.sav");
	while (!rdatei.eof())
	{
		for (int i = 0; i < 49; i++, buffer[i] = '\0'); //Löscht den Inhalt der Buffer
		for (int i = 0; i < 19; i++, bufferValue1[i] = '\0', bufferValue2[i] = '\0');

		for (int i = 0; i < 48; i++, rdatei.get(buffer[i])); //Holt sich den Inhalt der Datei

		first = std::string(buffer).find("\""); //Sucht das erste Gänsefüßchen
		second = std::string(buffer).find("\"", first + 1); //Sucht das zweite Gänsefüßchen
		length1 = second - first - 1;
		std::string(buffer).copy(bufferValue1, length1, first + 1); //Kopiert das was zwischen den beiden Gänsefüßchen steht in einen anderen string
	}
	rdatei.close();

	PauseMenu::getInstance()->setSliderHelper(std::stof(bufferValue1));

	std::string datei; //Dateipfad
	datei = "saves/savegame" + std::to_string(p_map->getIndex());
	datei += ".sav";

	std::ifstream FileTest(datei);//Überprüft ob die Datei existiert, wenn nicht, wird false zurückgegeben
	if (!FileTest)
		return false;

	rdatei.open(datei);

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
void Game::setStatus(int status)
{
	this->status = status;
}
void Game::setDroneCount(int _droneCount)
{
	droneCount = _droneCount;
}
void Game::startGame()
{
	loadGame();

	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				saveGame();
				window->close();
			}


			PauseMenu::getInstance()->checkPause(event);
		}

		updateEco();
		moveDrohnes();
		checkDroneCount();
		changeBackgroundMusic();
		checkLoseGame();

		if (status == 1 || status == 2) // wenn Host oder SinglePlayer
		{
			subRoundHealth();
			checkShoot();
			checkTowerAlias();
			generateMoneyTowers();
			for (auto i : Round::getInstance()->getAllTowers())
			{
				i->getUpdates()->canBuy();

			}

		}
		if (status == 3)
		{
			while (Multiplayer::receive());
		}
		draw();
	}
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
void Game::updateEco()
{
	eco.setString("Lives: " + std::to_string(round->getHealth()) +
		"\nMoney: " + std::to_string(round->getMoney()) + " $"
		"\nRound: " + std::to_string(round->getIndex() + 1)
		/* + "\nx: " + std::to_string(Mouse::getPosition(*window).x) +
		"\ny: " + std::to_string(Mouse::getPosition(*window).y)*/);
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
	for (TowerSpawn* i : round->getAllSpawns()) {
		i->moveSpawn();
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
		if (Sidebar::getInstance()->isChangeSpeed(window))
		{
			if (doubleSpeed)
			{
				Ressources::getInstance()->normalSpeed();
			}
			else
			{
				Ressources::getInstance()->doubleSpeed();
			}
			doubleSpeed = !doubleSpeed;
		}
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
		Sidebar::getInstance()->isChangeSpeed(window);
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

	for (auto* q : round->getAllSpawns()) //Drawt die Spawns
	{
		window->draw(q->getSpawnSprite());
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
void Game::checkShoot()
{
	CircleShape* tmp = new CircleShape;
	for (auto t : round->getAllAttackTower())
	{
		if (t->getIndex() == 3) {
			if (shootCooldown.getElapsedTime().asSeconds() > 3) {
				shootCooldown.restart();
				for (auto i : Round::getInstance()->getAllSpawns()) {
					i->shoot();
				}

			}
		}
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
void Game::generateMoneyTowers()
{
	for (auto i : Round::getInstance()->getAllMoneyTower())
	{
		i->generateMoney();
	}
}
void Game::subRoundHealth()
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
}
void Game::checkLoseGame()
{
	if (round->getLost())
	{
		round->setHealth(0);
		updateEco();

		if (status == 2)
		{
			Multiplayer::send(1, false);
		}

		gameOverBackgroundTexture.loadFromFile("img/gameOverScreen.png");
		gameOverBackround.setTexture(gameOverBackgroundTexture);
		Vector2f gameOverPos(window->getSize().x / 2 - gameOverBackgroundTexture.getSize().x / 2, window->getSize().y / 2 - gameOverBackgroundTexture.getSize().y / 2);
		//gameOverPos: Rechnung, um das Bild in der Mitte vom Bildschirm zu haben
		gameOverBackround.setPosition(gameOverPos);

		gameOverHomeButtonTexture.loadFromFile("img/buttons/homeButton.png");
		gameOverHomeButton.setTexture(gameOverHomeButtonTexture);
		gameOverHomeButton.setPosition(Vector2f(760, 650));

		gameOverRestartButtonTexture.loadFromFile("img/buttons/restartButton.png");
		gameOverRestartButton.setTexture(gameOverRestartButtonTexture);
		gameOverRestartButton.setPosition(Vector2f(1060, 650));

		Vector2i mousePos = Vector2i(0, 0);
		gameOverRound.setString(std::to_string(round->getIndex() + 1));
		gameOverRound.setFont(stdFont);
		gameOverRound.setCharacterSize(70);
		gameOverRound.setFillColor(Color::White);
		gameOverRound.setOutlineColor(Color::Black);
		gameOverRound.setOutlineThickness(3);
		gameOverRound.setPosition(Vector2f(970, 467));

		lost = true;

		if (doubleSpeed)
		{
			Ressources::getInstance()->normalSpeed();
			doubleSpeed = false;
		}
		while (lost)
		{
			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					saveGame();
					window->close();
					return;
				}
			}

			window->draw(gameOverBackround);
			window->draw(gameOverRound);
			window->draw(gameOverHomeButton);
			window->draw(gameOverRestartButton);
			window->display();

			mousePos = Mouse::getPosition();

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2f homeButtonPos, homeButtonPos2, restartButton, restartButton2;
				Service* serv = Service::getInstance();
				homeButtonPos = serv->getObjectPosition(gameOverHomeButton.getPosition());
				homeButtonPos2 = serv->getObjectPosition(gameOverHomeButton.getPosition() + Vector2f(100.f, 100.f));
				restartButton = serv->getObjectPosition(gameOverRestartButton.getPosition());
				restartButton2 = serv->getObjectPosition(gameOverRestartButton.getPosition() + Vector2f(100.f, 100.f)); //Muss noch bearbeitet werden
				//restartButton = gameOverRestartButton.getPosition();
				//restartButton2 = restartButton + Vector2f(gameOverRes				tartButtonTexture.getSize());

				if ((mousePos.x >= homeButtonPos.x && mousePos.x <= homeButtonPos2.x) &&
					(mousePos.y >= homeButtonPos.y && mousePos.y <= homeButtonPos2.y)) //Wenn home
				{
					mainMenu();
					return;
				}
				else if ((mousePos.x >= restartButton.x && mousePos.x <= restartButton2.x) &&
					(mousePos.y >= restartButton.y && mousePos.y <= restartButton2.y)) //Wenn restart
				{
					restart();
					return;
				}
			}
		}
	}

}
void Game::checkDroneCount()
{
	if (round->getDroneTimer().getElapsedTime().asSeconds() > p_ressources->getDroneSpawnTime() && droneCount < p_ressources->getDroneCountInRound())
	{
		droneCount++;
		round->addDrone(new Drone(0, p_map->getStart(), p_map->getStartMove().x, p_map->getStartMove().y));
		round->restartDroneTimer();
	}
	if (droneCount == p_ressources->getDroneCountInRound() && round->getAllDrones().empty() && status == 2)
	{
		round->nextRound();
	}
	else if (round->getReceivedFromHostNextRound() && status == 3)
	{
		round->nextRound();
	}
}
void Game::mainMenu()
{
	saveGame();
	lost = false;

	if (status == 2)
	{
		Multiplayer::send(3, false);
	}

	HomeMenu::getInstance()->HomeMenuStart();
}
void Game::restart()
{
	saveGame();
	lost = false;

	if (status == 2)
	{
		Multiplayer::send(4, false);
	}

	int mapIndex = p_map->getIndex(); //Zurücksetzen aller Klassen/Objekte
	resetAll();
	round = Round::getInstance();
	p_map = new Map(mapIndex);
	sidebar = Sidebar::getInstance();
}
void Game::resetAll()
{
	//Zurücksetzen der Attribute von Game
	lost = false;
	droneCount = 0;
	isMouseClicked = false;
	doubleSpeed = false;

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
	if (!round->getAllSpawns().empty())
	{
		for (auto i : round->getAllSpawns())
		{
			delete i;
		}
	}
	delete newTower;
	delete sidebar;
	delete p_map;
	delete round;
}
void Game::saveGame()
{
	system("md saves >nul 2>&1");
	//Erstellt den Ordner, wo die Spielstände gespeichert werden,
	//wenn der Ordner bereits existiert, wird eine Fehlermeldung zurückgegeben, diese wird aber mit ">nul 2>&1" unterdrückt

	std::ofstream wdatei;

	wdatei.open("saves/settings.sav");

	wdatei << "Volume=\"" << PauseMenu::getInstance()->getSliderHelper() << "\"\n";

	wdatei.close();

	return; //DELETE WHEN DONE : Nur zum testen, damit das nicht nervt

	if (round->getIndex() <= 0)
	{
		return;
	}
	else if (lost && round->getIndex() > 0)
	{
		std::string cmd_s = "del saves\\savegame" + std::to_string(p_map->getIndex()) + ".sav";
		const char* cmd_cc = cmd_s.c_str();
		system(cmd_cc);
		return;
	}

	std::string datei;
	datei = "saves/savegame" + std::to_string(p_map->getIndex()); //Dateiname
	datei += ".sav"; //Dateiendung. Kann mit Text-Editor geöffnet werden

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
#pragma endregion

#pragma region getter
Game* Game::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Game;
	}
	return instance;
}
RenderWindow* Game::getWindow()
{
	return window;
}
Font Game::getFont()
{
	return stdFont;
}
Sound Game::getMusic()
{
	return music[0];
}
int Game::getStatus()
{
	return status;
}
#pragma endregion

#pragma region setter
void Game::setMusicVolume(float v)
{
	for (int i = 0; i < 4; i++) {

		music[i].setVolume(v);

	}
}
void Game::setWindow(RenderWindow* _window) {
	window = _window;
}
#pragma endregion


#pragma region Destruktor
Game::~Game()
{
	resetAll();
	instance = nullptr;
}
#pragma endregion