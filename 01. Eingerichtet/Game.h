#pragma once
#include "Base.h"
#include "Sidebar.h";
#include "Map.h"
#include <list>
#include "Drone.h"
class Game
{
private:
	Base* base;
	Sidebar* sidebar;
	Map* map;
	RenderWindow* window;
	std::list<Drone*> drones;
	void newRound();
	void moveDrohnes();
	void checkButtonClick();
public:
	Game();
	void startGame();
};

