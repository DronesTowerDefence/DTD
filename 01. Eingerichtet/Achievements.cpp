#include "Achievements.h"
#include <fstream>

std::list<Achievement*> AchievementsContainer::allAchievements;

Achievement::Achievement(std::string _title, int _value0, int _value1, int _value2, int _id)
{
	m_unlocked = false;
	m_title = _title;
	m_value[0] = _value0;
	m_value[1] = _value1;
	m_value[2] = _value2;
	m_achievementID = _id;
}

void Achievement::setUnlocked(bool _unlocked)
{
	m_unlocked = _unlocked;
}

bool Achievement::getUnlocked()
{
	return m_unlocked;
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

int Achievement::getAchievementID()
{
	return m_achievementID;
}

void AchievementsContainer::createAchievements()
{
	std::string _title = "";
	int _value[3], _id;
	char buffer[60];
	std::ifstream file;
	file.open("saves/achievements.sav");
	if (file.fail())
		return;
	//Aufbau der Datei: id;title;value0;value1;value2;

	for (int i = 0; i < achievementCount; i++)
	{
		file.get(buffer, 60, ';');
		_id = std::stoi(buffer);
		for (int i = 0; i < 60; i++, buffer[i] = '\0');

		file.get(buffer, 60, ';');
		_title = buffer;
		for (int i = 0; i < 60; i++, buffer[i] = '\0');

		file.get(buffer, 60, ';');
		_value[0] = std::stoi(buffer);
		for (int i = 0; i < 60; i++, buffer[i] = '\0');

		file.get(buffer, 60, ';');
		_value[1] = std::stoi(buffer);
		for (int i = 0; i < 60; i++, buffer[i] = '\0');

		file.get(buffer, 60, ';');
		_value[2] = std::stoi(buffer);
		for (int i = 0; i < 60; i++, buffer[i] = '\0');

		addAchievement(new Achievement(_title, _value[0], _value[1], _value[2], _id));
	}

}

void AchievementsContainer::addAchievement(Achievement* _achievement)
{
	allAchievements.push_back(_achievement);
}

Achievement* AchievementsContainer::getAchievement(std::string _title, int _id)
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
