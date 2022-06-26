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
	defaultChatInput = "Deine Nachricht...";
	chatInput = defaultChatInput;

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

		if (event.key.code == Keyboard::BackSpace && chatInput.size() > 0)
		{
			chatInput.erase(chatInput.size() - 1);
		}
		else if (event.key.code == Keyboard::Enter && chatInput.size() > 0)
		{
			addChatMessage(res->getOwnAccountID(), chatInput);
			refreshChatOutput();
			Multiplayer::send(chatInput);
			chatInput = defaultChatInput;
			inputDefaultText = true;
		}
		chatInputText.setString(chatInput);

	}
}
void MultiplayerChat::refreshChatOutput()
{
	std::string str = "";

	if (!chatText.empty())
	{
		for (auto i : chatText)
		{
			str += std::to_string(i->getAccountID()); //TODO: AccountID zum Namen auflösen
			str += ": \"";
			str += i->getMessage();
			str += "\"\n";
		}
	}

	chatOutputText.setString(str);
}
void MultiplayerChat::checkChat()
{
	checkClicked();
	refreshChatOutput();
}
void MultiplayerChat::draw()
{
	if (isOpen)
	{
		window->draw(chatBackground);
		window->draw(buttonClose);
		window->draw(chatOutputText);
		window->draw(chatInputText);
	}
	else
	{
		window->draw(buttonOpen);
	}
}
void MultiplayerChat::addChatMessage(int _accountID, std::string _message)
{
	if (chatText.size() > 24)
	{
		chatText.erase(chatText.begin());
		chatText.push_back(new ChatMessage(_accountID, _message));
	}
	else
	{
		chatText.push_back(new ChatMessage(_accountID, _message));
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

#pragma endregion

#pragma region setter

#pragma endregion

#pragma region Destruktor
MultiplayerChat::~MultiplayerChat()
{
	instance = nullptr;
}
#pragma endregion