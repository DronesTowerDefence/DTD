#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Service.h"
using namespace sf;
class PauseMenu
{
	//Singleton
	static PauseMenu* instance;

	Ressources* res;

	float sliderHelperMusic;
	float sliderHelperSound;
	bool isClicked;
	bool play;
	bool mute;
	bool multiplayerIsPaused;
	RenderWindow* window;

	Vector2i mouse;
	Vector2f pos, pos2;
	
	Texture* mutebtnTexture;

	Sprite background;
	Sprite twitter;
	Sprite homebtn;
	Sprite playbtn;
	Sprite mutebtn;
	
	RectangleShape edge;
	RectangleShape musicSlider;
	RectangleShape sfxSlider;
	RectangleShape socialsBorder;
	RectangleShape musicOutline;
	RectangleShape sfxOutline;
	RectangleShape btnoutlines[3];


	Font font; //Font muss nochmal neu geladen werden aufgrund 
	Text text1;
	Text text2;

	PauseMenu();

	void click();

public:

	static PauseMenu* getInstance();
	/// <summary>
	/// Laustärkeslider als Zahl
	/// </summary>
	/// <returns>float sliderHelperMusic</returns>
	float getsliderHelperMusic();

	float getSliderHelperSound();
	
	void setMultiplayerIsPaused(bool);
	bool getMultiplayerIsPaused();


	RectangleShape getEdge(); //Get-Funktionen
	Sprite getBackground();
	Text getText();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="">float neuersliderHelperMusic</param>
	void setsliderHelperMusic(float);

	void setSliderHelperSound(float);

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

	/// <summary>
	/// Überprüft, ob das Spiel pausiert ist
	/// </summary>
	void checkPause();

	/// <summary>
	/// Wird nur für das Pause-Menu verwendet
	/// </summary>
	void draw();

};

