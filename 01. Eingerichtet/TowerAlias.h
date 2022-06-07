#pragma once
#include<SFML/Graphics.hpp>
#include "Ressources.h"
#include "Round.h"
#include "Service.h"
using namespace sf;

/**
Ein Turm, welcher nicht schießen etc kann. Wird benutzt um einen richtigen Turm zu platzieren
*/
class TowerAlias
{
private:
	/// <summary>
	/// Typ, um welchen Turm es sich handelt
	/// </summary>
	int index;

	/// <summary>
	/// Reichweite des Turmes
	/// </summary>
	float range;

	/// <summary>
	/// Kaufpreis des Turmes
	/// </summary>
	float price;

	/// <summary>
	/// Position des Turmes
	/// </summary>
	Vector2f pos;

	/// <summary>
	/// Kreis, der die Reichweite des Turmes darstellt
	/// </summary>
	CircleShape rangeShape;

	/// <summary>
	/// Rechteck für das Flugzeug: Die Bahn wo es lang fliegt
	/// </summary>
	RectangleShape* rangeShapePlane;

	/// <summary>
	/// Die Sprite des Turmes
	/// </summary>
	Sprite towerAliasSpr;

	/// <summary>
	/// Ein Pointer auf die Map (evtl. unnötig)
	/// </summary>
	Map* p_map;

	/// <summary>
	/// Pointer auf die Ressourcen-Klasse zum setzen der Attribute
	/// </summary>
	Ressources* res;

public:
	/// <summary>
	/// Konstruktor für TowerAlias
	/// </summary>
	/// <param name="int"></param>
	/// <param name="Map*"></param>
	TowerAlias(int, Map*);

	/// <summary>
	/// Um welchen Turm es sich handelt
	/// </summary>
	/// <returns>Return den Typ des Turmes</returns>
	int getIndex();

	/// <summary>
	/// Gibt die Position vom TowerAlias zurück
	/// </summary>
	/// <returns>Vector der Position</returns>
	Vector2f getPos();

	/// <summary>
	/// Gibt einen Zeiger auf den Kreis der Reichweite zurück
	/// </summary>
	/// <returns>CircleShape</returns>
	CircleShape* getRangeShape();

	/// <summary>
	/// Gibt einen Pointer auf das Rechteck der Flugbahn des Flugzeuges
	/// </summary>
	/// <returns>Pointer auf die Shape; Wenn kein Flugzeug, dann nullptr</returns>
	RectangleShape* getRangeShapePlane();

	/// <summary>
	/// Gibt einen Zeiger auf die Sprite von TowerAlias zurück
	/// </summary>
	/// <returns>Sprite des Turmes</returns>
	Sprite* getSpr();

	/// <summary>
	/// Setzt die Position des Objektes
	/// </summary>
	/// <param name="mouse">Position des Mauszeigers</param>
	void setPositionMouse(Vector2i);

	/// <summary>
	/// Erstellt einen Tower
	/// </summary>
	void CreateNewTower();
};