#include "Waypoint.h"

Vector2f Waypoint::getKooadinaten()
{
	return kooadinaten;
}

Vector2f Waypoint::getNewMove()
{
	return newMove;
}
bool Waypoint::getPass()
{
	return pass;
}

int Waypoint::getCondition()
{
	return condition;
}

void Waypoint::setPass(bool pass)
{
	this->pass = pass;
}

Waypoint::Waypoint(Vector2f kooardinaten, Vector2f newMove, int condition)
{
	this->kooadinaten = kooardinaten;
	this->newMove = newMove;
	this->condition = condition;
	pass = false;
}