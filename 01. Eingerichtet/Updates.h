#pragma once
#include "SFML/Graphics.hpp"
//#include "Round.h"
using namespace sf;
class Updates
{
private :
	Sprite* close;
	Sprite* update2;
	Sprite* update1;
	Texture* textureUpdate1;
	Texture* textureUpdate2;
	Texture* textureclose;
	int index1;
	int index2;
	bool closedClicked;	

public:
	Updates();
	void draw(RenderWindow * window);
	int isClicked(RenderWindow* window, float price1, float price2);

	bool IsCloses(RenderWindow* window);

	int getIndex1();
	int getIndex2();

};

