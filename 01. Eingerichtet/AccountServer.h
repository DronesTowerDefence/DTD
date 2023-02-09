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

	/// <summary>
	/// Sendet eine Request an den HTTP-Server
	/// </summary>
	/// <returns>Response Body | "-1" wenn nicht erfolgreich</returns>
	std::string send();

public:
	AccountServer();

	~AccountServer();

	/// <summary>
	/// Erstellt einen Account aus den User-Infos, welche von der sendLogin-Funktionen erhalten werden
	/// </summary>
	/// <param name="userName">"0" = Kein Benutzer vorhanden, "-1" Keine Verbindung zum Server</param>
	/// <returns>Pointer auf den Account wenn erfolgreich, ansonsten nullptr</returns>
	Account* createAccount(std::string userName, std::string email, sf::Image* profileImage);

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
	/// <returns>GameID</returns>
	std::string sendHostIP();

	/// <summary>
	/// Sendet eine Request mit dem Benutzernamen, um das dazugeh�rige Profilbild zu bekommen
	/// </summary>
	/// <param name="username"></param>
	/// <returns>Das Profilbild als smfl Image</returns>
	sf::Image* getProfilePicture(std::string username);

	/// <summary>
	/// �berpr�ft, ob der angegebene Benutzername existiert
	/// </summary>
	/// <param name="username"></param>
	/// <returns></returns>
	std::string checkUsername(std::string username);

};

