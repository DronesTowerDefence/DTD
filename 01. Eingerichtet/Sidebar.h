#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TowerAlias.h"
#include "Service.h"
using namespace sf;

class Sidebar
{
private:
	RectangleShape backround;
	Map* p_map;

	Sprite buttonSpr[4];
	Texture buttonTexture[4];

	float price[4]; //Wie viel die Tower kosten

	static Sidebar* instance;
	Sidebar();

public:
	/// <summary>
	/// Gibt die Instance zur�ck
	/// (Singelton)
	/// </summary>
	/// <returns>Instance</returns>
	static Sidebar* getInstance(Map*);

	/// <summary>
	/// GIbt zur�ck, welcher Button geklickt wurde
	/// </summary>
	/// <param name="window">Fenster</param>
	/// <returns>Nummer des Towers</returns>
	int isClicked(RenderWindow* window);

	/// <summary>
	/// Draw Sidebar
	/// </summary>
	/// <param name="window"></param>
	void draw(RenderWindow* window);
};