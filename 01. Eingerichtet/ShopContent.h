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
	Texture* m_texture[towerTextureCount + 1];

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="id">ID des Shopcontents</param>
	/// <param name="cost">Kosten des Skins</param>
	/// <param name="name">Name der Textur</param>
	/// <param name="type">0:Tower | 1:Drone | 2:Projectile</param>
	/// <param name="typeType">TowerType/DroneType/ProjectileType</param>
	/// <param name="_texture">Array: 0-3:Tower | 4:Alias | 5:NoBuy | 6:Preview</param>
	ShopContentData(int id, int cost, std::string name, int type, int typeType, Texture** _texture);
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
	Texture** getTexture();
	Texture* getPreviewTexture();
	/// <summary>
	/// Kopie der Liste
	/// </summary>
	/// <returns></returns>
	static std::list<ShopContentData*> getAllShopContentData();
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

	const int contentsPerRow = 4, distanceToNextSprite = 50, startPositionX = 350, startPositionY = 240;

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

