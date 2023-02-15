#include "Account.h"
#include "AccountServer.h"
#include "PopUpMessage.h"
#include <fstream>
#include <functional>

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
	m_experience = 0;

	if (image != nullptr)
	{
		m_profileImage = image;
	}

	if (userName != "???" && email != "0")
	{
		std::ofstream file("saves/user.sav");
		file << userName << "\n" << email << "\n";
	}
}

void Account::sendXp()
{
	Thread* thread = new Thread(std::bind(&AccountServer::sendXP, AccountServer::accountServerObject, m_acc->m_accName, std::to_string(m_acc->m_experience)));
	thread->launch();
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

bool Account::setExperience(int _exp)
{
	if (m_acc != nullptr && _exp > 0 && m_acc->m_accName != invalidUsername)
	{
		m_acc->m_experience = _exp;
		return true;
	}
	else
		return false;

}

bool Account::addExperience(int _exp)
{
	if (m_acc != nullptr && _exp > 0 && m_acc->m_accName != invalidUsername)
	{
		new PopUpMessage(std::to_string(_exp) + " Erfahrung erhalten", seconds(1));
		m_acc->m_experience += _exp;
		sendXp();
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

int Account::getExperience()
{
	return m_acc->m_experience;
}
