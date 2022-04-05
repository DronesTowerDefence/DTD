#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TowerAlias.h"
#include "Service.h"
using namespace sf;

class Sidebar
{
private:
	//Map* p_map;

	Sprite buttonSpr[5];
	Texture buttonTexture[5];

	Text buttonText[5];
	Font buttonTextFont;

	float price[5]; //Wie viel die Tower kosten

	static Sidebar* instance;
	Sidebar();

public:
	/// <summary>
	/// Gibt die Instance zurück
	/// (Singelton)
	/// </summary>
	/// <returns>Instance</returns>
	static Sidebar* getInstance(/*Map**/);

	/// <summary>
	/// GIbt zurück, welcher Button geklickt wurde
	/// </summary>
	/// <param name="window">Fenster</param>
	/// <returns>Nummer des Towers</returns>
	int isClicked(RenderWindow* window);

	/// <summary>
	/// Draw Sidebar
	/// </summary>
	/// <param name="window"></param>
	void draw(RenderWindow* window);

	Texture getTowerTexture(int);
};