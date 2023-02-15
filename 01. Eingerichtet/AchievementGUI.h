#pragma once
#include "Ressources.h"
#include "Achievements.h"

class AchievementSprite
{
private:
	RenderTexture* texture;
	Sprite* sprite;
	Sprite* background;
	Font* font;
	Text* id;
	Text* title;
	Text* progress;
	Text* earned;

public:
	/// <summary>
	/// Erstellt eine Sprite zu einem Achievement
	/// </summary>
	/// <param name=""></param>
	AchievementSprite(Achievement*);
	Sprite* getDrawSprite();
};

class AchievementGUI
{
private:
	std::list<Sprite*> allAchievementSprites;
	std::list<Sprite*> drawSprites;
	RenderWindow* window;

	bool isOpen;
	bool isClicked;
	int firstDisplayedEntry;
	Sprite* background;
	Sprite* closeButton;

	void draw();
	void checkClicked(Event*);

public:
	AchievementGUI(RenderWindow* _window);
	bool openAchievementGUI();
};
