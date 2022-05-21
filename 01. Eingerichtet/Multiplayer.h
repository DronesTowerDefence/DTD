#pragma once
//Singleton
#include "Round.h"

//Packet-Header: 0=Neuer Turm, 1=Update, 2=Turm verkauft, 3=Drohne nimmt Schaden, 4=Round-Werte (Leben&Runde)

class Multiplayer
{
private:
	Multiplayer();
	static Multiplayer* instance;
	Ressources* res;
	Round* p_round;

public:
	static Multiplayer* getInstance();

	/// <summary>
	/// Sendet ein Packet
	/// </summary>
	/// <param name="">Tower an welchem entwas geändert wurde</param>
	/// <param name="Index, was geändert wurde">1 = Update1, 2 = Update2</param>
	/// <param name="updateIndex"></param>
	/// <returns>True, wenn es geklappt hat</returns>
	bool send(Tower*, int, int);

	/// <summary>
	/// Sendet ein Packet
	/// </summary>
	/// <param name="">Tower an welchem entwas geändert wurde</param>
	/// <param name="">Index, was geändert wurde (0 = neuer Turm, 1 = Verkaufen)</param>
	/// <returns>True, wenn es geklappt hat</returns>
	bool send(Tower*, int);

	/// <summary>
	/// Sendet ein Packet
	/// </summary>
	/// <param name="">Drohne an welcher etwas geändert wurde</param>
	/// <param name="">Wie viel Schaden sie erhalten hat</param>
	/// <returns>True, wenn es geklappt hat</returns>
	bool send(Drone*, int);

	/// <summary>
	/// Synchronisiert die Werte/Attribute, welche in Round gespeichert sind
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool send();

	/// <summary>
	/// Empfängt ein Packet und wendet es an
	/// </summary>
	/// <returns>True, wenn es geklappt hat</returns>
	bool receive();
};