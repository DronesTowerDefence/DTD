#pragma once
#include "Ressources.h"

/// <summary>
/// Eigener Account
/// </summary>
class Account
{
private:
	static Account* m_acc;
	int m_accID;
	std::string m_accName;

	Account();

public:
	static void createAcc();
	static Account* getAcc();
	int getAccID();
	std::string getAccName();

};

