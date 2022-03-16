#pragma once
#include <SFML/Graphics.hpp>
#include "Base.h"
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

	static std::list<Tower*> allTowers;

	Texture towerTex;
	Sprite towerSpr;

	Tower();
	Tower(int);

public:

	Sprite getTowerSpr();
	void shoot(Drone*);
	void sell();
	Tower* buyNewTower(int);
	std::list<Tower*> getAllTowers();
	
};

