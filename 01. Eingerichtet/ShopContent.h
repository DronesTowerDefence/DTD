#pragma once
#include "Ressources.h"

#define shopContentCount 1

class ShopContentData
{
private:
	std::list<ShopContentData*> allShopContentData;

	int m_id;
	int m_cost;
	int m_size;
	std::string m_name;

public:
	ShopContentData(int id, int cost, std::string name, int size);
	static bool createShopContentDataFromFile();
	int getCost();
	std::string getName();
};


class ShopContentTexture
{
private:

	ShopContentData* p_shopContentData;

	RenderTexture* texture;
	Texture* spriteTexture;
	Sprite* sprite;

	Font* font;
	Text* headlineText;
	Text* costText;
	Sprite* contentSprite;

public:
	ShopContentTexture(ShopContentData* scd);
	Sprite* getSprite();
};

