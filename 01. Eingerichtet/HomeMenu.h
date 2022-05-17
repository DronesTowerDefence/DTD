#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
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
	
	bool isClicked;
	bool connected;
	
	std::string ipAdress;
	std::string ownIpAdress;
	Vector2f positionTower[5];

	RenderWindow* window;
	
	Texture* textureTower[5][4];	
	Texture* textureTitel;
	Texture* textureBackround;
	Texture* textureHost;
	Texture* textureClient;

	RectangleShape* pointer;
	
	Sprite* startButton;
	Sprite* towers[5];
	Sprite* map[3];
	Sprite* titel;
	Sprite* backround;
	Sprite* drone;
	Sprite* host;
	Sprite* client;
	
	Clock* animation;
	
	Font *font;
	Text *choseText;
	Text *ipAdressText;
	Text *ownIpAdressText;

	Ressources* res;
	

	void eingabe(Event event);
	int CheckClicked();
	void draw();
	
	void setTowerTexture();

public:
	HomeMenu();
	
	static HomeMenu* getInstance();
	int getChoseIndex();
	void setWindow(RenderWindow* window);
	
	void HomeMenuStart();
};

