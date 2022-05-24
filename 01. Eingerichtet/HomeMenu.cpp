
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

	startButton = new Sprite;
	font = new Font();
	titel = new Sprite;
	backround = new Sprite();
	drone = new Sprite();
	multiplayerMenue = new Sprite();
	copy = new Sprite();
	paste = new Sprite();

	pointer = new RectangleShape;

	textureTitel = new Texture;
	textureBackround = new Texture;
	textureClient = new Texture();
	textureHost = new Texture();
	textureCloseMultiplayer = new Texture();
	textureOpenMultiplayer = new Texture();
	textureCopy = new Texture();
	texturePaste = new Texture();

	ipAdressText = new Text();

	res = Ressources::getInstance();
	ipAdress = "";
	ownIpAdress = IpAddress::getLocalAddress().toString();

	client = new Sprite();
	host = new Sprite();
	textureTitel->loadFromFile("img/titleText.png");
	textureBackround->loadFromFile("img/backround.jpg");
	font->loadFromFile("fonts/arial.ttf");
	textureCloseMultiplayer->loadFromFile("img/buttons/multiplayerButtonUp.png");
	textureOpenMultiplayer->loadFromFile("img/buttons/multiplayerButtonDown.png");
	textureCopy->loadFromFile("img/buttons/copyButton.png");//TODO
	texturePaste->loadFromFile("img/buttons/pasteButton.png");//TODO
	textureClient->loadFromFile("img/buttons/clientButton.png");
	textureHost->loadFromFile("img/buttons/hostButton.png");

	startButton->setTexture(*res->getButtonStartTexture());
	titel->setTexture(*textureTitel);
	backround->setTexture(*textureBackround);
	drone->setTexture(*res->getDroneTexture(1, 0));;
	multiplayerMenue->setTexture(*textureOpenMultiplayer);
	paste->setTexture(*texturePaste);
	copy->setTexture(*textureCopy);

	choseIndex = -1;

	host->setTexture(*textureHost);
	client->setTexture(*textureClient);

	startButton->setPosition(Vector2f(900, 700));
	titel->setPosition(Vector2f(0, 0));
	drone->setPosition(Vector2f(0, 300));
	host->setPosition(Vector2f(1100, 700));
	client->setPosition(Vector2f(1250, 700));
	copy->setPosition(Vector2f(1550, 841));
	paste->setPosition(Vector2f(1550, 941));
	multiplayerMenue->setPosition(Vector2f(1100, 600));

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
	textureTower[0][3]->loadFromFile("img/tower0/tower0_1.png");

	textureTower[1][0]->loadFromFile("img/tower1/tower1_0.png");
	textureTower[1][1]->loadFromFile("img/tower1/tower1_0.png");
	textureTower[1][2]->loadFromFile("img/tower1/tower1_0.png");
	textureTower[1][3]->loadFromFile("img/tower1/tower1_0.png");

	textureTower[2][0]->loadFromFile("img/tower2/tower2_0.png");
	textureTower[2][1]->loadFromFile("img/tower2/tower2_1.png");
	textureTower[2][2]->loadFromFile("img/tower2/tower2_2.png");
	textureTower[2][3]->loadFromFile("img/tower2/tower2_1.png");

	textureTower[3][0]->loadFromFile("img/tower3/tower3_0.png");
	textureTower[3][1]->loadFromFile("img/tower3/tower3_0.png");
	textureTower[3][2]->loadFromFile("img/tower3/tower3_0.png");
	textureTower[3][3]->loadFromFile("img/tower3/tower3_0.png");

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
	pointer->setOutlineColor(Color::Magenta);
	pointer->setFillColor(Color::Transparent);

	choseText = new Text("Waehle eine Karte aus", *font, 40);
	choseText->setPosition(Vector2f(500, 450));

	ipAdressText->setFont(*font);
	ipAdressText->setPosition(Vector2f(1620, 941));
	ipAdressText->setFillColor(Color::Black);
	ipAdressText->setCharacterSize(50);

	ownIpAdressText = new Text();
	ownIpAdressText->setFont(*font);
	ownIpAdressText->setPosition(Vector2f(1620, 841));
	ownIpAdressText->setFillColor(Color::Black);
	ownIpAdressText->setCharacterSize(50);
	ownIpAdressText->setString(ownIpAdress);


}
#pragma endregion

#pragma region Funktionen


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

bool  HomeMenu::CheckClicked()
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


		//Host clicked
		mouse = Mouse::getPosition(*window);
		pos = Service::getInstance()->getObjectPosition(host->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(host->getPosition() + Vector2f(100, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			status = 2;


			if (Ressources::getInstance()->getClient()->connect(ipAdress, 4567) != sf::Socket::Done)
			{

			}


			return true;
		}

		//Client Clicked
		pos = Service::getInstance()->getObjectPosition(client->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(client->getPosition() + Vector2f(100, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			status = 3;
			Ressources* res = Ressources::getInstance();
			if (res->getListener()->listen(4567))
			{
				std::cout << "Error Port";
			}


			if (res->getListener()->accept(*res->getClient()) != Socket::Done)
			{
				std::cout << "Error Client";
				//Error
			}
			Packet p;
			res->getClient()->receive(p);
			p >> choseIndex;
			res->getClient()->setBlocking(false);
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
				multiplayerMenue->setTexture(*textureCloseMultiplayer);
			}
			else
			{
				multiplayerMenue->setTexture(*textureOpenMultiplayer);
			}
			isMultiplayerOpen = !isMultiplayerOpen;
			return 0;


		}
	}
	return false;



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


		drone->move(2, 0);
		setTowerTexture();
		if (drone->getPosition().x > 1920)
		{
			drone->setPosition(Vector2f(0, 300));
		}
		if (CheckClicked() && choseIndex != -1)
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
	window->draw(*startButton);
	window->draw(*drone);
	window->draw(*choseText);
	window->draw(*multiplayerMenue);
	if (isMultiplayerOpen)
	{
		window->draw(*copy);
		window->draw(*paste);
		window->draw(*ipAdressText);
		window->draw(*host);
		window->draw(*ownIpAdressText);
		window->draw(*client);

	}
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
#pragma endregion


#pragma region Desturktor
#pragma endregion
