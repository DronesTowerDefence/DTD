#pragma once
#include <list>
#include <string>
#include "SFML/Graphics.hpp"
#include "Waypoint.h"
#include "Drone.h"
using namespace sf;
class Map
{
public:
	void chekChanceRichtung(Drone* drohne);
	void move(Drone* drohne , Waypoint* wp , bool change);

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

