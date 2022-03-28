#pragma once
#include <list>
#include <string>
#include "SFML/Graphics.hpp"
#include "Waypoint.h"
#include "Drone.h"
//#include "Round.h"
using namespace sf;
class Map
{
public:
	/// <summary>
	/// Checkt, ob die Drohne den n�chsten Wegpunkt erreicht hat
	/// </summary>
	/// <param name="drone">zu �berpr�fende Drone</param>
	void checkChangeDirection(Drone* drone);
	/// <summary>
	/// �ndert die Bewegungsrichtung auf die im WegPunkt festgelegte richtung
	/// </summary>
	/// <param name="drone">Drone, dessen Richtumg ge�ndert wird</param>
	/// <param name="wp">Letzter erreichter Wegpunkt</param>
	void changeDirection(Drone* drone, Waypoint* wp);
	/// <summary>
	/// gibt die Startkoadinaten der Karte zur�ck
	/// </summary>
	/// <returns>Startkoadinaten</returns>
	Vector2f getStart();
	/// <summary>
	/// gibt die erste Bewegungsrichtung zur�ck
	/// </summary>
	/// <returns>Bewegungsrichtung</returns>
	Vector2f getStartMove();
	/// <summary>
	/// Gibt eine Liste mit allen Wegpunkten zur�ck
	/// </summary>
	/// <returns></returns>
	std::list<Waypoint*>& getPoints();
	/// <summary>
	/// gibt den Wegpunkt an an stelle i zur�ck
	/// </summary>
	/// <param name="index">Index</param>
	/// <returns>Wegpunkt</returns>
	Waypoint* getWaypoint(int index);
	/// <summary>
	/// gibt den Wegpunkt der Koordinaten als Vektor an der Stelle i zur�ck
	/// </summary>
	/// <param name="index">Index</param>
	/// <returns>Wegpunkt</returns>
	Vector2f getWaypointAsVector(int index);
	Map();
private:
	std::list<Waypoint*> points;
	Vector2f start;
	Vector2f startMove;

};

