#pragma once
#include "Ressources.h"

#define shopContentCount 5

class ShopContentData
{
private:
	static std::list<ShopContentData*> allShopContentData;

	// Ob von User gekauft
	bool m_isBought;

	// Ob ausgewählt ist
	bool m_isEquiped;

	// Typ (Tower:0 | Drone:1 | Projectile:2)
	int m_typ;

	// Typ-Typ (TowerType/DroneType/ProjectileType)
	int m_typTypID;

	// ID ist nullbasiert
	int m_id;

	// Kosten
	int m_cost;

	// Name
	std::string m_name;

	// Vorschau-Textur
	Texture* texture;

public:
	ShopContentData(int id, int cost, std::string name, int type, int typeType, Texture* _texture);
	static bool createShopContentDataFromFile();
	static bool loadBoughtFromServerString(std::string);
	void setIsBought(bool b = false);
	void setIsEquiped(bool b = false);
	bool getIsBought();
	bool getIsEquiped();
	int getCost();
	int getID();
	int getType();
	int getTypeType();
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
	Sprite* boughtSprite;
	Sprite* contentSprite;

	const int contentsPerRow = 4, distanzeToNextSprite = 50, startPositionX = 350, startPositionY = 240;

public:
	ShopContentTexture(ShopContentData* scd);
	/// <summary>
	/// Anordnung nicht mehr nach id sondern nach Index aus der ShopGUI::allShopContents Liste
	/// </summary>
	/// <param name="listIndex"></param>
	void updateSpritePosition(int listIndex);
	Sprite* getSprite();
	ShopContentData* getShopContentData();
};

