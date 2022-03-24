#pragma once
#include "Base.h"
#include "Sidebar.h";
#include "Map.h"
#include <list>
#include "Drone.h"
#include "TowerAlias.h"
class Game
{
private:
	Base* base;
	Sidebar* sidebar;
	Map* map;
	RenderWindow* window;
	TowerAlias* newTower;
	RectangleShape* background;
	Texture* texture;
	void newRound();
	/// <summary>
	/// Bewegt alle Drohnen eine Position weiter
	/// </summary>
	void moveDrohnes();
	/// <summary>
	/// Checkt, ob ein Button gekllickt wurde
	/// </summary>
	void checkButtonClick();
	/// <summary>
	/// Checkt, ob Drag & Drop aktiv ist, oder ob losgelassen wird
	/// </summary>
	void checkTowerAlias();
	/// <summary>
	/// Draw alle Elemente
	/// </summary>
	void draw();
	Game();
public:
	Game(RenderWindow * window);
	/// <summary>
	/// Startet das Spiel
	/// </summary>
	void startGame();
};

