#pragma once
#include "Ressources.h"
#include "ShopContent.h"

class ShopGUI
{
private:
	static std::list<ShopContentTexture*> allShopContents;
	RenderWindow* window;

	bool isOpen;
	bool isClicked;

	Sprite* background;
	Sprite* closeButton;

	Font* font;
	Text* headlineText;
	Text* shopCoinsText;

	void checkClicked(Event*);
	void draw();

public:
	ShopGUI(RenderWindow*);
	bool openShop();
	static void addShopContent(ShopContentTexture* sc);

};

