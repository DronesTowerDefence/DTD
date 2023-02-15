#pragma once
#include "Ressources.h"

#define achievementCount 12

class Achievement
{
private:
	bool m_unlocked[3];
	std::string m_title;
	int m_value[3];
	int m_currentValue;
	int m_achievementID;
	Achievement();

public:
	Achievement(std::string _title, int _value0, int _value1, int _value2, int _id);

	/** 
	Überprüft, ob ein Achievement erreicht wurde und gibt dem Spieler XP, wenn er sie noch nicht erhalten hat.
	Wird automatisch in getCurrentValue- und addToCurrentValue- Funktionen aufgerufen
	*/
	void checkAchievementValues();

	void addToCurrentValue(int value);

	void setUnlocked(int index, bool _unlocked);
	void setCurrentValue(int value);

	bool getUnlocked(int index);
	std::string getTitle();
	int getValue(int index);
	int getCurrentValue();
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
	static Achievement* getAchievement(int _id, std::string _title = "\0");
};
