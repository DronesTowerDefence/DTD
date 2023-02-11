#pragma once
#include "Ressources.h"

/// <summary>
/// Eigener Account
/// </summary>
class Account
{
private:
	static Account* m_acc;
	std::string m_accName;
	std::string m_email;
	sf::Image* m_profileImage;

	Account();
	Account(std::string userName, std::string email, sf::Image* image);

public:
	static Account* createAcc(std::string userName, std::string email, sf::Image* image);
	static Account* getAcc();
	static bool deleteAcc();
	static std::string getAccName();
	static std::string getEmail();
	static sf::Image* getProfileImage();
};

