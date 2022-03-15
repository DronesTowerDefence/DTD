
#include "Drone.h"
using namespace sf;

Drone::Drone(int typ)
{

	/*switch(typ) {

	default:*/
		droneTexture = Texture();
		droneTexture.loadFromFile("img/drone2_40x40.png");
		drone = Sprite();
		drone.setTexture(droneTexture);
		drone.setScale(1, 1);
		speed = .5;
		nextPoint = 0;
		lives = 3;
	/*case 1:*/

	/*}*/
}

void Drone::setPosition(Vector2f position)
{
	
	drone.setPosition(position); 

}

void Drone::setMove(Vector2f v)
{
	move_x = v.x;
	move_y = v.y;
}

Vector2f Drone::getPosition()
{
	return drone.getPosition();
}

sf::Sprite Drone::getDrone()
{
	return drone;
}

int Drone::getNextPoint()
{
	return nextPoint;
}


void Drone::move()
{
	
	drone.setPosition(Vector2f(drone.getPosition().x + move_x * speed, drone.getPosition().y + move_y * speed));
}

void Drone::pass()
{
	nextPoint++;
}

void Drone::takeDamage(int damage) {

	lives -= damage;
	if (lives <= 0) {
		delete this;
	}
}

int Drone::getLives()
{
	return lives;
}

Vector2i Drone::getMove()
{
	return Vector2i(move_x, move_y);
}
