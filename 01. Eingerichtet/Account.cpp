#include "Account.h"
#include "AccountServer.h"
#include "PopUpMessage.h"
#include <fstream>
#include <functional>

Account* Account::m_acc = nullptr;

Account::Account()
{
	m_accName = invalidUsername;
	m_email = "0";
	m_experience = 0;
	m_shopCoins = 0;
	m_profileImage = nullptr;
}

Account::Account(std::string userName, std::string email, sf::Image* image)
{
	m_accName = userName;
	m_email = email;
	m_profileImage = new sf::Image();
	*m_profileImage = Ressources::getInstance()->getAccountProfilePicture()->copyToImage();
	m_oldExperience = 0;
	m_experience = 0;
	m_shopCoins = 0;

	if (image != nullptr)
	{
		m_profileImage = image;
	}

	if (userName != invalidUsername && email != "0")
	{
		std::ofstream file("saves/user.sav");
		file << userName << "\n" << email << "\n";
	}
}

bool Account::checkLevelUp()
{
	return ((m_acc->m_experience / experiencePerLevel) > (m_acc->m_oldExperience / experiencePerLevel));
}

Account* Account::createAcc(std::string userName, std::string email, sf::Image* image)
{
	if (m_acc != nullptr)
	{
		delete m_acc;
	}
	m_acc = new Account(userName, email, image);

	return m_acc;
}

bool Account::setExperience(int _exp, Account* acc)
{
	if (acc != nullptr && _exp > 0 && acc->m_accName != invalidUsername)
	{
		acc->m_experience = _exp;
		acc->m_oldExperience = _exp;
		return true;
	}
	else
		return false;

}

bool Account::setShopCoins(int _coins, Account* acc)
{
	if (_coins >= 0)
	{
		acc->m_shopCoins = _coins;
		return true;
	}
	else return false;
}

bool Account::addExperience(int _exp, Account* acc)
{
	if (acc != nullptr && _exp > 0 && acc->m_accName != invalidUsername)
	{
		new PopUpMessage(std::to_string(_exp) + " Erfahrung erhalten", seconds(1));
		acc->m_experience += _exp;
		if (checkLevelUp())
		{
			acc->m_shopCoins += shopCoinsPerLevel;
			new PopUpMessage(std::to_string(shopCoinsPerLevel) + " Shop-Coins erhalten!");
			AccountServer::getAccServerObj()->sendCoins(acc->m_accName, acc->m_shopCoins);
		}
		return true;
	}
	else return false;
}

Account* Account::getAcc()
{
	return m_acc;
}

bool Account::deleteAcc()
{
	if (m_acc != nullptr)
	{
		delete m_acc;
		m_acc = nullptr;
		return true;
	}
	else return false;
}

std::string Account::getAccName(Account* acc)
{
	return acc->m_accName;
}

std::string Account::getEmail(Account* acc)
{
	return acc->m_email;
}

sf::Image* Account::getProfileImage(Account* acc)
{
	return acc->m_profileImage;
}

int Account::getExperience(Account* acc)
{
	return acc->m_experience;
}

int Account::getShopCoins(Account* acc)
{
	return acc->m_shopCoins;
}
