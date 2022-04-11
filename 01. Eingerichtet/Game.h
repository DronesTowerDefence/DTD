#pragma once
#include <SFML/Audio.hpp>
#include <list>
#include "Round.h"
#include "Sidebar.h"
#include "TowerAlias.h"

class Game
{
private:
	Round* round;
	Sidebar* sidebar;
	Map* p_map;
	RenderWindow* window;
	TowerAlias* newTower;
	RectangleShape* background;
	Texture* texture;
	Font stdFont;
	Text eco;

	SoundBuffer musicBuffer[4];
	Sound music[4];
	int chooseMusic;
	Clock changeMusicTimer;

	bool lost;
	int droneCount;

	/// <summary>
	/// Ver�ndert regelm��ig die Musik
	/// </summary>
	void changeBackgroundMusic();

	void newRound();
	/// <summary>
	/// Bewegt alle Drohnen eine Position weiter
	/// </summary>
	void moveDrohnes();
	/// <summary>
	/// Checkt, ob ein Button gekllickt wurde
	/// </summary>
	void checkButtonClick();
	/// <summary>
	/// Checkt, ob Drag & Drop aktiv ist, oder ob losgelassen wird
	/// </summary>
	void checkTowerAlias();
	/// <summary>
	/// Draw alle Elemente
	/// </summary>
	void draw();

	/// <summary>
	/// �berpr�ft ob ein Turm eine Drohne abschie�en kann
	/// </summary>
	void checkShoot();

	/// <summary>
	/// L�sst MoneyTower Geld generieren
	/// </summary>
	void generateMoneyTowers();

	void loseGame();

	/// <summary>
	/// �berpr�ft, ob der towerAlias an einer verbotenen Position ist.
	/// Z.B. Die Sidebar oder die Strecke
	/// </summary>
	/// <returns></returns>
	bool towerAliasForbiddenPosition();

	/// <summary>
	/// Konstruktor von Game
	/// </summary>
	Game();

	/// <summary>
	/// Musik und Sounds werden initialisiert
	/// </summary>
	void setMusicSound();

	/// <summary>
	/// Speichert das Spiel
	/// </summary>
	void safeGame();

	/// <summary>
	/// L�dt einen gespeicherten Spielstand
	/// NOCH NICHT FERTIG!
	/// </summary>
	/// <param name="Map Index"></param>
	/// <returns>Erfolgreich?</returns>
	bool loadGame(int);

	static Game* instance;
public:

	static Game* getInstance();

	/// <summary>
	/// Startet das Spiel
	/// </summary>
	void startGame();

	/// <summary>
	/// Gibt die Schriftart zur�ck
	/// </summary>
	/// <returns>Font</returns>
	Font getFont();
	
	/// <summary>
	/// Gibt einen Pointer auf das Fenster zur�ck
	/// </summary>
	/// <returns>RenderWindow*</returns>
	RenderWindow* getWindow();

	/// <summary>
	/// Legt das Fenster fest
	/// </summary>
	/// <param name="RenderWindow*"></param>
	void setWindow(RenderWindow*);
};