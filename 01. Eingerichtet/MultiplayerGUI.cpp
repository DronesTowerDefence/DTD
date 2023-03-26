#include "MultiplayerGUI.h"
#include "Multiplayer.h"
#include "HomeMenu.h"
#include "Controls.h"
#include "PopUpMessage.h"

bool MultiplayerGUI::checkClicked(Event* event)
{
	if (!window->hasFocus())
		return 0;

	Vector2i mouse = Mouse::getPosition();

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2f pos, pos2;
		isClicked = false;

		//Close
		if (closeButton->checkHover(mouse))
		{
			isOpen = false;
			return true;
		}

		//Copy
		if (copyButton->checkHover(mouse))
		{
			Clipboard::setString(hostIP);
			return true;
		}

		//Paste
		if (pasteButton->checkHover(mouse))
		{
			hostIP = Clipboard::getString();
			ipText->setString("IP-Adresse:\n" + hostIP);
			return true;
		}

		//Start
		if (startButton->checkHover(mouse))
		{
			isStart = true;
			return true;
		}

		//Plus
		if (regulatePlayerCountButton[1]->checkHover(mouse))
		{
			if (multiplayerPlayerCount < 3)
			{
				setMultiplayerPlayerCount(multiplayerPlayerCount + 1);
			}
			return true;
		}

		//Minus
		if (regulatePlayerCountButton[0]->checkHover(mouse))
		{
			if (multiplayerPlayerCount > 1)
			{
				setMultiplayerPlayerCount(multiplayerPlayerCount - 1);
			}
			return true;
		}

		if (isHost)
		{
			//Map
			for (int i = 0; i < 3; i++)
			{
				pos = Service::getInstance()->getObjectPosition(maps[i]->getPosition());
				pos2 = Service::getInstance()->getObjectPosition(maps[i]->getPosition() + Vector2f(
					maps[i]->getTexture()->getSize().x * maps[i]->getScale().x, maps[i]->getTexture()->getSize().y * maps[i]->getScale().y));
				if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
				{
					setChooseIndex(i);
					return true;
				}
			}
		}
	}

	closeButton->checkHover(mouse);
	copyButton->checkHover(mouse);
	pasteButton->checkHover(mouse);
	startButton->checkHover(mouse);
	regulatePlayerCountButton[1]->checkHover(mouse);
	regulatePlayerCountButton[0]->checkHover(mouse);


	return false;
}

void MultiplayerGUI::draw()
{
	window->clear();
	HomeMenu::getInstance()->drawPublic();

	if (isOpen)
	{
		window->draw(*Ressources::getInstance()->getBlackBackgroundSprite());
		window->draw(*background);
		window->draw(*closeButton);
		window->draw(*ipText);
		window->draw(*copyButton);

		if (isHost || !isClientInHostLobby)
		{
			window->draw(*startButton);
		}

		if (isClientInHostLobby || isHost)
		{
			for (int i = 0; i < 3; i++)
			{
				window->draw(*maps[i]);
			}
			for (int i = 0; i < multiplayerPlayerCount + 1; i++)
			{
				window->draw(*playerNames[i]);
				window->draw(*profilePictures[i]);
			}
			window->draw(*mapChoose);
			window->draw(*multiplayerPlayerCountText);
		}

		if (isHost)
		{
			for (int i = 0; i < 2; i++)
			{
				window->draw(*regulatePlayerCountButton[i]);
			}
		}
		else if (!isClientInHostLobby)
		{
			window->draw(*pasteButton);
		}
	}
	window->display();
}

void MultiplayerGUI::ipAdressInput(Event* event) {

	if (event->type == Event::KeyReleased)
	{
		if (hostIP.length() < 15)
		{
			std::string c;
			c = Controls::checkKeyboardInput(event);
			if (c != "")
				hostIP += c;
		}
	}
	if (event->key.code == Keyboard::BackSpace)
	{
		if (hostIP.length() > 0)
		{
			hostIP.erase(hostIP.size() - 1);
		}
	}
	ipText->setString("IP-Adresse:\n" + hostIP);
}

bool MultiplayerGUI::updateLobby()
{
	if (isHost)
	{
		for (int i = 0; i < Multiplayer::multiplayerPlayerCount; i++)
		{
			playerNames[i]->setString(Multiplayer::player[i]->getPlayerName());
		}
	}
	else
	{
		for (int i = 0; i < Multiplayer::multiplayerPlayerCount + 1; i++)
		{
			if (Multiplayer::playerLight[i] != nullptr)
			{
				playerNames[i]->setString(Multiplayer::playerLight[i]->getPlayerName());
				setPlayerProfilePictures(i, Multiplayer::playerLight[i]->getProfileImage());
			}
		}
	}
	return false;
}

