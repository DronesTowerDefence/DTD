#pragma once
#include "Ressources.h"

class Achievement
{
private:
	bool m_unlocked;
	std::string m_title;
	int m_value[3];
	int m_achievementID;
	Achievement();

public:
	Achievement(std::string _title, int _value0, int _value1, int _value2, int _id);

	void setUnlocked(bool _unlocked);

	bool getUnlocked();
	std::string getTitle();
	int getValue(int index);
	int getAchievementID();
};

static class AchievementsContainer
{
private:
	static std::list<Achievement*> allAchievements;
	AchievementsContainer();

public:
	static void createAchievements();
	static void addAchievement(Achievement* _achievement);
	static Achievement* getAchievement(std::string _title = "\0", int _id = -1);
};
