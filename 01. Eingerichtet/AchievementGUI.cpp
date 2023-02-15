#include "AchievementGUI.h"
#include "HomeMenu.h"
#include "PopUpMessage.h"
#include "Controls.h"

AchievementTexture::AchievementTexture(Achievement* a)
{
	achievement = a;

	background = new Sprite;
	background->setTexture(*Ressources::getInstance()->getSendMoneyBackgroundTexture());
	background->setPosition(0, 0);
	background->setScale(3, 1);

	earned = new Sprite();
	earned->setPosition(1115, 40);
	if (a->getUnlocked(2))
	{
		earned->setTexture(*Ressources::getInstance()->getAchievementEarnedYesSymbolTexture());
	}
	else
	{
		earned->setTexture(*Ressources::getInstance()->getAchievementEarnedNotSymbolTexture());
	}

	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	id = new Text();
	id->setCharacterSize(40);
	id->setFillColor(Color::White);
	id->setOutlineThickness(4);
	id->setOutlineColor(Color::Black);
	id->setFont(*font);
	id->setPosition(30, 60);
	id->setString(std::to_string(a->getAchievementID()));

	title = new Text();
	title->setCharacterSize(35);
	title->setFillColor(Color::White);
	title->setOutlineThickness(3.5);
	title->setOutlineColor(Color::Black);
	title->setFont(*font);
	title->setPosition(110, 60);
	title->setString(a->getTitle());

	progress = new Text();
	progress->setCharacterSize(30);
	progress->setFillColor(Color::White);
	progress->setOutlineThickness(3);
	progress->setOutlineColor(Color::Black);
	progress->setFont(*font);
	progress->setPosition(900, 60);

	if (!a->getUnlocked(0))
		progress->setString(std::to_string(a->getCurrentValue()) + " / " + std::to_string(a->getValue(0)));
	else if (!a->getUnlocked(1))
		progress->setString(std::to_string(a->getCurrentValue()) + " / " + std::to_string(a->getValue(1)));
	else if (!a->getUnlocked(2))
		progress->setString(std::to_string(a->getCurrentValue()) + " / " + std::to_string(a->getValue(2)));

	texture = new RenderTexture;
	texture->create(1300, 200);
	texture->draw(*background);
	texture->draw(*id);
	texture->draw(*title);
	texture->draw(*progress);
	texture->draw(*earned);
	texture->display();

	sprite = new Sprite(texture->getTexture());
}

Sprite AchievementTexture::getSprite()
{
	return *sprite;
}

Achievement* AchievementTexture::getAchievement()
{
	return achievement;
}



void AchievementGUI::draw()
{
	window->clear();
	HomeMenu::getInstance()->drawPublic();
	window->draw(*Ressources::getInstance()->getBlackBackgroundSprite());
	window->draw(*background);

	for (int i = 0; i < 5; i++)
	{
		window->draw(*drawSprites[i]);
	}

	window->draw(*closeButton);
	window->display();
}

void AchievementGUI::checkClicked(Event* event)
{
	if (!window->hasFocus())
		return;
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2f pos, pos2;
		Vector2i mouse = Mouse::getPosition();
		isClicked = false;

		//Close
		pos = Service::getInstance()->getObjectPosition(closeButton->getPosition());
		pos2 = Service::getInstance()->getObjectPosition(closeButton->getPosition() + Vector2f(closeButton->getTexture()->getSize()));
		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			isOpen = false;
			return;
		}
	}
}

void AchievementGUI::updateDrawSprites()
{
	int i = 0;
	for (auto j : allAchievementSprites)
	{
		if (j->getAchievement()->getAchievementID() >= firstIndex && i < 5)
		{
			drawSprites[i]->setTexture(*j->getSprite().getTexture());
			i++;
		}
	}
}

AchievementGUI::AchievementGUI(RenderWindow* _window)
{
	window = _window;
	isOpen = false;
	isClicked = false;
	firstIndex = 1;

	background = new Sprite();
	background->setPosition(100, 50);
	background->setTexture(*Ressources::getInstance()->getAccountLoginBackground());
	background->setScale(2.15, 1.11);

	closeButton = new Sprite();
	closeButton->setPosition(1720, 50);
	closeButton->setTexture(*Ressources::getInstance()->getButtonCloseTexture());

	for (int i = 1; i <= achievementCount; i++)
	{
		allAchievementSprites.push_back((new AchievementTexture(AchievementsContainer::getAchievement(i))));
	}

	int i = 0;
	for (auto j : allAchievementSprites)
	{
		drawSprites[i] = new Sprite(j->getSprite());
		drawSprites[i]->setPosition(350, 150 * (i + 1) - 50);
		//drawSprites[i]->setColor(Color::Red);
		i++;
		if (i == 5)
			break;
	}
}

bool AchievementGUI::openAchievementGUI()
{
	isOpen = true;

	Event event;

	while (window->isOpen() && isOpen)
	{
		Controls::checkControls();
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			checkClicked(&event);
			Controls::checkKeyboardInput(&event);
		}
		draw();

		if (Controls::getArrowUpIsPressed())
		{
			if (firstIndex > 0)
			{
				firstIndex--;
				updateDrawSprites();
			}
		}
		else if (Controls::getArrowDownIsPressed())
		{
			if (firstIndex < achievementCount - 4)
			{
				firstIndex++;
				updateDrawSprites();
			}
		}

		if (Controls::getEscIsPressed())
		{
			isOpen = false;
			Controls::checkControls();
		}

	}

	return isOpen;
}
