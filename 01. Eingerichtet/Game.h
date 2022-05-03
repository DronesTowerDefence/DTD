#pragma once
#include <SFML/Audio.hpp>
#include <list>
#include "Ressources.h"
#include "Round.h"
#include "Sidebar.h"
#include "TowerAlias.h"
#include "PauseMenu.h"
#include "HomeMenu.h"

class Game
{
private:

	Ressources* p_ressources;
	Round* round;
	Sidebar* sidebar;
	Map* p_map;
	RenderWindow* window;
	TowerAlias* newTower;
	Font stdFont;
	Text eco;

	Texture gameOverRestartButtonTexture;
	Texture gameOverHomeButtonTexture;
	Texture gameOverBackgroundTexture;
	Sprite gameOverBackround;
	Sprite gameOverRestartButton;
	Sprite gameOverHomeButton;

	SoundBuffer musicBuffer[4];
	Sound music[4];
	int chooseMusic;
	Clock changeMusicTimer;

	bool lost;
	bool isMouseClicked;
	bool doubleSpeed;
	int droneCount;
	Tower* tower;
	RectangleShape toolbar;

	Text gameOverRound;

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
	/// Überprüft ob ein Turm eine Drohne abschießen kann
	/// </summary>
	void checkShoot();

	/// <summary>
	/// Lässt MoneyTower Geld generieren
	/// </summary>
	void generateMoneyTowers();

	void checkLoseGame();

	/// <summary>
	/// Überprüft, ob der towerAlias an einer verbotenen Position ist.
	/// Z.B. Die Sidebar oder die Strecke
	/// </summary>
	/// <returns></returns>
	bool towerAliasForbiddenPosition();

	/// <summary>
	/// Konstruktor von Game
	/// </summary>
	Game();



	/// <summary>
	/// Speichert das Spiel
	/// </summary>
	void saveGame();

	/// <summary>
	/// Lädt einen gespeicherten Spielstand
	/// NOCH NICHT FERTIG!
	/// </summary>
	/// <param name="Map Index"></param>
	/// <returns>Erfolgreich?</returns>
	bool loadGame();

	void getNewEco();

	static Game* instance;
public:
	~Game();

	/// <summary>
	/// Verändert regelmäßig die Musik
	/// </summary>
	void changeBackgroundMusic();


	static Game* getInstance();

	/// <summary>
	/// Startet das Spiel
	/// </summary>
	void startGame();

	/// <summary>
	/// Gibt die Schriftart zurück
	/// </summary>
	/// <returns>Font</returns>
	Font getFont();

	/// <summary>
	/// Gibt einen Pointer auf das Fenster zurück
	/// </summary>
	/// <returns>RenderWindow*</returns>
	RenderWindow* getWindow();


	/// <summary>
	/// Legt das Fenster fest
	/// </summary>
	/// <param name="RenderWindow*"></param>
	void setWindow(RenderWindow*);

	/// <summary>
	/// Gibt erstes Feld der Music wieder
	/// </summary>
	/// <returns></returns>
	Sound getMusic();

	/// <summary>
	/// Setzt die Musik Lautstärke
	/// </summary>
	/// <param name=""></param>
	void setMusicVolume(float);

	/// <summary>
	/// Übergibt das Pause-Screen Window (Kann nicht als festes Attribut in Game sein)
	/// </summary>
	/// <param name=""></param>
	void setPauseScreen(RenderWindow*);



};