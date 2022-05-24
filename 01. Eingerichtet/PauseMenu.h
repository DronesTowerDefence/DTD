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
	bool mute;
	bool multiplayerIsPaused;
	RenderWindow* window;

	Vector2i mouse;
	Vector2f pos, pos2;

	Texture backgroundTexture;
	Texture twitterTexture;
	Texture homebtnTexture;
	Texture playbtnTexture;
	Texture mutebtnTexture;
	
	Sprite background;
	Sprite twitter;
	Sprite homebtn;
	Sprite playbtn;
	Sprite mutebtn;
	
	RectangleShape edge;
	RectangleShape volumeSlider;
	RectangleShape socialsBorder;
	RectangleShape volumeOutline;
	RectangleShape btnoutlines[3];


	Font font;

	Text text1;
	Text text2;

	PauseMenu();

	void click();

public:

	static PauseMenu* getInstance();
	float getSliderHelper();
	void setMultiplayerIsPaused(bool);
	bool getMultiplayerIsPaused();
	RectangleShape getEdge();
	Sprite getBackground();
	Text getText();

	void setSliderHelper(float);

	/// <summary>
		/// Überprüft, ob ESC gedrückt wird, und erstellt eine while-Schlife des Pause-Menu, falls es zutrifft (wird in Game::startGame() aufgerufen)
	/// </summary>
	/// <param name="">Event event</param>
	void checkPause(Event);

	/// <summary>
	/// !!NUR FÜR MULTIPLAYER-KLASSE!! Wenn der Host in das Pause-Menü geht soll der Client auch ins Pause-Menü gehen
	/// </summary>
	/// <param name=""></param>
	void checkPause(bool);

	void checkPause();

	/// <summary>
	/// Wird nur für das Pause-Menu verwendet
	/// </summary>
	void draw();

};

