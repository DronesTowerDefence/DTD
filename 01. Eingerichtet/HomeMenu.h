#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
using namespace sf;

class HomeMenu
{
private:
	Sprite* startButton;
	RectangleShape* pointer;
	Sprite* map[2];
	Sprite* titel;
	Sprite* backround;
	Sprite* drone;

	Sprite* towers[5];
	Texture* textureStartButton;
	Texture* textureMap[2];
	Texture* textureTitel;
	Texture* textureTower[5][4];
	Texture* textureBackround;
	Texture* textureDrone;
	int choseIndex;
	static HomeMenu* instance;
	RenderWindow* window;
	Vector2f positionTower[5];
	bool isClicked;
	Clock* animation;
	int animationIndex;
	void draw();
	bool CheckClicked();
	void 	setTowerTexture();
	Font *font;
	Text *choseText;
public:
	static HomeMenu* getInstance();
	void HomeMenuStart();
	int getChoseIndex();
	void setWindow(RenderWindow* window);

	HomeMenu();

};

