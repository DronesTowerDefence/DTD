#pragma once
#include "Round.h"
#include "MultiplayerPlayer.h"

#define port 4567

/**
| Static-Class |

Die Clients kommunizieren nur �ber den Host. Sie wissen also nicht, wie viele Mitspieler es tats�chlich gibt.
Der Host muss diese Infos (Name, Bild, etc.) an die Clients senden.

Wenn ein Client z.B. einen Turm platziert sendet er diese Info an den Host, der Host leitet diese Info dann an alle
Clients, au�er an den von welchem er die Info bekommen hat, weiter.


Packet-Header:
0=Neuer Turm, 1=Update, 2=Turm verkauft, 3=Drohne nimmt Schaden, 4=Leben&Runde,
5=Verloren, 6=PauseMenu, 7=HomeMenu/Restart, 8=Doppelte Geschwindigkeit, 9=Verbindungs�berpr�fung,
10=ChatMessage, 11=Nagelhaufen wird platziert, 12=Geld senden, 13=Spielstart
*/
static class Multiplayer
{
private:
	Multiplayer(); //Laut Internet unn�tig die Konstruktoren bei einer statischen Klasse privat zu machen, aber habs ausprobiert, man muss es doch machen
	Multiplayer(const Multiplayer&);

	static bool send(sf::Packet* p, int from = -1);

public:

	// Zeit, wann die Verbindung als abgebrochen gilt
	static const Time timeout;

	// Zeit, in welchen Abst�nden die �berpr�fungspackete gesendet werden sollen
	static const Time timeoutSend;

	// Zeit, wann bei keiner Verbindung in den Singleplayer gewechselt wird
	static const Time timeUntilSingleplayer;

	// F�r Host (F�r die Kommunikation mit anderem Spieler). Wenn Client dann: player[0]=host
	static MultiplayerPlayer* player[3];

	// F�r Client (Nur zum Anzeigen der Spieler)
	static MultiplayerPlayer_light* playerLight[4];

	// Anzahl an Spielern (Im SP=0)
	static int multiplayerPlayerCount;

	// F�r Thread
	static bool initializeMultiplayerIsDone;

	// F�r Thread, l�uft solange bis false
	static bool checkMultiplayerConnect;

	// Sendet ein minimales Packet, um die Verbindung zu �berpr�fen
	static bool send();

	/// <summary>
	/// Sendet ein Packet, welches einen Turm platziert oder verkauft
	/// </summary>
	/// <param name="">Tower an welchem entwas ge�ndert wurde</param>
	/// <param name="">Index, was ge�ndert wurde (0 = neuer Turm, 1 = Verkaufen)</param>
	/// <returns>True, wenn gesendet</returns>
	static bool send(Tower*, int);

	/// <summary>
	/// Sendet ein Packet, welches einen Turm upgradet
	/// </summary>
	/// <param name="TowerID">Tower an welchem entwas ge�ndert wurde</param>
	/// <param name="Index, was ge�ndert wurde">1 = Update1, 2 = Update2</param>
	/// <param name="updateIndex"></param>
	/// <returns>True, wenn gesendet</returns>
	static bool send(int, int, int);

	/// <summary>
	/// Sendet ein Packet, welches auf eine Drohne schie�t
	/// </summary>
	/// <param name="TowerID">Turm welcher auf eine Drohne schie�t</param>
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
	/// Sendet ein Packet, welches die eigene AccountID und die Nachricht enth�lt
	/// </summary>
	/// <param name="">Nachricht</param>
	/// <returns>True, wenn gesendet</returns>
	static bool send(std::string);

	/// <summary>
	/// Sendet ein Packet, welches Geld enth�lt
	/// </summary>
	/// <param name="">Geld Betrag</param>
	/// <returns>True, wenn gesendet</returns>
	static bool send(std::string, int);

	/// <summary>
	/// Nagelhaufen wird platziert
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	static bool send(int turmID, Vector2f pos);

	/// <summary>
	/// !!ACHTUNG!! Sendet ein Packet, ohne �berpr�fung der Parameter
	/// </summary>
	/// <param name="">Header</param>
	/// <param name="">Inhalt</param>
	/// <returns></returns>
	static bool send(int, std::string);

	/// <summary>
	/// <para>Empf�ngt Packete und wendet sie an.</para>
	/// </summary>
	static void receive();

	/// <summary>
	/// Setzt alle Membervariablen etc zur�ck
	/// </summary>
	static void deleteMultiplayer();

	static void setBlocking(bool blocking);

	static void updatePlayerCount(bool isHost);

	/// <summary>
	/// Baut eine Verbindung auf. Nur f�r MultiplayerGUI
	/// </summary>
	/// <param name="isHost">False, wenn Client</param>
	static void initializeMultiplayer(bool isHost);
};