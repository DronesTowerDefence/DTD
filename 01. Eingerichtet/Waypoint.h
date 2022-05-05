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
	/// <param name="condition">�berpf�fung</param>
	Waypoint(Vector2f kooardinaten, Vector2f newMove, int condition);
	/// <summary>
	/// gibt zur�ck, wie die Kooadinaten �berpf�ft werden m�ssen
	/// </summary>
	/// <returns></returns>
	int getCondition();
	/// <summary>
	/// Gibt die Kooadinaten des WayPoints zur�ck
	/// </summary>
	/// <returns>Koaedinaten</returns>
	Vector2f getKooadinaten();
	/// <summary>
	/// Gibt die Bewegung in x und y Richtung zur�ck
	/// </summary>
	/// <returns>Vektor (x , y)</returns>
	Vector2f getNewMove();
	/// <summary>
	/// gibt zur�ck, ob der WayPoint �berquert wurde
	/// </summary>
	/// <returns>ist�berquert</returns>
	bool getPass();

	/// <summary>
	/// Wird aufgerufen, wenn der WayPoint �berquert wurde
	/// </summary>
	/// <param name="pass"></param>
	void setPass(bool pass);
};