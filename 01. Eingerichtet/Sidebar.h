#pragma once
#include "SFML/Graphics.hpp"
#include "BuyTower.h"
#include "Base.h"
using namespace sf;
class Sidebar
{
private:
	RectangleShape backround;
	BuyTower* towers[4];

	static Sidebar* instance;
	Sidebar();

public:
	static Sidebar* getInstance();
	int isCklickes(RenderWindow* window);
	void draw(RenderWindow* window);
};

