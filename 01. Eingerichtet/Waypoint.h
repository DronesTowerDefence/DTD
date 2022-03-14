#pragma once
#include <list>
#include <string>
#include "SFML/Graphics.hpp"
using namespace sf;
class Waypoint
{
private:
	Vector2f kooadinaten;
	Vector2f newMove;
	bool pass;
	
	int condition;
public:
	Vector2f getKooadinaten();
	Vector2f getNewMove();
	bool getPass();
	int getCondition();
	void setPass(bool pass);
	Waypoint(Vector2f kooardinaten, Vector2f newMove ,int condition);
};

