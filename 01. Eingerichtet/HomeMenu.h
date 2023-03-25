#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window/Clipboard.hpp"
#include "Game.h"
#include "Service.h"
#include "Account.h"
#include "AccountServer.h"
#include "AccountLogin.h"
#include "MultiplayerGUI.h"
#include "AchievementGUI.h"
#include "ShopGUI.h"
#include "SkinsGUI.h"
#include "Credits.h"
#include "Button.h"
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
	Music music;
	RenderWindow* window;

	Texture* textureTower[5][4];

	RectangleShape* pointer;
	RectangleShape* sideMenu;
	RectangleShape* upperBorder;

	Sprite* towers[5];
	Sprite* map[4];
	Sprite* titel;
	Sprite* backround;
	Sprite* drone;

	Button* startButton;
	Button* hostButton;
	Button* clientButton;
	Button* multiplayerMenueButton;
	Button* exitButton;
	Button* deleteSavesButton;
	Button* accountButton;
	Button* accountFriendsMenuButton;
	Button* achievementsButton;
	Button* dailyButton;
	Button* shopButton;
	Button* skinsButton;
	Button* creditsButton;
	Button* openMenuButton;

	Clock* animation;

	Font* font;
	Text* choseText;
	Text* creditsText;

	MultiplayerGUI* multiplayerGUI;
	AchievementGUI* achievementGUI;
	ShopGUI* shopGUI;
	AccountServer* accServer;
	SkinsGUI* skinsGUI;
	Daily* daily;
	Credits* credits;

	Ressources* res;


	/// <summary>
	/// Checkt, ob etwas geklicht wurde
	/// </summary>
	/// <returns></returns>
	int CheckClicked(Event*);
	int checkButtonClick(Event*);
	void checkButtonHover();

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

	/// <summary>
	/// 1=Single
	/// 2=Host
	/// 3=Client
	/// </summary>
	/// <returns></returns>
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

