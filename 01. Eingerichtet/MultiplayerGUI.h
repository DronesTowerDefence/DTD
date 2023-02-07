#pragma once
#include "SFML/Graphics.hpp"
#include "AccountServer.h"
using namespace sf;

class MultiplayerGUI
{
private:

	bool isClicked;
	bool isHost;
	bool isOpen;
	bool isStart;
	bool isClientInHostLobby;
	int multiplayerPlayerCount;
	int mapChooseIndex;
	std::string gameID;
	std::string hostIP;

	RenderWindow* window;
	AccountServer* accServer;
	Thread* multiplayerConnectThread;

	Sprite* background;
	Sprite* closeButton;
	Sprite* copyButton;
	Sprite* pasteButton;
	Sprite* startButton;
	Sprite* regulatePlayerCountButton[2];
	Sprite* maps[3];
	RectangleShape* mapChoose;
	Font* font;
	Text* gameIDText;
	Text* playerNames[4];
	Text* multiplayerPlayerCountText;

	bool checkClicked(Event* event);
	void draw();
	void gameIDInput(Event* event);
	bool updateLobby();
	bool connect();

public:
	MultiplayerGUI(RenderWindow* _window);
	bool start(bool _isHost);

	std::string getGameID();
	std::string getHostIP();

	void setChooseIndex(int);
	void setPlayerNames(int, std::string);
	void setMultiplayerPlayerCount(int);
};

