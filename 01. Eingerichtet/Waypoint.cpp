#include "Waypoint.h"

#pragma region Konstruktor
Waypoint::Waypoint(Vector2f kooardinaten, Vector2f newMove, int condition)
{
	this->kooadinaten = kooardinaten;
	this->newMove = newMove;
	this->condition = condition;
	pass = false;
}
#pragma endregion

#pragma region Funktionen

#pragma endregion

#pragma region getter
int Waypoint::getCondition()
{
	return condition;
}
bool Waypoint::getPass()
{
	return pass;
}
Vector2f Waypoint::getKooadinaten()
{
	return kooadinaten;
}
Vector2f Waypoint::getNewMove()
{
	return newMove;
}
#pragma endregion

#pragma region setter
void Waypoint::setPass(bool pass)
{
	this->pass = pass;
}
#pragma endregion

#pragma region Desturktor

#pragma endregion