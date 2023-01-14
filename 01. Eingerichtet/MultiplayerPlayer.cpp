#include "MultiplayerPlayer.h"

MultiplayerPlayer::MultiplayerPlayer(int _playerID)
{
	m_playerID = _playerID;
	m_playerName = "Player" + std::to_string(m_playerID); //TODO
	m_sender = new TcpSocket();
	m_receiver = new TcpSocket();
}

void MultiplayerPlayer::resetSockets()
{
	delete m_sender;
	delete m_receiver;
	m_sender = new TcpSocket();
	m_receiver = new TcpSocket();
}

int MultiplayerPlayer::getPlayerID()
{
	return m_playerID;
}

std::string MultiplayerPlayer::getPlayerName()
{
	return m_playerName;
}

TcpSocket* MultiplayerPlayer::getSender()
{
	return m_sender;
}

TcpSocket* MultiplayerPlayer::getReceiver()
{
	return m_receiver;
}
