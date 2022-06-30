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

	sideMenu = new RectangleShape();
	pointer = new RectangleShape;
	upperBorder = new RectangleShape();

	ipAdressText = new Text();
	credits = new Text();

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
	credits->setFont(*font);
	credits->setCharacterSize(25);
	credits->setFillColor(Color::Black);
	credits->setString("© Amon Sarfo, Daniel Schmidt, Jonas Eberhardt, Tim Scheunert");
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
	copy->setPosition(Vector2f(500, 600));
	paste->setPosition(Vector2f(500, 700));
	multiplayerMenue->setPosition(Vector2f(500, 350));
	exitButton->setPosition(Vector2f(20, 871));
	deleteSavesButton->setPosition(Vector2f(1700, 900));

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
	timeUntilTestVersionEndClock = new Clock();

	pointer->setSize(Vector2f(1920 * 0.1, 991 * 0.1));
	pointer->setOutlineThickness(10);
	pointer->setOutlineColor(Color::Red);
	pointer->setFillColor(Color::Transparent);

	choseText = new Text("Wähle eine Karte aus:", *font, 30);
	choseText->setPosition(Vector2f(25, 300));

	ipAdressText->setFont(*font);
	ipAdressText->setPosition(Vector2f(570, 696));
	ipAdressText->setFillColor(Color::Black);
	ipAdressText->setCharacterSize(50);

	ownIpAdressText = new Text();
	ownIpAdressText->setFont(*font);
	ownIpAdressText->setPosition(Vector2f(570, 596));
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
void HomeMenu::ipAdressInput(Event event) {

	if (event.type == Event::KeyReleased)
	{
		if (ipAdress.size() < 15)
		{
			ipAdress += keyboardInput(event);
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
		mouse = Mouse::getPosition(*window);
		pos = Service::getInstance()->getObjectPosition(host->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(host->getPosition() + Vector2f(100, 100));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			status = 2;
			connected = true;

			if (connect(event)) return 2;
			else return 0;

			return 2;
		}

		//Client Clicked
		pos = Service::getInstance()->getObjectPosition(client->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(client->getPosition() + Vector2f(100, 100));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			connected = true;
			status = 3;

			if (connect(event)) return 3;
			else return 0;
		}

		//startclicked
		mouse = Mouse::getPosition(*window);

		pos = Service::getInstance()->getObjectPosition(startButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(startButton->getPosition() + Vector2f(100, 100));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			return 1;


		}

		//Copy
		pos = Service::getInstance()->getObjectPosition(copy->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(copy->getPosition() + Vector2f(50, 50));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			Clipboard::setString(IpAddress::getLocalAddress().toString());
			return 0;
		}



		//Paste
		pos = Service::getInstance()->getObjectPosition(paste->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(paste->getPosition() + Vector2f(50, 50));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			ipAdress = Clipboard::getString();
			ipAdressText->setString(ipAdress);
			return 0;


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
		while (!window->hasFocus());
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
			}
			ipAdressInput(event);
		}

		checkTestVersionEnd();

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
	window->draw(*sideMenu);
	window->draw(*upperBorder);
	window->draw(*titel);
	window->draw(*drone);
	window->draw(*choseText);
	window->draw(*multiplayerMenue);
	window->draw(*exitButton);
	window->draw(*deleteSavesButton);
	window->draw(*credits);
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
bool HomeMenu::deleteSave(int index)
{
	std::ifstream FileTest("saves/savegame" + std::to_string(index) + ".sav"); //Überprüft ob die Datei existiert, wenn nicht wird false zurückgegeben
	if (!FileTest)
		return false;

	std::string cmd_s = "del saves\\savegame" + std::to_string(index) + ".sav";
	const char* cmd_cc = cmd_s.c_str();
	system(cmd_cc); //TODO Funktioniert nicht

	return true;
}
char HomeMenu::keyboardInput(Event event)
{
	char c = '\0';

	switch (event.key.code)
	{
	case Keyboard::Num0:
	case Keyboard::Numpad0:
		c = '0';
		break;
	case Keyboard::Num1:
	case Keyboard::Numpad1:
		c = '1';
		break;
	case Keyboard::Num2:
	case Keyboard::Numpad2:
		c = '2';
		break;
	case Keyboard::Num3:
	case Keyboard::Numpad3:
		c = '3';
		break;
	case Keyboard::Num4:
	case Keyboard::Numpad4:
		c = '4';
		break;
	case Keyboard::Num5:
	case Keyboard::Numpad5:
		c = '5';
		break;
	case Keyboard::Num6:
	case Keyboard::Numpad6:
		c = '6';
		break;
	case Keyboard::Num7:
	case Keyboard::Numpad7:
		c = '7';
		break;
	case Keyboard::Num8:
	case Keyboard::Numpad8:
		c = '8';
		break;
	case Keyboard::Num9:
	case Keyboard::Numpad9:
		c = '9';
		break;
	case Keyboard::A:
		c = 'a';
		break;
	case Keyboard::B:
		c = 'b';
		break;
	case Keyboard::C:
		c = 'c';
		break;
	case Keyboard::D:
		c = 'd';
		break;
	case Keyboard::E:
		c = 'e';
		break;
	case Keyboard::F:
		c = 'f';
		break;
	case Keyboard::G:
		c = 'g';
		break;
	case Keyboard::H:
		c = 'h';
		break;
	case Keyboard::I:
		c = 'i';
		break;
	case Keyboard::J:
		c = 'j';
		break;
	case Keyboard::K:
		c = 'k';
		break;
	case Keyboard::L:
		c = 'l';
		break;
	case Keyboard::M:
		c = 'm';
		break;
	case Keyboard::N:
		c = 'n';
		break;
	case Keyboard::O:
		c = 'o';
		break;
	case Keyboard::P:
		c = 'p';
		break;
	case Keyboard::Q:
		c = 'q';
		break;
	case Keyboard::R:
		c = 'r';
		break;
	case Keyboard::S:
		c = 's';
		break;
	case Keyboard::T:
		c = 't';
		break;
	case Keyboard::U:
		c = 'u';
		break;
	case Keyboard::V:
		c = 'v';
		break;
	case Keyboard::W:
		c = 'w';
		break;
	case Keyboard::X:
		c = 'x';
		break;
	case Keyboard::Y:
		c = 'y';
		break;
	case Keyboard::Z:
		c = 'z';
		break;
	case Keyboard::Period:
		c = '.';
		break;
	case Keyboard::Add:
		c = '+';
		break;
	case Keyboard::Comma:
		c = ',';
		break;
	case Keyboard::Dash:
		c = '-';
		break;
	case Keyboard::Divide:
		c = '/';
		break;
	case Keyboard::Equal:
		c = '=';
		break;
	case Keyboard::Multiply:
		c = '*';
		break;
	case Keyboard::Quote:
		c = '"';
		break;
	case Keyboard::Semicolon:
		c = ';';
		break;
	case Keyboard::Slash:
		c = '#';
		break;
	case Keyboard::Space:
		c = ' ';
		break;
	case Keyboard::Subtract:
		c = '-';
		break;
	case Keyboard::Tilde:
		c = '~';
		break;


	default:
		c = '\0';
	}

	return c;
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
bool HomeMenu::connect(Event event)
{
	res->getSender()->setBlocking(false);
	res->getReceiver()->setBlocking(false);
	res->getListener()->setBlocking(false);

	if (status == 2) //Erneuter Verbindungsaufbau, wenn Host
	{
		res->getListener()->listen(4567); //Horcht am Port

		while (res->getListener()->accept(*res->getReceiver()) != Socket::Done) //Stellt Verbindung her
		{
			while (!window->hasFocus());
			while (window->pollEvent(event)) //Überprüft, ob das Fenster geschlossen wird
			{
				if (event.type == Event::Closed)
				{
					window->close();
					return 0;
				}
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)	return false;
			}
		}

		Packet p;
		std::string ip_client;
		p >> ip_client;
		res->setIpAddress(ip_client);

		while (res->getSender()->connect(res->getIpAddress(), 4568) != Socket::Done) //Verbindet sich mit dem Client
		{
			while (!window->hasFocus());
			while (window->pollEvent(event)) //Überprüft, ob das Fenster geschlossen wird
			{
				if (event.type == Event::Closed)
				{
					window->close();
					return false;
				}
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) return false;
			}
		}

		Packet p5;
		p5 << choseIndex;
		Ressources::getInstance()->getSender()->send(p5);

		return true;
	}
	else if (status == 3) //Erneuter Verbindungsaufbau, wenn Client
	{
		res->setIpAddress(ipAdress);

		while (res->getSender()->connect(res->getIpAddress(), 4567) != Socket::Done) //Verbindet sich mit dem Host
		{
			while (!window->hasFocus());
			while (window->pollEvent(event)) //Überprüft, ob das Fenster geschlossen wird
			{
				if (event.type == Event::Closed)
				{
					window->close();
					return false;
				}
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) return false;
			}
		}

		Packet p1;
		p1 << ownIpAdress;
		res->getSender()->send(p1);

		res->getListener()->listen(4568); //Horcht am Port

		while (res->getListener()->accept(*res->getReceiver()) != Socket::Done) //Stellt Verbindung her
		{
			while (!window->hasFocus());
			while (window->pollEvent(event)) //Überprüft, ob das Fenster geschlossen wird
			{
				if (event.type == Event::Closed)
				{
					window->close();
					return false;
				}
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) return false;
			}
		}

		Packet p2;
		while (res->getReceiver()->receive(p2));
		p2 >> choseIndex;

		return true;
	}
}
#pragma endregion

#pragma region Desturktor
#pragma endregion
