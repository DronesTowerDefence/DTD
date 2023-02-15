#include "AchievementGUI.h"
#include "HomeMenu.h"
#include "PopUpMessage.h"
#include "Controls.h"

AchievementSprite::AchievementSprite(Achievement* a)
{
	background = new Sprite;
	background->setTexture(*Ressources::getInstance()->getSendMoneyBackgroundTexture());
	background->setPosition(0, 0);
	background->setScale(3, 1);

	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	id = new Text();
	id->setCharacterSize(40);
	id->setFillColor(Color::White);
	id->setOutlineThickness(4);
	id->setOutlineColor(Color::Black);
	id->setFont(*font);
	id->setPosition(30, 50);
	id->setString(std::to_string(a->getAchievementID()));

	title = new Text();
	title->setCharacterSize(40);
	title->setFillColor(Color::White);
	title->setOutlineThickness(4);
	title->setOutlineColor(Color::Black);
	title->setFont(*font);
	title->setPosition(110, 50);
	title->setString(a->getTitle());

	progress = new Text();
	progress->setCharacterSize(30);
	progress->setFillColor(Color::White);
	progress->setOutlineThickness(3);
	progress->setOutlineColor(Color::Black);
	progress->setFont(*font);
	progress->setPosition(850, 50);
	progress->setString("100000 / 100000");

	earned = new Text();
	earned->setCharacterSize(30);
	earned->setFillColor(Color::White);
	earned->setOutlineThickness(3);
	earned->setOutlineColor(Color::Black);
	earned->setFont(*font);
	earned->setPosition(1150, 50);
	earned->setString(std::to_string(a->getUnlocked()));

	texture = new RenderTexture;
	texture->create(1200, 200);
	texture->draw(*background);
	texture->draw(*id);
	texture->draw(*title);
	texture->draw(*progress);
	texture->draw(*earned);
	texture->display();

	sprite = new Sprite();
	sprite->setTexture(texture->getTexture());
	sprite->setPosition(350, 150 * a->getAchievementID() - 70);
}

Sprite* AchievementSprite::getDrawSprite()
{
	return sprite;
}


void AchievementGUI::draw()
{
	window->clear();
	HomeMenu::getInstance()->drawPublic();
	window->draw(*Ressources::getInstance()->getBlackBackgroundSprite());
	window->draw(*background);

	/*int j = 0;
	for (auto i : allAchievementSprites)
	{
		if (j >= firstDisplayedEntry)
			window->draw(*i);
		j++;
	}*/

	for (auto i : drawSprites)
	{
		window->draw(*i);
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

AchievementGUI::AchievementGUI(RenderWindow* _window)
{
	window = _window;
	isOpen = false;
	isClicked = false;
	firstDisplayedEntry = 0;

	background = new Sprite();
	background->setPosition(100, 50);
	background->setTexture(*Ressources::getInstance()->getAccountLoginBackground());
	background->setScale(2.15, 1.11);

	closeButton = new Sprite();
	closeButton->setPosition(1720, 50);
	closeButton->setTexture(*Ressources::getInstance()->getButtonCloseTexture());

	for (int i = 1; i <= achievementCount; i++)
	{
		allAchievementSprites.push_back((new AchievementSprite(AchievementsContainer::getAchievement(i)))->getDrawSprite());
	}

	int i = 0;
	for (auto j : allAchievementSprites)
	{
		drawSprites.push_back(j);
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
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			checkClicked(&event);
			Controls::checkControls();
			Controls::checkKeyboardInput(&event);
		}
		draw();

		if (Controls::getArrowUpIsPressed())
		{
			firstDisplayedEntry--;
			drawSprites.pop_back();
			drawSprites.push_front(nullptr); //TODO
		}
		else if (Controls::getArrowDownIsPressed())
		{
			firstDisplayedEntry++;
			drawSprites.pop_front();
			drawSprites.push_back(nullptr); //TODO
		}

	}

	return isOpen;
}
