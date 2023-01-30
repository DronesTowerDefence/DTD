#pragma once
#include "Ressources.h"

class MultiplayerPlayer
{
private:
	std::string m_playerName;
	TcpSocket* m_sender;
	TcpSocket* m_receiver;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	MultiplayerPlayer(std::string);

	/// <summary>
	/// Erstellt den m_sender und m_receiver neu, ohne sich zu verbinden
	/// </summary>
	void resetSockets();

	/// <summary>
	/// Verbindet sich mit der angegebenen IP
	/// </summary>
	/// <param name="ip"></param>
	/// <param name="port"></param>
	/// <returns></returns>
	bool connect(std::string ip, int port);

	std::string getPlayerName();
	TcpSocket* getSender();
	TcpSocket* getReceiver();
};

