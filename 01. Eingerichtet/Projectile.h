#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"
#include "Drone.h"
using namespace sf;

/**
Projektil/Schuss, welches vom Turm abgeschossen
*/
class Projectile
{
private:

	/// <summary>
	/// !! NICHT BENUTZEN !!
	/// </summary>
	Projectile();

	/// <summary>
	/// Um welchen Projektil-Typ es sich handelt
	/// </summary>
	int style;

	/// <summary>
	/// Geschwindigkeit des Projektils (je kleiner desto schneller, min. 1 = instant)
	/// </summary>
	float speed;

	/// <summary>
	/// Ob der Schuss, eine Drohne getroffen hat
	/// </summary>
	bool collided;

	/// <summary>
	/// In welche Richtig sich das Projektil bewegt
	/// </summary>
	Vector2f move;

	/// <summary>
	/// KA, was Amon damit will
	/// </summary>
	Vector2f targetstill;

	/// <summary>
	/// KA, was Amon damit will
	/// </summary>
	Vector3f target;

	/// <summary>
	/// Sprite des Projektils
	/// </summary>
	Sprite projectilesprite;

	/// <summary>
	/// Die Drohne, welche das Projektil treffen soll
	/// </summary>
	Drone* dronetarget;

	/// <summary>
	/// Turm, von welchem das Projektil abgeschossen wurde
	/// </summary>
	Tower* tower;

	/// <summary>
	/// Pointer auf die Ressourcen-Klasse zum setzten der Attribute
	/// </summary>
	Ressources* res;

	TowerSpawn* towerspawn;

public:
	Projectile(Tower* _tower, Vector2f _targetstill);
	/// <summary>
	/// Konstruktor vom Projektil
	/// </summary>
	/// <param name="">Welche Drohne getroffen werden soll</param>
	/// <param name="">Von wo das Projektil abgeschossen wurde</param>
	/// <param name="">Wie Turm, nur wenn ein Spawn schießt</param>
	/// <param name="">Projektil-Typ</param>
	/// <param name="">Position</param>
	Projectile(Drone*, Tower*, TowerSpawn*, int, Vector2f);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>Ob das Projektil eine Drohne getroffen hat</returns>
	bool getcollided();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>Gibt die Sprite des Projektils zurück</returns>
	Sprite* getProjectileSprite();

	Vector2f getTargetstill();

	/// <summary>
	/// Setzt die Bewegungsrichtung
	/// </summary>
	void setmove();

	/// <summary>
	/// Feuert den Schuss ab, wird am Ende des Konstruktors aufgerufen
	/// </summary>
	void operate();

	/// <summary>
	/// Sucht ein Ziel
	/// </summary>
	void targeting();

	/// <summary>
	/// Verfolgt ein Ziel
	/// </summary>
	void homing();

	/// <summary>
	/// Bewegt das Projektil
	/// </summary>
	void moveProjectile();

	/// <summary>
	/// Kollidiert mit einem Ziel und macht diesem Schaden
	/// </summary>
	void collission();

	/// <summary>
	/// Destruktor
	/// </summary>
	~Projectile();
};