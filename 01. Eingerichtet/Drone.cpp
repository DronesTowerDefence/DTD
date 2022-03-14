
#include "Drone.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Drone::Drone(int typ,	std::list<Waypoint*>::iterator np)
{

	droneTexture = Texture();
	droneTexture.loadFromFile("img/drone2_40x40.png");
	drone = Sprite();
	drone.setTexture(droneTexture);
	drone.setScale(40, 40);
	nextPoint = np;
}

void Drone::setPosition(Vector2f position)
{
	this->position = position;

}

Vector2f Drone::getPosition()
{
	return Vector2f();
}

std::list<Waypoint*>::iterator Drone::getNextPoint()
{
	return nextPoint;
}

void Drone::setMove(Vector2f v)
{
	
}

void Drone::move()
{
	//TODO: Drohne Bewegen mit (v*x_richtung   , v*y richtung)
}

