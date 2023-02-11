#include "Account.h"
#include <fstream>

Account* Account::m_acc = nullptr;

Account::Account()
{
	m_accName = "???";
	m_email = "0";
	m_profileImage = nullptr;
}

Account::Account(std::string userName, std::string email, sf::Image* image)
{
	m_accName = userName;
	m_email = email;
	m_profileImage = new sf::Image();
	*m_profileImage = Ressources::getInstance()->getAccountProfilePicture()->copyToImage();

	if (image != nullptr)
	{
		m_profileImage = image;
	}

	if (userName != "???" && email != "0")
	{
		std::ofstream file("saves/user.sav");
		file << userName << "\n" << email;
	}
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

std::string Account::getAccName()
{
	return m_acc->m_accName;
}

std::string Account::getEmail()
{
	return m_acc->m_email;
}

sf::Image* Account::getProfileImage()
{
	return m_acc->m_profileImage;
}
