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

	buttonOpen = new Button(Vector2f(1595, 150), res->getSendMoneyButtonOpenTexture());
	buttonClose = new Button(Vector2f(1595, 150), res->getButtonCloseTexture());

	for (int i = 0; i < 3; i++)
	{
		playerName[i] = new Text();
	}
	if (Multiplayer::multiplayerPlayerCount > 0)
	{
		for (int i = 0; i < Multiplayer::multiplayerPlayerCount; i++)
		{
			background[i] = new Button(Vector2f(1295, 150 + i * 110), res->getSendMoneyBackgroundTexture());

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
			playerName[i]->setStyle(Text::Underlined);
			playerName[i]->setPosition(background[i]->getPosition().x + 35, background[i]->getPosition().y + 25);
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

	Vector2i mouse = Mouse::getPosition(*window);

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		mouseClicked = true;
	}
	if (mouseClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		mouseClicked = false;
		Vector2f pos, pos2;

		if (!isOpen && buttonOpen->checkHover(mouse))
		{
			isOpen = true;
		}
		else if (isOpen && buttonClose->checkHover(mouse))
		{
			isOpen = false;
		}

		if (isOpen)
		{
			for (int i = 0; i < Multiplayer::multiplayerPlayerCount; i++)
			{
				if (background[i]->checkHover(mouse))
				{
					chooseShape->setPosition(background[i]->getPosition());
				}
			}
		}
	}

	buttonClose->checkHover(mouse);
	buttonOpen->checkHover(mouse);
	for (int i = 0; i < Multiplayer::multiplayerPlayerCount; i++)
	{
		background[i]->checkHover(mouse);
	}
}
bool SendMoney::checkInput(Event* event)
{
	if (isOpen)
	{
		if (event->type == Event::KeyReleased && isOpen)
		{
			if (event->key.code == Keyboard::Escape)
			{
				isOpen = false;
			}
			else if ((event->key.code == Keyboard::BackSpace && input.size() > 0) || input.size() > maxSize)
			{
				input.erase(input.size() - 1);
				inputText->setString(input);
			}
			else if (event->key.code == Keyboard::Enter && input.size() > 0)
			{
				send();
			}

			std::string tmp = "";
			tmp = Controls::checkKeyboardInput(event);

			if (tmp[0] >= 48 && tmp[0] <= 57)
			{
				input += tmp;
				inputText->setString(input);
			}

			return true;
		}
	}
	else return false;
}
bool SendMoney::send()
{
	inputAsInt = Service::getInstance()->stringToInt(input);

	if (inputAsInt > 0 && Round::getInstance()->getMoney() >= inputAsInt)
	{
		std::string name = invalidUsername;

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
	//return; //TODO
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
