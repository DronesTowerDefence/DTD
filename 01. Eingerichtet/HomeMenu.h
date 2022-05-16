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
	
	bool isClicked;
	
	std::string ipAdress;
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

	Ressources* res;
	

	void eingabe(Event event);
	bool CheckClicked();
	void draw();
	
	void setTowerTexture();

public:
	HomeMenu();
	
	static HomeMenu* getInstance();
	int getChoseIndex();
	void setWindow(RenderWindow* window);
	
	void HomeMenuStart();
};

