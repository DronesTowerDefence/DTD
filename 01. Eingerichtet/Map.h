#pragma once
#include <list>
#include <string>
#include "SFML/Graphics.hpp"
#include "Waypoint.h"
using namespace sf;
class Map
{
public:
	void chekChanceRichtung(RectangleShape* drohne, int* x, int *y, float v);
	void move(RectangleShape* drohne, int* x, int* y, float v, Waypoint* kp, bool change);

	Vector2f getStart();
	Vector2f getStartMove();

	Map();
private:
	std::list<Waypoint*> points;
	Vector2f start;
	Vector2f startMove;

};

