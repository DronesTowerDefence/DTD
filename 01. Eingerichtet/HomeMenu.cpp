#include "HomeMenu.h"
#include "Controls.h"
#include "Multiplayer.h"
#include "PopUpMessage.h"
#include "Friends.h";
HomeMenu* HomeMenu::instance = nullptr;

#pragma region Konstruktor
HomeMenu::HomeMenu()
{
	music.openFromFile("music/music.wav");
	music.setLoop(true);
	music.play();
	daily = new Daily();
	accServer = new AccountServer();
	connected = false;
	isMultiplayerOpen = false;
	status = 1;
	callCount = 1;
	choseIndex = -1;
	isClicked = false;
	window = nullptr;
	multiplayerGUI = nullptr;
	achievementGUI = nullptr;
	shopGUI = nullptr;
	skinsGUI = nullptr;
	credits = nullptr;
	menuIsOpen = false;
	res = Ressources::getInstance();

	font = new Font();
	titel = new Sprite();
	backround = new Sprite();
	drone = new Sprite();

	startButton = new Button(Vector2f(400, 550), res->getButtonStartTexture());
	multiplayerMenueButton = new Button(Vector2f(750, 550), res->getButtonMultiplayerTexture(1));
	exitButton = new Button(Vector2f(1800, 871), res->getButtonExitTexture());
	clientButton = new Button(Vector2f(750, 775), res->getButtonClientTexture());
	hostButton = new Button(Vector2f(750, 650), res->getButtonHostTexture());
	deleteSavesButton = new Button(Vector2f(75, 900), res->getDeleteAllSavesButtonTexture());
	accountButton = new Button(Vector2f(1650, 851), res->getAccountIconButtonTexture());
	accountFriendsMenuButton = new Button(Vector2f(1650, 721), res->getAccountFriendsButtonTexture());
	achievementsButton = new Button(Vector2f(1650, 591), res->getAchievementsButtonTexture());
	dailyButton = new Button(Vector2f(575, 550), res->getStartDailyButtonTexture());
	shopButton = new Button(Vector2f(1650, 461), res->getOpenShopButtonTexture());
	skinsButton = new Button(Vector2f(1650, 331), res->getSkinsMenuIconTexture());
	creditsButton = new Button(Vector2f(1650, 201), res->getCreditsIconTexture());
	openMenuButton = new Button(Vector2f(1800, 721), res->getSettingsIconTexture());

	sideMenu = new RectangleShape();
	pointer = new RectangleShape();
	upperBorder = new RectangleShape();
	creditsText = new Text();

	chalange = "";

	font->loadFromFile("fonts/arial.ttf");

	titel->setTexture(*res->getTitleTextTexture());
	backround->setTexture(*res->getHomeMenuBackgroundTexture());
	drone->setTexture(*res->getDroneDmgTexture(1, 0));

	creditsText->setCharacterSize(25);
	creditsText->setFont(*font);
	creditsText->setFillColor(Color::Black);
	creditsText->setString("© Amon Sarfo, Daniel Schmidt, Jonas Eberhardt, Tim Scheunert");
	creditsText->setPosition(Vector2f(650, 950));

	Color black(0x2F2F2Fff);

	sideMenu->setSize(Vector2f(370.f, 1020.f));
	sideMenu->setPosition(Vector2f(0.f, 0.f));
	sideMenu->setFillColor(black);

	upperBorder->setSize(Vector2f(1550.f, 215.f));
	upperBorder->setPosition(Vector2f(370.f, 0.f));
	upperBorder->setFillColor(black);

	titel->setPosition(Vector2f(0, 0));
	drone->setPosition(Vector2f(150, 150));

	drone->setScale(3, 3);
	drone->setRotation(90);

	int y = 300;
	for (int i = 0; i < Ressources::getInstance()->getMapCount(); i++, y += 150)
	{
		map[i] = new Sprite;
		map[i]->setScale(0.1, 0.1);
		map[i]->setTexture(*res->getMapTexture(i));
		map[i]->setPosition(Vector2f(80, y));

	}

	positionTower[0] = Vector2f(1300, 250);
	positionTower[1] = Vector2f(1300, 400);
	positionTower[2] = Vector2f(1300, 550);
	positionTower[3] = Vector2f(1300, 700);
	positionTower[4] = Vector2f(1300, 850);
	for (int i = 0; i < 5; i++)
	{
		for (int x = 0; x < 4; x++)
		{
			textureTower[i][x] = new Texture();
		}
	}
	textureTower[0][0]->loadFromFile("img/tower0/tower0_0.png");
	textureTower[0][1]->loadFromFile("img/tower0/tower0_1.png");
	textureTower[0][2]->loadFromFile("img/tower0/tower0_2.png");
	textureTower[0][3]->loadFromFile("img/tower0/tower0_3.png");

	textureTower[1][0]->loadFromFile("img/tower1/tower1_0.png");
	textureTower[1][1]->loadFromFile("img/tower1/tower1_1.png");
	textureTower[1][2]->loadFromFile("img/tower1/tower1_2.png");
	textureTower[1][3]->loadFromFile("img/tower1/tower1_3.png");

	textureTower[2][0]->loadFromFile("img/tower2/tower2_0.png");
	textureTower[2][1]->loadFromFile("img/tower2/tower2_1.png");
	textureTower[2][2]->loadFromFile("img/tower2/tower2_2.png");
	textureTower[2][3]->loadFromFile("img/tower2/tower2_3.png");

	textureTower[3][0]->loadFromFile("img/tower3/tower3_0.png");
	textureTower[3][1]->loadFromFile("img/tower3/tower3_1.png");
	textureTower[3][2]->loadFromFile("img/tower3/tower3_2.png");
	textureTower[3][3]->loadFromFile("img/tower3/tower3_3.png");

	textureTower[4][0]->loadFromFile("img/tower4/tower4_0.png");
	textureTower[4][1]->loadFromFile("img/tower4/tower4_1.png");
	textureTower[4][2]->loadFromFile("img/tower4/tower4_2.png");
	textureTower[4][3]->loadFromFile("img/tower4/tower4_3.png");

	for (int i = 0; i < 5; i++)
	{
		towers[i] = new Sprite();

		towers[i]->setTexture(*textureTower[i][0]);
		towers[i]->setPosition(positionTower[i]);
		towers[i]->setScale(2, 2);

	}
	animationIndex = 0;
	animation = new Clock();

	pointer->setSize(Vector2f(1920 * 0.1, 991 * 0.1));
	pointer->setOutlineThickness(10);
	pointer->setOutlineColor(Color::Red);
	pointer->setFillColor(Color::Transparent);
	pointer->setPosition(-500, -500);

	choseText = new Text("Wähle eine Karte aus:", *font, 30);
	choseText->setPosition(Vector2f(25, 200));
}
#pragma endregion

