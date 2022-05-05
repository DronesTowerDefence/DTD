#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
using namespace sf;
class PauseMenu
{
	//Singleton
	static PauseMenu* instance;

	float sliderHelper;

	bool isClicked;
	RenderWindow* window;
	
	Vector2i mouse;
	Vector2f pos, pos2;

	Texture backgroundTexture;
	Texture homebtnTexture;
	Texture twitterTexture;
	
	RectangleShape mouseRect;
	RectangleShape edge;
	RectangleShape volumeSlider;
	RectangleShape socialsBorder;

	Sprite background;
	Sprite homebtn;
	Sprite twitter;


	Font font;

	Text text1;
	Text text2;

	PauseMenu();
	
	void click();

public:

	static PauseMenu* getInstance();
	RectangleShape getEdge();
	Sprite getBackground();
	Text getText();
    
	/// <summary>
    /// �berpr�ft, ob ESC gedr�ckt wird, und erstellt eine while-Schlife des Pause-Menu, falls es zutrifft (wird in Game::startGame() aufgerufen)
    /// </summary>
    /// <param name="">Event event</param>
    void checkPause(Event);
	/// <summary>
	/// Wird nur f�r das Pause-Menu verwendet
	/// </summary>
	void draw();

};

