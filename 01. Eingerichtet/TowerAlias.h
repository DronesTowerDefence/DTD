#pragma once
#include<SFML/Graphics.hpp>
#include "Ressources.h"
#include "Round.h"
#include "Service.h"
using namespace sf;

class TowerAlias
{
private:

	int index;
	float range;
	float price;
	Vector2f pos;
	Map* p_map;
	Sprite towerAliasSpr;
	Texture towerAliasTexture;
	CircleShape rangeShape;

public:
	/// <summary>
	/// Konstruktor f�r TowerAlias
	/// </summary>
	/// <param name="int"></param>
	/// <param name="Map*"></param>
	TowerAlias(int, Map*);

	/// <summary>
	/// Setzt die Position des Objektes
	/// </summary>
	/// <param name="mouse">Position des Mauszeigers</param>
	void setPositionMouse(Vector2i);

	/// <summary>
	/// Erstellt einen Tower
	/// </summary>
	void CreateNewTower();

	/// <summary>
	/// Gibt den Preis zur�ck
	/// </summary>
	/// <returns>price</returns>
	float getPrice();

	/// <summary>
	/// Gibt einen Zeiger auf die Sprite von TowerAlias zur�ck
	/// </summary>
	/// <returns>Sprite</returns>
	Sprite* getSpr();

	/// <summary>
	/// Gibt einen Zeiger auf den Kreis der Reichweite zur�ck
	/// </summary>
	/// <returns>CircleShape</returns>
	CircleShape* getRangeShape();

	/// <summary>
	/// Gibt die Position von TowerAlias zur�ck
	/// </summary>
	/// <returns>Vector2f</returns>
	Vector2f getPos();
};