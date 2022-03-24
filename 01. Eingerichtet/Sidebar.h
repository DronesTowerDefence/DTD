#pragma once
#include "SFML/Graphics.hpp"
#include "BuyTower.h"
#include "Base.h"
using namespace sf;
class Sidebar
{
private:
	RectangleShape backround;
	BuyTower* towers[4];

	static Sidebar* instance;
	Sidebar();

public:
	/// <summary>
	/// Gibt die Instance zurück
	/// (Singelton)
	/// </summary>
	/// <returns>Instance</returns>
	static Sidebar* getInstance();
	/// <summary>
	/// GIbt zurück, welcher Button geklickt wurde
	/// </summary>
	/// <param name="window">Fenster</param>
	/// <returns>Nummer des Towers</returns>
	int isCklickes(RenderWindow* window);
	/// <summary>
	/// Draw Sidebar
	/// </summary>
	/// <param name="window"></param>
	void draw(RenderWindow* window);
};

