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
	bool startGame;
	bool terminateThread;
	int multiplayerPlayerCount;
	int mapChooseIndex;
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
	Sprite* profilePictures[4];
	Texture* profilePicturesTextures[4];
	RectangleShape* mapChoose;
	Font* font;
	Text* ipText;
	Text* playerNames[4];
	Text* multiplayerPlayerCountText;

	bool checkClicked(Event* event);
	void draw();
	void ipAdressInput(Event* event);
	bool updateLobby();
	bool connect();
	bool closeLobby();

public:
	MultiplayerGUI(RenderWindow* _window);
	~MultiplayerGUI();
	bool start(bool _isHost);

	std::string getHostIP();

	void setChooseIndex(int);
	void setPlayerNames(int, std::string);
	void setPlayerProfilePictures(int index, Image* image);
	void setMultiplayerPlayerCount(int);
	void setStartGame(bool);
};

