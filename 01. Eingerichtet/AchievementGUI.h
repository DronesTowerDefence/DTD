#pragma once
#include "Ressources.h"
#include "Achievements.h"

class AchievementTexture
{
private:
	Achievement* achievement;
	RenderTexture* texture;
	Sprite* background;
	Sprite* sprite;
	Sprite* earned;
	RectangleShape* milestoneProgress[3];
	Font* font;
	Text* id;
	Text* title;
	Text* progress;

public:
	/// <summary>
	/// Erstellt eine Sprite zu einem Achievement
	/// </summary>
	/// <param name=""></param>
	AchievementTexture(Achievement*);
	~AchievementTexture();

	/// <summary>
	/// Sollte nur benutzt werden um eine Kopie zu erstellen
	/// </summary>
	/// <returns>Kopie der Sprite</returns>
	Sprite getSprite();
	Achievement* getAchievement();
};

class AchievementGUI
{
private:
	std::list<AchievementTexture*> allAchievementSprites;
	Sprite* drawSprites[5];
	RenderWindow* window;

	bool isOpen;
	bool isClicked;
	int firstIndex;
	Sprite* background;
	Sprite* closeButton;

	void draw();
	void checkClicked(Event*);
	void updateDrawSprites();

public:
	AchievementGUI(RenderWindow* _window);
	~AchievementGUI();

	/// <summary>
	/// Öffnet das Achievement-Fenster
	/// </summary>
	/// <returns></returns>
	bool openAchievementGUI();
};
