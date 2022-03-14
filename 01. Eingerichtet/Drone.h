#pragma once
#include <list>
#include <string>
#include "SFML/Graphics.hpp"
#include "Waypoint.h"
using namespace sf;
class Drone
{
private:

	float speed;
	int move_x;
	int move_y;
	Vector2f position;
	Texture droneTexture;
	Sprite drone;
	std::list<Waypoint*>::iterator nextPoint;

	Drone();

public:

	Drone(int typ, std::list<Waypoint*>::iterator np); //Konstruktor
	void setPosition(Vector2f position);
	Vector2f getPosition();
	std::list<Waypoint*>::iterator getNextPoint();
	void setMove(Vector2f v);
	void move();

};

