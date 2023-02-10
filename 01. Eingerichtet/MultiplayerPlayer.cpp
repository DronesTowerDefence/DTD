#include "MultiplayerPlayer.h"

TcpListener* MultiplayerPlayer::listener = new TcpListener();

MultiplayerPlayer::MultiplayerPlayer()
{
	m_playerName = "???";
	m_socket = new TcpSocket();
}

MultiplayerPlayer::~MultiplayerPlayer()
{
	delete m_socket;
}

void MultiplayerPlayer::resetSockets()
{
	if (m_socket != nullptr)
	{
		delete m_socket;
		m_socket = new TcpSocket();
	}
}

void MultiplayerPlayer::resetListener()
{
	delete listener;
	listener = new TcpListener();
}

void MultiplayerPlayer::setUsername(std::string _username)
{
	m_playerName = _username;
}

std::string MultiplayerPlayer::getPlayerName()
{
	return m_playerName;
}

TcpSocket* MultiplayerPlayer::getSocket()
{
	return m_socket;
}

TcpListener* MultiplayerPlayer::getListener()
{
	return listener;
}

MultiplayerPlayer_light::MultiplayerPlayer_light()
{
	m_playerName = "P";
}

std::string MultiplayerPlayer_light::getPlayerName()
{
	return m_playerName;
}

void MultiplayerPlayer_light::setPlayerName(std::string s)
{
	m_playerName = s;
}
