#pragma once
#include <list>
#include "Round.h"
#include "Sidebar.h"
#include "TowerAlias.h"

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

	/// <summary>
	/// �berpr�ft ob ein Turm eine Drohne abschie�en kann
	/// </summary>
	void checkShoot();

	/// <summary>
	/// Konstruktor von Game
	/// </summary>
	Game();

	static Game* instance;
public:

	static Game* getInstance();

	/// <summary>
	/// Startet das Spiel
	/// </summary>
	void startGame();

	/// <summary>
	/// Gibt die Schriftart zur�ck
	/// </summary>
	/// <returns>Font</returns>
	Font getFont();
	
	/// <summary>
	/// Gibt einen Pointer auf das Fenster zur�ck
	/// </summary>
	/// <returns>RenderWindow*</returns>
	RenderWindow* getWindow();

	/// <summary>
	/// Legt das Fenster fest
	/// </summary>
	/// <param name="RenderWindow*"></param>
	void setWindow(RenderWindow*);
};