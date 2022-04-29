#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
using namespace sf;

class HomeMenu
{
private:
	Sprite* startButton;
	//Sprite* choseMap;
	RectangleShape* pointer;
	Sprite* map[1];
	Sprite* titel;
	Sprite* backround;
	Sprite* drone;

	Sprite* towers[5];
	Texture* textureStartButton;
	Texture* textureChoseMap;
	Texture* textureMap[1];
	Texture* textureTitel;
	Texture* textureTower[5][4];
	Texture* textureBackround;
	Texture* textureDrone;
	int choseIndex;
	static HomeMenu* instance;
	RenderWindow* window;
	HomeMenu(RenderWindow* win);
	Vector2f positionMap[1];
	Vector2f positionTower[5];
	bool isClicked;
	Clock* animation;
	int animationIndex;
	void draw();
	bool CheckClicked();
	void 	setTowerTexture();
public:
	static HomeMenu* getInstance(RenderWindow* win);
	void HomeMenuStart();


};

