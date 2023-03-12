#pragma once
#include "SFML/Graphics.hpp"
#include "AccountServer.h"
using namespace sf;

class MultiplayerGUI
{
private:

	// Für die checkClicked-Funktion
	bool isClicked;

	// Ob Host
	bool isHost;

	// Ob das Fenster offen ist
	bool isOpen;

	// Ob Enter gedrückt wurde
	bool isStart;

	// Nur für draw, ob der Client sich mit dem Host verbunden hat
	bool isClientInHostLobby;

	// Ob das Spiel gestartet wurde (Host-Enter)
	bool startGame;

	// Thread?
	bool terminateThread;

	// Anzahl der Spieler
	int multiplayerPlayerCount;

	// Ausgewählte Map
	int mapChooseIndex;

	// Host-IP für Eingabe bei Client
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

	// Überprüft auf Tastendruck
	bool checkClicked(Event* event);

	// Drawt alles
	void draw();

	// Für die Eingabe der IP beim Client
	void ipAdressInput(Event* event);

	// Zum aktualisieren der Lobby (wenn z.B. jemand neues joined). Ohne Socket Kommunikation!
	bool updateLobby();

	// Verbindungsaufbau mit der Multiplayer-Klasse
	bool connect();

	// Stoppt den Thread (aus der connect-Methode)
	bool closeLobby();

public:
	MultiplayerGUI(RenderWindow* _window);
	~MultiplayerGUI();

	// main
	bool start(bool _isHost);

	std::string getHostIP();
	int getMultiplayerPlayerCount();
	void setChooseIndex(int);
	void setPlayerNames(int, std::string);
	void setPlayerProfilePictures(int index, Image* image);
	void setMultiplayerPlayerCount(int);
	void setStartGame(bool);
};

