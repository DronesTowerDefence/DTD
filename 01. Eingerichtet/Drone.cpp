
#include "Drone.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Drone::Drone(int typ)
{

	droneTexture = Texture();
	droneTexture.loadFromFile("img/drone2_40x40.png");
	drone = Sprite();
	drone.setTexture(droneTexture);
	drone.setScale(1, 1);
	speed = .5;
	nextPoint = 0;

}

void Drone::setPosition(Vector2f position)
{
	this->position = position;
	drone.setPosition(position); //TODO richtig

}

void Drone::setMove(Vector2f v)
{
	move_x = v.x;
	move_y = v.y;
}

Vector2f Drone::getPosition()
{
	return position;
}

sf::Sprite Drone::getDrone()
{
	return drone;
}

int Drone::getNextPoint()
{
	return nextPoint;
}


void Drone::move(Vector2f value)
{
	Vector2f pos = getPosition();
	setPosition(Vector2f(pos.x + value.x, pos.y + value.y));
}

void Drone::move()
{
	position = Vector2f(position.x + move_x * speed, position.y + move_y * speed);
	drone.setPosition(position);
}

void Drone::pass()
{
	nextPoint++;
}




