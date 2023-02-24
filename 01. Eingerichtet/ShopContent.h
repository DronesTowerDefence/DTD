#pragma once
#include "Ressources.h"

#define shopContentCount 1

class ShopContentData
{
private:
	static std::list<ShopContentData*> allShopContentData;

	int m_id;
	int m_cost;
	std::string m_name;
	Texture* texture;

public:
	ShopContentData(int id, int cost, std::string name, Texture* _texture);
	static bool createShopContentDataFromFile();
	int getCost();
	std::string getName();
	Texture* getTexture();
};


class ShopContentTexture
{
private:

	ShopContentData* p_shopContentData;

	RenderTexture* texture;
	Sprite* sprite;

	Font* font;
	Text* headlineText;
	Text* costText;
	Sprite* contentSprite;

public:
	ShopContentTexture(ShopContentData* scd);
	Sprite* getSprite();
};

