#pragma once
#include "Ressources.h"
#include "ShopContent.h"
#include "Button.h"

class ShopGUI
{
private:
	static std::list<ShopContentTexture*> allShopContents;
	RenderWindow* window;

	bool isOpen;
	bool isClicked;

	Sprite* background;
	Button* coinsIcon;
	Button* closeButton;

	Font* font;
	Text* headlineText;
	Text* shopCoinsText;
	Text* emptyShop;

	void checkClicked(Event*);
	void draw();
	bool shopContentClicked(ShopContentTexture* sct);

public:
	ShopGUI(RenderWindow*);
	bool openShop();
	static void removeBoughtContent();
	static void addShopContent(ShopContentTexture* sc);
	static ShopContentTexture* getShopContentTexture(int id);

};

