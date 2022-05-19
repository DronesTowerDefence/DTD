#include "Drone.h"
#include "Round.h"
#include "HomeMenu.h"
#include "Game.h"
#include<iostream>
using namespace sf;


int Drone::droneID = 0;

#pragma region Konstruktor
Drone::Drone(int typSpecifier, Vector2f startPosition, int x, int y)
{
	droneType = typSpecifier;

	res = Ressources::getInstance();

	//In Ressoucen gespeichert
	drone.setTexture(*res->getDroneDmgTexture(droneType, 0));
	speed = res->getDroneSpeed(typSpecifier);
	nextPoint = 0;
	//""
	lives = res->getDroneLives(typSpecifier);
	drone.setPosition(startPosition);
	move_x = x;
	move_y = y;
	id = droneID;
	droneID++;

	if (HomeMenu::getInstance()->getChoseIndex() != 0) {
		drone.setRotation(90);
	}
}
#pragma endregion

#pragma region Funktionen
void Drone::move()
{
	//x,y-Position der Drone plus die Richtung mal die Geschwindigkeit der Drone
	drone.setPosition(Vector2f(drone.getPosition().x + move_x * speed, drone.getPosition().y + move_y * speed));
}
void Drone::pass()
{
	//Wegpunkte in der Map, wenn die Drone einen Wegpunkt passiert, erh�ht sich der Counter als Index f�r die Liste der Wegpunkte




	nextPoint++;


	if (HomeMenu::getInstance()->getChoseIndex() == 0) {


		if (nextPoint % 2 == 0) {

			drone.setRotation(0);
		}
		else {
			drone.setRotation(90);
			drone.move(50, 0);
		}
		return;
	}
	else {


		if (nextPoint % 2 == 0) {

			drone.setRotation(90);
			drone.move(50, 0);
		}
		else {
			drone.setRotation(0);

		}


	}



	//if (nextPoint == 1) {
	//	
	//}
	//if (nextPoint == 2) {
	//	
	//}
}
bool Drone::takeDamage(int damage) {
	int livesDiff = lives;
	lives -= damage;
	livesDiff -= lives;

	Round::getInstance()->addMoney(livesDiff * 3); // mal 3, da Geld wenig

	if (lives <= 0)
	{
		//True, wenn Drone tot ist
		delete this;
		return true;
	}
		
	drone.setTexture(*res->getDroneDmgTexture(droneType, res->getDroneLives(droneType) - lives));
	animationCounter = -1;

	return false;
}
#pragma endregion

#pragma region getter
int Drone::getNextPoint()
{
	return nextPoint;
}
int Drone::getLives()
{
	return lives;
}
int Drone::getIndex()
{
	return droneType;
}
Vector2i Drone::getMove()
{
	return Vector2i(move_x, move_y);
}
Vector2f Drone::getPosition()
{
	return drone.getPosition();
}
Vector2f Drone::getNextPosition(int nextFrame)
{
	//Wird die �berhaupt noch benutzt?

	Vector2f deezNuts;

	for (int i = 0; i < nextFrame; i++) {

		deezNuts.x += drone.getPosition().x + move_x * speed;
		deezNuts.y += drone.getPosition().y + move_y * speed;

	}

	return deezNuts;

}
Sprite Drone::getDroneSprite()
{
	return drone;
}
Sprite* Drone::getDrawSprite()
{
	animationCounter = -1; //Animationen kommen irgendwann
	return &drone; 

	//Animationsdings von Jonas
	if (animationTimer.getElapsedTime().asMilliseconds() >= droneChangeFrame)
	{
		switch (animationCounter)
		{
		case -1:
			return &drone;
			break;
		case 0:
			animationCounter = 1;
			break;
		case 1:
			animationCounter = 2;
			break;
		case 2:
			animationCounter = 3;
			break;
		case 3:
			animationCounter = 0;
			break;
		}
		drone.setTexture(*res->getDroneTexture(droneType, animationCounter));
		animationTimer.restart();
	}
	return &drone;
}
#pragma endregion

#pragma region setter
void Drone::setSeed(float speed)
{
	this->speed = speed;
}
void Drone::setPosition(Vector2f position)
{

	drone.setPosition(position);

}
void Drone::setMove(Vector2f v)
{
	move_x = int(v.x);
	move_y = int(v.y);
}
void Drone::setLives(int _lives)
{
	lives = _lives;
}
#pragma endregion


#pragma region Destruktor
Drone::~Drone()
{
	Round::getInstance()->deleteDrone(this);
}
#pragma endregion








