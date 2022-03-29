#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Map.h"
using namespace sf;

class Tower
{
private:
	std::string name;
	float damage;
	float speed;
	float price;
	float range;
	float value;
	float attackspeed;

	std::list<Vector3f> coverableArea;

	Texture towerTex;
	Sprite towerSpr;
	Map* p_map;
	Vector2f position;

	Tower() = delete; //Standart-Konstruktor soll nicht benutzt werden
	void setCoverableArea();


public:
	/// <summary>
	/// Neuen Turm kaufen; 0,1,2,3
	/// </summary>
	/// <param name="int 0,1,2,3"></param>
	Tower(int, Vector2f, Map*);

	/// <summary>
	/// Returnt die Tower Sprite
	/// </summary>
	/// <param name="void"></param>
	Sprite getTowerSpr();

	/// <summary>
	/// Tower schieﬂt Drone ab
	/// </summary>
	/// <param name="Drone*"></param>
	void shoot(Drone*);

	/// <summary>
	/// Returnt Value
	/// </summary>
	/// <param name="float"></param>
	float getValue();

	/// <summary>
	/// Returnt ProjectileSpeed
	/// </summary>
	/// <param name="float"></param>
	float getAttackSpeed();

	/// <summary>
	/// Returnt die Liste CoverableArea
	/// </summary>
	/// <param name="int"></param>
	std::list<Vector3f> getCoverableArea();
};