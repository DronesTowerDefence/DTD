#include "MultiplayerGUI.h"
#include "Multiplayer.h"
#include "HomeMenu.h"
#include "Controls.h"

bool MultiplayerGUI::checkClicked(Event* event)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2f pos, pos2;
		Vector2i mouse = Mouse::getPosition();
		isClicked = false;

		//Close
		pos = Service::getInstance()->getObjectPosition(closeButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(closeButton->getPosition() + Vector2f(closeButton->getTexture()->getSize()));
		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			isOpen = false;
			return true;
		}

		//Copy
		pos = Service::getInstance()->getObjectPosition(copyButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(copyButton->getPosition() + Vector2f(50, 50));
		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			Clipboard::setString(gameID);
			return true;
		}

		//Paste
		pos = Service::getInstance()->getObjectPosition(pasteButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(pasteButton->getPosition() + Vector2f(50, 50));
		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			gameID = Clipboard::getString();
			gameIDText->setString("Spiel-ID: " + gameID);
			return true;
		}

		//Start
		pos = Service::getInstance()->getObjectPosition(startButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(startButton->getPosition() + Vector2f(200, 100));
		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			isStart = true;
			return true;
		}

		//Plus
		pos = Service::getInstance()->getObjectPosition(regulatePlayerCountButton[1]->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(regulatePlayerCountButton[1]->getPosition() + Vector2f(50, 50));
		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			if (multiplayerPlayerCount < 4)
			{
				setMultiplayerPlayerCount(multiplayerPlayerCount + 1);
			}
			return true;
		}

		//Minus
		pos = Service::getInstance()->getObjectPosition(regulatePlayerCountButton[0]->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(regulatePlayerCountButton[0]->getPosition() + Vector2f(50, 50));
		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
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
					mapChooseIndex = i;
					mapChoose->setPosition(maps[i]->getPosition());
					Multiplayer::send(13, std::to_string(mapChooseIndex));
					return true;
				}
			}
		}
	}
	return false;
}

