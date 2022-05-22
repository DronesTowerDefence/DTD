#pragma once
//Singleton
#include "Round.h"

//Packet-Header: 0=Neuer Turm, 1=Update, 2=Turm verkauft, 3=Drohne nimmt Schaden, 4=Round-Werte (Leben&Runde), 5=Verloren

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
	/// <param name="">Tower an welchem entwas ge‰ndert wurde</param>
	/// <param name="">Index, was ge‰ndert wurde (0 = neuer Turm, 1 = Verkaufen)</param>
	/// <returns>True, wenn es geklappt hat</returns>
	bool send(Tower*, int);

	/// <summary>
	/// Sendet ein Packet
	/// </summary>
	/// <param name="TowerID">Tower an welchem entwas ge‰ndert wurde</param>
	/// <param name="Index, was ge‰ndert wurde">1 = Update1, 2 = Update2</param>
	/// <param name="updateIndex"></param>
	/// <returns>True, wenn es geklappt hat</returns>
	bool send(int, int, int);

	/// <summary>
	/// Sendet ein Packet
	/// </summary>
	/// <param name="TowerID">Turm welcher auf eine Drohne schieﬂt</param>
	/// <param name="DroneID">Drohne auf die geschossen wird</param>
	/// <returns>True, wenn es geklappt hat</returns>
	bool send(int, int);

	/// <summary>
	/// !!FUNKTIONIERT NICHT!!
	/// Synchronisiert die Werte/Attribute, welche in Round gespeichert sind
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool send();

	/// <summary>
	/// Empf‰ngt ein Packet und wendet es an
	/// </summary>
	/// <returns>True, wenn es geklappt hat</returns>
	bool receive();
};