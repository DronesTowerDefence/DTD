#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
#include "Account.h"
#include "AccountServer.h"
#include "AccountLogin.h"
#include "MultiplayerGUI.h"
#include "AchievementGUI.h"
#include "ShopGUI.h"
#include "SkinsGUI.h"
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

	bool isClicked;
	bool connected;
	bool isMultiplayerOpen;
	bool menuIsOpen;

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
	Sprite* exitButton;
	Sprite* deleteSavesButton;
	Sprite* accountButton;
	Sprite* accountFriendsMenuButton;
	Sprite* achievementsButton;
	Sprite* dailyButton;
	Sprite* shopButton;
	Sprite* skinsButton;
	Sprite* openMenuButton;

	Clock* animation;

	Font* font;
	Text* choseText;
	Text* credits;

	MultiplayerGUI* multiplayerGUI;
	AchievementGUI* achievementGUI;
	ShopGUI* shopGUI;
	AccountServer* accServer;
	SkinsGUI* skinsGUI;
	Daily* daily;

	Ressources* res;

	/// <summary>
	/// Checkt, ob etwas geklicht wurde
	/// </summary>
	/// <returns></returns>
	int CheckClicked(Event*);

	std::string chalange;

	void setTowerTexture();
	void draw();

public:
	HomeMenu();

	void drawPublic();

	static HomeMenu* getInstance();

	// bool checkTestVersionEnd();
	int getChoseIndex();
	MultiplayerGUI* getMultiplayerGUI();
	ShopGUI* getShopGUI();
	int getStatus();
	RenderWindow* getWindow();

	void setWindow(RenderWindow* window);
	void setChoseIndex(int _choseIndex);
	void setStatus(int _status);

	/// <summary>
	/// Löscht den Spielstand zur aktuellen Map
	/// </summary>
	/// <returns>True wenn erfolgreich</returns>
	/// <param>Map-Index, welcher Spielstand gelöscht werden soll</param>
	bool deleteSave(int);

	void HomeMenuStart();

	void startGame();

	void loadDaily();

	Daily* getDaily();
};

