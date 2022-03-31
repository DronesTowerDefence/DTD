#include "Drone.h"
using namespace sf;


int Drone::droneID = 0;


Drone::Drone(int typSpecifier, Vector2f startPosition, int x, int y)
{
	droneType = typSpecifier;

	/*switch(droneType) {

	default:*/
	droneTexture = Texture();
	droneTexture.loadFromFile("img/drone0_40x40.png");
	drone = Sprite();
	drone.setTexture(droneTexture);
	drone.setScale(1, 1);
	speed = 2.5;
	nextPoint = 0;
	lives = 3;
	drone.setPosition(startPosition);
	move_x = x;
	move_y = y;
	id = droneID;
	droneID++;
	
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

sf::Sprite Drone::getDroneSprite()
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
	drone.setRotation(90 + drone.getRotation());
}

bool Drone::takeDamage(int damage) {

	lives -= damage;
	if (lives == 2) {
		droneTexture.loadFromFile("img/drone0(damage1)40x40.png");
		drone.setTexture(droneTexture);
	}
	else if (lives == 1) {
		droneTexture.loadFromFile("img/drone0(damage2)40x40.png");
		drone.setTexture(droneTexture);
	}
	if (lives <= 0) {
		delete this;
		//True, wenn Drone tot ist
		return true;
	}

	return false;
}

int Drone::getLives()
{
	return lives;
}

Vector2i Drone::getMove()
{
	return Vector2i(move_x, move_y);
}

Vector2f Drone::getNextPosition(int nextFrame)
{

	Vector2f deezNuts;

	for (int i = 0; i < nextFrame; i++) {

		deezNuts.x += drone.getPosition().x + move_x * speed;
		deezNuts.y += drone.getPosition().y + move_y * speed;

	}

	return deezNuts;

}