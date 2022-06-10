#include "HomeMenu.h"

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
	timeUntilTestVersionEnd = 0;
	res = Ressources::getInstance();
	ipAdress = "";
	ownIpAdress = IpAddress::getLocalAddress().toString();

	startButton = new Sprite;
	font = new Font();
	titel = new Sprite;
	backround = new Sprite();
	drone = new Sprite();
	multiplayerMenue = new Sprite();
	copy = new Sprite();
	paste = new Sprite();
	exitButton = new Sprite();
	client = new Sprite();
	host = new Sprite();
	deleteSavesButton = new Sprite();

	pointer = new RectangleShape;

	ipAdressText = new Text();

	font->loadFromFile("fonts/arial.ttf");

	startButton->setTexture(*res->getButtonStartTexture());
	titel->setTexture(*res->getTitleTextTexture());
	backround->setTexture(*res->getHomeMenuBackgroundTexture());
	drone->setTexture(*res->getDroneTexture(1, 0));;
	multiplayerMenue->setTexture(*res->getButtonMultiplayerTexture(1));
	paste->setTexture(*res->getPasteTexture());
	copy->setTexture(*res->getCopyTexture());
	host->setTexture(*res->getButtonHostTexture());
	client->setTexture(*res->getButtonClientTexture());
	exitButton->setTexture(*res->getButtonExitTexture());
	deleteSavesButton->setTexture(*res->getDeleteAllSavesButtonTexture());

	choseIndex = -1;


	startButton->setPosition(Vector2f(900, 700));
	titel->setPosition(Vector2f(0, 0));
	drone->setPosition(Vector2f(0, 300));
	host->setPosition(Vector2f(1100, 690));
	client->setPosition(Vector2f(1350, 690));
	copy->setPosition(Vector2f(1100, 831));
	paste->setPosition(Vector2f(1100, 931));
	multiplayerMenue->setPosition(Vector2f(1100, 600));
	exitButton->setPosition(Vector2f(20, 871));
	deleteSavesButton->setPosition(Vector2f(1700, 900));

	drone->setScale(2, 2);
	//
	int x = 500;
	for (int i = 0; i < Ressources::getInstance()->getMapCount(); i++, x += 242)
	{
		map[i] = new Sprite;
		map[i]->setScale(0.1, 0.1);
		map[i]->setTexture(*res->getMapTexture(i));
		map[i]->setPosition(Vector2f(x, 500));

	}
	positionTower[0] = Vector2f(100, 400);
	positionTower[1] = Vector2f(300, 500);
	positionTower[2] = Vector2f(700, 800);
	positionTower[3] = Vector2f(1400, 200);
	positionTower[4] = Vector2f(1570, 400);
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
	timeUntilTestVersionEndClock = new Clock();

	pointer->setSize(Vector2f(1920 * 0.1, 991 * 0.1));
	pointer->setOutlineThickness(10);
	pointer->setOutlineColor(Color::Magenta);
	pointer->setFillColor(Color::Transparent);

	choseText = new Text("Wähle eine Karte aus", *font, 40);
	choseText->setPosition(Vector2f(500, 450));

	ipAdressText->setFont(*font);
	ipAdressText->setPosition(Vector2f(1170, 931));
	ipAdressText->setFillColor(Color::Black);
	ipAdressText->setCharacterSize(50);

	ownIpAdressText = new Text();
	ownIpAdressText->setFont(*font);
	ownIpAdressText->setPosition(Vector2f(1170, 831));
	ownIpAdressText->setFillColor(Color::Black);
	ownIpAdressText->setCharacterSize(50);
	ownIpAdressText->setString(ownIpAdress);
}
#pragma endregion

