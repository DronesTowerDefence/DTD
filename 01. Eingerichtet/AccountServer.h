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
	int lastStatusCode;

	/// <summary>
	/// Sendet eine Request an den HTTP-Server
	/// </summary>
	/// <returns>Response Body | "-1" wenn nicht erfolgreich</returns>
	std::string send();

	static AccountServer* accountServerObject;
public:
	AccountServer();
	~AccountServer();

	static AccountServer* getAccServerObj();

	/// <summary>
	/// HTML-Statuscode (200 = OK)
	/// </summary>
	/// <returns></returns>
	int getRequestLastStatusCode();

	/// <summary>
	/// Um am Ende eines Spieles alle Achievements und XP an den Server zu senden
	/// </summary>
	/// <returns></returns>
	static bool sendAllAchievementsAndXp();

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
	/// Sendet eine Request mit dem Benutzernamen, um das dazugehörige Profilbild zu bekommen
	/// </summary>
	/// <param name="username"></param>
	/// <returns>Das Profilbild als smfl Image</returns>
	sf::Image* getProfilePicture(std::string username);

	/// <summary>
	/// Überprüft, ob der angegebene Benutzername existiert
	/// </summary>
	/// <param name="username"></param>
	/// <returns></returns>
	std::string checkUsername(std::string username);

	/// <summary>
	/// Sendet ein Achievement an den Server mit dem aktuell angemeldeten Benutzer
	/// </summary>
	/// <param name="achievementID"></param>
	/// <returns>"1" wenn erfolgreich</returns>
	std::string sendAchievement(int achievementID, int currentValue);

	/// <summary>
	/// Bekommt alle AchievemtIDs zu dem Benutzer
	/// </summary>
	/// <param name="username"></param>
	/// <returns>AchievementIDs mit '&' getrennt</returns>
	std::string getAchievement(std::string username);

	std::string sendXP(std::string username, std::string xp);

	std::string getXP(std::string username);

	std::string sendCoins(std::string username, int _coins);

	std::string getCoins(std::string username);

	std::string setShopContent(std::string username, int id);

	std::string getShopContent(std::string username);

	/// <summary>
	/// Ruft die Aktuelle Chanlage auf
	/// </summary>
	/// <returns></returns>
	std::string getChallenge();
	std::string wonChallenge(std::string unsername);

	std::string getFriends(std::string unsername);

	std::string getIncomingFriendRequests(std::string username);

};

