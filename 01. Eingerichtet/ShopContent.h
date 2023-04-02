#pragma once
#include "Ressources.h"

class ShopContentData
{
private:
	static std::list<ShopContentData*> allShopContentData;

	static int shopContentCount;

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
	static int getShopContentCount();
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


class ShopContentTexture : public sf::Drawable
{
private:

	ShopContentData* p_shopContentData;

	Font* font;
	Text* headlineText;
	Text* costText;
	Sprite* boughtSprite;
	Sprite* contentSprite;

	Vector2f position;

	const Vector2f startPosition = Vector2f(350, 240), maxSize = Vector2f(300, 300), headlineTextPos = Vector2f(10, 0), costTextPos = Vector2f(20, 260), boughtSpritePos = Vector2f(0, 50), contentSpritePos = Vector2f(0, 50);
	const int contentsPerRow = 4, distanceToNextSprite = 50;


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	ShopContentTexture(ShopContentData* scd);

	/// <summary>
	/// Anordnung nicht mehr nach id sondern nach Index aus der ShopGUI::allShopContents Liste
	/// </summary>
	/// <param name="listIndex"></param>
	void updatePosition(int listIndex);

	ShopContentData* getShopContentData();
	Vector2f getPosition();
	Vector2f getSize();
};

