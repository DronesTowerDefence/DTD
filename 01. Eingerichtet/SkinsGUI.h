#pragma once
#include "Ressources.h"
#include "ShopContent.h"

class SkinsGUI
{
private:

	class SkinsGUIDisplayedSkin
	{
	private:
		ShopContentData* p_scd;

		const int contentsPerRow = 4, distanceToNextSprite = 50, startPositionX = 350, startPositionY = 240;

		Text* title;
		Sprite* contentPreview;

		RenderTexture* texture;
		Sprite* sprite;
	public:
		SkinsGUIDisplayedSkin(Font*, ShopContentData*);
		void updatePosition(int index);
		ShopContentData* getShopContentData();
		Sprite* getSprite();
	};

	RenderWindow* window;
	std::list<SkinsGUIDisplayedSkin*> allSkinsGUIDisplayedSkins;

	bool isOpen;
	bool isClicked;

	Font* font;
	Text* headlineText;
	Text* emptyText;
	Sprite* background;
	Sprite* closeButton;
	std::list<Sprite*> allEquipedSprites;

	void createEquipedSprite(SkinsGUIDisplayedSkin*);
	Sprite* getEquipedSprite(SkinsGUIDisplayedSkin*);
	bool checkClicked();
	void draw();
	void initialize();

public:
	SkinsGUI(RenderWindow*);
	bool openGUI();
	void updateAllBoughtShopContent();
};

