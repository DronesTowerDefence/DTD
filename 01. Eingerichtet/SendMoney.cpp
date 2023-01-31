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

	font.loadFromFile("fonts/arial.ttf");

	inputText.setString(input);
	inputText.setFont(font);
	inputText.setCharacterSize(50);
	inputText.setFillColor(Color::White);
	inputText.setOutlineThickness(5);
	inputText.setOutlineColor(Color::Black);
	inputText.setPosition(Vector2f(1335, 200));

	buttonOpen.setTexture(*res->getSendMoneyButtonOpenTexture());
	buttonOpen.setPosition(Vector2f(1595, 150));

	buttonClose.setTexture(*res->getButtonCloseTexture());
	buttonClose.setPosition(Vector2f(1595, 150));

	background.setTexture(*res->getSendMoneyBackgroundTexture());
	background.setPosition(Vector2f(1295, 150));

}
#pragma endregion

#pragma region Funktionen
void SendMoney::checkClicked()
{
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
			pos = Service::getInstance()->getObjectPosition(buttonClose.getPosition());
			pos2 = Service::getInstance()->getObjectPosition(buttonClose.getPosition() + Vector2f(100, 100));
		}
		else
		{
			pos = Service::getInstance()->getObjectPosition(buttonOpen.getPosition());
			pos2 = Service::getInstance()->getObjectPosition(buttonOpen.getPosition() + Vector2f(100, 100));

		}

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			isOpen = !isOpen;
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
				inputText.setString(input);
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

			inputText.setString(input);

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
		if (Multiplayer::send(inputAsInt))
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
			window->draw(background);
			window->draw(inputText);
			window->draw(buttonClose);
		}
		else
		{
			window->draw(buttonOpen);
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
