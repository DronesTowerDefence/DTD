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
	
	Vector2f positionTower[5];

	RenderWindow* window;
	
	Texture* textureTower[5][4];	
	Texture* textureTitel;
	Texture* textureBackround;

	RectangleShape* pointer;
	
	Sprite* startButton;
	Sprite* towers[5];
	Sprite* map[2];
	Sprite* titel;
	Sprite* backround;
	Sprite* drone;
	
	Clock* animation;
	
	Font *font;
	Text *choseText;

	Ressources* res;
	
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

