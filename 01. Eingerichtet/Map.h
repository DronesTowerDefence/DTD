#pragma once
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include "Waypoint.h"
#include "Drone.h"
//#include "Round.h"
using namespace sf;
class Map
{
private:
	int index;
	int wayPointCount; // Wieviele WegPunkte es gibt
	
	Vector2f start;	//Startposition
	Vector2f startMove; // Startbewegung
	
	RectangleShape background; // Hintergrund
	std::list<Waypoint*> points; // Liste der Wegpunkte
	
	
	Map();
public:
	
	Map(int index);
	

	int getIndex();
	int getWayPointCount();
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
	/// gibt den Wegpunkt der Koordinaten als Vektor an der Stelle i zur�ck
	/// </summary>
	/// <param name="index">Index</param>
	/// <returns>Wegpunkt</returns>
	Vector2f getWaypointAsVector(int index);
	RectangleShape* getBackround();
	/// <summary>
	/// gibt den Wegpunkt an an stelle i zur�ck
	/// </summary>
	/// <param name="index">Index</param>
	/// <returns>Wegpunkt</returns>
	Waypoint* getWaypoint(int index);
	/// <summary>
	/// Gibt eine Liste mit allen Wegpunkten zur�ck
	/// </summary>
	/// <returns></returns>
	std::list<Waypoint*>& getPoints();
	
	/// <summary>
	/// Checkt, ob die Drohne den n�chsten Wegpunkt erreicht hat
	/// </summary>
	/// <param name="drone">zu �berpr�fende Drone</param>
	/// <summary>
	/// Gibt den Index der Map zur�ck
	/// </summary>
	/// <returns></returns>
	void checkChangeDirection(Drone* drone);
	/// <summary>
	/// �ndert die Bewegungsrichtung auf die im WegPunkt festgelegte richtung
	/// </summary>
	/// <param name="drone">Drone, dessen Richtumg ge�ndert wird</param>
	/// <param name="wp">Letzter erreichter Wegpunkt</param>
	void changeDirection(Drone* drone, Waypoint* wp);
};