#pragma once
#include "Ressources.h"

// Für Host (Für die Kommunikation mit anderem Spieler)
class MultiplayerPlayer
{
private:
	std::string m_playerName;
	TcpSocket* m_socket;
	Image* m_profileImage;
	static TcpListener* listener;

public:
	/// <summary>
	/// Erstellt einen Player für den Multiplayer
	/// </summary>
	MultiplayerPlayer();

	~MultiplayerPlayer();

	/// <summary>
	/// Erstellt den socket neu, ohne sich zu verbinden
	/// </summary>
	void resetSockets();

	/// <summary>
	/// Erstellt den listener neu
	/// </summary>
	static void resetListener();

	void setUsername(std::string _username);
	void setProfilImage(Image* image);

	std::string getPlayerName();
	TcpSocket* getSocket();
	Image* getProfilImage();
	static TcpListener* getListener();
	
};

// Für Client (Nur zum Anzeigen der Spieler)
class MultiplayerPlayer_light
{
private:
	std::string m_playerName;
	Image* m_profileImage;
public:

	MultiplayerPlayer_light();

	std::string getPlayerName();
	Image* getProfileImage();
	void setPlayerName(std::string);
	void setProfileImage(Image* image);
};