bool MultiplayerGUI::connect()
{
	// Verbindungsaufbau mit Threads
	if (multiplayerConnectThread == nullptr && !Multiplayer::initializeMultiplayerIsDone)
	{
		multiplayerConnectThread = new Thread(&Multiplayer::initializeMultiplayer, isHost);
		multiplayerConnectThread->launch();
	}
	else if (Multiplayer::initializeMultiplayerIsDone)
	{
		if (multiplayerConnectThread != nullptr)
		{
			multiplayerConnectThread->terminate();
			// delete multiplayerConnectThread;
			multiplayerConnectThread = nullptr;
		}
	}
	return Multiplayer::initializeMultiplayerIsDone;
}

bool MultiplayerGUI::closeLobby()
{
	if (!Multiplayer::initializeMultiplayerIsDone)
	{
		Multiplayer::checkMultiplayerConnect = false; //Sagt dem Thread, dass er zum Ende kommen soll
		new PopUpMessage("Spiel wird gestartet...");
		draw();
		while (!Multiplayer::initializeMultiplayerIsDone); //Wartet, bis der Thread zu Ende ist
	}

	//delete multiplayerConnectThread;
	//multiplayerConnectThread->terminate();
	multiplayerConnectThread = nullptr;
	return true;
}

#pragma region Konstruktor/Destruktor
MultiplayerGUI::MultiplayerGUI(RenderWindow* _window)
{
	isClicked = false;
	isHost = false;
	isOpen = false;
	isStart = false;
	startGame = false;
	multiplayerPlayerCount = 1;
	mapChooseIndex = 0;
	hostIP = IpAddress::getLocalAddress().toString();
	window = _window;
	accServer = new AccountServer();

	Ressources* res = Ressources::getInstance();
	Multiplayer::multiplayerPlayerCount = multiplayerPlayerCount;

	background = new Sprite();
	background->setTexture(*res->getAccountLoginBackground());
	background->setScale(Vector2f(1.5, 1));
	background->setPosition(Vector2f(360, 100));

	closeButton = new Button(Vector2f((background->getPosition().x + background->getTexture()->getSize().x * background->getScale().x - res->getButtonCloseTexture()->getSize().x), (background->getPosition().y)),
		res->getButtonCloseTexture());

	pasteButton = new Button(Vector2f(650, 600), res->getPasteTexture());
	copyButton = new Button(Vector2f(550, 600), res->getCopyTexture());
	startButton = new Button(Vector2f(550, 700), res->getButtonClientTexture());

	regulatePlayerCountButton[0] = new Button(Vector2f(520, 380), res->getregulateMultiplayerPlayerCountTexture(1));
	regulatePlayerCountButton[1] = new Button(Vector2f(650, 380), res->getregulateMultiplayerPlayerCountTexture(0));

	for (int i = 0; i < 3; i++)
	{
		maps[i] = new Sprite();
		maps[i]->setTexture(*res->getMapTexture(i));
		maps[i]->setScale(Vector2f(0.1, 0.1));
		maps[i]->setPosition(Vector2f(background->getPosition().x + 150 + i * (maps[i]->getTexture()->getSize().x * maps[i]->getScale().x + 50), background->getPosition().y + 100));
	}


	for (int i = 0; i < 4; i++)
	{
		profilePicturesTextures[i] = new Texture(*res->getAccountProfilePicture());
		profilePictures[i] = new Sprite();
		profilePictures[i]->setPosition(1025, 500 + i * 60);
		profilePictures[i]->setTexture(*profilePicturesTextures[i]);
		profilePictures[i]->setScale(Vector2f(40 / float(profilePicturesTextures[i]->getSize().x), 40 / float(profilePicturesTextures[i]->getSize().y)));
	}
	profilePicturesTextures[0] = new Texture();
	profilePicturesTextures[0]->loadFromImage(*Account::getProfileImage());
	profilePictures[0] = new Sprite();
	profilePictures[0]->setPosition(1025, 500 + 0 * 60);
	profilePictures[0]->setTexture(*profilePicturesTextures[0]);
	profilePictures[0]->setScale(Vector2f(40 / float(profilePicturesTextures[0]->getSize().x), 40 / float(profilePicturesTextures[0]->getSize().y)));


	mapChoose = new RectangleShape();
	mapChoose->setFillColor(Color::Transparent);
	mapChoose->setOutlineColor(Color::Red);
	mapChoose->setOutlineThickness(8);
	mapChoose->setSize(Vector2f(maps[0]->getTexture()->getSize().x * maps[0]->getScale().x, maps[0]->getTexture()->getSize().y * maps[0]->getScale().y));
	mapChoose->setPosition(maps[0]->getPosition());


	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	ipText = new Text();
	ipText->setFont(*font);
	ipText->setFillColor(Color::Black);
	ipText->setCharacterSize(50);
	ipText->setPosition(Vector2f(550, 470));
	ipText->setString("IP-Adresse:\n" + hostIP);

	multiplayerPlayerCountText = new Text();
	multiplayerPlayerCountText->setFont(*font);
	multiplayerPlayerCountText->setFillColor(Color::Black);
	multiplayerPlayerCountText->setCharacterSize(40);
	multiplayerPlayerCountText->setPosition(Vector2f(600, 380));
	multiplayerPlayerCountText->setString(std::to_string(multiplayerPlayerCount));

	for (int i = 0; i < 4; i++)
	{
		playerNames[i] = new Text();
		playerNames[i]->setFont(*font);
		playerNames[i]->setPosition(Vector2f(1100, 500 + i * 60));
		playerNames[i]->setFillColor(Color::Black);
		playerNames[i]->setCharacterSize(40);
		playerNames[i]->setString("<Player " + std::to_string(i + 1) + ">");
	}
	playerNames[0]->setString(Account::getAcc()->getAccName());
}

