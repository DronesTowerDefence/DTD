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
	p_map = new Map(HomeMenu::getInstance()->getChoseIndex());
	round = Round::getInstance(p_map);
	sidebar = Sidebar::getInstance();
	newTower = nullptr;

	currentDrones[0] = *Ressources::getInstance()->getDroneTypesInRound(0);
	currentDrones[1] = *(Ressources::getInstance()->getDroneTypesInRound(0) + 1);
	currentDrones[2] = *(Ressources::getInstance()->getDroneTypesInRound(0) + 2);
	currentDrones[3] = *(Ressources::getInstance()->getDroneTypesInRound(0) + 3);
	currentDrones[4] = *(Ressources::getInstance()->getDroneTypesInRound(0) + 4);

	droneCount = 0;
	chooseMusic = 0;
	shootClockSpeed = 2;

	eco.setFont(stdFont);
	eco.setCharacterSize(30);
	eco.setPosition(20, 20);
	eco.setFillColor(Color::White);
	eco.setOutlineThickness(4);
	eco.setOutlineColor(Color::Black);
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
	std::ifstream rdatei;

	char bufferValue1[30], bufferValue2[30], buffer[50];
	Tower* newTower = nullptr;
	int counter = 0, defaultCounter = 0, first = 0, second = 0, third = 0, length1 = 0, length2 = 0, towerIndex = 0;

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
			if (defaultCounter == 0)
			{
				towerIndex = std::stoi(bufferValue1);
				defaultCounter++;
			}
			else if (defaultCounter == 1)
			{
				first = std::string(buffer).find("\"");
				second = std::string(buffer).find(",", first + 1);
				third = std::string(buffer).find("\"", second + 1);
				length1 = second - first - 1;
				length2 = third - second - 1;
				std::string(buffer).copy(bufferValue1, length1, first + 1);
				std::string(buffer).copy(bufferValue2, length2, second + 1);

				newTower = new Tower(towerIndex, Vector2f(std::stof(bufferValue1), std::stof(bufferValue2)), p_map);

				defaultCounter++;
			}
			else if (defaultCounter == 2)
			{
				first = std::string(buffer).find("\"");
				second = std::string(buffer).find(",", first + 1);
				third = std::string(buffer).find("\"", second + 1);
				length1 = second - first - 1;
				length2 = third - second - 1;
				std::string(buffer).copy(bufferValue1, length1, first + 1);
				std::string(buffer).copy(bufferValue2, length2, second + 1);

				newTower->setUpdate(std::stoi(bufferValue1), std::stoi(bufferValue2));

				defaultCounter = 0;
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
void Game::startGame()
{
	loadGame();

	while (window->isOpen())
	{
		while (Multiplayer::receive());

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				saveGame();
				window->close();
			}
			// Shortcuts
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space)
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
				Sidebar::getInstance()->setSpeedButton(doubleSpeed);
			}

			if (tower != nullptr)
			{
				if (event.type == Event::KeyReleased)
				{
					if (event.key.code == Keyboard::Period)
					{
						tower->Update2();
					}
					else if (event.key.code == Keyboard::Comma)
					{
						tower->Update1();
					}
					else if (event.key.code == Keyboard::BackSpace)
					{
						Round::getInstance()->sellTower(tower);
						Multiplayer::send(tower, 1);
						tower = nullptr;
					}

				}
			}
			else if (newTower == nullptr && tower == nullptr)
			{
				if (event.type == Event::KeyReleased)
				{

					if (event.key.code >= 27 && event.key.code < 27 + Ressources::getInstance()->getTowerCount() && Round::getInstance()->getMoney() >= Ressources::getInstance()->getTowerPrice(event.key.code - 27))
					{
						newTower = new TowerAlias(event.key.code - 27, p_map);
					}
				}
			}
			PauseMenu::getInstance()->checkPause(event);
		}

		while (Multiplayer::receive());

		HomeMenu::getInstance()->checkTestVersionEnd();

		updateEco();
		moveDrohnes();
		checkDroneCount();
		changeBackgroundMusic();
		checkLoseGame();
		checkTowerAlias();
		for (auto i : Round::getInstance()->getAllTowers())
		{
			i->getUpdates()->canBuy();

		}

		if (status != 1) //Wenn Host oder Client
		{
			while (Multiplayer::receive());
			checkMultiplayerConnection();
		}

		if (status == 1 || status == 2) // wenn Host oder SinglePlayer
		{
			subRoundHealth();
			checkShoot();
			generateMoneyTowers();
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
		if (newTower == nullptr /* || index == -1*/)
		{
			isMouseClicked = true;
		}
	}

	if (isMouseClicked && !Mouse::isButtonPressed(Mouse::Button::Left))
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
		isMouseClicked = false;
		if (Sidebar::getInstance()->isChangeSpeed(window))
		{
			if (doubleSpeed)
			{
				Ressources::getInstance()->normalSpeed();
				Multiplayer::send(5, false);
			}
			else
			{
				Ressources::getInstance()->doubleSpeed();
				Multiplayer::send(5, false);
			}
			doubleSpeed = !doubleSpeed;
			Sidebar::getInstance()->setSpeedButton(doubleSpeed);

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
				Multiplayer::send(tower, 1);

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
			isMouseClicked = true;
		}

		newTower->setPositionMouse(Mouse::getPosition(*window)); //Bewegt den TowerAlias an die Position der Maus
		if (isMouseClicked && !Mouse::isButtonPressed(Mouse::Button::Left))
		{
			isMouseClicked = false;
			if (newTower->getSpr()->getPosition().x > 1700) // löschen vom Tower
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
}
void Game::draw()
{
	window->clear();

	window->draw(*p_map->getBackround()); //Karte wird gedrawt
	window->draw(toolbar);
	CircleShape* a;

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
		if (newTower->getRangeShapePlane() != nullptr)
			window->draw((*newTower->getRangeShapePlane()));
	}
	if (tower != nullptr)
	{
		window->draw(*tower->getRangeShape());
		if (tower->getRangeShapePlane() != nullptr)
			window->draw(*tower->getRangeShapePlane());
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
		window->draw(*q->getSpawnSprite());
	}


	if (round->getLost())
	{
		window->draw(gameOverWonBackround);
		window->draw(homeButton);
		window->draw(restartButton);
	}
	else if (round->getWon())
	{
		window->draw(gameOverWonBackround);
		window->draw(homeButton);
		window->draw(restartButton);
	}

	window->draw(eco);
	window->display();
}
void Game::checkShoot()
{
	CircleShape* tmp = new CircleShape;
	tmp->setFillColor(Color::Transparent);
	tmp->setRadius(15);

	for (auto t : round->getAllAttackTower())
	{
		if (t->getIndex() == 1)
		{
			t->shoot(nullptr);
		}
		else if (t->getIndex() == 3)
		{
			t->shoot(nullptr);
		}
		else
		{
			for (auto iter : t->getCoverableArea())
			{
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
				case 5:
					if (pos_drohne.x > 1720.f) {
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
	if (round->getLost() || round->getWon())
	{
		if (round->getLost())
		{
			//Setzen der Texturen/Positionen
			round->setHealth(0);
			updateEco();
			gameOverWonBackround.setTexture(*p_ressources->getGameOverTexture());

			gameOverWonText[0].setString(std::to_string(round->getIndex() + 1));
			gameOverWonText[0].setFont(stdFont);
			gameOverWonText[0].setCharacterSize(70);
			gameOverWonText[0].setFillColor(Color::White);
			gameOverWonText[0].setOutlineColor(Color::Black);
			gameOverWonText[0].setOutlineThickness(3);
			gameOverWonText[0].setPosition(Vector2f(970, 467));

			if (status == 2) //Multiplayer
			{
				Multiplayer::send(1, false);
			}
		}
		else if (round->getWon()) //Setzen der Textur
		{
			gameOverWonBackround.setTexture(*p_ressources->getGameWonTexture());
			updateEco();

			for (int i = 0; i < (sizeof(gameOverWonText) / sizeof(*gameOverWonText)); i++)
			{
				gameOverWonText[i].setFont(stdFont);
				gameOverWonText[i].setCharacterSize(70);
				gameOverWonText[i].setFillColor(Color::White);
				gameOverWonText[i].setOutlineColor(Color::Black);
				gameOverWonText[i].setOutlineThickness(3);
			}
			gameOverWonText[0].setString(std::to_string(1)); //TODO
			gameOverWonText[1].setString(std::to_string(2));
			gameOverWonText[0].setPosition(Vector2f(1200, 440));
			gameOverWonText[1].setPosition(Vector2f(1200, 530));
		}

		//Setzen der Texturen
		Vector2f gameOverPos(window->getSize().x / 2 - p_ressources->getGameWonTexture()->getSize().x / 2, window->getSize().y / 2 - p_ressources->getGameWonTexture()->getSize().y / 2);
		//gameOverPos: Rechnung, um das Bild in der Mitte vom Bildschirm zu haben

		gameOverWonBackround.setPosition(gameOverPos);

		homeButton.setTexture(*p_ressources->getButtonHomeTexture());
		homeButton.setPosition(Vector2f(760, 650));

		restartButton.setTexture(*p_ressources->getButtonRestartTexture());
		restartButton.setPosition(Vector2f(1060, 650));

		Vector2i mousePos = Vector2i(0, 0);

		if (doubleSpeed)
		{
			Ressources::getInstance()->normalSpeed();
			doubleSpeed = false;
		}
		while (round->getLost() || round->getWon())
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

			//Draw
			window->draw(gameOverWonBackround);
			window->draw(homeButton);
			window->draw(restartButton);

			if (round->getLost())
			{
				window->draw(gameOverWonText[0]);
			}
			else
			{
				for (int i = 0; i < (sizeof(gameOverWonText) / sizeof(*gameOverWonText)); i++)
				{
					window->draw(gameOverWonText[i]);
				}
			}

			window->display();

			//Überprüfung, ob einer der beiden Buttons geklickt wurde
			mousePos = Mouse::getPosition();

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2f homeButtonPos, homeButtonPos2, restartButtonPos, restartButtonPos2;
				Service* serv = Service::getInstance();
				homeButtonPos = serv->getObjectPosition(homeButton.getPosition());
				homeButtonPos2 = serv->getObjectPosition(homeButton.getPosition() + Vector2f(100.f, 100.f));
				restartButtonPos = serv->getObjectPosition(restartButton.getPosition());
				restartButtonPos2 = serv->getObjectPosition(restartButton.getPosition() + Vector2f(100.f, 100.f));

				if ((mousePos.x >= homeButtonPos.x && mousePos.x <= homeButtonPos2.x) &&
					(mousePos.y >= homeButtonPos.y && mousePos.y <= homeButtonPos2.y)) //Wenn home
				{
					mainMenu();
					return;
				}
				else if ((mousePos.x >= restartButtonPos.x && mousePos.x <= restartButtonPos2.x) &&
					(mousePos.y >= restartButtonPos.y && mousePos.y <= restartButtonPos2.y)) //Wenn restart
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
		std::unique_ptr<int> rI(new int(round->getIndex())); //roundIndex
		std::unique_ptr<int> help(new int(0));

		//Falls eine neue Runde beginnt, wird die nächste Drohnen-Reihe eingelesen
		if (currentRound != round->getIndex()) {
			currentDrones[0] = *Ressources::getInstance()->getDroneTypesInRound(*rI);
			currentDrones[1] = *(Ressources::getInstance()->getDroneTypesInRound(*rI) + 1);
			currentDrones[2] = *(Ressources::getInstance()->getDroneTypesInRound(*rI) + 2);
			currentDrones[3] = *(Ressources::getInstance()->getDroneTypesInRound(*rI) + 3);
			currentDrones[4] = *(Ressources::getInstance()->getDroneTypesInRound(*rI) + 4);

			currentRound = round->getIndex();
		}


		//Die stärksten Drohnen werden zuerst gespawnt
		if (currentDrones[4] != 0) {
			currentDrones[4] -= 1;
			round->addDrone(new Drone(4, p_map->getStart(), p_map->getStartMove().x, p_map->getStartMove().y));

			droneCount++;
			round->restartDroneTimer();
			return;
		}
		if (currentDrones[3] != 0) {
			currentDrones[3] -= 1;
			round->addDrone(new Drone(3, p_map->getStart(), p_map->getStartMove().x, p_map->getStartMove().y));
			droneCount++;
			round->restartDroneTimer();
			return;
		}
		if (currentDrones[2] != 0) {
			currentDrones[2] -= 1;
			round->addDrone(new Drone(2, p_map->getStart(), p_map->getStartMove().x, p_map->getStartMove().y));
			droneCount++;
			round->restartDroneTimer();
			return;
		}
		if (currentDrones[1] != 0) {
			currentDrones[1] -= 1;
			round->addDrone(new Drone(1, p_map->getStart(), p_map->getStartMove().x, p_map->getStartMove().y));
			droneCount++;
			round->restartDroneTimer();
			return;
		}
		if (currentDrones[0] != 0) {
			currentDrones[0] -= 1;
			round->addDrone(new Drone(0, p_map->getStart(), p_map->getStartMove().x, p_map->getStartMove().y));
			droneCount++;
			round->restartDroneTimer();
			return;
		}

		round->restartDroneTimer();
	}
	if (droneCount == p_ressources->getDroneCountInRound() && round->getAllDrones().empty() && status != 3)
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

	if (status == 2)
	{
		Multiplayer::send(3, false);
	}

	HomeMenu::getInstance()->HomeMenuStart();
}
void Game::restart()
{
	deleteSaveGame();

	if (status == 2)
	{
		Multiplayer::send(4, false);
	}

	int mapIndex = p_map->getIndex(); //Zurücksetzen aller Klassen/Objekte
	resetAll();
	p_map = new Map(mapIndex);
	round = Round::getInstance(p_map);
	sidebar = Sidebar::getInstance();
}
void Game::sellTower(Tower* t)
{
	if (tower == t)
	{
		tower = nullptr;
	}
}
bool Game::deleteSaveGame()
{
	std::ifstream FileTest("saves/savegame" + std::to_string(p_map->getIndex()) + ".sav"); //Überprüft ob die Datei existiert, wenn nicht
	if (!FileTest)
		return false;

	std::string cmd_s = "del saves\\savegame" + std::to_string(p_map->getIndex()) + ".sav";
	const char* cmd_cc = cmd_s.c_str();
	system(cmd_cc);

	return true;
}
void Game::checkMultiplayerConnection()
{
	if (multiplayerCheckConnectionSendClock.getElapsedTime() > Multiplayer::timeoutSend)
	{
		Multiplayer::send(); //Sendet das Packet zum Überprüfen der Verbindung
		multiplayerCheckConnectionSendClock.restart();
	}

	if (multiplayerCheckConnectionClock.getElapsedTime() > Multiplayer::timeout)
	{
		Clock noConnectionPossibleClock;
		Time noConnectionPossibleTimer = seconds(20);
		Text waitText;
		waitText.setFont(stdFont);
		waitText.setCharacterSize(40);
		waitText.setFillColor(Color::White);
		waitText.setOutlineColor(Color::Black);
		waitText.setOutlineThickness(2);
		waitText.setPosition(Service::getInstance()->getObjectPosition(Vector2f(900, 500)));
		waitText.setString("Verbindungsproblem!\nWarten auf anderen Spieler");

		window->draw(waitText);
		window->display();

		p_ressources->newConnection();

		if (status == 2) //Erneuter Verbindungsaufbau, wenn Host
		{
			p_ressources->getListener()->listen(4567); //Horcht am Port

			while (p_ressources->getListener()->accept(*p_ressources->getReceiver()) != Socket::Done) //Stellt Verbindung her
			{
				while (window->pollEvent(event)) //Überprüft, ob das Fenster geschlossen wird
				{
					if (event.type == Event::Closed)
					{
						saveGame(); //Speichert das Spiel
						window->close();
					}
				}
				if (noConnectionPossibleClock.getElapsedTime() > noConnectionPossibleTimer) //Nach einer bestimmten Zeit wird in den Singleplayer gewechselt
				{
					status = 1;
					p_ressources->newConnection();
					return;
				}
			}

			while (p_ressources->getSender()->connect(p_ressources->getIpAddress(), 4568) != Socket::Done) //Verbindet sich mit dem Client
			{
				while (window->pollEvent(event)) //Überprüft, ob das Fenster geschlossen wird
				{
					if (event.type == Event::Closed)
					{
						saveGame(); //Speichert das Spiel
						window->close();
					}
				}
				if (noConnectionPossibleClock.getElapsedTime() > noConnectionPossibleTimer) //Nach einer bestimmten Zeit wird in den Singleplayer gewechselt
				{
					status = 1;
					p_ressources->newConnection();
					return;
				}
			}

			multiplayerCheckConnectionClock.restart();
		}
		else if (status == 3) //Erneuter Verbindungsaufbau, wenn Client
		{
			while (p_ressources->getSender()->connect(p_ressources->getIpAddress(), 4567) != Socket::Done) //Verbindet sich mit dem Host
			{
				while (window->pollEvent(event)) //Überprüft, ob das Fenster geschlossen wird
				{
					if (event.type == Event::Closed)
					{
						saveGame(); //Speichert das Spiel
						window->close();
					}
				}
				if (noConnectionPossibleClock.getElapsedTime() > noConnectionPossibleTimer) //Nach einer bestimmten Zeit wird in den Singleplayer gewechselt
				{
					status = 1;
					p_ressources->newConnection();
					return;
				}
			}

			p_ressources->getListener()->listen(4568); //Horcht am Port

			while (p_ressources->getListener()->accept(*p_ressources->getReceiver()) != Socket::Done) //Stellt Verbindung her
			{
				while (window->pollEvent(event)) //Überprüft, ob das Fenster geschlossen wird
				{
					if (event.type == Event::Closed)
					{
						saveGame(); //Speichert das Spiel
						window->close();
					}
				}
				if (noConnectionPossibleClock.getElapsedTime() > noConnectionPossibleTimer) //Nach einer bestimmten Zeit wird in den Singleplayer gewechselt
				{
					status = 1;
					p_ressources->newConnection();
					return;
				}
			}

			multiplayerCheckConnectionClock.restart();
		}

		p_ressources->getSender()->setBlocking(false);
		p_ressources->getReceiver()->setBlocking(false);
		p_ressources->getListener()->setBlocking(false);

	}
}
void Game::setDroneRow(int g)
{
	this->droneRow = g;
}
void Game::resetAll()
{
	//Zurücksetzen der Attribute von Game
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

	if (round->getIndex() <= 0)
	{
		return;
	}
	else if ((round->getLost() || round->getWon()) && round->getIndex() > 0)
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
	for (auto i : round->getAllTowers())
	{
		wdatei << "Tower" << j << "_index=\"" << i->getIndex() << "\"\n";
		wdatei << "Tower" << j << "_position=\"" << i->getTowerPos().x << "," << i->getTowerPos().y << "\"\n";
		wdatei << "Tower" << j << "_Upgrade=\"" << i->getUpdates()->getIndex1() << "," << i->getUpdates()->getIndex2() << "\"\n";
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
int Game::getShootClockSpeed()
{
	return shootClockSpeed;
}
bool Game::getDoubleSpeed()
{
	return doubleSpeed;
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
Clock* Game::getMultiplayerCheckConnectionClock()
{
	return &multiplayerCheckConnectionClock;
}
int Game::getStatus()
{
	return status;
}
int Game::getDroneRow()
{
	return droneRow;
}
#pragma endregion

#pragma region setter

void Game::setStatus(int status)
{
	this->status = status;
	//this->status = 3;
}
void Game::setDoubleSpeed(bool wert)
{
	doubleSpeed = wert;
}
void Game::setDroneCount(int _droneCount)
{
	droneCount = _droneCount;
}
void Game::setMusicVolume(float v)
{
	for (int i = 0; i < 4; i++) {

		music[i].setVolume(v);

	}
}
void Game::setShootClockSpeed(int a)
{
	shootClockSpeed = a;
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