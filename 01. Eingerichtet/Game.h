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
	void moveDrohnes();
	void checkButtonClick();
	void checkTowerAlias();
	void draw();
	Game();
public:
	Game(RenderWindow * window);
	void startGame();
};

