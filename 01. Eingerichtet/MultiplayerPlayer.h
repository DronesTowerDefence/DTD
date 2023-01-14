#pragma once
#include "Ressources.h"

class MultiplayerPlayer
{
private:
	int m_playerID;
	std::string m_playerName;
	TcpSocket* m_sender;
	TcpSocket* m_receiver;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	MultiplayerPlayer(int);

	/// <summary>
	/// Erstellt den m_sender und m_receiver neu
	/// </summary>
	void resetSockets();

	int getPlayerID();
	std::string getPlayerName();
	TcpSocket* getSender();
	TcpSocket* getReceiver();
};

