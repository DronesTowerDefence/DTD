#include "Achievements.h"
#include "Account.h"
#include "AccountServer.h"
#include <fstream>

std::list<Achievement*> AchievementsContainer::allAchievements;

Achievement::Achievement(std::string _title, int _value0, int _value1, int _value2, int _id)
{
	m_unlocked[0] = false;
	m_unlocked[1] = false;
	m_unlocked[2] = false;
	m_title = _title;
	m_value[0] = _value0;
	m_value[1] = _value1;
	m_value[2] = _value2;
	m_currentValue = 0;
	m_achievementID = _id;
}

void Achievement::checkAchievementValues()
{
	AccountServer* accServer = new AccountServer();
	accServer->sendAchievement(m_achievementID, m_currentValue);
	delete accServer;

	if (m_currentValue >= m_value[0] && !m_unlocked[0])
	{
		m_unlocked[0] = true;
		Account::addExperience(400);
	}
	if (m_currentValue >= m_value[1] && m_unlocked[0] && !m_unlocked[1])
	{
		m_unlocked[1] = true;
		Account::addExperience(500);
	}
	if (m_currentValue >= m_value[2] && m_unlocked[1] && !m_unlocked[2])
	{
		m_unlocked[2] = true;
		Account::addExperience(600);
	}
}

void Achievement::addToCurrentValue(int value)
{
	if (value > 0)
		m_currentValue += value;
	checkAchievementValues();
}

void Achievement::setUnlocked(int index, bool _unlocked)
{
	if (index >= 0 && index < 3)
		m_unlocked[index] = _unlocked;
}

void Achievement::setCurrentValue(int value)
{
	if (value > 0)
	{
		m_currentValue = value;
		if (m_currentValue >= m_value[0] && !m_unlocked[0])
		{
			m_unlocked[0] = true;
		}
		if (m_currentValue >= m_value[1] && m_unlocked[0] && !m_unlocked[1])
		{
			m_unlocked[1] = true;
		}
		if (m_currentValue >= m_value[2] && m_unlocked[1] && !m_unlocked[2])
		{
			m_unlocked[2] = true;
		}
	}
}

bool Achievement::getUnlocked(int index)
{
	if (index >= 0 && index < 3)
		return m_unlocked[index];
	else return false;
}

std::string Achievement::getTitle()
{
	return m_title;
}

int Achievement::getValue(int index)
{
	if (index >= 0 && index < 3)
		return m_value[index];
	else
		return 0;
}

int Achievement::getCurrentValue()
{
	return m_currentValue;
}

int Achievement::getAchievementID()
{
	return m_achievementID;
}

void AchievementsContainer::createAchievements()
{
	std::string _title = "";
	int _value[3], _id;
	char buffer[60], c;
	std::ifstream file;
	file.open("saves/achievements.sav");
	if (file.fail())
	{
		std::cout << " Fehler beim Laden der Achievements, Datei nicht gefunden.\n";
		return;
	}
	//Aufbau der Datei: id;title;value0;value1;value2;
	//# = ü | + = ö | _ = ä

	for (int i = 0; i < achievementCount; i++)
	{
		file.get(buffer, 60, ';');
		_id = std::stoi(buffer);
		for (int i = 0; i < 60; i++) buffer[i] = '\0';
		file.get(c);

		file.get(buffer, 60, ';');
		_title = buffer;
		for (int i = 0; i < _title.length(); i++)
		{
			if (_title[i] == '#')
				_title[i] = 252;
			else if (_title[i] == '+')
				_title[i] = 246;
			else if (_title[i] == '_')
				_title[i] = 228;
		}
		for (int i = 0; i < 60; i++) buffer[i] = '\0';
		file.get(c);

		file.get(buffer, 60, ';');
		_value[0] = std::stoi(buffer);
		for (int i = 0; i < 60; i++) buffer[i] = '\0';
		file.get(c);

		file.get(buffer, 60, ';');
		_value[1] = std::stoi(buffer);
		for (int i = 0; i < 60; i++) buffer[i] = '\0';
		file.get(c);

		file.get(buffer, 60, ';');
		_value[2] = std::stoi(buffer);
		for (int i = 0; i < 60; i++) buffer[i] = '\0';
		file.get(c);

		addAchievement(new Achievement(_title, _value[0], _value[1], _value[2], _id));
	}
	std::cout << allAchievements.size() << " von " << achievementCount << " Achievements geladen\n";
}

void AchievementsContainer::addAchievement(Achievement* _achievement)
{
	allAchievements.push_back(_achievement);
}

Achievement* AchievementsContainer::getAchievement(int _id, std::string _title)
{
	Achievement* returnValue = nullptr;
	for (auto i : allAchievements)
	{
		if (i->getTitle() == _title || i->getAchievementID() == _id)
		{
			returnValue = i;
			break;
		}
	}
	return returnValue;
}
