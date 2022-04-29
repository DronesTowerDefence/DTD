#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
using namespace sf;
class PauseMenu
{
	static PauseMenu* instance;

	RenderWindow* window;
	Text text;
	Texture backgroundTexture;
	Sprite background;
	RectangleShape edge;



	PauseMenu();
	

	
	void draw();
	void click();

public:

	static PauseMenu* getInstance();
    void checkPause(Event);
};

