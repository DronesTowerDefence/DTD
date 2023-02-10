#include "HomeMenu.h"
#include "Controls.h"
#include "Multiplayer.h"

HomeMenu* HomeMenu::instance = nullptr;

#pragma region Konstruktor
HomeMenu::HomeMenu()
{
	connected = false;
	isMultiplayerOpen = false;
	status = 1;
	callCount = 1;
	isClicked = false;
	window = nullptr;
	multiplayerGUI = nullptr;
	res = Ressources::getInstance();

	startButton = new Sprite;
	font = new Font();
	titel = new Sprite;
	backround = new Sprite();
	drone = new Sprite();
	multiplayerMenue = new Sprite();
	exitButton = new Sprite();
	client = new Sprite();
	host = new Sprite();
	deleteSavesButton = new Sprite();
	accountButton = new Sprite();

	sideMenu = new RectangleShape();
	pointer = new RectangleShape;
	upperBorder = new RectangleShape();

	credits = new Text();

	font->loadFromFile("fonts/arial.ttf");

	startButton->setTexture(*res->getButtonStartTexture());
	titel->setTexture(*res->getTitleTextTexture());
	backround->setTexture(*res->getHomeMenuBackgroundTexture());
	drone->setTexture(*res->getDroneTexture(1, 0));;
	multiplayerMenue->setTexture(*res->getButtonMultiplayerTexture(1));
	host->setTexture(*res->getButtonHostTexture());
	client->setTexture(*res->getButtonClientTexture());
	exitButton->setTexture(*res->getButtonExitTexture());
	deleteSavesButton->setTexture(*res->getDeleteAllSavesButtonTexture());
	accountButton->setTexture(*res->getAccountIconButtonTexture());

	credits->setCharacterSize(25);
	credits->setFont(*font);
	credits->setFillColor(Color::Black);
	credits->setString("� Amon Sarfo, Daniel Schmidt, Jonas Eberhardt, Tim Scheunert");
	credits->setPosition(Vector2f(650, 950));

	Color black(0x2F2F2Fff);

	sideMenu->setSize(Vector2f(370.f, 1020.f));
	sideMenu->setPosition(Vector2f(0.f, 0.f));
	sideMenu->setFillColor(black);

	upperBorder->setSize(Vector2f(1550.f, 215.f));
	upperBorder->setPosition(Vector2f(370.f, 0.f));
	upperBorder->setFillColor(black);

	/*upperBorder->setOutlineColor(Color::Black);
	upperBorder->setOutlineThickness(2.0);*/

	startButton->setPosition(Vector2f(900, 700));
	titel->setPosition(Vector2f(0, 0));
	drone->setPosition(Vector2f(0, 300));
	host->setPosition(Vector2f(500, 450));
	client->setPosition(Vector2f(750, 450));
	multiplayerMenue->setPosition(Vector2f(500, 350));
	exitButton->setPosition(Vector2f(20, 871));
	deleteSavesButton->setPosition(Vector2f(1700, 900));
	accountButton->setPosition(Vector2f(1770, 750));

	choseIndex = -1;

	drone->setScale(2, 2);
	//
	int y = 400;
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
	for (int i = 0; i < Ressources::getInstance()->getTowerCount(); i++)
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

	for (int i = 0; i < Ressources::getInstance()->getTowerCount(); i++)
	{
		towers[i] = new Sprite();

		towers[i]->setTexture(*textureTower[i][0]);
		towers[i]->setPosition(positionTower[i]);
		towers[i]->setScale(2, 2);

	}
	animationIndex = 0;
	animation = new Clock();
	animation->restart();

	pointer->setSize(Vector2f(1920 * 0.1, 991 * 0.1));
	pointer->setOutlineThickness(10);
	pointer->setOutlineColor(Color::Red);
	pointer->setFillColor(Color::Transparent);
	pointer->setPosition(-500, -500);

	choseText = new Text("W�hle eine Karte aus:", *font, 30);
	choseText->setPosition(Vector2f(25, 300));
}
#pragma endregion

