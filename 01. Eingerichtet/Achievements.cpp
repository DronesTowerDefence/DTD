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
