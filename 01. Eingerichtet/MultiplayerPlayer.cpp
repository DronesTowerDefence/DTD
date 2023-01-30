#include "MultiplayerPlayer.h"

MultiplayerPlayer::MultiplayerPlayer(std::string _playerName)
{
	m_playerName = _playerName;
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

bool MultiplayerPlayer::connect(std::string ip, int port)
{
	return m_sender->connect(ip, port) == sf::Socket::Done;
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
