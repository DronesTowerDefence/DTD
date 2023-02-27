#pragma once
#include "Ressources.h"

#define achievementCount 13

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


class UniqueAchievement
{
private:
	static std::list<UniqueAchievement*> allUniqueAchievements;
	Achievement* p_achievement;
	int counter;
	bool towerPlaced[towerTypeCount];

public:
	UniqueAchievement(int achievementID);
	bool checkAchievement();
	void setCounter(int _counter);
	void setTowerPlaced(int index, bool b = true);
	int getCounter();
	static UniqueAchievement* getUniqueAchievement(int achievementID);
};


static class AchievementsContainer
{
private:
	static std::list<Achievement*> allAchievements;
	AchievementsContainer();

public:
	/// <summary>
	/// Ließt die Achievements aus der Datei
	/// </summary>
	static void createAchievements();

	/// <summary>
	/// Fügt ein Achievement der Liste hinzu
	/// </summary>
	/// <param name="_achievement"></param>
	static void addAchievement(Achievement* _achievement);

	/// <summary>
	/// Nicht nullpbasiert!
	/// </summary>
	/// <param name="_id"></param>
	/// <param name="_title"></param>
	/// <returns></returns>
	static Achievement* getAchievement(int _id, std::string _title = "\0");

	/// <summary>
	/// Setzt die Werte der Achievements zurück
	/// </summary>
	static void resetAllAchievements();

	/// <summary>
	/// Setzt die Werte der Achievements vom Server
	/// </summary>
	/// <returns></returns>
	static bool getAchievementsFromServer(std::string accName);
};