#pragma region Funktionen
bool HomeMenu::checkTestVersionEnd()
{
	if (timeUntilTestVersionEndClock->getElapsedTime().asSeconds() > timeUntilTestVersionEnd)
	{
		window->close();
		return false;
	}
	else return true;
}
void HomeMenu::eingabe(Event event) {
	if (event.type == Event::KeyReleased)
	{

		if (ipAdress.size() < 15)
		{
			switch (event.key.code)
			{
			case Keyboard::Num0:
			case Keyboard::Numpad0:
				ipAdress += "0";
				break;

			case Keyboard::Num1:
			case Keyboard::Numpad1:
				ipAdress += "1";
				break;

			case Keyboard::Num2:
			case Keyboard::Numpad2:
				ipAdress += "2";
				break;

			case Keyboard::Num3:
			case Keyboard::Numpad3:
				ipAdress += "3";
				break;
			case Keyboard::Num4:
			case Keyboard::Numpad4:
				ipAdress += "4";
				break;
			case Keyboard::Num5:
			case Keyboard::Numpad5:
				ipAdress += "5";
				break;
			case Keyboard::Num6:
			case Keyboard::Numpad6:
				ipAdress += "6";
				break;
			case Keyboard::Num7:
			case Keyboard::Numpad7:
				ipAdress += "7";
				break;
			case Keyboard::Num8:
			case Keyboard::Numpad8:
				ipAdress += "8";
				break;
			case Keyboard::Num9:
			case Keyboard::Numpad9:
				ipAdress += "9";
				break;
			case Keyboard::Period:
				ipAdress += ".";
				break;

			default:
				break;
			}
			ipAdressText->setString(ipAdress);
		}
		if (event.key.code == Keyboard::BackSpace)
		{
			if (ipAdress.size() > 0)
			{
				ipAdress.erase(ipAdress.size() - 1);
			}
			ipAdressText->setString(ipAdress);

		}
	}
}
int  HomeMenu::CheckClicked()
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

			pos = Service::getInstance()->getObjectPosition(map[i]->getPosition()); //Holt sich die Position des Turmes i
			pos2 = Service::getInstance()->getObjectPosition(map[i]->getPosition() + Vector2f(1920 * 0.1, 991 * 0.1)); //Holt sich die Position des Turmes i + 50 wegen der Größe

			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
			{
				pointer->setPosition(Vector2f(map[i]->getPosition().x, map[i]->getPosition().y));
				choseIndex = i;
			}
		}

		Ressources* res = Ressources::getInstance();

		//Host clicked
		mouse = Mouse::getPosition(*window);
		pos = Service::getInstance()->getObjectPosition(host->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(host->getPosition() + Vector2f(100, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			status = 2;
			connected = true;

			if (res->getListener()->listen(4567))
			{
				connected = false;
			}

			if (res->getListener()->accept(*res->getReceiver()) != Socket::Done)
			{
				connected = false;
			}
			Packet p;
			while (res->getReceiver()->receive(p) != Socket::Done);

			std::string ip_client;
			p >> ip_client;
			res->setIpAddress(ip_client);

			if (Ressources::getInstance()->getSender()->connect(ip_client, 4568) != sf::Socket::Done)
			{
				//connected = false;
			}
			Packet p5;
			p5 << choseIndex;
			Ressources::getInstance()->getSender()->send(p5);

			res->getSender()->setBlocking(false);
			res->getReceiver()->setBlocking(false);


			return 2;
		}

		//Client Clicked
		pos = Service::getInstance()->getObjectPosition(client->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(client->getPosition() + Vector2f(100, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			connected = true;
			status = 3;

			res->setIpAddress(ipAdress);

			if (res->getSender()->connect(ipAdress, 4567) != sf::Socket::Done)
			{
				connected = false;
			}

			Packet p1;
			p1 << ownIpAdress;
			res->getSender()->send(p1);


			if (res->getListener()->listen(4568))
			{
				connected = false;
			}

			if (res->getListener()->accept(*res->getReceiver()) != Socket::Done)
			{
				connected = false;
			}
			Packet p2;

			while (res->getReceiver()->receive(p2));
			p2 >> choseIndex;
			res->getSender()->setBlocking(false);
			res->getReceiver()->setBlocking(false);

			return 3;
		}


		//startclicked
		mouse = Mouse::getPosition(*window);

		pos = Service::getInstance()->getObjectPosition(startButton->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(startButton->getPosition() + Vector2f(100, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			return 1;


		}

		//Copy
		pos = Service::getInstance()->getObjectPosition(copy->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(copy->getPosition() + Vector2f(50, 50)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			Clipboard::setString(IpAddress::getLocalAddress().toString());
			return 0;
		}



		//Paste
		pos = Service::getInstance()->getObjectPosition(paste->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(paste->getPosition() + Vector2f(50, 50)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			ipAdress = Clipboard::getString();
			ipAdressText->setString(ipAdress);
			return 0;


		}

		//MultiplayerMunue
		pos = Service::getInstance()->getObjectPosition(multiplayerMenue->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(multiplayerMenue->getPosition() + Vector2f(250, 50)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
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
		pos = Service::getInstance()->getObjectPosition(exitButton->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(exitButton->getPosition() + Vector2f(100, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			window->close();
			return 0;
		}

		//DeleteSaves
		pos = Service::getInstance()->getObjectPosition(deleteSavesButton->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(deleteSavesButton->getPosition() + Vector2f(200, 50)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			deleteAllSaves();
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

	while (window->isOpen())
	{ //test
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
			}
			eingabe(event);
		}

		checkTestVersionEnd();

		drone->move(2, 0);
		setTowerTexture();
		if (drone->getPosition().x > 1920)
		{
			drone->setPosition(Vector2f(0, 300));
		}
		int clicked = CheckClicked();
		if (clicked == 1 && choseIndex != -1) // singleplayer
		{
			break;
		}
		else if (clicked == 2 && choseIndex != -1 && connected)
		{
			break;
		}
		else if (clicked == 3 && connected && choseIndex != -1)
		{
			break;
		}

		draw();

	}
	Game::getInstance()->setWindow(&*window);
	Game::getInstance()->setStatus(status);
	Game::getInstance()->startGame();
}
void HomeMenu::draw()
{
	window->clear();
	window->draw(*backround);
	window->draw(*titel);
	window->draw(*drone);
	window->draw(*choseText);
	window->draw(*multiplayerMenue);
	window->draw(*exitButton);
	window->draw(*deleteSavesButton);
	if (isMultiplayerOpen)
	{
		window->draw(*copy);
		window->draw(*paste);
		window->draw(*ipAdressText);
		window->draw(*host);
		window->draw(*ownIpAdressText);
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

	window->display();
}
void HomeMenu::deleteAllSaves()
{
	for (int i = 0; i < res->getMapCount(); i++)
	{
		std::ifstream FileTest("saves/savegame" + std::to_string(i) + ".sav"); //Überprüft ob die Datei existiert
		if (!FileTest)
			continue;
		FileTest.close();
		std::string cmd_s = "del saves\\savegame" + std::to_string(i) + ".sav";
		const char* cmd_cc = cmd_s.c_str();
		system(cmd_cc);
		//delete cmd_cc;
	}
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
#pragma endregion

#pragma region setter
void HomeMenu::setWindow(RenderWindow* window)
{
	this->window = window;

}
void HomeMenu::setTimeUntilTestVersionEnd(unsigned long long _timeUntilTestVersionEnd)
{
	timeUntilTestVersionEnd = _timeUntilTestVersionEnd;
}
#pragma endregion


#pragma region Desturktor
#pragma endregion
