#pragma once
#include "Ressources.h"

class Credits
{
	static constexpr auto creditTextCount = 2;
	static constexpr auto pageCount = 2;

	RenderWindow* m_window;

	Clock* m_changeClock;
	Time* m_changeTime;
	Font* m_font;
	Text* m_creditText[creditTextCount];
	Sprite* m_creditsSprite;

	bool isOpen;
	int displayIndex;

	void draw();
	void checkClicked();

public:
	Credits(RenderWindow*);
	void openCredits();
};

