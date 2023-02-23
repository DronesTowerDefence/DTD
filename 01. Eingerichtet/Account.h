#pragma once
#include "Ressources.h"

#define invalidUsername "???"

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
	int m_experience;
	int m_shopCoins;

	Account();
	Account(std::string userName, std::string email, sf::Image* image);
	static void sendXp();

public:
	static Account* createAcc(std::string userName, std::string email, sf::Image* image);
	static bool setExperience(int _exp);
	static bool setShopCoins(int _coins);
	static bool addExperience(int _exp);
	static Account* getAcc();
	static bool deleteAcc();
	static std::string getAccName();
	static std::string getEmail();
	static sf::Image* getProfileImage();
	static int getExperience();
	static int getShopCoins();
};

