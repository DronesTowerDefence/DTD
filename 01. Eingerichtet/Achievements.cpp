#include "Achievements.h"
#include "Account.h"
#include "AccountServer.h"
#include "Round.h"
#include <fstream>

std::list<Achievement*> AchievementsContainer::allAchievements;
std::list<UniqueAchievement*> UniqueAchievement::allUniqueAchievements;

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
	/*AccountServer* accServer = new AccountServer();
	accServer->sendAchievement(m_achievementID, m_currentValue);
	delete accServer;*/

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
	if (value >= 0)
	{
		m_currentValue = value;
		if (m_currentValue >= m_value[0] && !m_unlocked[0])
		{
			m_unlocked[0] = true;
		}
		else m_unlocked[0] = false;

		if (m_currentValue >= m_value[1] && m_unlocked[0] && !m_unlocked[1])
		{
			m_unlocked[1] = true;
		}
		else m_unlocked[1] = false;

		if (m_currentValue >= m_value[2] && m_unlocked[1] && !m_unlocked[2])
		{
			m_unlocked[2] = true;
		}
		else m_unlocked[2] = false;

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


UniqueAchievement::UniqueAchievement(int achievementID)
{
	allUniqueAchievements.push_back(this);
	p_achievement = AchievementsContainer::getAchievement(achievementID);
	counter = 0;
	for (int i = 0; i < towerTypeCount; i++)
	{
		towerPlaced[i] = false;
	}
}

bool UniqueAchievement::checkAchievement()
{
	if (p_achievement->getAchievementID() == 11)
	{
		//Jede Turmart
		int j = 0;
		for (int i = 0; i < towerTypeCount; i++)
		{
			if (towerPlaced[i])
				j++;
		}

		if (j == towerTypeCount)
			return true;
		else
			return false;
	}
	else if (p_achievement->getAchievementID() == 12)
	{
		//Nur eine Turmart
		int j = 0;
		for (int i = 0; i < towerTypeCount; i++)
		{
			if (towerPlaced[i])
				j++;
		}

		if (j == 1)
			return true;
		else
			return false;
	}
	else return false;
}

void UniqueAchievement::setCounter(int _counter)
{
	counter = _counter;
}

int UniqueAchievement::getCounter()
{
	return counter;
}

UniqueAchievement* UniqueAchievement::getUniqueAchievement(int achievementID)
{
	UniqueAchievement* uA = nullptr;
	for (auto i : allUniqueAchievements)
	{
		if (i->p_achievement->getAchievementID() == achievementID)
		{
			uA = i;
			break;
		}
	}
	return uA;
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

void AchievementsContainer::resetAllAchievements()
{
	for (int i = 1; i <= achievementCount; i++)
	{
		getAchievement(i)->setCurrentValue(0);
	}
}

bool AchievementsContainer::getAchievementsFromServer(std::string accName)
{
	resetAllAchievements();

	AccountServer* accServer = new AccountServer();
	std::string allAchievementValues = accServer->getAchievement(accName);
	delete accServer;

	if (allAchievementValues != "0" && allAchievementValues != "-1")
	{
		int currentValue = 0, achievementID = 0, pos1 = 0, pos2 = 0, pos3 = 0;
		std::string str = "";
		Achievement* achievement = nullptr;

		while (pos3 < allAchievementValues.length())
		{
			pos1 = allAchievementValues.find('_', pos3);
			pos2 = allAchievementValues.find('&', pos3);
			str = allAchievementValues.substr(pos3, pos1 - pos3);
			achievementID = std::stoi(str);
			str = ""; pos1 = 0; pos2 = 0;

			pos1 = allAchievementValues.find('_', pos3);
			pos2 = allAchievementValues.find('&', pos3);
			str = allAchievementValues.substr(pos1 + 1, pos2 - pos1 - 1);
			currentValue = std::stoi(str);

			pos3 = pos2 + 1;

			achievement = AchievementsContainer::getAchievement(achievementID);
			if (achievement != nullptr)
			{
				achievement->setCurrentValue(currentValue);
			}
			str = ""; pos1 = 0; pos2 = 0; achievementID = 0; currentValue = 0;
		}

		return true;
	}
	return false;
}
