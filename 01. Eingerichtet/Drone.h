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
	Texture droneTexture;
	Sprite drone;
	int nextPoint;
	int lives;

	Drone();

public:

	Drone(int typ); //Konstruktor
	void setPosition(Vector2f position);
	void setMove(Vector2f v);
	Vector2f getPosition();
	sf::Sprite getDrone();
	int getNextPoint();
	void move();
	void pass();
	void takeDamage(int damage);
	int getLives();

};

