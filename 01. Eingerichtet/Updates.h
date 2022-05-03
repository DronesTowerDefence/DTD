#pragma once
#include "SFML/Graphics.hpp"
//#include "Round.h"
using namespace sf;
class Updates
{
private:
	Sprite* close;
	Sprite* sell;
	Sprite* update2;
	Sprite* update1;
	Texture* textureUpdate1;
	Texture* textureUpdate1NoBuy;
	Texture* textureUpdate2;
	Texture* textureUpdate2NoBuy;
	Texture* textureclose;
	Texture* textureSell;
	RectangleShape* shoowUpdate1[4];
	RectangleShape* shoowUpdate2[4];
	int index1;
	int index2;
	Text* text1;
	Text* text2;
	Font arial;
	int towerIndex;

public:
	Updates(int towerIndex);
	void draw(RenderWindow* window);
	int isClicked(RenderWindow* window);

	bool IsClosed(RenderWindow* window);
	bool isSell(RenderWindow* window);
	int getIndex1();
	int getIndex2();
	void canBuy();	
};

