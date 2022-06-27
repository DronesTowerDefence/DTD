#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
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
	
	unsigned long long timeUntilTestVersionEnd;

	bool isClicked;
	bool connected;
	bool isMultiplayerOpen;
	
	std::string ipAdress;
	std::string ownIpAdress;
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
	
	
	Clock* animation;
	Clock* timeUntilTestVersionEndClock;
	
	Font *font;
	Text *choseText;
	Text *ipAdressText;
	Text *ownIpAdressText;
	Text* credits;

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
	int CheckClicked();
	void draw();
	
	void setTowerTexture();

public:
	HomeMenu();
	
	static HomeMenu* getInstance();

	/// <summary>
	/// Überprüft auf eine Tastatureingabe
	/// </summary>
	/// <param name=""></param>
	/// <returns>Das Zeichen, welches gedrückt wurde</returns>
	static char keyboardInput(Event);

	bool checkTestVersionEnd();
	int getChoseIndex();
	void setWindow(RenderWindow* window);
	void setTimeUntilTestVersionEnd(unsigned long long);

	/// <summary>
	/// Löscht den Spielstand zur aktuellen Map
	/// </summary>
	/// <returns>True wenn erfolgreich</returns>
	/// <param>Map-Index, welcher Spielstand gelöscht werden soll</param>
	bool deleteSave(int);

	void HomeMenuStart();


};

