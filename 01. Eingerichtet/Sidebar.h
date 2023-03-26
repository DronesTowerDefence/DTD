#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ressources.h"
#include "TowerAlias.h"
#include "Service.h"
#include "Daily.h"
#include "Button.h"
using namespace sf;

class Sidebar
{
private:
	//Map* p_map;
	static Sidebar* instance;
	float price[towerCount]; //Wie viel die Tower kosten
	Button* buttonSpr[towerCount];
	Button* doubleSpeed;

	Font buttonTextFont;
	Text buttonText[towerCount];

	Ressources* res;

	Sidebar();

public:

	~Sidebar();
	/// <summary>
	/// Gibt die Instance zurück
	/// (Singelton)
	/// </summary>
	/// <returns>Instance</returns>
	static Sidebar* getInstance(/*Map**/);

	void checkHover(RenderWindow* window);

	bool isChangeSpeed(RenderWindow* window);
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
	void setSpeedButton(bool speed);

};