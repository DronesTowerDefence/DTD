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
	int m_oldExperience;
	int m_experience;
	int m_shopCoins;

	Account();
	Account(std::string userName, std::string email, sf::Image* image);
	static bool checkLevelUp();

public:
	static const int shopCoinsPerLevel = 800;
	static const int experiencePerLevel = 1000;
	static Account* createAcc(std::string userName = invalidUsername, std::string email = "0", sf::Image* image = nullptr);
	static bool setExperience(int _exp, Account* acc = m_acc);
	static bool setShopCoins(int _coins, Account* acc = m_acc);
	static bool addExperience(int _exp, Account* acc = m_acc);
	static Account* getAcc();
	static bool deleteAcc();
	static std::string getAccName(Account* acc = m_acc);
	static std::string getEmail(Account* acc = m_acc);
	static sf::Image* getProfileImage(Account* acc = m_acc);
	static int getExperience(Account* acc = m_acc);
	static int getShopCoins(Account* acc = m_acc);
};

