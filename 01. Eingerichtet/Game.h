#pragma once
#include "Ressources.h"
#include "Sidebar.h"
#include "TowerAlias.h"
#include "PauseMenu.h"
#include "HomeMenu.h"
#include "Tower.h"

/**
Das Hauptspiel, wo auf einer Map Drohnen sich bewegen und vom Spieler platzierte Türme auf diese Drohnen schießen
*/
class Game
{
private:
	/// <summary>
	/// Instance, weil Singleton
	/// </summary>
	static Game* instance;

	/// <summary>
	/// Welcher Track der Musik gerade läuft
	/// </summary>
	int chooseMusic;

	/// <summary>
	/// Wie viele Drohnen gerade auf dem Bildschirm sind
	/// </summary>
	int droneCount;

	/// <summary>
	/// 1 = Single
	/// 2 = Host
	/// 3 = Client
	/// </summary>
	int status;
	int droneRow;

	int currentDrones[5];
	int currentRound;

	/// <summary>
	/// Unnötig? Ist glaube der alte Counter vom Flugzeug-Schuss
	/// </summary>
	int shootClockSpeed;

	/// <summary>
	/// Ob die linke Maustaste gedrückt wurde
	/// </summary>
	bool isMouseClicked;

	/// <summary>
	/// Ob doppelte Geschwindigkeit
	/// </summary>
	bool doubleSpeed;

	/// <summary>
	/// Die Shape, wo die Sidebar drin ist
	/// </summary>
	RectangleShape toolbar;

	/// <summary>
	/// Die Sprite des Bildschirmes, ob man gewonnen oder verloren hat
	/// </summary>
	Sprite gameOverWonBackround;

	/// <summary>
	/// Die Sprite des Neustart-Knopfes
	/// </summary>
	Sprite restartButton;

	/// <summary>
	/// Die Sprite des Hauptmenü-Knopfes
	/// </summary>
	Sprite homeButton;

	/// <summary>
	/// Wann die Musik wechselt
	/// </summary>
	Clock changeMusicTimer;

	/// <summary>
	/// Die Buffer der Musik
	/// </summary>
	SoundBuffer musicBuffer[4];

	/// <summary>
	/// Die Musik
	/// </summary>
	Sound music[4];

	/// <summary>
	/// Ein Pointer auf einen Turm
	/// </summary>
	Tower* tower;

	/// <summary>
	/// Die Schriftart
	/// </summary>
	Font stdFont;

	/// <summary>
	/// Der Text oben links, welcher die Leben, Geld und Rundenanzahl anzeigt
	/// </summary>
	Text eco;

	/// <summary>
	/// Der Text, welcher auf dem gewinnen-/verlieren-Bildschirm angezeigt wird
	/// </summary>
	Text gameOverWonText[2];

	/// <summary>
	/// Das event, welches z.B. auf einen Tastendruck überprüft
	/// </summary>
	Event event;

	/// <summary>
	/// Die Clock für die Überprüfung der Verbindung (empfangen)
	/// </summary>
	Clock multiplayerCheckConnectionClock;

	/// <summary>
	/// Die Clock für die Überprüfung der Verbindung (senden)
	/// </summary>
	Clock multiplayerCheckConnectionSendClock;

	/// <summary>
	/// Pointer auf die Ressourcen-Klasse, fürs setzen der Attribute
	/// </summary>
	Ressources* p_ressources;

	/// <summary>
	/// Pointer auf die Round
	/// </summary>
	Round* round;

	/// <summary>
	/// Pointer auf die Sidebar
	/// </summary>
	Sidebar* sidebar;

	/// <summary>
	/// Pointer auf die Map
	/// </summary>
	Map* p_map;

	/// <summary>
	/// Pointer auf das Fenster
	/// </summary>
	RenderWindow* window;

	/// <summary>
	/// TowerAlias; nullptr, wenn kein Turm platziert werden soll / kein TowerAlias ausgewählt ist
	/// </summary>
	TowerAlias* newTower;

	/// <summary>
	/// Lädt einen gespeicherten Spielstand
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
	/// Zieht Leben ab, wenn eine Drohne den Ausgang erreicht hat
	/// </summary>
	void subRoundHealth();

	/// <summary>
	/// Überprüft ob man verloren hat
	/// </summary>
	void checkLoseGame();

	/// <summary>
	/// Überprüft, ob Drohnen am Eingang erscheinen sollen und ob die nächste Runde beginnt
	/// </summary>
	void checkDroneCount();

	/// <summary>
	/// Konstruktor von Game
	/// </summary>
	Game();

public:
	~Game();

	/// <summary>
	/// Singleton
	/// </summary>
	/// <returns>Gibt die Instance zurück</returns>
	static Game* getInstance();

	int getShootClockSpeed();

	bool getDoubleSpeed();

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

	Clock* getMultiplayerCheckConnectionClock();

	/// <summary>
	/// Gibt den Status zurück, ob Singleplayer/Host/Client
	/// </summary>
	/// <returns></returns>
	int getStatus();

	int getDroneRow();

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

	void setShootClockSpeed(int);
	void setStatus(int state);
	void setDoubleSpeed(bool wert);
	void setDroneCount(int);

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
	/// Kehrt ins Hauptmenü zurück
	/// </summary>
	void mainMenu();

	/// <summary>
	/// Startet das Spiel auf der aktuellen Map neu
	/// </summary>
	void restart();

	/// <summary>
	/// Verkauft einen Tower
	/// </summary>
	/// <param name="t">Welcher Tower verkauft werden soll</param>
	void sellTower(Tower* t);

	/// <summary>
	/// Überprüft die Multiplayer-Verbindung
	/// </summary>
	void checkMultiplayerConnection();

	/// <summary>
	///
	/// </summary>
	void setDroneRow(int g);

	/// <summary>
	/// Löscht den Spielstand zur aktuellen Map
	/// </summary>
	/// <returns>True wenn erfolgreich</returns>
	bool deleteSaveGame();
};