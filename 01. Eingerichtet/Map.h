#pragma once
#include <list>
#include <string>
#include "SFML/Graphics.hpp"
#include "Waypoint.h"
#include "Drone.h"
#include "Base.h"
using namespace sf;
class Map
{
public:
	void checkChangeDirection(Drone* drone);
	void changeDirection(Drone* drone, Waypoint* wp);
	Vector2f getStart();
	Vector2f getStartMove();
	std::list<Waypoint*>& getPoints();
	Waypoint* getWaypoint(int index);
	Map();
private:
	std::list<Waypoint*> points;
	Vector2f start;
	Vector2f startMove;

};

