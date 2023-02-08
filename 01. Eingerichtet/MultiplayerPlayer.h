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

	~MultiplayerPlayer();

	/// <summary>
	/// Erstellt den m_socket neu, ohne sich zu verbinden
	/// </summary>
	void resetSockets();

	/// <summary>
	/// Erstellt den listener neu
	/// </summary>
	static void resetListener();

	void setUsername(std::string _username);

	std::string getPlayerName();
	TcpSocket* getSocket();
	static TcpListener* getListener();
};

class MultiplayerPlayer_light
{
private:
	std::string m_playerName;
public:

	MultiplayerPlayer_light();

	std::string getPlayerName();
	void setPlayerName(std::string);
};