#pragma once
#include <list>
#include "Sidebar.h"
#include "Map.h"
#include "Drone.h"
#include "TowerAlias.h"
#include "Round.h"

class Game
{
private:
	Round* round;
	Sidebar* sidebar;
	Map* map;
	RenderWindow* window;
	TowerAlias* newTower;
	RectangleShape* background;
	Texture* texture;
	Font stdFont;
	Text eco;
	

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

	static Game* instance;
public:
	static Game* getInstance();

	Game(RenderWindow* window);
	/// <summary>
	/// Startet das Spiel
	/// </summary>
	void startGame();

	Font getFont();
	
	RenderWindow* getWindow();
};