#pragma region Funktionen
void HomeMenu::drawPublic()
{
	window->draw(*backround);
	window->draw(*sideMenu);
	window->draw(*upperBorder);
	window->draw(*titel);
	//window->draw(*drone);
	window->draw(*choseText);
	window->draw(*creditsText);

	window->draw(*multiplayerMenueButton);
	window->draw(*exitButton);
	window->draw(*deleteSavesButton);
	window->draw(*openMenuButton);

	if (menuIsOpen)
	{
		window->draw(*accountButton);
		window->draw(*accountFriendsMenuButton);
		window->draw(*achievementsButton);
		window->draw(*shopButton);
		window->draw(*skinsButton);
		window->draw(*creditsButton);
	}

	if (isMultiplayerOpen)
	{
		window->draw(*hostButton);
		window->draw(*clientButton);
	}
	else
	{
		window->draw(*startButton);
		window->draw(*dailyButton);
	}

	for (int i = 0; i < Ressources::getInstance()->getMapCount(); i++)
	{
		window->draw(*map[i]);
	}
	if (choseIndex > -1)
	{
		window->draw(*pointer);
	}

	/*for (int i = 0; i < 5; i++)
	{
		window->draw(*towers[i]);
	}*/

}
int  HomeMenu::CheckClicked(Event* event)
{
	if (!window->hasFocus())
		return 0;
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		return checkButtonClick(event);
	}
	checkButtonHover();
	return 0;
}
int HomeMenu::checkButtonClick(Event* event)
{
	isClicked = false;
	Vector2i mouse = Mouse::getPosition(*window);
	Ressources* res = Ressources::getInstance();

	// TODO
	//map clicked;
	Vector2f pos, pos2;
	for (int i = 0; i < res->getMapCount(); i++)
	{

		pos = Service::getInstance()->getObjectPosition(map[i]->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(map[i]->getPosition() + Vector2f(1920 * 0.1, 991 * 0.1));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			pointer->setPosition(Vector2f(map[i]->getPosition().x, map[i]->getPosition().y));
			choseIndex = i;
		}
	}


	//Host clicked
	if (isMultiplayerOpen)
	{
		if (hostButton->checkHover(mouse))
		{
			status = 2;

			multiplayerGUI = new MultiplayerGUI(window);
			if (multiplayerGUI->start(true))
			{
				delete multiplayerGUI;
				return 2;
			}
			else
			{
				delete multiplayerGUI;
				status = 0;
				return 0;
			}

		}

		//Client Clicked
		if (clientButton->checkHover(mouse))
		{
			status = 3;

			multiplayerGUI = new MultiplayerGUI(window);
			if (multiplayerGUI->start(false))
			{
				delete multiplayerGUI;
				return 3;
			}
			else
			{
				delete multiplayerGUI;
				status = 0;
				return 0;
			}

		}
	}
	else
	{
		//startclicked
		if (startButton->checkHover(mouse))
		{
			status = 1;
			music.stop();
			return 1;
		}

		// Daily
		if (dailyButton->checkHover(mouse))
		{
			if (Account::getAcc()->getAccName() == invalidUsername)
			{
				new PopUpMessage("Bitte vorher anmelden", sf::seconds(2));
				return 0;
			}
			loadDaily();
			if (!daily->getIsDaily())
			{
				new PopUpMessage("Fehler bei der Daily");
				return 0;
			}
			else
			{
				music.stop();
				Game::getInstance()->setWindow(&*window);
				Game::getInstance()->setStatus(1);
				Game::getInstance()->startGame();
			}
		}
	}
	//MultiplayerMunue
	if (multiplayerMenueButton->checkHover(mouse))
	{
		if (isMultiplayerOpen)
		{
			multiplayerMenueButton->setTexture(res->getButtonMultiplayerTexture(1));
			isMultiplayerOpen = false;
		}
		else
		{
			if (Account::getAcc()->getAccName() == invalidUsername)
			{
				new PopUpMessage("Bitte vorher anmelden", sf::seconds(2));
				return 0;
			}
			multiplayerMenueButton->setTexture(res->getButtonMultiplayerTexture(0));
			isMultiplayerOpen = true;
		}
		return 0;
	}

	//Exit
	if (exitButton->checkHover(mouse))
	{
		window->close();
		exit(0);
		return 0;
	}

	//DeleteSaves
	if (deleteSavesButton->checkHover(mouse))
	{
		for (int i = 0; i < res->getMapCount(); i++)
		{
			deleteSave(i);
		}
		new PopUpMessage("Alle Spielstände gelöscht", sf::seconds(2));
		return 0;
	}

	//MenuButton
	if (openMenuButton->checkHover(mouse))
	{
		menuIsOpen = !menuIsOpen;
		return 0;
	}

	if (menuIsOpen)
	{
		//AccountButton
		if (accountButton->checkHover(mouse))
		{
			AccountLogin* accLog = new AccountLogin(window, res);
			accLog->openAccountLoginWindow(event);
			delete accLog;
			return 0;
		}

		//AccountFriendsMenuButton
		if (accountFriendsMenuButton->checkHover(mouse))
		{
			if (Account::getAcc()->getAccName() == invalidUsername)
			{
				new PopUpMessage("Bitte vorher anmelden", sf::seconds(2));
				return 0;
			}
			else
			{
				FriendsGUI* fr = new FriendsGUI(window, 0);
			}
		}

		//AchievementsButton
		if (achievementsButton->checkHover(mouse))
		{
			achievementGUI = new AchievementGUI(window);
			achievementGUI->openAchievementGUI();
			delete achievementGUI;
			return 0;
		}

		//ShopButton
		if (shopButton->checkHover(mouse))
		{
			if (Account::getAcc()->getAccName() == invalidUsername)
			{
				new PopUpMessage("Bitte vorher anmelden");
			}
			else
			{
				shopGUI = new ShopGUI(window);
				shopGUI->openShop();
				delete shopGUI;
			}
			return 0;
		}

		//SkinsButton
		if (skinsButton->checkHover(mouse))
		{
			if (Account::getAcc()->getAccName() == invalidUsername)
			{
				new PopUpMessage("Bitte vorher anmelden");
			}
			else
			{
				skinsGUI = new SkinsGUI(window);
				skinsGUI->openGUI();
				delete skinsGUI;
			}
			return 0;
		}

		//CreditsButton
		if (creditsButton->checkHover(mouse))
		{
			credits = new Credits(window);
			credits->openCredits();
			delete credits;
			return 0;
		}
	}
}
void HomeMenu::checkButtonHover()
{
	Vector2i mouse = Mouse::getPosition(*window);

	startButton->checkHover(mouse);
	hostButton->checkHover(mouse);
	clientButton->checkHover(mouse);
	multiplayerMenueButton->checkHover(mouse);
	exitButton->checkHover(mouse);
	deleteSavesButton->checkHover(mouse);
	accountButton->checkHover(mouse);
	accountFriendsMenuButton->checkHover(mouse);
	achievementsButton->checkHover(mouse);
	dailyButton->checkHover(mouse);
	shopButton->checkHover(mouse);
	skinsButton->checkHover(mouse);
	creditsButton->checkHover(mouse);
	openMenuButton->checkHover(mouse);
}
void HomeMenu::HomeMenuStart()
{
	if (music.getStatus() != music.Playing)
		music.play();
	if (callCount > 1)
	{
		delete Game::getInstance();
		new PopUpMessage("Synchronisiere Achievements");
		if (AccountServer::sendAllAchievementsAndXp())
		{
			new PopUpMessage("Achievements synchronisiert");
		}
		else new PopUpMessage("Fehler beim Synchronisieren");
	}
	callCount++;

	Event* event = Controls::getEvent();
	Vector2f droneMoveDirection(4, 0);
	while (window->isOpen())
	{
		while (window->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				window->close();
				exit(0);
			}
		}

		drone->move(droneMoveDirection);
		setTowerTexture();
		if (drone->getPosition().x > 1920)
		{
			droneMoveDirection = Vector2f(-4, 0);
		}
		else if (drone->getPosition().x < 150)
		{
			droneMoveDirection = Vector2f(4, 0);
		}

		int clicked = CheckClicked(event);
		if (clicked == 1 && choseIndex != -1) // singleplayer
		{
			break;
		}
		else if (clicked == 2)
		{
			break;
		}
		else if (clicked == 3)
		{
			break;
		}

		draw();

	}
	startGame();
}
void HomeMenu::startGame()
{
	music.stop();
	if (status == 2)
	{
		std::string str = "Spielstart";
		Multiplayer::send(13, str);
	}
	Game::getInstance()->setWindow(&*window);
	Game::getInstance()->setStatus(status);
	Game::getInstance()->startGame();

}
void HomeMenu::loadDaily()
{
	std::string challenge = accServer->getChallenge();
	if (challenge == "-1")
	{
		daily->setIsDaily(false);
		choseIndex = -1;
		return;
	}

	int pos[12] = { 0 };
	pos[0] = challenge.find(";");
	pos[1] = challenge.find(";", pos[0] + 1);
	pos[2] = challenge.find(";", pos[1] + 1);
	pos[3] = challenge.find(";", pos[2] + 1);
	pos[4] = challenge.find(";", pos[3] + 1);
	pos[5] = challenge.find(";", pos[4] + 1);
	pos[6] = challenge.find(";", pos[5] + 1);
	pos[7] = challenge.find(";", pos[6] + 1);
	pos[8] = challenge.find(";", pos[7] + 1);
	pos[9] = challenge.find(";", pos[8] + 1);
	pos[10] = challenge.find(";", pos[9] + 1);
	pos[11] = challenge.find(";", pos[10] + 1);
	std::string tmp;

	//Anfangsgeld
	tmp = challenge.substr(0, pos[0]);
	daily->setGeld(std::stoi(tmp));

	//Startrunde
	tmp = challenge.substr(pos[0] + 1, pos[1] - pos[0] - 1);
	daily->setVon(std::stoi(tmp));

	//endrunde
	tmp = challenge.substr(pos[1] + 1, pos[2] - pos[1] - 1);
	daily->setBis(std::stoi(tmp));

	//Leben
	tmp = challenge.substr(pos[2] + 1, pos[3] - pos[2] - 1);
	daily->setLeben(std::stoi(tmp));

	//karte
	tmp = challenge.substr(pos[3] + 1, pos[4] - pos[3] - 1);
	choseIndex = std::stoi(tmp) - 1;

	//sind dir Türme erlaubt
	for (int i = 0; i < 7; i++)
	{
		tmp = challenge.substr(pos[i + 4] + 1, pos[i + 5] - pos[i + 4] - 1);
		if (tmp == "1") { daily->setIsTowerAllowed(i, true); }
		else { daily->setIsTowerAllowed(i, false); };
	}
	daily->setIsDaily(true);
}
Daily* HomeMenu::getDaily()
{
	return daily;
}
void HomeMenu::draw()
{
	window->clear();
	drawPublic();
	PopUpMessage::draw(window);
	window->display();
}
bool HomeMenu::deleteSave(int index)
{
	std::ifstream FileTest("saves/savegame" + std::to_string(index) + ".sav"); //Überprüft ob die Datei existiert, wenn nicht wird false zurückgegeben
	if (FileTest.fail())
	{
		FileTest.close();
		return false;
	}
	FileTest.close();

	std::string cmd_s = "del saves\\savegame" + std::to_string(index) + ".sav";
	const char* cmd_cc = cmd_s.c_str();
	system(cmd_cc);

	return true;
}
#pragma endregion

