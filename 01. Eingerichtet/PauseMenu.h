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
	bool play;
	RenderWindow* window;

	Vector2i mouse;
	Vector2f pos, pos2;

	Texture backgroundTexture;
	Texture twitterTexture;
	Texture homebtnTexture;
	Texture playbtnTexture;
	Sprite background;
	Sprite twitter;
	Sprite homebtn;
	Sprite playbtn;
	RectangleShape edge;
	RectangleShape volumeSlider;
	RectangleShape socialsBorder;
	RectangleShape volumeOutline;
	RectangleShape btnoutlines[2];

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
		/// Überprüft, ob ESC gedrückt wird, und erstellt eine while-Schlife des Pause-Menu, falls es zutrifft (wird in Game::startGame() aufgerufen)
	/// </summary>
	/// <param name="">Event event</param>
	void checkPause(Event);
	void checkPause();
	/// <summary>
	/// Wird nur für das Pause-Menu verwendet
	/// </summary>
	void draw();

};

