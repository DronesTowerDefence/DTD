#pragma once
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;

class Waypoint
{
private:
	bool pass;
	
	int condition;
	
	Vector2f kooadinaten;
	Vector2f newMove;

public:
	/// <summary>
	/// Kosntruktor
	/// </summary>
	/// <param name="kooardinaten">Koadinaten </param>
	/// <param name="newMove">Bewegung der Drohne x,y</param>
	/// <param name="condition">überpfüfung</param>
	Waypoint(Vector2f kooardinaten, Vector2f newMove, int condition);
	/// <summary>
	/// gibt zurück, wie die Kooadinaten überpfüft werden müssen
	/// </summary>
	/// <returns></returns>
	int getCondition();
	/// <summary>
	/// Gibt die Kooadinaten des WayPoints zurück
	/// </summary>
	/// <returns>Koaedinaten</returns>
	Vector2f getKooadinaten();
	/// <summary>
	/// Gibt die Bewegung in x und y Richtung zurück
	/// </summary>
	/// <returns>Vektor (x , y)</returns>
	Vector2f getNewMove();
	/// <summary>
	/// gibt zurück, ob der WayPoint überquert wurde
	/// </summary>
	/// <returns>istÜberquert</returns>
	bool getPass();

	/// <summary>
	/// Wird aufgerufen, wenn der WayPoint überquert wurde
	/// </summary>
	/// <param name="pass"></param>
	void setPass(bool pass);
};