#pragma region Funktionen
void HomeMenu::drawPublic()
{
	window->draw(*backround);
	window->draw(*sideMenu);
	window->draw(*upperBorder);
	window->draw(*titel);
	window->draw(*drone);
	window->draw(*choseText);
	window->draw(*multiplayerMenue);
	window->draw(*exitButton);
	window->draw(*deleteSavesButton);
	window->draw(*credits);
	window->draw(*accountButton);

	if (isMultiplayerOpen)
	{
		window->draw(*host);
		window->draw(*client);
	}
	else
		window->draw(*startButton);
	for (int i = 0; i < Ressources::getInstance()->getMapCount(); i++)
	{
		window->draw(*map[i]);
	}

	for (int i = 0; i < Ressources::getInstance()->getTowerCount(); i++)
	{
		window->draw(*towers[i]);
	}
	if (choseIndex > -1)
	{
		window->draw(*pointer);
	}
}
int  HomeMenu::CheckClicked(Event event)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		//map clicked;
		isClicked = false;
		Vector2i mouse = Mouse::getPosition(*window);
		Vector2f pos, pos2;
		for (int i = 0; i < Ressources::getInstance()->getMapCount(); i++)
		{

			pos = Service::getInstance()->getObjectPosition(map[i]->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(map[i]->getPosition() + Vector2f(1920 * 0.1, 991 * 0.1));

			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				pointer->setPosition(Vector2f(map[i]->getPosition().x, map[i]->getPosition().y));
				choseIndex = i;
			}
		}

		Ressources* res = Ressources::getInstance();

		//Host clicked
		if (isMultiplayerOpen)
		{
			mouse = Mouse::getPosition(*window);
			pos = Service::getInstance()->getObjectPosition(host->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(host->getPosition() + Vector2f(100, 100));

			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				status = 2;

				if (multiplayerGUI->start(true))
				{
					delete multiplayerGUI;
					multiplayerGUI = new MultiplayerGUI(window);
					return 2;
				}
				else
				{
					delete multiplayerGUI;
					multiplayerGUI = new MultiplayerGUI(window);
					std::cout << "Multiplayer geschlossen" << std::endl;
					status = 0;
					return 0;
				}

			}

			//Client Clicked
			pos = Service::getInstance()->getObjectPosition(client->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(client->getPosition() + Vector2f(100, 100));

			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				status = 3;

				if (multiplayerGUI->start(false))
				{
					delete multiplayerGUI;
					multiplayerGUI = new MultiplayerGUI(window);
					return 3;
				}
				else
				{
					delete multiplayerGUI;
					multiplayerGUI = new MultiplayerGUI(window);
					std::cout << "Multiplayer geschlossen" << std::endl;
					status = 0;
					return 0;
				}

			}
		}
		else
		{
			//startclicked
			mouse = Mouse::getPosition(*window);

			pos = Service::getInstance()->getObjectPosition(startButton->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(startButton->getPosition() + Vector2f(100, 100));

			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				status = 1;
				return 1;
			}
		}
		//MultiplayerMunue
		pos = Service::getInstance()->getObjectPosition(multiplayerMenue->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(multiplayerMenue->getPosition() + Vector2f(250, 50));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			if (isMultiplayerOpen)
			{
				multiplayerMenue->setTexture(*res->getButtonMultiplayerTexture(1));
			}
			else
			{
				multiplayerMenue->setTexture(*res->getButtonMultiplayerTexture(0));
			}
			isMultiplayerOpen = !isMultiplayerOpen;
			return 0;
		}

		//Exit
		pos = Service::getInstance()->getObjectPosition(exitButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(exitButton->getPosition() + Vector2f(100, 100));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			window->close();
			exit(0);
			return 0;
		}

		//DeleteSaves
		pos = Service::getInstance()->getObjectPosition(deleteSavesButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(deleteSavesButton->getPosition() + Vector2f(200, 50));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			for (int i = 0; i < res->getMapCount(); i++)
			{
				deleteSave(i);
			}
			return 0;
		}

		//AccountButton
		pos = Service::getInstance()->getObjectPosition(accountButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(accountButton->getPosition() + Vector2f(accountButton->getTexture()->getSize()));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			AccountLogin* accLog = new AccountLogin(window, res);
			accLog->openAccountLoginWindow(&event);
			delete accLog;
			return 0;
		}

	}
	return 0;
}
void HomeMenu::HomeMenuStart()
{
	if (callCount > 1)
	{
		delete Game::getInstance();
	}
	callCount++;

	multiplayerGUI = new MultiplayerGUI(window);

	while (window->isOpen())
	{
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
				exit(0);
			}
		}

		drone->move(2, 0);
		setTowerTexture();
		if (drone->getPosition().x > 1920)
		{
			drone->setPosition(Vector2f(0, 300));
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
	if (status == 2)
	{
		std::string woIstDasEinBool = "dasIstEinString!";
		Multiplayer::send(16, woIstDasEinBool);
	}
	Game::getInstance()->setWindow(&*window);
	Game::getInstance()->setStatus(status);
	Game::getInstance()->startGame();
}
void HomeMenu::draw()
{
	window->clear();
	drawPublic();
	window->display();
}
bool HomeMenu::deleteSave(int index)
{
	std::ifstream FileTest("saves/savegame" + std::to_string(index) + ".sav"); //�berpr�ft ob die Datei existiert, wenn nicht wird false zur�ckgegeben
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
int HomeMenu::getStatus()
{
	return status;
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

		for (int i = 0; i < Ressources::getInstance()->getTowerCount(); i++)
		{
			towers[i]->setTexture(*textureTower[i][animationIndex]);
		}
		animation->restart();
	}

}
#pragma endregion

#pragma region Desturktor
#pragma endregion
