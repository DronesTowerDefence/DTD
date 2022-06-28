#include "Multiplayer.h"
#include "Game.h"
#include "MultiplayerChat.h"

MultiplayerChat* MultiplayerChat::instance = nullptr;

#pragma region Konstruktor
MultiplayerChat::MultiplayerChat()
{
	res = Ressources::getInstance();
	window = Game::getInstance()->getWindow();

	font.loadFromFile("fonts/arial.ttf");

	isOpen = false;
	mouseClicked = false;
	inputDefaultText = true;
	chatNavigationHorizontal = 0;
	chatNavigationVertical = 0;
	defaultChatInput = "Deine Nachricht...";
	chatInput = defaultChatInput;

	rightChatBorder.setFillColor(Color::Red);
	rightChatBorder.setPosition(1665, 65);
	rightChatBorder.setSize(Vector2f(1, 750));

	bottomChatBorder.setFillColor(Color::Red);
	bottomChatBorder.setPosition(1300, 650);
	bottomChatBorder.setSize(Vector2f(400, 1));

	chatInputText.setString(chatInput);
	chatInputText.setPosition(Vector2f(1335, 750));
	chatInputText.setFont(font);
	chatInputText.setCharacterSize(20);
	chatInputText.setFillColor(Color::White);
	chatInputText.setOutlineThickness(3);
	chatInputText.setOutlineColor(Color::Black);

	chatOutputText.setString("");
	chatOutputText.setPosition(Vector2f(1335, 65));
	chatOutputText.setFont(font);
	chatOutputText.setCharacterSize(20);
	chatOutputText.setFillColor(Color::White);
	chatOutputText.setOutlineThickness(3);
	chatOutputText.setOutlineColor(Color::Black);

	buttonOpen.setTexture(*res->getOpenChatButtonTexture());
	buttonOpen.setPosition(Vector2f(1595, 25));

	buttonClose.setTexture(*res->getButtonCloseTexture());
	buttonClose.setPosition(Vector2f(1595, 25));

	chatBackground.setTexture(*res->getMultiplayerChatBackgroundTexture());
	chatBackground.setPosition(Vector2f(1295, 25));

}
#pragma endregion

