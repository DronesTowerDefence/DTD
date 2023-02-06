#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
#include "Account.h"
#include "AccountServer.h"
#include "AccountLogin.h"
#include "SFML/Window/Clipboard.hpp"
using namespace sf;

class HomeMenu
{
private:
	
	static HomeMenu* instance;
	/// <summary>
	/// Index für gewählte Map (wichtig für Rotation, Bewegung & Spawn der Drohnen)
	/// </summary>
	int choseIndex; 
	int animationIndex;
	int callCount;
	/// <summary>
	/// 1 = Single
	/// 2 = Host
	/// 3 = Client
	/// </summary>
	int status; 
	
	int multiplayerPlayerCount;
	std::string gameID;

	bool isClicked;
	bool connected;
	bool isMultiplayerOpen;
	
	std::string ipAdress;
	Vector2f positionTower[5];

	RenderWindow* window;
	
	Texture* textureTower[5][4];	

	RectangleShape* pointer;
	RectangleShape* sideMenu;
	RectangleShape* upperBorder;

	Sprite* startButton;
	Sprite* towers[5];
	Sprite* map[3];
	Sprite* titel;
	Sprite* backround;
	Sprite* drone;
	Sprite* host;
	Sprite* client;
	Sprite* multiplayerMenue;
	Sprite* copy;
	Sprite* paste;
	Sprite* exitButton;
	Sprite* deleteSavesButton;
	Sprite* accountButton;
	
	Clock* animation;
	
	Font *font;
	Text *choseText;
	Text *ipAdressText;
	Text* credits;

	Thread* multiplayerConnectThread;

	Ressources* res;
	
	/// <summary>
	/// Checkt, ob Zahlen 0-9 geklickt wird oder "." für die Eingabe der IP-Adersse
	/// </summary>
	/// <param name="event"></param>
	void ipAdressInput(Event event);
	/// <summary>
	/// Checkt, ob etwas geklicht wurde
	/// </summary>
	/// <returns></returns>
	int CheckClicked(Event);
	
	void setTowerTexture();
	void draw();

public:
	HomeMenu();
	
	void drawPublic();

	static HomeMenu* getInstance();

	// bool checkTestVersionEnd();
	int getChoseIndex();

	std::string getIPAdress();

	void setWindow(RenderWindow* window);
	void setChoseIndex(int _choseIndex);

	/// <summary>
	/// Löscht den Spielstand zur aktuellen Map
	/// </summary>
	/// <returns>True wenn erfolgreich</returns>
	/// <param>Map-Index, welcher Spielstand gelöscht werden soll</param>
	bool deleteSave(int);

	void HomeMenuStart();


};

