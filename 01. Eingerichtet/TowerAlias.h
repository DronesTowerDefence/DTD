#pragma once
#include<SFML/Graphics.hpp>
#include "Tower.h"
using namespace sf;
class TowerAlias
{
public:
	TowerAlias(int index);
	void setPositionMouse(Vector2i mouse);
	void draw(RenderWindow* window);
private:
	int index;
	Sprite* sprite;
	Texture* texture;
	void CreateNewTower();
};

