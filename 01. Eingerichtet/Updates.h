#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Tower;
class Updates
{
private:
	int index1;
	int index2;
	Text *informationtext;
	bool showinformation;
	Sprite* background;
	Texture* backgroundTexture;
	Sprite* information1;
	Sprite* information2;
	Texture* informationTexture;
	
	bool isClosed1;
	bool isClosed2;

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
	Text* towerOwnerText;

	Tower* tower;
	Ressources* res;

public:
	Updates(Tower* tower);

	int getIndex1();
	int getIndex2();
	bool getIsClosed1();
	bool getIsClosed2();

	void setIndex1(int index);
	void setIndex2(int index);
	void setIsClosed1(bool);
	void setIsClosed2(bool);
	void setText1(std::string text);
	void setText2(std::string text);

	void addIndex1();
	void addIndex2();

	void hover(RenderWindow* window);

	void draw(RenderWindow* window);
	int isClicked(RenderWindow* window, Tower* tow);
	bool IsClosed(RenderWindow* window);
	bool isSell(RenderWindow* window);
	void canBuy();
	void setStringPrice();
};

