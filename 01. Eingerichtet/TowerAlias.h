#pragma once
#include<SFML/Graphics.hpp>
#include "Round.h"
using namespace sf;

class TowerAlias
{
private:
	int index;
	Sprite* sprite;
	Texture* texture;
	Map* p_map;
public:
	TowerAlias(int index, Map* n_map);
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
};