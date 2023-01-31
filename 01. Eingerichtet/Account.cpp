#include "Account.h"
#include <fstream>

Account* Account::m_acc = nullptr;

Account::Account()
{
	m_accName = "???";
}

Account::Account(std::string userName)
{
	m_accName = userName;

	if (userName != "???")
	{
		std::ofstream file("saves/user.sav");
		file << userName;
	}
}

Account* Account::createAcc(std::string userName)
{
	if (m_acc != nullptr)
	{
		delete m_acc;
	}
	m_acc = new Account(userName);

	return m_acc;
}

Account* Account::getAcc()
{
	return m_acc;
}

std::string Account::getAccName()
{
	return m_accName;
}
