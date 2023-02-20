#pragma once
#include "Tower.h"
#include "Ressources.h"

/**
Zusatz-Objekt zu normalem Turm
*/
class TowerSpawn
{
private:
	/// <summary>
	/// !! NICHT BENUTZEN !!
	/// </summary>
	TowerSpawn();

	/// <summary>
	/// Wegpunkte
	/// <para>0: Oben Links</para>
	/// <para>1: Oben Rechts</para>
	/// <para>2: Unten Rechts</para>
	/// <para>3: Unten Links</para>
	/// </summary>
	Vector2f waypoint[4];

	/// <summary>
	/// Wie schnell und in welche Richtung sich das Objekt bewegt, in px pro Frame
	/// </summary>
	Vector2f move;

	/// <summary>
	/// Die Größe der Textur/des Objekts, in px
	/// </summary>
	Vector2f towerSpawnSize;

	/// <summary>
	/// Sprite des Objektes
	/// </summary>
	Sprite spawnsprite;

	/// <summary>
	/// Zeiger auf den Turm, wozu das Objekt gehört
	/// </summary>
	Tower* tower;

	/// <summary>
	/// Zeiger auf die Ressourcen-Klasse für die Initialisierung der Attribute
	/// </summary>
	Ressources* res;

	/// <summary>
	/// Um welche Art von Objekt es sich handelt
	/// <para>1: Flugzeug</para>
	/// </summary>
	int index;

	/// <summary>
	/// Geschwindigkeit des Objektes in px pro Frame
	/// </summary>
	int speed;

	std::list<Vector3f> coverableArea;

	Vector2f target;

public:
	~TowerSpawn();

	/// <summary>
	/// Konstruktor
	/// </summary>
	/// <param name="1: Flugzeug"></param>
	/// <param name="Pointer auf den zugehörigen Tower"></param>
	TowerSpawn(int, Tower*,Vector2f);

	void setCoverableArea();

	std::list<Vector3f> getCoverableArea();

	/// <summary>
	/// Sprite des Flugzeuges
	/// </summary>
	/// <returns>Einen Pointer auf die Sprite des Objektes</returns>
	Sprite* getSpawnSprite();

	/// <summary>
	/// Textur aus der Ressourcen-Klasse
	/// </summary>
	/// <returns>Pointer auf die Textur</returns>
	Texture* getSpawnTexture();

	/// <summary>
	/// Index des Objektes
	/// </summary>
	/// <returns>1: Flugzeug</returns>
	int getIndex();

	/// <summary>
	/// Geschwindigkeit des Objektes in px pro Frame
	/// </summary>
	/// <returns>Geschwindigkeit</returns>
	int getSpeed();

	/// <summary>
	/// Setzt die Geschwindigkeit des Objektes
	/// </summary>
	/// <param name="px pro Frame"></param>
	void setSpeed(int);

	void setMove();

	/// <summary>
	/// Lässt das Objekt schießen
	/// </summary>
	void shoot();

	/// <summary>
	/// Bewegt das Objekt
	/// </summary>
	void moveSpawn();
};

