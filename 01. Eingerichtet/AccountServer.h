#pragma once
#include "Account.h"

class AccountServer
{
private:
	sf::Http* http;
	sf::Http::Request* request;
	sf::Http::Response* response;
	sf::Time* timeout;
	int httpVersion[2];

public:
	AccountServer();

	/// <summary>
	/// Erstellt einen Account aus den User-Infos, welche von der sendLogin-Funktionen erhalten werden
	/// </summary>
	/// <param name="userName"></param>
	/// <returns>Pointer auf den Account wenn erfolgreich, ansonsten nullptr</returns>
	Account* createAccount(std::string userName);

	/// <summary>
	/// Sendet eine Request mit den Parametern an den HTTP-Server
	/// </summary>
	/// <param name="email"></param>
	/// <param name="passwort"></param>
	/// <returns>UserID&Username</returns>
	std::string sendLogin(std::string email, std::string passwort);

	/// <summary>
	/// Sendet eine Request mit dem Parameter an den HTTP-Server
	/// </summary>
	/// <param name="gameID"></param>
	/// <returns>HostIP</returns>
	std::string sendGameID(std::string gameID);

	/// <summary>
	/// Sendet eine Request mit dem Parameter an den HTTP-Server
	/// </summary>
	/// <param name="hostIP"></param>
	/// <returns>GameID</returns>
	std::string sendHostIP(std::string hostIP);

	/// <summary>
	/// Überprüft, ob der angegebene Benutzername existiert
	/// </summary>
	/// <param name="username"></param>
	/// <returns></returns>
	std::string checkUsername(std::string username);

};