#pragma region Funktionen
void MultiplayerChat::checkClicked()
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
void MultiplayerChat::checkInput(Event event)
{
	if (event.type == Event::KeyReleased && isOpen)
	{
		char tmp = '\0';

		tmp = HomeMenu::keyboardInput(event);

		if (tmp != '\0')
		{
			if (inputDefaultText)
			{
				chatInput = tmp;
				inputDefaultText = false;
			}
			else
			{
				chatInput += tmp;
			}
		}
		if (chatInput.size() == 0)
		{
			chatInput = defaultChatInput;
			inputDefaultText = true;
		}
		if (chatInputText.getGlobalBounds().intersects(rightChatBorder.getGlobalBounds()))
		{
			chatInput += "\n";
			int arrLeng = chatInput.size();
			char* arr = new char[arrLeng + 1];
			char tmpC1, tmpC2;
			strcpy_s(arr, arrLeng + 1, chatInput.c_str());

			tmpC1 = arr[arrLeng - 3];
			tmpC2 = arr[arrLeng - 1];

			arr[arrLeng - 1] = tmpC1;
			arr[arrLeng - 3] = tmpC2;

			chatInput = arr;
			chatInputText.setString(chatInput);
		}

		if (event.key.code == Keyboard::BackSpace && chatInput.size() > 0 && !inputDefaultText)
		{
			chatInput.erase(chatInput.size() - 1);
		}
		else if (event.key.code == Keyboard::Enter && chatInput.size() > 0 && !inputDefaultText)
		{
			if (!chatCommand())
			{
				addChatMessage(Game::getInstance()->getStatus(), chatInput); //TODO AccID
				Multiplayer::send(chatInput);
			}
			refreshChatOutput();
			chatInput = defaultChatInput;
			inputDefaultText = true;
			chatNavigationVertical = 0;
			chatNavigationHorizontal = 0;
		}

		if (event.key.code == Keyboard::Up && chatNavigationVertical < chatText.size())
		{
			chatNavigationVertical++;
		}
		else if (event.key.code == Keyboard::Down && chatNavigationVertical > 0)
		{
			chatNavigationVertical--;
			if (chatNavigationVertical == 0)
			{
				chatInput = defaultChatInput;
				inputDefaultText = true;
			}
		}

		if (event.key.code == Keyboard::Right && chatNavigationHorizontal < chatInput.size())
		{
			chatNavigationHorizontal++;
		}
		else if (event.key.code == Keyboard::Left && chatNavigationHorizontal > 0)
		{
			chatNavigationHorizontal--;
		}
	}
	checkChatNavigation();

	chatInputText.setString(chatInput);
}
void MultiplayerChat::refreshChatOutput()
{
	std::string str = "";
	int count = 0;
	for (auto iter : chatText)
	{
		count++;
		if (count == chatText.size())
		{
			str = iter->message;
		}
	}
	count = 0;

	int arrLeng = str.size();
	char tmpC;
	char* arr = new char[arrLeng + 1];
	strcpy_s(arr, arrLeng + 1, str.c_str());

	if (chatOutputText.getGlobalBounds().intersects(rightChatBorder.getGlobalBounds()))
	{
		unsigned int accID = 0;
		for (auto iter : chatText)
		{
			count++;
			if (count == chatText.size())
			{
				accID = iter->accountID;
			}
		}
		count = 0;


		for (int i = 0; i <= arrLeng; i++)
		{
			if (arr[i] == '\n')
			{
				std::string userName = std::to_string(accID); //TODO: AccountID zum Namen auflösen 
				int userNameLeng = userName.size();

				tmpC = arr[i];
				arr[i] = arr[i - userNameLeng - 4];
				arr[i - userNameLeng - 4] = tmpC;
			}
		}
		str = arr;

		for (auto iter : chatText)
		{
			count++;
			if (count == chatText.size())
			{
				iter->message = str;
			}
		}
		count = 0;
	}


	str = "";
	if (!chatText.empty())
	{
		for (auto i : chatText)
		{
			str += std::to_string(i->accountID); //TODO: AccountID zum Namen auflösen
			str += ": \"";
			str += i->message;
			str += "\"\n";
		}
	}
	chatOutputText.setString(str);

}
void MultiplayerChat::checkChatNavigation()
{
	if (chatNavigationVertical > 0)
	{
		int j = 0;
		for (auto i : chatText) //TODO: falschrum
		{
			j++;
			if (j == (chatText.size() + 1) - chatNavigationVertical)
			{
				chatInput = i->message;
				inputDefaultText = false;
			}
		}
	}
	else if (chatNavigationVertical == 0 && chatNavigationHorizontal > 0)
	{

	}
}
bool MultiplayerChat::chatCommand()
{
	bool stringIsCommand = false;
	int arrLeng = chatInput.size();
	char* arr = new char[arrLeng + 1];
	char tmpC1, tmpC2;
	strcpy_s(arr, arrLeng + 1, chatInput.c_str());

	if (arrLeng > 3 && (arr[0] == '#' && arr[1] == '+' && arr[2] == '#'))
	{
		std::string str = "", output = "Unknown Command";
		char value[10];
		int iValue = 0;
		size_t found;
		for (int i = 3; i <= arrLeng; i++)
		{
			str += tolower(arr[i]);
		}

		if (str.find("system") != std::string::npos)
		{
			if (str.size() > 7)
			{
				char cmdC[50];
				found = str.find(" ");
				str.copy(cmdC, 10, found);
				const char* cmdCC = cmdC;
				system(cmdCC);
				output = "Executed command: \"";
				output += cmdC;
				output += "\" succesfully";
			}
		}
		else if (str.find("addmoney") != std::string::npos)
		{
			if (str.size() > 9)
			{
				found = str.find(" ");
				str.copy(value, 10, found);
				Round::getInstance()->addMoney(stoi(value));
				output = "added ";
				output += value;
				output += " money";
			}
		}
		else if (str.find("submoney") != std::string::npos)
		{
			if (str.size() > 9)
			{
				found = str.find(" ");
				str.copy(value, 10, found);
				Round::getInstance()->submoney(stoi(value));
				output = "subtracted ";
				output += value;
				output += " money";
			}
		}
		else if (str.find("addhealth") != std::string::npos)
		{
			if (str.size() > 10)
			{
				found = str.find(" ");
				str.copy(value, 10, found);
				Round::getInstance()->addHealth(stoi(value));
				output = "added ";
				output += value;
				output += " health";
			}
		}
		else if (str.find("subhealth") != std::string::npos)
		{
			if (str.size() > 10)
			{
				found = str.find(" ");
				str.copy(value, 10, found);
				Round::getInstance()->subhealth(stoi(value));
				output = "subtracted ";
				output += value;
				output += " health";
			}
		}
		else if (str.find("setround") != std::string::npos)
		{
			if (str.size() > 9)
			{
				found = str.find(" ");
				str.copy(value, 10, found);
				Round::getInstance()->setIndex(stoi(value));
				output = "set round to ";
				output += value;
			}
		}
		else if (str.find("kickallplayer") != std::string::npos)
		{
			if (str.size() == 14)
			{
				res->newConnection();
				Game::getInstance()->setStatus(1);
				output = "kicked all players and switched to singleplayer";
			}
		}
		else if (str.find("killall") != std::string::npos)
		{
			if (str.size() == 8)
			{
				for (auto i : Round::getInstance()->getAllDrones())
				{
					delete i;
				}
				output = "destroyed all drones";
			}
		}
		else if (str.find("sellall") != std::string::npos)
		{
			if (str.size() == 8)
			{
				for (auto i : Round::getInstance()->getAllTowers())
				{
					Round::getInstance()->sellTower(i);
				}
				output = "sold all towers";
			}
		}
		else if (str.find("freeze") != std::string::npos)
		{
			if (str.size() > 6)
			{
				found = str.find(" ");
				str.copy(value, 10, found);

				Time time = seconds(std::stoi(value));
				Clock timer;

				while (timer.getElapsedTime() < time);

				output = "froze game for ";
				output += value;
				output += " seconds";
			}
		}
		else if (str.find("mainmenu") != std::string::npos)
		{
			if (str.size() == 9)
			{
				Game::getInstance()->mainMenu();
				output = "sent to mainmenu";
			}
		}
		else if (str.find("savegame") != std::string::npos)
		{
			if (str.size() == 8)
			{
				Game::getInstance()->saveGame();
				output = "saved the game";
			}
		}
		else if (str.find("deletesave") != std::string::npos)
		{
			if (str.size() > 14)
			{
				found = str.find(" ");
				str.copy(value, 10, found);
				if (std::stoi(value) < res->getMapCount() && std::stoi(value) >= 0)
				{
					HomeMenu::getInstance()->deleteSave(std::stoi(value));
					output = "deleted the saved the game";
				}
			}
		}

		addChatMessage(0, output);
		return true;
	}
	else return false;

}
int MultiplayerChat::stoi(char* c)
{
	int returnValue = 0;
	int size = 0;
	char tmp;

	for (; c[size] != '\0'; size++);

	for (int k = 0; k < size; k++)
	{
		tmp = c[k];
		c[k] = c[k + 1];
		c[k + 1] = tmp;


	}
	size--;

	for (int i = 0; i < size; i++)
	{
		returnValue *= 10;
		returnValue += (c[i] - 48);
	}

	return returnValue;
}
void MultiplayerChat::checkChat()
{
	checkClicked();
	if (isOpen)
		refreshChatOutput();
}
void MultiplayerChat::draw()
{
	if (isOpen)
	{
		window->draw(chatBackground);
		window->draw(chatOutputText);
		window->draw(chatInputText);
		window->draw(buttonClose);
		//window->draw(bottomChatBorder);
		//window->draw(rightChatBorder);
	}
	else
	{
		window->draw(buttonOpen);
	}
}
void MultiplayerChat::addChatMessage(int _accountID, std::string _message)
{
	chatText.push_back(new ChatMessage(_accountID, _message));

	refreshChatOutput();

	while (chatOutputText.getGlobalBounds().intersects(bottomChatBorder.getGlobalBounds()))
	{
		chatText.erase(chatText.begin());
		refreshChatOutput();
	}
}
#pragma endregion

#pragma region getter
MultiplayerChat* MultiplayerChat::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MultiplayerChat();
		return instance;
	}
	else return instance;
}

bool MultiplayerChat::getIsOpen()
{
	return isOpen;
}

#pragma endregion

#pragma region setter

#pragma endregion

#pragma region Destruktor
MultiplayerChat::~MultiplayerChat()
{
	instance = nullptr;
}
#pragma endregion