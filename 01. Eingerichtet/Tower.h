#pragma once
#include <SFML/Graphics.hpp>
#include "Drone.h"

using namespace sf;

class Tower
{
private:
	std::string name;
	int damage;
	int speed;
	int price;
	int range;
	int value;

	std::list<Vector2f> coverableArea;

	Texture towerTex;
	Sprite towerSpr;

	Tower();


public:
	/// <summary>
	/// Neuen Turm kaufen; 0,1,2,3
	/// </summary>
	/// <param name="int 0,1,2,3"></param>
	Tower(int a, Vector2f position);

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
	/// <param name="int"></param>
	int getValue();
};

