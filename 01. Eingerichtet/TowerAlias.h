#pragma once
#include<SFML/Graphics.hpp>
#include "Tower.h"
#include "Base.h"
using namespace sf;
class TowerAlias
{
public:
	TowerAlias(int index);
	void setPositionMouse(Vector2i mouse);
	void draw(RenderWindow* window);
	void CreateNewTower();
private:
	int index;
	Sprite* sprite;
	Texture* texture;
};

