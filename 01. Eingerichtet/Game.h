#pragma once
#include <list>
#include "Transmit.h"
#include "Ressources.h"
#include "Round.h"
#include "Sidebar.h"
#include "TowerAlias.h"
#include "PauseMenu.h"
#include "HomeMenu.h"


class Game
{
private:
	static Game* instance;

	int chooseMusic;
	int droneCount;
	/// <summary>
	/// 1 = Single
	/// 2 = Host
	/// 3 = Client
	/// </summary>
int status;

	bool lost;
	bool isMouseClicked;
	bool doubleSpeed;


	Texture gameOverRestartButtonTexture;
	Texture gameOverHomeButtonTexture;
	Texture gameOverBackgroundTexture;

	RectangleShape toolbar;

	Sprite gameOverBackround;
	Sprite gameOverRestartButton;
	Sprite gameOverHomeButton;

	Clock changeMusicTimer;
	Clock sendPacketTimer;
	SoundBuffer musicBuffer[4];
	Sound music[4];

	Tower* tower;

	Font stdFont;
	Text eco;
	Text gameOverRound;

	Event event;

	Clock shootCooldown;
	Clock shootCooldown2;


	Ressources* p_ressources;
	Round* round;
	Sidebar* sidebar;
	Map* p_map;
	RenderWindow* window;
	TowerAlias* newTower;
	/// <summary>
	/// Lädt einen gespeicherten Spielstand
	/// NOCH NICHT FERTIG!
	/// </summary>
	/// <param name="Map Index"></param>
	/// <returns>Erfolgreich?</returns>
	bool loadGame();
	/// <summary>
	/// Überprüft, ob der towerAlias an einer verbotenen Position ist.
	/// Z.B. Die Sidebar oder die Strecke
	/// </summary>
	/// <returns></returns>
	bool towerAliasForbiddenPosition();

	/// <summary>
	/// Lädt ein Packet in die Game
	/// </summary>
	/// <returns></returns>
	bool loadPacketContent(Transmit*);

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

	/// <summary>
	/// Zieht Leben ab, wenn eine Drohne den Ausgang erreicht hat und überprüft ob man verloren hat
	/// </summary>
	void checkLoseGame();

	/// <summary>
	/// Konstruktor von Game
	/// </summary>
	Game();

public:
	~Game();

	static Game* getInstance();



	/// <summary>
	/// Gibt einen Pointer auf das Fenster zurück
	/// </summary>
	/// <returns>RenderWindow*</returns>
	RenderWindow* getWindow();
	/// <summary>
	/// Gibt die Schriftart zurück
	/// </summary>
	/// <returns>Font</returns>
	Font getFont();
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
	/// Legt das Fenster fest
	/// </summary>
	/// <param name="RenderWindow*"></param>
	void setWindow(RenderWindow*);
	/// <summary>
	/// Übergibt das Pause-Screen Window (Kann nicht als festes Attribut in Game sein)
	/// </summary>
	/// <param name=""></param>
	//void setPauseScreen(RenderWindow*);

	void setStatus(int state);

	/// <summary>
	/// Startet das Spiel
	/// </summary>
	void startGame();

	/// <summary>
	/// Verändert regelmäßig die Musik
	/// </summary>
	void changeBackgroundMusic();

	/// <summary>
	/// Aktualisiert die Infos oben Links (Geld, Leben, Runde)
	/// </summary>
	void updateEco();

	/// <summary>
	/// Klassen, welche von Game verwaltet werden, werden gelöscht
	/// </summary>
	void resetAll();

	/// <summary>
	/// Speichert das Spiel
	/// </summary>
	void saveGame();

	/// <summary>
	/// Sendet Informationen
	/// </summary>
	/// <returns> True wenn erfolgreich</returns>
	bool sendPackets();

	/// <summary>
	/// Empfängt informationen
	/// </summary>
	/// <returns>True wenn was angekommen ist</returns>
	Transmit* receivePacket();

};