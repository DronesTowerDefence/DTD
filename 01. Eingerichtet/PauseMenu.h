#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
using namespace sf;
class PauseMenu
{
	static PauseMenu* instance;

	RenderWindow* window;
	Text text1;
	Texture backgroundTexture;
	Sprite background;
	RectangleShape edge;
	Font font;


	PauseMenu();
	

	
	
	void click();

public:

	static PauseMenu* getInstance();
    void checkPause(Event);
	void draw();

	RectangleShape getEdge();
	Sprite getBackground();
	Text getText();
};

