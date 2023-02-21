#include "Multiplayer.h"
#include "Game.h"
#include "SendMoney.h"
#include "Controls.h"

SendMoney* SendMoney::instance = nullptr;

#pragma region Konstruktor
SendMoney::SendMoney()
{
	res = Ressources::getInstance();
	window = Game::getInstance()->getWindow();

	input = "";
	inputAsInt = 0;
	maxSize = 6;
	isOpen = false;
	mouseClicked = false;

	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	inputText = new Text();
	inputText->setString(input);
	inputText->setFont(*font);
	inputText->setCharacterSize(50);
	inputText->setFillColor(Color::White);
	inputText->setOutlineThickness(5);
	inputText->setOutlineColor(Color::Black);
	inputText->setPosition(Vector2f(1335, 200));

	buttonOpen = new Sprite();
	buttonOpen->setTexture(*res->getSendMoneyButtonOpenTexture());
	buttonOpen->setPosition(Vector2f(1595, 150));

	buttonClose = new Sprite();
	buttonClose->setTexture(*res->getButtonCloseTexture());
	buttonClose->setPosition(Vector2f(1595, 150));

	for (int i = 0; i < 3; i++)
	{
		background[i] = new Sprite();
		playerName[i] = new Text();
	}
	if (Multiplayer::multiplayerPlayerCount > 0)
	{
		for (int i = 0; i < Multiplayer::multiplayerPlayerCount; i++)
		{
			background[i]->setTexture(*res->getSendMoneyBackgroundTexture());
			background[i]->setPosition(Vector2f(1295, 150 + i * 110));

			if (Game::getInstance()->getStatus() == 2)
			{
				playerName[i]->setString(Multiplayer::player[i]->getPlayerName());
			}
			else if (Game::getInstance()->getStatus() == 3)
			{
				playerName[i]->setString(Multiplayer::playerLight[i]->getPlayerName());
			}
			playerName[i]->setFont(*font);
			playerName[i]->setCharacterSize(30);
			playerName[i]->setFillColor(Color::White);
			playerName[i]->setOutlineThickness(3);
			playerName[i]->setOutlineColor(Color::Black);
			playerName[i]->setPosition(background[i]->getPosition().x + 20, background[i]->getPosition().y + 10);
		}

		chooseShape = new RectangleShape();
		chooseShape->setFillColor(Color::Transparent);
		chooseShape->setSize(Vector2f(res->getSendMoneyBackgroundTexture()->getSize()));
		chooseShape->setOutlineColor(Color::Red);
		chooseShape->setOutlineThickness(5);
		chooseShape->setPosition(background[0]->getPosition());
	}
}
#pragma endregion

#pragma region Funktionen
void SendMoney::checkClicked()
{
	if (!window->hasFocus())
		return;
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		mouseClicked = true;
	}
	if (mouseClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		mouseClicked = false;
		Vector2i mouse = Mouse::getPosition(*window);
		Vector2f pos, pos2;

		if (isOpen)
		{
			pos = Service::getInstance()->getObjectPosition(buttonClose->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(buttonClose->getPosition() + Vector2f(100, 100));
		}
		else
		{
			pos = Service::getInstance()->getObjectPosition(buttonOpen->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(buttonOpen->getPosition() + Vector2f(100, 100));
		}

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			isOpen = !isOpen;
		}

		if (isOpen)
		{
			for (int i = 0; i < Multiplayer::multiplayerPlayerCount; i++)
			{
				pos = Service::getInstance()->getObjectPosition(background[i]->getPosition());
				pos2 = Service::getInstance()->getObjectPosition(background[i]->getPosition() + Vector2f(background[i]->getTexture()->getSize()));
				if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
				{
					chooseShape->setPosition(background[i]->getPosition());
				}
			}
		}

	}
}
bool SendMoney::checkInput(Event event)
{
	if (isOpen)
	{
		if (event.type == Event::KeyReleased && isOpen)
		{
			if (event.key.code == Keyboard::Escape)
			{
				isOpen = false;
			}
			else if ((event.key.code == Keyboard::BackSpace && input.size() > 0) || input.size() > maxSize)
			{
				input.erase(input.size() - 1);
				inputText->setString(input);
			}
			else if (event.key.code == Keyboard::Enter && input.size() > 0)
			{
				send();
			}

			char tmp = '\0';
			tmp = Controls::checkKeyboardInput(&event);

			if (tmp < 48 || tmp > 57)
			{
				return false;
			}
			else
			{
				input += tmp;
			}

			inputText->setString(input);

			return true;
		}
	}
	else return false;
}

bool SendMoney::send()
{
	int arrLen = input.size();
	char* arr = new char[arrLen];
	strcpy_s(arr, arrLen + 1, input.c_str());
	inputAsInt = Service::getInstance()->stringToInt(arr);

	if (inputAsInt > 0 && Round::getInstance()->getMoney() >= inputAsInt)
	{
		std::string name = "???";

		for (int i = 0; i < Multiplayer::multiplayerPlayerCount; i++)
		{
			if (chooseShape->getPosition() == background[i]->getPosition())
			{
				name = playerName[i]->getString();
			}
		}

		if (Multiplayer::send(name, inputAsInt))
		{
			Round::getInstance()->submoney(inputAsInt);
			return true;
		}
		else
		{
			return false;
		}
	}
}
void SendMoney::checkSendMoney()
{
	if (Game::getInstance()->getStatus() != 1)
	{
		checkClicked();
	}
}
void SendMoney::draw()
{
	if (Game::getInstance()->getStatus() != 1)
	{
		if (isOpen)
		{
			for (int i = 0; i < Multiplayer::multiplayerPlayerCount; i++)
			{
				window->draw(*background[i]);
				window->draw(*playerName[i]);
			}
			window->draw(*inputText);
			window->draw(*chooseShape);
			window->draw(*buttonClose);
		}
		else
		{
			window->draw(*buttonOpen);
		}
	}
}
#pragma endregion

#pragma region getter
SendMoney* SendMoney::getInstance()
{
	if (instance == nullptr)
	{
		instance = new SendMoney();
		return instance;
	}
	else return instance;
}
bool SendMoney::getIsOpen()
{
	return isOpen;
}
#pragma endregion

#pragma region setter

#pragma endregion

#pragma region Destruktor

#pragma endregion