#pragma region getter
HomeMenu* HomeMenu::getInstance()
{
	if (instance == nullptr)
	{
		instance = new HomeMenu();
	}
	return instance;
}
int HomeMenu::getChoseIndex()
{
	return choseIndex;
}

MultiplayerGUI* HomeMenu::getMultiplayerGUI()
{
	return multiplayerGUI;
}
ShopGUI* HomeMenu::getShopGUI()
{
	return shopGUI;
}
int HomeMenu::getStatus()
{
	return status;
}
RenderWindow* HomeMenu::getWindow()
{
	return window;
}
#pragma endregion

#pragma region setter
void HomeMenu::setWindow(RenderWindow* window)
{
	this->window = window;

}
void HomeMenu::setChoseIndex(int _choseIndex)
{
	if (_choseIndex >= 0)
	{
		choseIndex = _choseIndex;
	}
}

void HomeMenu::setStatus(int _status)
{
	status = _status;
}
void HomeMenu::setTowerTexture()
{
	if (animation->getElapsedTime().asMilliseconds() >= 300)
	{
		animationIndex++;
		if (animationIndex > 3)
			animationIndex = 0;

		for (int i = 0; i < 5 - 1; i++)
		{
			towers[i]->setTexture(*textureTower[i][animationIndex]);
		}
		animation->restart();
	}

}
#pragma endregion

#pragma region Desturktor
#pragma endregion
