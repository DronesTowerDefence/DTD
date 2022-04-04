#pragma once
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include "Waypoint.h"
using namespace sf;
/// <summary>
/// Zeichenbares Objekt der Klasse Drone                          
/// <para/> 
/// Erzeugt eine Drone, die mit einer Sprite dargestellt wird
/// </summary>
class Drone
{
private:
	/// <summary>
	/// Static int für Drohnen-ID
	/// </summary>
	static int droneID;
	/// <summary>
	/// NICHT ÄNDERN, einmalige ID der Drohne
	/// </summary>
	int id;
	/// <summary>
	/// Geschwindigkeit der Drohne : float
	/// </summary>
	float speed;
	int move_x;
	int move_y;
	/// <summary>
	/// Textur der Drone : Texture
	/// </summary>
	Texture droneTexture;
	/// <summary>
	/// Sprite der Drone : Sprite
	/// </summary>
	Sprite drone;
	/// <summary>
	/// Counter für die Liste WayPoint in der Map-Klasse : int
	/// </summary>
	int nextPoint;
	/// <summary>
	/// Leben der Drone : int
	/// </summary>
	int lives;
	/// <summary>
	/// Drohnentyp für versch. Atrribute im Parameterkonstruktor : int
	/// </summary>
	int droneType;

	bool alive;

	/// <summary>
	/// !NICHT BENUTZEN!
	/// </summary>
	Drone();

public:
	/// <summary>
	/// Konstruktor
	/// </summary>
	/// <param name="int"></param>
	Drone(int typSpecifier, Vector2f startPosition, int x, int y); //Konstruktor
	/// <summary>
	/// Setzt die Position der Drone mit einem 2-float Vector
	/// </summary>
	/// <param name="Vector2f position"></param>
	void setPosition(Vector2f position);
	/// <summary>
	/// Setzt die move_x und move_y Koordinaten mit einem 2-float Vector
	/// </summary>
	/// <param name="Vector2f v"></param>
	void setMove(Vector2f v);
	/// <summary>
	/// Gibt die Position als 2-float Vector
	/// </summary>
	/// <returns>Vector2f</returns>
	Vector2f getPosition();
	/// <summary>
	/// Gibt die Sprite der Drone zurück
	/// </summary>
	/// <returns>sf::Sprite</returns>
	sf::Sprite getDroneSprite();
	/// <summary>
	/// Gibt den nextPoint zurück, den die Drone auf der Map erreichen wird (Map-Relevant)
	/// </summary>
	/// <returns>int</returns>
	int getNextPoint();
	/// <summary>
	/// Bewegt die Drone, indem die aktuelle Position + die move-Werte * der Geschwindigkeit gesetzt wird
	/// </summary>
	void move();
	/// <summary>
	/// Addiert 1 zu nextPoint (Wenn die Drone einen Punkt auf der Map erreicht) (Map-Relevant)
	/// </summary>
	void pass();
	/// <summary>
	/// Zieht Leben von der Drone ab (Standart-Lebenwert (WIP) = 3)
	/// </summary>
	/// <param name="int damage"></param>
	bool takeDamage(int damage);
	/// <summary>
	/// Gibt die Anzahl der verbleibenden Leben der Drone zurück
	/// </summary>
	/// <returns>int lives</returns>
	int getLives();
	/// <summary>
	/// Gibt die move_x und move_y Koordinaten mit einem 2-float Vector zurück
	/// </summary>
	/// <returns>Vector21</returns>
	Vector2i getMove();
	/// <summary>
	/// Gibt die Position zurück, in den nächsten Frames (der int ist die Anzahl der Frames)
	/// </summary>
	/// <returns>Vector2f &position</returns>
	Vector2f getNextPosition(int);

	void setAlive(bool);

	bool getAlive();
	
	~Drone();




};