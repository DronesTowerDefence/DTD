#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
using namespace sf;
class AccountMenu
{
	static AccountMenu* instance;

	Ressources* res;
	RenderWindow* window;

	Sprite background;
	Sprite homeButton;
	
	std::vector<RectangleShape> btnoutlines{1};

	Font font; //Font muss nochmal neu geladen werden aufgrund 
	Text text1;

	/// <summary>
	/// Für Click-Funktion
	/// </summary>
	Vector2i mouse;
	Vector2f pos, pos2;
	bool isClicked;

	AccountMenu();

public:

	static AccountMenu* getInstance();

	void onClick();

	void click();

	void draw();
};

