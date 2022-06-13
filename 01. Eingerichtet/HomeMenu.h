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
	/// Checkt, ob Zahlen 0-9 geklickt wird oder "." f�r die Eingabe der IP-Adersse
	/// </summary>
	/// <param name="event"></param>
	void eingabe(Event event);
	/// <summary>
	/// Checkt, ob etwas geklicht wurde
	/// </summary>
	/// <returns></returns>
	int CheckClicked();
	void draw();
	void deleteAllSaves();
	
	void setTowerTexture();

public:
	HomeMenu();
	
	static HomeMenu* getInstance();
	bool checkTestVersionEnd();
	int getChoseIndex();
	void setWindow(RenderWindow* window);
	void setTimeUntilTestVersionEnd(unsigned long long);

	void HomeMenuStart();
};

