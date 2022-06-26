#pragma once
#include "Ressources.h"

/*
Hilfsklasse für die MultiplayerChat-Klasse um mehrere Daten in einer Liste zu speichern
*/
class ChatMessage
{
private:
	/// <summary>
	/// Der Inhalt der Nachricht
	/// </summary>
	std::string message;

	/// <summary>
	/// Die Account-ID von der Person, welche die Nachricht geschrieben hat
	/// </summary>
	unsigned int accountID;

public:
	ChatMessage(int _accountID, std::string _message)
	{
		accountID = _accountID;
		message = _message;
	}

	/// <returns>Die Account-ID von der Person, welche die Nachricht geschrieben hat</returns>
	int getAccountID()
	{
		return accountID;
	}

	/// <returns>Den Inhalt der Nachricht</returns>
	std::string getMessage()
	{
		return message;
	}
};

/*
Die Klasse ist für den Multiplayerchat in einem Spiel zuständig
*/
class MultiplayerChat
{
private:

	static MultiplayerChat* instance;
	Ressources* res;
	RenderWindow* window;
	Font font;

	bool isOpen;
	bool mouseClicked;
	bool inputDefaultText;
	std::string chatInput;
	std::string defaultChatInput;

	Text chatInputText;
	Text chatOutputText;
	std::list<ChatMessage*> chatText;
	Sprite buttonOpen;
	Sprite buttonClose;
	Sprite chatBackground;

	MultiplayerChat();
	void checkClicked();
	void refreshChatOutput();

public:

	void checkInput(Event);
	void checkChat();
	void draw();
	void addChatMessage(int, std::string);

	static MultiplayerChat* getInstance();
	bool getIsOpen();

	~MultiplayerChat();
};

