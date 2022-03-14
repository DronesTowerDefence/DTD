#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Tower
{
private:
	std::string name;
	int damage;
	int speed;
	int price;
	int range;

	Texture towerTex;
	Sprite towerSpr;

	Tower();

public:

	Tower(int);
	
};

