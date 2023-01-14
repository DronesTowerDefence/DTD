#include "Account.h"

Account* Account::m_acc = nullptr;

Account::Account()
{
	m_accID = 0; //TODO
	m_accName = "0"; //TODO
}

void Account::createAcc()
{
	if (m_acc != nullptr)
	{
		delete m_acc;
	}
	m_acc = new Account();
}

Account* Account::getAcc()
{
	return m_acc;
}

int Account::getAccID()
{
	return m_accID;
}

std::string Account::getAccName()
{
	return m_accName;
}
