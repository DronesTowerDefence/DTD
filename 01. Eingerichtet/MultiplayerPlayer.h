#pragma once
#include "Ressources.h"

class MultiplayerPlayer
{
private:
	std::string m_playerName;
	TcpSocket* m_socket;
	static TcpListener* listener;

public:
	/// <summary>
	/// Erstellt einen Player für den Multiplayer
	/// </summary>
	/// <param name="">playerName / userName</param>
	MultiplayerPlayer();

	/// <summary>
	/// Erstellt den m_sender und m_receiver neu, ohne sich zu verbinden
	/// </summary>
	void resetSockets();

	void setUsername(std::string _username);

	std::string getPlayerName();
	TcpSocket* getSocket();
	static TcpListener* getListener();
};

