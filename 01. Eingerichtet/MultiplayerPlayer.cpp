#include "MultiplayerPlayer.h"

TcpListener* MultiplayerPlayer::listener = new TcpListener();

MultiplayerPlayer::MultiplayerPlayer()
{
	m_playerName = "???";
	m_socket = new TcpSocket();
	m_profileImage = new Image(Ressources::getInstance()->getAccountProfilePicture()->copyToImage());
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

void MultiplayerPlayer::setProfilImage(Image* image)
{
	if (m_profileImage != nullptr)
	{
		delete m_profileImage;
	}
	m_profileImage = new Image(*image);
}

std::string MultiplayerPlayer::getPlayerName()
{
	return m_playerName;
}

TcpSocket* MultiplayerPlayer::getSocket()
{
	return m_socket;
}

Image* MultiplayerPlayer::getProfilImage()
{
	return m_profileImage;
}

TcpListener* MultiplayerPlayer::getListener()
{
	return listener;
}



MultiplayerPlayer_light::MultiplayerPlayer_light()
{
	m_playerName = "PlayerX";
	m_profileImage = new Image(Ressources::getInstance()->getAccountProfilePicture()->copyToImage());
}

std::string MultiplayerPlayer_light::getPlayerName()
{
	return m_playerName;
}

Image* MultiplayerPlayer_light::getProfileImage()
{
	return m_profileImage;
}

void MultiplayerPlayer_light::setPlayerName(std::string s)
{
	m_playerName = s;
}

void MultiplayerPlayer_light::setProfileImage(Image* image)
{
	if (m_profileImage != nullptr)
		delete m_profileImage;
	m_profileImage = new Image(*image);
}
