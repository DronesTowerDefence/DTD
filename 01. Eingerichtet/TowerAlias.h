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
	CircleShape rangeShape;
	RectangleShape* rangeShapePlane;
	Sprite towerAliasSpr;
	Map* p_map;
	Ressources* res;

public:
	/// <summary>
	/// Konstruktor für TowerAlias
	/// </summary>
	/// <param name="int"></param>
	/// <param name="Map*"></param>
	TowerAlias(int, Map*);

	int getIndex();
	/// <summary>
	/// Gibt die Position von TowerAlias zurück
	/// </summary>
	/// <returns>Vector2f</returns>
	Vector2f getPos();
	/// <summary>
	/// Gibt einen Zeiger auf den Kreis der Reichweite zurück
	/// </summary>
	/// <returns>CircleShape</returns>
	CircleShape* getRangeShape();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	RectangleShape* getRangeShapePlane();

	/// <summary>
	/// Gibt einen Zeiger auf die Sprite von TowerAlias zurück
	/// </summary>
	/// <returns>Sprite</returns>
	Sprite* getSpr();


	/// <summary>
	/// Setzt die Position des Objektes
	/// </summary>
	/// <param name="mouse">Position des Mauszeigers</param>
	void setPositionMouse(Vector2i);
	/// <summary>
	/// Erstellt einen Tower
	/// </summary>
	void CreateNewTower();
};