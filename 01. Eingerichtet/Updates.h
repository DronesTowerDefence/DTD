#pragma once
#include "SFML/Graphics.hpp"
//#include "Round.h"
using namespace sf;
class Tower;
class Updates
{
private:
	int index1;
	int index2;
	
	RectangleShape* shoowUpdate1[4];
	RectangleShape* shoowUpdate2[4];
	
	Texture* textureUpdate1;
	Texture* textureUpdate1NoBuy;
	Texture* textureUpdate2;
	Texture* textureUpdate2NoBuy;
	Texture* textureclose;
	Texture* textureSell;
	Sprite* close;
	Sprite* sell;
	Sprite* update2;
	Sprite* update1;
	Font arial;
	Text* text1;
	Text* text2;
	Text* price;

	Tower* tower;

public:
	Updates(Tower * tower);
	
	int getIndex1();
	int getIndex2();

	void setIndex1(int index);
	void setIndex2(int index);

	void setText1(std::string text);

	void setText2(std::string text);

	void addIndex1();
	void addIndex2();

	
	void draw(RenderWindow* window);
	int isClicked(RenderWindow* window);
	bool IsClosed(RenderWindow* window);
	bool isSell(RenderWindow* window);
	void canBuy();	
	void setStringPrice();
};

