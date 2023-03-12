#include "Credits.h"
#include "Controls.h"

void Credits::draw()
{
	m_window->clear(Color::White);

	switch (displayIndex)
	{
	case 0:
		m_window->draw(*m_creditsSprite);

		break;

	case 1:
		for (int i = 0; i < creditTextCount; i++)
		{
			m_window->draw(*m_creditText[i]);
		}
		break;
	}

	m_window->display();
}

void Credits::checkClicked()
{
	if (Controls::getLeftMouseIsClicked() || Controls::getArrowUpIsPressed())
	{
		displayIndex++;
		if (displayIndex >= pageCount)
		{
			isOpen = false;
		}
	}
	else if (Controls::getRightMouseIsClicked() || Controls::getArrowDownIsPressed())
	{
		displayIndex--;
		if (displayIndex <= 0)
		{
			displayIndex = 0;
		}
	}
	if (Controls::getEscIsPressed())
	{
		isOpen = false;
	}
}

Credits::Credits(RenderWindow* _window)
{
	m_window = _window;
	isOpen = false;
	displayIndex = 0;

	m_font = new Font();
	m_font->loadFromFile("fonts/arial.ttf");

	m_changeClock = new Clock();
	m_changeTime = new Time(seconds(5));

	m_creditsSprite = new Sprite();
	m_creditsSprite->setTexture(*Ressources::getInstance()->getCreditsTexture());
	m_creditsSprite->setPosition(0, 0);


	for (int i = 0; i < creditTextCount; i++)
	{
		m_creditText[i] = new Text();
		m_creditText[i]->setFont(*m_font);
		m_creditText[i]->setCharacterSize(80);
		m_creditText[i]->setFillColor(Color::White);
		m_creditText[i]->setOutlineThickness(8);
		m_creditText[i]->setOutlineColor(Color::Black);
	}
	m_creditText[0]->setString("Turm-Skin-Design:\n\"DreamTheDuck\"");
	m_creditText[0]->setPosition(600, 200);
	m_creditText[1]->setString("Musik:\Louisa Schmidt");
	m_creditText[1]->setPosition(600, 600);
}

void Credits::openCredits()
{
	isOpen = true;
	Event* event = Controls::getEvent();
	while (m_window->isOpen() && isOpen)
	{
		while (m_window->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				m_window->close();
				exit(0);
			}
			Controls::checkKeyboardInput(event);
			checkClicked();
		}
		draw();

		if (m_changeClock->getElapsedTime() >= *m_changeTime)
		{
			if (displayIndex == 0)
				displayIndex++;
			else displayIndex = 0;
			m_changeClock->restart();
		}
	}
}
