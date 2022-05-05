#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ressources.h"
#include "TowerAlias.h"
#include "Service.h"
using namespace sf;

class Sidebar
{
private:
	//Map* p_map;
	static Sidebar* instance;
	float price[5]; //Wie viel die Tower kosten
	Texture buttonTexture[5];
	Texture buttonTextureNoBuy[5];
	Texture doubleSpeedTexture;
	Sprite buttonSpr[5];
	Sprite doubleSpeed;


	Font buttonTextFont;
	Text buttonText[5];


	Sidebar();

public:

	~Sidebar();
	/// <summary>
	/// Gibt die Instance zurück
	/// (Singelton)
	/// </summary>
	/// <returns>Instance</returns>
	static Sidebar* getInstance(/*Map**/);
	Texture getTowerTexture(int);

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

};