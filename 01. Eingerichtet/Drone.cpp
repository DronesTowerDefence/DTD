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

	//Dronen-Texturen werden geladen
	switch (droneType) {
	case 0:
		droneTexture[0].loadFromFile("img/drone0/drone0_0.png");
		droneTexture[1].loadFromFile("img/drone0/drone0_0.png");
		droneTexture[2].loadFromFile("img/drone0/drone0_0.png");
		droneTexture[3].loadFromFile("img/drone0/drone0_0.png");
		break;

	case 1:
		droneTexture[0].loadFromFile("img/drone1/drone1_0.png");
		droneTexture[1].loadFromFile("img/drone1/drone1_0.png");
		droneTexture[2].loadFromFile("img/drone1/drone1_0.png");
		droneTexture[3].loadFromFile("img/drone1/drone1_0.png");
		break;

	case 2:
		droneTexture[0].loadFromFile("img/drone2/drone2_0.png");
		droneTexture[1].loadFromFile("img/drone2/drone2_0.png");
		droneTexture[2].loadFromFile("img/drone2/drone2_0.png");
		droneTexture[3].loadFromFile("img/drone2/drone2_0.png");
		break;
	case 3:
		droneTexture[0].loadFromFile("img/drone3/drone3_0.png");
		droneTexture[1].loadFromFile("img/drone3/drone3_0.png");
		droneTexture[2].loadFromFile("img/drone3/drone3_0.png");
		droneTexture[3].loadFromFile("img/drone3/drone3_0.png");
		break;
	}

	drone.setTexture(droneTexture[0]);
	//In Ressoucen gespeichert
	speed = Ressources::getInstance()->getDroneSpeed(typSpecifier);
	nextPoint = 0;
	//""
	lives = Ressources::getInstance()->getDroneLives(typSpecifier);
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


#pragma region getter
int Drone::getNextPoint()
{
	return nextPoint;
}
int Drone::getLives()
{
	return lives;
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
	//Wird die überhaupt noch benutzt?

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
	//Animationsdings von Jonas?
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
		drone.setTexture(droneTexture[animationCounter]);
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
#pragma endregion

#pragma region Funktionen
void Drone::move()
{
	//x,y-Position der Drone plus die Richtung mal die Geschwindigkeit der Drone
	drone.setPosition(Vector2f(drone.getPosition().x + move_x * speed, drone.getPosition().y + move_y * speed));
}
void Drone::pass()
{
	//Wegpunkte in der Map, wenn die Drone einen Wegpunkt passiert, erhöht sich der Counter als Index für die Liste der Wegpunkte




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

	if (lives < 0)
		lives = 0;

	switch (lives)
	{
	case 0:
		//True, wenn Drone tot ist
		delete this;
		return true;
		break;
	case 1:
		droneTextureDmg.loadFromFile("img/drone0/drone0_0_d2.png");
		break;

	case 2:
		droneTextureDmg.loadFromFile("img/drone0/drone0_0_d1.png");
		break;
	}

	animationCounter = -1;
	drone.setTexture(droneTextureDmg);

	return false;
}
#pragma endregion

#pragma region Destruktor
Drone::~Drone()
{
	Round::getInstance()->deleteDrone(this);
}
#pragma endregion








