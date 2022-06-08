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
	/// gibt die Startkoadinaten der Karte zurück
	/// </summary>
	/// <returns>Startkoadinaten</returns>
	Vector2f getStart();
	/// <summary>
	/// gibt die erste Bewegungsrichtung zurück
	/// </summary>
	/// <returns>Bewegungsrichtung</returns>
	Vector2f getStartMove();
	/// <summary>
	/// gibt den Wegpunkt der Koordinaten als Vektor an der Stelle i zurück
	/// </summary>
	/// <param name="index">Index</param>
	/// <returns>Wegpunkt</returns>
	Vector2f getWaypointAsVector(int index);
	RectangleShape* getBackround();
	/// <summary>
	/// gibt den Wegpunkt an an stelle i zurück
	/// </summary>
	/// <param name="index">Index</param>
	/// <returns>Wegpunkt</returns>
	Waypoint* getWaypoint(int index);
	/// <summary>
	/// Gibt eine Liste mit allen Wegpunkten zurück
	/// </summary>
	/// <returns></returns>
	std::list<Waypoint*>& getPoints();
	
	/// <summary>
	/// Checkt, ob die Drohne den nächsten Wegpunkt erreicht hat
	/// </summary>
	/// <param name="drone">zu überprüfende Drone</param>
	/// <summary>
	/// Gibt den Index der Map zurück
	/// </summary>
	/// <returns></returns>
	void checkChangeDirection(Drone* drone);
	/// <summary>
	/// Ändert die Bewegungsrichtung auf die im WegPunkt festgelegte richtung
	/// </summary>
	/// <param name="drone">Drone, dessen Richtumg geändert wird</param>
	/// <param name="wp">Letzter erreichter Wegpunkt</param>
	void changeDirection(Drone* drone, Waypoint* wp);
};