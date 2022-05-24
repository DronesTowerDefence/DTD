#pragma once
#include "Round.h"

/**
|Static-Class|
Packet-Header:
0=Neuer Turm, 1=Update, 2=Turm verkauft, 3=Drohne nimmt Schaden, 4=Leben&Runde,
5=Verloren, 6=PauseMenu, 7=HomeMenu, 8=Doppelte Geschwindigkeit
*/
static class Multiplayer
{
private:
	Multiplayer(); //Laut Internet unnötig, aber habs ausprobiert, man braucht es doch
	Multiplayer(const Multiplayer&);

public:

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
	/// Empfängt ein Packet und wendet es an.
	/// Immer in einer eigenen while-Schleife aufrufen - Bsp.:"while(Multiplayer::receive());"
	/// </summary>
	/// <returns>True, wenn empfangen</returns>
	static bool receive();
};