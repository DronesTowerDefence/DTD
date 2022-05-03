#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
using namespace sf;
class PauseMenu
{
	//Singleton
	static PauseMenu* instance;

	RenderWindow* window;

	Font font;

	Text text1;
	Text text2;

	Texture backgroundTexture;
	Sprite background;
	RectangleShape edge;
	
	RectangleShape volumeSlider;
	float sliderHelper;


	bool isClicked;
	Vector2i mouse;
	Vector2f pos, pos2;

	Texture twitterTexture;
	Sprite twitter;
	RectangleShape socialsBorder;

	Texture homebtnTexture;
	Sprite homebtn;

	RectangleShape mouseRect;

	PauseMenu();
	
	void click();

public:

	static PauseMenu* getInstance();
    /// <summary>
    /// �berpr�ft, ob ESC gedr�ckt wird, und erstellt eine while-Schlife des Pause-Menu, falls es zutrifft (wird in Game::startGame() aufgerufen)
    /// </summary>
    /// <param name="">Event event</param>
    void checkPause(Event);
	/// <summary>
	/// Wird nur f�r das Pause-Menu verwendet
	/// </summary>
	void draw();

	RectangleShape getEdge();
	Sprite getBackground();
	Text getText();
};

