#pragma once
#include "Round.h"
#include "MultiplayerPlayer.h"

#define port 4567

/**
|Static-Class|
Packet-Header:
0=Neuer Turm, 1=Update, 2=Turm verkauft, 3=Drohne nimmt Schaden, 4=Leben&Runde,
5=Verloren, 6=PauseMenu, 7=HomeMenu/Restart, 8=Doppelte Geschwindigkeit, 9=Verbindungsüberprüfung,
10=ChatMessage, 11=Nagelhaufen wird platziert, 12=Geld senden, 13=MapChooseIndex, 14=PlayerName,
15=MultiplayerPlayerCount, 16=Spielstart
*/
static class Multiplayer
{
private:
	Multiplayer(); //Laut Internet unnötig die Konstruktoren bei einer statischen Klasse privat zu machen, aber habs ausprobiert, man muss es doch machen
	Multiplayer(const Multiplayer&);

	static bool send(sf::Packet* p, int from);

public:

	/// <summary>
	/// Zeit, wann die Verbindung als abgebrochen gilt
	/// </summary>
	static const Time timeout;

	/// <summary>
	/// Zeit, in welchen Abständen die Überprüfungspackete gesendet werden sollen
	/// </summary>
	static const Time timeoutSend;

	/// <summary>
	/// Zeit, wann bei keiner Verbindung in den Singleplayer gewechselt wird
	/// </summary>
	static const Time timeUntilSingleplayer;

	/// <summary>
	/// Array mit allen Spielern
	/// </summary>
	static MultiplayerPlayer* player[3];

	static MultiplayerPlayer_light* playerLight[3];

	/// <summary>
	/// Anzahl an Spielern (Im SP=0)
	/// </summary>
	static int multiplayerPlayerCount;

	/// <summary>
	/// Für Thread
	/// </summary>
	static bool initializeMultiplayerIsDone;

	/// <summary>
	/// Sendet ein minimales Packet, um die Verbindung zu überprüfen
	/// </summary>
	static bool send();

	/// <summary>
	/// Sendet ein Packet, welches einen Turm platziert oder verkauft
	/// </summary>
	/// <param name="">Tower an welchem entwas geändert wurde</param>
	/// <param name="">Index, was geändert wurde (0 = neuer Turm, 1 = Verkaufen)</param>
	/// <returns>True, wenn gesendet</returns>
	static bool send(Tower*, int);

	/// <summary>
	/// Sendet ein Packet, welches einen Turm upgradet
	/// </summary>
	/// <param name="TowerID">Tower an welchem entwas geändert wurde</param>
	/// <param name="Index, was geändert wurde">1 = Update1, 2 = Update2</param>
	/// <param name="updateIndex"></param>
	/// <returns>True, wenn gesendet</returns>
	static bool send(int, int, int);

	/// <summary>
	/// Sendet ein Packet, welches auf eine Drohne schießt
	/// </summary>
	/// <param name="TowerID">Turm welcher auf eine Drohne schießt</param>
	/// <param name="DroneID">Drohne auf die geschossen wird</param>
	/// <returns>True, wenn gesendet</returns>
	static bool send(int, int);

	/// <summary>
	/// Synchronisiert Round-Attribute, ob das Spiel verloren, pausiert, verlassen oder neugestartet wurde
	/// </summary>
	/// <param name="Index:">0=Synchronisiert Health und Round-Index, 1=Verloren, 2=Pausiert, 3=HomeMenu, 4=Restart, 5=doubleSpeed</param>
	/// <param name="Bei Index 0:">True = Pausiert, False = Nicht mehr pausiert</param>
	/// <returns>True, wenn gesendet</returns>
	static bool send(int, bool);

	/// <summary>
	/// Sendet ein Packet, welches die eigene AccountID und die Nachricht enthält
	/// </summary>
	/// <param name="">Nachricht</param>
	/// <returns>True, wenn gesendet</returns>
	static bool send(std::string);

	/// <summary>
	/// Sendet ein Packet, welches Geld enthält
	/// </summary>
	/// <param name="">Geld Betrag</param>
	/// <returns>True, wenn gesendet</returns>
	static bool send(int);

	static bool send(int, Vector2f);

	/// <summary>
	/// !!ACHTUNG!! Sendet ein Packet, ohne Überprüfung der Parameter
	/// </summary>
	/// <param name="">Header</param>
	/// <param name="">Inhalt</param>
	/// <returns></returns>
	static bool send(int, std::string);

	/// <summary>
	/// <para>Empfängt Packete und wendet sie an.</para>
	/// </summary>
	static void receive();

	/// <summary>
	/// Setzt alle Membervariablen etc zurück
	/// </summary>
	static void deleteMultiplayer();

	static void resetMultiplayerSockets();

	static void setBlocking(bool blocking);

	static void updatePlayerCount();

	/// <summary>
	/// Baut eine Verbindung auf. Am besten als Thread ausführen
	/// </summary>
	/// <param name="isHost">False, wenn Client</param>
	static void initializeMultiplayer(bool isHost);
};