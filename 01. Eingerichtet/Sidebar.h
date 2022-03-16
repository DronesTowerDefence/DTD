#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
using namespace sf;
class Sidebar
{
private:
	RectangleShape backround;
	Button* towers[4];

	static Sidebar* instance;
	Sidebar();

public:
	static Sidebar* getInstance();
	int isCklickes(RenderWindow* window);
	void draw(RenderWindow* window);
};