void MultiplayerGUI::draw()
{
	window->clear();
	HomeMenu::getInstance()->drawPublic();

	if (isOpen)
	{
		window->draw(*background);
		window->draw(*closeButton);
		window->draw(*gameIDText);
		window->draw(*copyButton);
		window->draw(*startButton);

		if (isClientInHostLobby || isHost)
		{
			for (int i = 0; i < 3; i++)
			{
				window->draw(*maps[i]);
			}
			for (int i = 0; i < multiplayerPlayerCount + 1; i++)
			{
				window->draw(*playerNames[i]);
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
		else
		{
			window->draw(*pasteButton);
		}
	}
	window->display();
}

void MultiplayerGUI::gameIDInput(Event* event) {

	if (event->type == Event::KeyReleased)
	{
		if (gameID.length() < 4)
		{
			gameID += Controls::checkKeyboardInput(event);
		}
		if (gameID == "0000")
		{
			gameID = Controls::checkKeyboardInput(event);
		}
	}
	if (event->key.code == Keyboard::BackSpace)
	{
		if (gameID.length() > 0)
		{
			gameID.erase(gameID.size() - 1);
		}
	}
	gameIDText->setString("Spiel-ID: " + gameID);
}

bool MultiplayerGUI::updateLobby()
{
	if (!isHost && Multiplayer::initializeMultiplayerIsDone)
	{
		Multiplayer::receive();
		// MapChooseIndex und playerLight werden in der receive-Funktion gesetzt
	}

	for (int i = 0; i < Multiplayer::multiplayerPlayerCount + 1; i++)
	{
		if (isHost)
		{
			playerNames[i]->setString(Multiplayer::player[i]->getPlayerName());
		}
		else
		{
			if (Multiplayer::playerLight[i] != nullptr)
			{
				playerNames[i]->setString(Multiplayer::playerLight[i]->getPlayerName());
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
			delete multiplayerConnectThread;
			multiplayerConnectThread = nullptr;
		}
	}
	return Multiplayer::initializeMultiplayerIsDone;
}

bool MultiplayerGUI::closeLobby()
{
	if (!Multiplayer::initializeMultiplayerIsDone)
	{
		multiplayerConnectThread->terminate();

	}

	delete multiplayerConnectThread;
	multiplayerConnectThread = nullptr;
	Multiplayer::initializeMultiplayerIsDone = true;

	return true;
}

MultiplayerGUI::MultiplayerGUI(RenderWindow* _window)
{
	isClicked = false;
	isHost = false;
	isOpen = false;
	isStart = false;
	startGame = false;
	multiplayerPlayerCount = 1;
	mapChooseIndex = 0;
	gameID = "0000";
	hostIP = "000.000.000.00";
	window = _window;
	accServer = new AccountServer();

	Ressources* res = Ressources::getInstance();
	Multiplayer::multiplayerPlayerCount = multiplayerPlayerCount;

	background = new Sprite();
	background->setTexture(*res->getAccountLoginBackground());
	background->setScale(Vector2f(1.5, 1));
	background->setPosition(Vector2f(360, 100));

	closeButton = new Sprite();
	closeButton->setTexture(*res->getButtonCloseTexture());
	closeButton->setPosition(Vector2f((background->getPosition().x + background->getTexture()->getSize().x * background->getScale().x - closeButton->getTexture()->getSize().x), (background->getPosition().y)));

	pasteButton = new Sprite();
	pasteButton->setTexture(*res->getPasteTexture());
	pasteButton->setPosition(Vector2f(650, 600));

	copyButton = new Sprite();
	copyButton->setTexture(*res->getCopyTexture());
	copyButton->setPosition(Vector2f(550, 600));

	startButton = new Sprite();
	startButton->setTexture(*res->getButtonClientTexture());
	startButton->setPosition(550, 700);

	regulatePlayerCountButton[0] = new Sprite();
	regulatePlayerCountButton[1] = new Sprite();
	regulatePlayerCountButton[0]->setTexture(*res->getregulateMultiplayerPlayerCountTexture(1));
	regulatePlayerCountButton[1]->setTexture(*res->getregulateMultiplayerPlayerCountTexture(0));
	regulatePlayerCountButton[0]->setPosition(Vector2f(520, 380));
	regulatePlayerCountButton[1]->setPosition(Vector2f(650, 380));

	for (int i = 0; i < 3; i++)
	{
		maps[i] = new Sprite();
		maps[i]->setTexture(*res->getMapTexture(i));
		maps[i]->setScale(Vector2f(0.1, 0.1));
		maps[i]->setPosition(Vector2f(background->getPosition().x + 150 + i * (maps[i]->getTexture()->getSize().x * maps[i]->getScale().x + 50), background->getPosition().y + 100));
	}

	mapChoose = new RectangleShape();
	mapChoose->setFillColor(Color::Transparent);
	mapChoose->setOutlineColor(Color::Red);
	mapChoose->setOutlineThickness(8);
	mapChoose->setSize(Vector2f(maps[0]->getTexture()->getSize().x * maps[0]->getScale().x, maps[0]->getTexture()->getSize().y * maps[0]->getScale().y));
	mapChoose->setPosition(maps[0]->getPosition());

	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	gameIDText = new Text();
	gameIDText->setFont(*font);
	gameIDText->setFillColor(Color::Black);
	gameIDText->setCharacterSize(50);
	gameIDText->setPosition(Vector2f(550, 500));
	gameIDText->setString("Spiel-ID: " + gameID);

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

bool MultiplayerGUI::start(bool _isHost)
{
	isHost = _isHost;
	isOpen = true;

	if (isHost)
	{
		gameID = accServer->sendHostIP();
	}

	Event event;
	while (window->isOpen() && isOpen)
	{
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			gameIDInput(&event);
			checkClicked(&event);
		}
		draw();

		if (isHost)
		{
			isClientInHostLobby = true;
			connect();
		}


		if (isStart)
		{
			if (isHost)
			{
				closeLobby();
				startGame = true;
			}
			else
			{
				isClientInHostLobby = connect();
			}
			updateLobby();

		}

		if (startGame) return true;
	}
	return false;
}

std::string MultiplayerGUI::getGameID()
{
	return gameID;
}

std::string MultiplayerGUI::getHostIP()
{
	return hostIP;
}

void MultiplayerGUI::setChooseIndex(int i)
{
	if (i >= 0)
	{
		mapChooseIndex = i;
		mapChoose->setPosition(maps[i]->getPosition());
	}
}

void MultiplayerGUI::setPlayerNames(int i, std::string s)
{
	if (i >= 0 && i < 4)
	{
		playerNames[i]->setString(s);
	}
}

void MultiplayerGUI::setMultiplayerPlayerCount(int i)
{
	if (i >= 0)
	{
		multiplayerPlayerCount = i;
		multiplayerPlayerCountText->setString(std::to_string(multiplayerPlayerCount));
		if (isHost)
		{
			Multiplayer::send(15, std::to_string(multiplayerPlayerCount));
		}
		Multiplayer::multiplayerPlayerCount = multiplayerPlayerCount;
		Multiplayer::updatePlayerCount();
	}
}

void MultiplayerGUI::setStartGame(bool b)
{
	startGame = b;
}
