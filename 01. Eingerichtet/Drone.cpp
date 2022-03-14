
#include "Drone.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Drone::Drone(int typ)
{

	droneTexture = Texture();
	droneTexture.loadFromFile("img/drone2_40x40.png");
	drone = Sprite();
	drone.setTexture(droneTexture);
	drone.setScale(40, 40);
}

void Drone::setPosition(Vector2f position)
{
	this->position = position;

}

Vector2f Drone::getPosition()
{
	return Vector2f();
}
