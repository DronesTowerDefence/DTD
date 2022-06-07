#pragma once
#include "Round.h"

/**
|Static-Class|
Packet-Header:
0=Neuer Turm, 1=Update, 2=Turm verkauft, 3=Drohne nimmt Schaden, 4=Leben&Runde,
5=Verloren, 6=PauseMenu, 7=HomeMenu/Restart, 8=Doppelte Geschwindigkeit, 9=Verbindungs�berpr�fung
*/
static class Multiplayer
{
private:
	Multiplayer(); //Laut Internet unn�tig die Konstruktoren bei einer statischen Klasse privat zu machen, aber habs ausprobiert, man muss es doch machen
	Multiplayer(const Multiplayer&);

public:

	/// <summary>
	/// Zeit, wann die Verbindung als abgebrochen gilt
	/// </summary>
	static const Time timeout;

	/// <summary>
	/// Zeit, in welchen Abst�nden die �berpr�fungspackete gesendet werden sollen
	/// </summary>
	static const Time timeoutSend;

	/// <summary>
	/// Sendet ein minimales Packet, um die Verbindung zu �berpr�fen
	/// </summary>
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
	/// <para>Empf�ngt ein Packet und wendet es an.</para>
	/// <para>Immer in einer eigenen while-Schleife aufrufen: Bsp.:"while(Multiplayer::receive());"</para>
	/// </summary>
	/// <returns>
	/// <para>True, wenn empfangen und Packet-Header g�ltig</para>
	/// <para>False, wenn Packet-Header ung�ltig</para>
	/// </returns>
	static bool receive();
};