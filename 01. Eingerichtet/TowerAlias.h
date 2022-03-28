#pragma once
#include<SFML/Graphics.hpp>
#include "Tower.h"
#include "Round.h"
using namespace sf;
class TowerAlias
{
public:
	TowerAlias(int index);
	/// <summary>
	/// Setzt die Position des Objektes
	/// </summary>
	/// <param name="mouse">Position des Mauszeigers</param>
	void setPositionMouse(Vector2i mouse);
	/// <summary>
	/// Erstellt einen Tower
	/// </summary>
	void CreateNewTower();
	/// <summary>
	/// Gibt den Sprite zurück
	/// </summary>
	/// <returns>Sprite</returns>
	Sprite* getSprite();
private:
	int index;
	Sprite* sprite;
	Texture* texture;
};