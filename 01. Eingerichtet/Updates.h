#pragma once
#include "SFML/Graphics.hpp"
//#include "Round.h"
using namespace sf;
class Updates
{
private:
	Sprite* close;
	Sprite* update2;
	Sprite* update1;
	Texture* textureUpdate1;
	Texture* textureUpdate2;
	Texture* textureclose;
	RectangleShape* shoowUpdate1[4];
	RectangleShape* shoowUpdate2[4];
	int index1;
	int index2;
	Text* text1;
	Text* text2;
	Font arial;

public:
	Updates();
	void draw(RenderWindow* window);
	int isClicked(RenderWindow* window, float price1, float price2);

	bool IsCloses(RenderWindow* window);

	int getIndex1();
	int getIndex2();

};