MultiplayerGUI::~MultiplayerGUI()
{
	if (accServer != nullptr)
	{
		delete accServer;
	}
	/*if (multiplayerConnectThread != nullptr)
	{
		multiplayerConnectThread->terminate();
		delete multiplayerConnectThread;
	}*/

	for (int i = 0; i < 4; i++)
	{
		if (playerNames[i] != nullptr)
			delete playerNames[i];
		if (i < 2 && regulatePlayerCountButton != nullptr)
			delete regulatePlayerCountButton[i];
		if (i < 3 && maps[i] != nullptr)
			delete maps[i];
	}
	delete background;
	delete closeButton;
	delete copyButton;
	delete pasteButton;
	delete startButton;
	delete mapChoose;
	delete font;
	delete ipText;
	delete multiplayerPlayerCountText;

	if (!Multiplayer::initializeMultiplayerIsDone)
	{
		Multiplayer::deleteMultiplayer();
		HomeMenu::getInstance()->setStatus(1);
	}
}
#pragma endregion

bool MultiplayerGUI::start(bool _isHost)
{
	if (Account::getAcc()->getAccName() == invalidUsername)
	{
		new PopUpMessage("Bitte vorher anmelden");
		return false;
	}
	isHost = _isHost;
	isOpen = true;

	setChooseIndex(0);

	Event* event = Controls::getEvent();
	while (window->isOpen() && isOpen)
	{
		while (window->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			if (!isHost)
			{
				ipAdressInput(event);
			}
			checkClicked(event);
			Controls::checkKeyboardInput(event);
			if (Controls::getEnterIsPressed())
				isStart = true;
		}
		draw();

		if (isHost)
		{
			isClientInHostLobby = true;
			connect();
		}

		if (isStart) //Button unten links gedr�ckt
		{
			if (isHost) //Wenn Host, dann wird das Spiel gestartet
			{
				closeLobby();
				startGame = true;
			}
			else //Wenn Client, dann wird eine Verbindung zum Host aufgebaut
			{
				connect();
				isClientInHostLobby = Multiplayer::player[0] != nullptr;
			}
			updateLobby();
		}

		if (startGame) return true;
	}

	if (multiplayerConnectThread != nullptr)
	{
		Multiplayer::checkMultiplayerConnect = false; //Beendet den Multiplayer-Thread
	}
	return false;
}

#pragma region getter/setter
std::string MultiplayerGUI::getHostIP()
{
	return hostIP;
}
int MultiplayerGUI::getMultiplayerPlayerCount()
{
	return multiplayerPlayerCount;
}
void MultiplayerGUI::setChooseIndex(int i)
{
	if (i >= 0)
	{
		mapChooseIndex = i;
		mapChoose->setPosition(maps[i]->getPosition());
		HomeMenu::getInstance()->setChoseIndex(i);
	}
}
void MultiplayerGUI::setPlayerNames(int i, std::string s)
{
	if (i >= 0 && i < 4)
	{
		playerNames[i]->setString(s);
	}
}
void MultiplayerGUI::setPlayerProfilePictures(int index, Image* image)
{
	if (index >= 0 && index < 4 && image != nullptr && image->getSize().x > 0 && image->getSize().x < 1000)
	{
		if (profilePicturesTextures[index] != nullptr)
		{
			delete profilePicturesTextures[index];
		}
		profilePicturesTextures[index] = new Texture();
		profilePicturesTextures[index]->loadFromImage(*image);

		if (profilePictures[index] != nullptr)
		{
			delete profilePictures[index];
		}
		profilePictures[index] = new Sprite();
		profilePictures[index]->setPosition(1025, 500 + index * 60);
		profilePictures[index]->setTexture(*profilePicturesTextures[index]);
		profilePictures[index]->setScale(Vector2f(40 / float(profilePicturesTextures[index]->getSize().x), 40 / float(profilePicturesTextures[index]->getSize().y)));
	}
}
void MultiplayerGUI::setMultiplayerPlayerCount(int i)
{
	if (i >= 0)
	{
		multiplayerPlayerCount = i;
		multiplayerPlayerCountText->setString(std::to_string(multiplayerPlayerCount));
	}
}
void MultiplayerGUI::setStartGame(bool b)
{
	startGame = b;
}
#pragma endregion