#pragma once
#include "Ressources.h"

/*
Hilfsklasse für die MultiplayerChat-Klasse um mehrere Daten in einer Liste zu speichern
*/
class ChatMessage
{
public:
	ChatMessage(int _accountID, std::string _message)
	{
		accountID = _accountID;
		message = _message;
	}

	/// <summary>
	/// Die Account-ID von der Person, welche die Nachricht geschrieben hat
	/// </summary>
	unsigned int accountID;
	/// <summary>
	/// Der Inhalt der Nachricht
	/// </summary>
	std::string message;
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

	int chatOutputLines;
	int chatNavigationVertical;
	int chatNavigationHorizontal;

	std::string chatInput;
	std::string defaultChatInput;

	std::list<ChatMessage*> chatText;

	Text chatInputText;
	Text chatOutputText;

	RectangleShape rightChatBorder;
	RectangleShape bottomChatBorder;

	Sprite buttonOpen;
	Sprite buttonClose;
	Sprite chatBackground;

	MultiplayerChat();
	void checkClicked();
	void refreshChatOutput();
	void checkChatNavigation();
	bool chatCommand();
	int stoi(char*);

public:

	void checkInput(Event);
	void checkChat();
	void draw();
	void addChatMessage(int, std::string);

	static MultiplayerChat* getInstance();
	bool getIsOpen();

	~MultiplayerChat();
};

