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

	Account();
	Account(std::string userName);

public:
	static Account* createAcc(std::string userName);
	static Account* getAcc();
	std::string getAccName();

};

